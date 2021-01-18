#ifndef  __CONFIG_H__
#define __CONFIG_H__

class Interface
{
public:
	int id;

	char* CAN_Name;
	int CAN_ID;
	bool CAN_FD;

	char* IP_OUT;
	char* PORT_IN;
	char* PORT_OUT;

	int sin;
	int sout;
	int scan;
	pthread_t thread;

	int buf_rx_size = 8;
	int buf_tx_size = 8 + 4;
	unsigned char* buf_rx;
	unsigned char* buf_tx;

	Interface()
	{
	}

	Interface(int i, char* name, int can_id, bool can_fd, char* ip, char* in, char* out)
	{
		id = i;
		CAN_Name = name;
		CAN_ID = can_id;
		CAN_FD = can_fd;
		IP_OUT = ip;
		PORT_IN = in;
		PORT_OUT = out;
		sin = -1;
		sout = -1;
		scan = -1;

		if (can_fd)
		{
			buf_rx_size = 64;
			buf_tx_size = 64 + 4;
		}
		buf_rx = new unsigned char[buf_rx_size];
		buf_tx = new unsigned char[buf_tx_size];
	}

	void CopyFrom(Interface i)
	{
		id = i.id;
		CAN_Name = i.CAN_Name;
		CAN_ID = i.CAN_ID;
		CAN_FD = i.CAN_FD;
		IP_OUT = i.IP_OUT;
		PORT_IN = i.PORT_IN;
		PORT_OUT = i.PORT_OUT;
		sin = i.sin;
		sout = i.sout;
		scan = i.scan;
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

