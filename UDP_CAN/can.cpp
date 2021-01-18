#include "stdio.h"
#include "string.h"
#include <list>
#include <pthread.h>
#include <mutex>
#include <unistd.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <chrono>

#include "config.h"

#define __CAN_MAIN_H__
#include "can.h"

struct timeval can_tout;
std::timed_mutex sout_mutex;
std::timed_mutex* scan_mutex;

bool CAN_CreateSocket(Interface* i)
{
	/* Create a socket */
	int scan = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (scan >= 0)
	{
		struct sockaddr_can addr;
		struct ifreq ifr;

		strcpy(ifr.ifr_name, i->CAN_Name);
		ioctl(scan, SIOCGIFINDEX, &ifr);

		addr.can_family = AF_CAN;
		addr.can_ifindex = ifr.ifr_ifindex;

		int opt = 0;
		if (i->CAN_FD)
		{
			int opt_val = 1;
			opt = setsockopt(scan, SOL_CAN_RAW, CAN_RAW_FD_FRAMES, &opt_val, sizeof(opt_val));
		}

		/* Set can name for the created socket */
		if (bind(scan, (struct sockaddr*)&addr, sizeof(addr)) >= 0)
		{		
			/* Set timeout for non-blocking reading from the socket */
			can_tout.tv_sec = 0;
			can_tout.tv_usec = 1000;

			/* Save id of the socket */
			i->scan = scan;
			return true;
		}
	}

	printf("Interface %i: Failed to create a CAN socket\n", i->id);
	return false;
}

void* CAN_ThreadFunction(void* arg)
{
	/* Copy the interface descriptor */
	Interface i;
	i.CopyFrom(*(Interface*)arg);

	while (true)
	{
		int size = 0;

		/* Check which CAN version the interface uses */
		if (i.CAN_FD)
			size = CANFD_ReceiveFrame(i);
		else
			size = CAN_ReceiveFrame(i);

		if (size > 0)
		{
			/* Synchronized access to the UDP output sockets to have a possibility to use the same output ip address and port in several interfaces */
			if (sout_mutex.try_lock_for(std::chrono::milliseconds(1000)))
			{
				/* If got a CAN frame send into a corresponding UDP output socket */
				if (send(i.sout, i.buf_tx, size, 0) < 0)
					printf("Inerface %i: Failed to send a UDP frame\n", i.id);
				sout_mutex.unlock();
			}
		}

		/* A cancellation point to stop the thread correctly */
		pthread_testcancel();
	}
}

int CAN_ReceiveFrame(Interface i)
{
	/* Check first if there is some data in the socket to not block the thread */
	if (CAN_CheckSocket(i))
	{
		struct can_frame frame;

		int size = 0;
		/* Synchronized access to the CAN socket. The same socket is using for sending and reading data in different threads */
		if (scan_mutex[i.id - 1].try_lock_for(std::chrono::milliseconds(1000)))
		{
			/* Read from the CAN socket(i->scan) and save into the 'frame' buffer */
			size = read(i.scan, &frame, sizeof(struct can_frame));
			scan_mutex[i.id - 1].unlock();
		}

		if (size > 0)
		{
			/* Prepare received data to send into a UDP socket */
			memcpy((void*)&i.buf_tx[0], (void*)&frame.can_id, sizeof(canid_t));
			for (int j = 0; j < frame.can_dlc; j++)
				i.buf_tx[j + sizeof(canid_t)] = frame.data[j];

			/* Return size of received data */
			return frame.can_dlc + sizeof(canid_t);
		}
	}
	return 0;
}

int CANFD_ReceiveFrame(Interface i)
{
	/* Check first if there is some data in the socket to not block the thread */
	if (CAN_CheckSocket(i))
	{
		struct canfd_frame frame;

		int size = 0;
		/* Synchronized access to the CAN socket. The same socket is using for sending and reading data in different threads */
		if (scan_mutex[i.id - 1].try_lock_for(std::chrono::milliseconds(1000)))
		{
			/* Read from the CAN socket(i->scan) and save into the 'frame' buffer */
			size = read(i.scan, &frame, sizeof(struct canfd_frame));
			scan_mutex[i.id - 1].unlock();
		}

		if (size > 0)
		{
			/* Prepare received data to send into a UDP socket */
			memcpy((void*)&i.buf_tx[0], (void*)&frame.can_id, sizeof(canid_t));
			for (int j = 0; j < frame.len - 1; j++)
				i.buf_tx[j + sizeof(canid_t)] = frame.data[j];

			/* Return size of received data */
			return frame.len - 1 + sizeof(canid_t);
		}
	}
	return 0;
}

bool CAN_CheckSocket(Interface i)
{
	fd_set set;
	FD_ZERO(&set);
	FD_SET(i.scan, &set);

	/* Get size of data in the socket at the moment */
	int rv = select(i.scan + 1, &set, NULL, NULL, &can_tout);
	if (rv > 0)
		return true;
	return false;
}

void CAN_SendFrame(Interface* i, int size)
{
	/* Prepare data to send into the CAN socket */
	struct can_frame frame;
	frame.can_id = i->CAN_ID;
	frame.can_dlc = (unsigned char)size;
	for (int j = 0; j < size; j++)
		frame.data[j] = i->buf_rx[j];

	int nbytes = 0;
	/* Synchronized access to the CAN socket. The same socket is using for sending and reading data in different threads */
	if (scan_mutex[i->id - 1].try_lock_for(std::chrono::milliseconds(1000)))
	{
		nbytes = write(i->scan, &frame, sizeof(struct can_frame));
		scan_mutex[i->id - 1].unlock();
	}

	if (nbytes < 0)
		printf("Interface %i: Failed to send a CAN frame\n", i->id);
}

void CANFD_SendFrame(Interface* i, int size)
{
	/* Prepare data to send into the CAN socket */
	struct canfd_frame frame;
	frame.can_id = i->CAN_ID;
	frame.len = (unsigned char)size;
	for (int j = 0; j < size; j++)
		frame.data[j] = i->buf_rx[j];

	int nbytes = 0;
	/* Synchronized access to the CAN socket. The same socket is using for sending and reading data in different threads */
	if (scan_mutex[i->id - 1].try_lock_for(std::chrono::milliseconds(1000)))
	{
		nbytes = write(i->scan, &frame, sizeof(struct canfd_frame));
		scan_mutex[i->id - 1].unlock();
	}

	if (nbytes < 0)
		printf("Interface %i: Failed to send a CAN frame\n", i->id);
}