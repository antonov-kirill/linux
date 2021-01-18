#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "pugixml.hpp"
#include <list>

#define __CONFIG_MAIN_H__
#include "config.h"

void GetCongiguration(char* path, std::list<Interface*> &interfaces)
{
	printf("A configuration file path: %s\n", path);

	/* Read the file */
	if (ReadConfigFile(path, interfaces))
		printf("The configuration file was read successfully.\r\n");
	else
	{
		/* If failed to read the file close the program because it isn't possible to work without interface descriptors */
		printf("Failed to read the configuration file.\r\n");
		exit(1);
	}
}

bool ReadConfigFile(char* path, std::list<Interface*> &interfaces)
{
	/* Read the XML file */
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(path);

	if (result.status != 0)
		return false;

	try
	{
		printf("ID\tCAN_NAME\tCAN_ID\tCAN_FD\tIP_OUT\t\tPORT_IN\tPORT_OUT\n");
		int cntr = 1;

		/* Parse all nested elements in the element <Interfaces></Interfaces> */
		for (pugi::xml_node node : doc.child("Interfaces"))
		{
			char* name = (char*)node.child("CAN_Name").text().as_string();
			char* can_id = (char*)node.child("CAN_ID").text().as_string();
			char* can_fd = (char*)node.child("CAN_FD").text().as_string();

			char* ip = (char*)node.child("IP_OUT").text().as_string();
			char* pin = (char*)node.child("PORT_IN").text().as_string();
			char* pout = (char*)node.child("PORT_OUT").text().as_string();

			char * end;
			unsigned long ci = strtol(can_id, &end, 16);

			/* Create a new interface descriptor and save it into the list of interface descriptors */
			Interface* i = new Interface(cntr, name, ci, strcmp(can_fd, "false"), ip, pin, pout);
			interfaces.push_back(i);

			printf("%i\t%s\t\t%s\t%s\t%s\t%s\t%s\n", cntr++, name, can_id, can_fd, ip, pin, pout);
		}
	}
	catch (const std::exception&)
	{
		return false;
	}
	return true;
}