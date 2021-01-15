#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <list>

using namespace std;

#include "config.h"
#include "tfunc.h"

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

	while (true)
	{
		if (kbhit())
		{
			char ch = getch();
			if ((ch == 'Q') || (ch == 'q'))
			{
				printf("Exit\n");
				break;
			}
		}
	}
	exit(0);
}









