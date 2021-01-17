#ifndef  __CONFIG_H__
#define __CONFIG_H__

class Interface
{
public:
	const int buf_rx_size = 64;
	const int buf_tx_size = 64;

	int id;

	char* CAN_Name;
	char* IP_OUT;
	char* PORT_IN;
	char* PORT_OUT;

	int sin;
	int sout;
	pthread_t thread;

	unsigned char* buf_rx;
	unsigned char* buf_tx;

	Interface()
	{
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
		buf_rx = new unsigned char[buf_rx_size];
		buf_tx = new unsigned char[buf_tx_size];
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
		buf_rx = i.buf_rx;
		buf_tx = i.buf_tx;
	}
};

#ifdef __CONFIG_MAIN_H__

void GetCongiguration(char* path, std::list<Interface*> &interfaces);
bool ReadConfigFile(char* path, std::list<Interface*> &interfaces);

#else

extern void GetCongiguration(char* path, std::list<Interface*> &interfaces);

#endif // __CONFIG_MAIN_H__


#endif // ! __CONFIG_H__

