#include "stdio.h"
#include "stdlib.h"
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "config.h"

#define __UDP_MAIN_H__
#include "udp.h"

struct timeval udp_tout;

bool UDP_CreateInputSocket(Interface* i)
{
	/* Create a socket */
	int sin = socket(AF_INET, SOCK_DGRAM, 0);
	if (sin >= 0)
	{
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons((uint16_t)atoi(i->PORT_IN));
		addr.sin_addr.s_addr = htonl(INADDR_ANY);

		/* Set ip address and port number for the created socket */
		if (bind(sin, (struct sockaddr*)&addr, sizeof(addr)) >= 0)
		{
			/* Set timeout for non-blocking reading from the socket */
			udp_tout.tv_sec = 0;
			udp_tout.tv_usec = 1000;

			/* Save id of the socket */
			i->sin = sin;
			return true;
		}
	}

	printf("Interface %i: Failed to create a UDP input socket\n", i->id);
	return false;
}

bool UDP_CreateOutputSocket(Interface* i)
{
	/* Create a socket */
	int sout = socket(AF_INET, SOCK_DGRAM, 0);
	if (sout >= 0)
	{
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons((uint16_t)atoi(i->PORT_OUT));
		unsigned long ip;
		inet_pton(AF_INET, i->IP_OUT, &ip);
		addr.sin_addr.s_addr = ip;

		/* Set ip address and port number for the created socket */
		connect(sout, (struct sockaddr*)&addr, sizeof(addr));

		/* Save id of the socket */
		i->sout = sout;
		return true;
	}

	printf("Interface %i: Failed to create a UDP output socket\n", i->id);
	return false;
}

int UDP_ReceiveFrame(Interface* i)
{
	/* Check first if there is some data in the socket to not block the thread */
	if (UDP_CheckSocket(i))
	{
		/* Read from the UDP input socket (i->sin) and save into the i->buf_rx buffer */
		int size = recvfrom(i->sin, i->buf_rx, i->buf_rx_size, 0, NULL, NULL);
		if (size > 0)
		{
			/* Return size of received data */
			return size;
		}
	}
	return 0;
}

bool UDP_CheckSocket(Interface* i)
{
	fd_set set;
	FD_ZERO(&set);
	FD_SET(i->sin, &set);

	/* Get size of data in the socket at the moment */
	int rv = select(i->sin + 1, &set, NULL, NULL, &udp_tout);
	if (rv > 0)
		return true;
	return false;
}
