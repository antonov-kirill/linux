#include "stdio.h"
#include "stdlib.h"
#include "pugixml.hpp"
#include <list>

using namespace std;

#define __CONFIG_MAIN_H__
#include "config.h"

void GetCongiguration(char* path, char* dest_ip, list<Interface> &interfaces)
{
	printf("The configuration file path: %s\n", path);

	if (ReadConfigFile(path, dest_ip, interfaces))
		printf("The configuration file was read successfully.\r\n");
	else
	{
		printf("Failed to read the configuration file.\r\n");
		exit(1);
	}
}

bool ReadConfigFile(char* path, char* dest_ip, list<Interface> &interfaces)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(path);

	if (result.status != 0)
		return false;

	try
	{
		dest_ip = (char*)doc.child("Interfaces").attribute("ip_out").as_string();
		printf("\nDestination IP: %s\n", dest_ip);

		printf("Num\tCAN\tUDP_IN\tUDP_OUT\n");
		int cntr = 1;
		for (pugi::xml_node node : doc.child("Interfaces"))
		{
			char* name = (char*)node.child("CAN_Name").text().as_string();
			char* in = (char*)node.child("UDP_IN").text().as_string();
			char* out = (char*)node.child("UDP_OUT").text().as_string();

			Interface* i = new Interface(name, in, out);
			interfaces.push_back(*i);

			printf("%i\t%s\t%s\t%s\n", cntr++, name, in, out);
		}
		printf("\n");
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}