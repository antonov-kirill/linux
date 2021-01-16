#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <list>
#include <pthread.h>
#include <unistd.h>

#include "config.h"
#include "tfunc.h"
#include "can.h"
#include "udp.h"

int main(int argc, char* argv[])
{
	char* path = (char*)"config.xml";

	// Read command line arguments
	int ptr = 0;
	while (ptr < argc)
	{
		if (strcmp(argv[ptr], "--path") == 0)
			path = argv[++ptr];
		ptr++;
	}

	// Read the configuration file (config.xml)
	std::list<Interface*> interfaces;
	GetCongiguration(path, interfaces);

	// Create threads, sockets
	if (interfaces.size() > 0)
	{
		for (auto i : interfaces)
		{
			if (CreateInputSocket(i) && CreateOutputSocket(i))
			{
				if (!pthread_create(&(i->thread), NULL, CAN_ThreadFunction, i))
					printf("Thread of the interface [%s -> %s:%s] was created\n", i->CAN_Name, i->IP_OUT, i->PORT_OUT);
			}
		}
	}
	else
		printf("Interfaces list is empty\n");

	printf("Start converting. Press 'q' to exit\n");
	while (true)
	{


		// Nonblocking console input
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

	// Stop threads, close sockets, objects destruction
	while (interfaces.size() > 0)
	{
		Interface* i = interfaces.front();

		pthread_cancel(i->thread);
		pthread_join(i->thread, NULL);

		delete i;
		interfaces.pop_front();
	}

	exit(0);
}









