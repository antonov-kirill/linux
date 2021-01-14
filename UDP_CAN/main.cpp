#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <list>

using namespace std;

#include "config.h"

int main(int argc, char* argv[])
{
	char* path = (char*)"config.xml";
	char* dest_ip = (char*)"";

	int ptr = 0;
	while (ptr < argc)
	{
		if (strcmp(argv[ptr], "--path") == 0)
			path = argv[++ptr];
		ptr++;
	}

	list<Interface> interfaces;
	GetCongiguration(path, dest_ip,	interfaces);

	getchar();
	return 0;
}









