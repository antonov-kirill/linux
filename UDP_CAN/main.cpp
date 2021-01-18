#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <list>
#include <pthread.h>
#include <mutex>
#include <unistd.h>

#include "config.h"
#include "tfunc.h"
#include "can.h"
#include "udp.h"

int main(int argc, char* argv[])
{
	char* path = (char*)"config.xml";

	/* Read command line arguments */
	int ptr = 0;
	while (ptr < argc)
	{
		/* A path to config.xml */
		if (strcmp(argv[ptr], "--path") == 0)
			path = argv[++ptr];
		ptr++;
	}

	/* Read the configuration file (config.xml) and fill the list of interface descriptors */
	std::list<Interface*> interfaces;
	GetCongiguration(path, interfaces);

	if (interfaces.size() > 0)
	{
		/* Create array of mutexes for shared access to CAN sockets from main thread and CAN threads */
		scan_mutex = new std::timed_mutex[interfaces.size()];

		for (auto i : interfaces)
		{
			/* Create sockets */
			if (UDP_CreateInputSocket(i) && UDP_CreateOutputSocket(i) && CAN_CreateSocket(i))
			{
				/* Create threads */
				if (!pthread_create(&(i->thread), NULL, CAN_ThreadFunction, i))
				{
					/* Stop the main thread for a second to each created thread could copy an interface descriptor */
					sleep(1);
					printf("Interface %i [%s -> %s:%s]: Started working\n", i->id, i->CAN_Name, i->IP_OUT, i->PORT_OUT);
				}
				else
					printf("Interface %i: Failed to create a thread\n", i->id);
			}
			else
				printf("Interface %i: Failed to create sockets\n", i->id);
		}
	}
	else
		printf("The list of interface descriptors is empty\n");

	printf("Start converting. Press 'q' to exit\n");
	while (true)
	{
		/* Read from UDP input sockets */
		for (auto i : interfaces)
		{
			if (i->sin != -1 && i->scan != -1)
			{
				int size = UDP_ReceiveFrame(i);

				/* If got a UDP frame send it into a corresponding CAN socket */
				if (size > 0)
				{
					/* Check which CAN version the interface uses */
					if (i->CAN_FD)
						CANFD_SendFrame(i, size);
					else
						CAN_SendFrame(i, size);
				}
			}
		}

		/* Non-blocking console input */
		if (kbhit())
		{
			char ch = (char)getch();
			if ((ch == 'Q') || (ch == 'q'))
			{
				printf("Exit\n");
				break;
			}
		}
	}

	/* Stop threads, close sockets, free memory */
	while (interfaces.size() > 0)
	{
		Interface* i = interfaces.front();

		pthread_cancel(i->thread);
		pthread_join(i->thread, NULL);

		delete i->buf_rx;
		delete i->buf_tx;
		delete i;
		interfaces.pop_front();
	}
	delete[] scan_mutex;

	exit(0);
}









