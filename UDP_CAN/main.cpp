#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <list>

using namespace std;

#include "config.h"





#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>


int kbhit(void)
{
	static const int STDIN = 0;
	static bool initialized = false;

	if (!initialized) 
	{
		struct termios term;
		tcgetattr(STDIN, &term);
		term.c_lflag &= ~ICANON;
		tcsetattr(STDIN, TCSANOW, &term);
		setbuf(stdin, NULL);
		initialized = true;
	}

	int bytesWaiting;
	ioctl(STDIN, FIONREAD, &bytesWaiting);
	return bytesWaiting;
}

int getch()
{
	struct termios oldt, newt;
	int ch;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
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

	while (true)
	{
		if (kbhit())
		{
			char ch = getch();

			printf("char: %c\n", ch);

			if ((ch == 'Q') || (ch == 'q'))
			{
				printf("Exit\n");
			}
		}
	}
	return 0;
}









