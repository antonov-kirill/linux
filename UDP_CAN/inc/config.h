#ifndef  __CONFIG_H__
#define __CONFIG_H__

class Interface
{
public:
	int id;
	char* CAN_Name;
	char* IP_OUT;
	char* PORT_IN;
	char* PORT_OUT;
	int sin;
	int sout;
	pthread_t thread;

	Interface()
	{
		id = 0;
		CAN_Name = (char*)"";
		IP_OUT = (char*)"";
		PORT_IN = (char*)"";
		PORT_OUT = (char*)"";
		sin = -1;
		sout = -1;
	}

	Interface(int i, char* name, char* ip, char* in, char* out)
	{
		id = i;
		CAN_Name = name;
		IP_OUT = ip;
		PORT_IN = in;
		PORT_OUT = out;
		sin = -1;
		sout = -1;
	}

	void CopyFrom(Interface i)
	{
		id = i.id;
		CAN_Name = i.CAN_Name;
		IP_OUT = i.IP_OUT;
		PORT_IN = i.PORT_IN;
		PORT_OUT = i.PORT_OUT;
		sin = i.sin;
		sout = i.sout;
		thread = i.thread;
	}
};

#ifdef __CONFIG_MAIN_H__

void GetCongiguration(char* path, std::list<Interface*> &interfaces);
bool ReadConfigFile(char* path, std::list<Interface*> &interfaces);

#else

extern void GetCongiguration(char* path, std::list<Interface*> &interfaces);

#endif // __CONFIG_MAIN_H__


#endif // ! __CONFIG_H__

