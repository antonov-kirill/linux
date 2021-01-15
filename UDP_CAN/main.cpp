#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <list>
#include <pthread.h>

using namespace std;

#include "config.h"
#include "tfunc.h"

void * ThreadFunction(void * arg)
{
	while (true)
	{
		printf("Thread\n");
	}
}

int main(int argc, char* argv[])
{
	char* path = (char*)"config.xml";
	int ptr = 0;
	while (ptr < argc)
	{
		if (strcmp(argv[ptr], "--path") == 0)
			path = argv[++ptr];
		ptr++;
	}

	char* dest_ip = (char*)"";
	list<Interface> interfaces;
	GetCongiguration(path, dest_ip,	interfaces);

	pthread_t thread;
	pthread_create(&thread, NULL, ThreadFunction, NULL);

	printf("Start converting. Press 'q' to exit\n");
	while (true)
	{
		printf("MainThread\n");

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
	exit(0);
}









