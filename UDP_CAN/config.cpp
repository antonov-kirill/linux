#include "stdio.h"
#include "stdlib.h"
#include "pugixml.hpp"
#include <list>

#define __CONFIG_MAIN_H__
#include "config.h"

void GetCongiguration(char* path, std::list<Interface*> &interfaces)
{
	printf("The configuration file path: %s\n", path);

	if (ReadConfigFile(path, interfaces))
		printf("The configuration file was read successfully.\r\n");
	else
	{
		printf("Failed to read the configuration file.\r\n");
		exit(1);
	}
}

bool ReadConfigFile(char* path, std::list<Interface*> &interfaces)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(path);

	if (result.status != 0)
		return false;

	try
	{
		printf("ID\tCAN\tIP_OUT\t\tPORT_IN\tPORT_OUT\n");
		int cntr = 1;
		for (pugi::xml_node node : doc.child("Interfaces"))
		{
			char* name = (char*)node.child("CAN_Name").text().as_string();
			char* ip = (char*)node.child("IP_OUT").text().as_string();
			char* pin = (char*)node.child("PORT_IN").text().as_string();
			char* pout = (char*)node.child("PORT_OUT").text().as_string();

			Interface* i = new Interface(cntr, name, ip, pin, pout);
			interfaces.push_back(i);

			printf("%i\t%s\t%s\t%s\t%s\n", cntr++, name, ip, pin, pout);
		}
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}