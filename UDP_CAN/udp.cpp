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

bool UDP_CreateInputSocket(Interface* i)
{
	int sin = socket(AF_INET, SOCK_DGRAM, 0);
	if (sin >= 0)
	{
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(atoi(i->PORT_IN));
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		if (bind(sin, (struct sockaddr*)&addr, sizeof(addr)) >= 0)
		{
			i->sin = sin;
			return true;
		}
	}

	return false;
}

bool UDP_CreateOutputSocket(Interface* i)
{
	int sout = socket(AF_INET, SOCK_DGRAM, 0);
	if (sout >= 0)
	{
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(atoi(i->PORT_OUT));
		unsigned long ip;
		inet_pton(AF_INET, i->IP_OUT, &ip);
		addr.sin_addr.s_addr = ip;

		connect(sout, (struct sockaddr*)&addr, sizeof(addr));
		i->sout = sout;
		return true;
	}

	return false;
}

void UDP_ReceiveMessage(Interface* i)
{
	if (CheckSocket(i))
	{
		int bytes = recvfrom(i->sin, i->buf_rx, i->buf_rx_size, 0, NULL, NULL);
		if (bytes > 0)
		{
			printf("Interface %i: A message has been received\n", i->id);
		}
	}
}

bool CheckSocket(Interface* i)
{
	fd_set set;
	FD_ZERO(&set);
	FD_SET(i->sin, &set);

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 10000;

	int rv = select(i->sin + 1, &set, NULL, NULL, &timeout);
	if (rv > 0)
		return true;
	return false;
}
