#include <list>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>

#include "config.h"

#define __CAN_MAIN_H__
#include "can.h"

char msg[] = "Hello there!\n";

void* CAN_ThreadFunction(void* arg)
{
	Interface i;
	i.CopyFrom(*(Interface*)arg);

	while (true)
	{
		send(i.sout, msg, sizeof(msg), 0);
		sleep(1);

		pthread_testcancel();
	}
}