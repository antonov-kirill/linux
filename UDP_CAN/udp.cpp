#include "stdlib.h"
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "config.h"

#define __UDP_MAIN_H__
#include "udp.h"

bool CreateInputSocket(Interface* i)
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

bool CreateOutputSocket(Interface* i)
{
	int sout = socket(AF_INET, SOCK_DGRAM, 0);
	if (sout >= 0)
	{
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(atoi(i->PORT_OUT));
		addr.sin_addr.s_addr = htonl(atoi(i->IP_OUT));

		connect(sout, (struct sockaddr*)&addr, sizeof(addr));
		i->sout = sout;
		return true;
	}

	return false;
}