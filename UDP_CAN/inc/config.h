#ifndef  __CONFIG_H__
#define __CONFIG_H__

class Interface
{
public:
	char* CAN_Name;
	char* UDP_IN;
	char* UDP_OUT;

	Interface()
	{
		CAN_Name = (char*)"";
		UDP_IN = (char*)"";
		UDP_OUT = (char*)"";
	}

	Interface(char* name, char* in, char* out)
	{
		CAN_Name = name;
		UDP_IN = in;
		UDP_OUT = out;
	}
};

#ifdef __CONFIG_MAIN_H__

void GetCongiguration(char* path, list<Interface> &interfaces);
bool ReadConfigFile(char* path, list<Interface> &interfaces);

#else

extern void GetCongiguration(char* path, list<Interface> &interfaces);

#endif // __CONFIG_MAIN_H__


#endif // ! __CONFIG_H__

