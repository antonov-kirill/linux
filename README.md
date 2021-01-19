This programm is a UDP-to-CAN converter. It can be installed on devices with operating system Linux which have 
Ethernet interface and one or more CAN interfaces.
 
Each CAN interface has a specific input UDP port. Data from the UDP port are being transmited to the CAN interface.
Data received from the CAN interface are being transmited to a predefined output UDP port and IP address.

To the programm work corectly it should be configured before the first run. To make it the configuration file 'config.xml'
should be modified. The file is generated in '/bin' directory after the build process.

File 'config.xml' contains interface descriptors. Each block <Interface/> represents an interface descriptor and contains
the following parameters:
1. <CAN_Name>	- char*			          - CAN interface name in Linux (can0/vcan1/...)
2. <CAN_ID>	  - int (HEX)		       - ID of the converter in CAN frames
3. <CAN_FD>	  - bool (true/false)	- CAN version (false - CAN 2.0; true - CAN FD)
4. <PORT_IN>	 - char*			          - input UDP port. Data from the UDP port are being transmited to the CAN interface
5. <IP_OUT>	  - char*			          - output IP address. Data received from the CAN interface are being transmited to this IP
6. <PORT_OUT>	- char*			          - output UDP port. Data received from the CAN interface are being transmited to this port

Note: parameters <CAN_NAME>, <CAN_ID>, <CAN_FD>, <IP_OUT>, <PORT_OUT> can be the same for several interfaces,
but the parameter <PORT_IN> must be unique for each interface.

Command line arguments:
--path path_to_file	- path to 'config.xml' (default - a project output directory)

###########################################################

Данная программа представляет собой конвертер интерфейсов UDP-to-CAN и предназначена для установки на устройствах, 
работающих под операционной системой Linux, имеющих Ethernet интерфейс и любое количество CAN интерфейсов.

Каждому CAN интерфейсу соответствует определенный приемный UDP-порт, данные с которого передаются в соответствующий CAN.
Данные, пришедшие из CAN, передаются на другой заранее определенный UDP-порт по заранее определенному IP-адресу.

Для корректной работы перед первым запуском необходимо настроить программу путем внесения изменений в конфигурационный файл
'config.xml', генерирующийся в папке '/bin' после выполнения сборки проекта.

Файл config.xml содержит дескрипторы интерфейсов. Каждый блок <Interface/> представляет собой дескриптор интерфейса 
и содержит следующие параметры:
1. <CAN_Name>  - char*             - имя интерфейса CAN в системе Linux (can0/vcan1/...)
2. <CAN_ID>    - int (HEX)         - идентификатор конвертера в CAN фреймах
3. <CAN_FD>    - bool (true/false) - выерсия CAN (false - CAN 2.0; true - CAN FD)
4. <PORT_IN>	  - char*             - UDP-порт, откуда считываются данные, предназначенные для отправки в CAN
5. <IP_OUT>	   - char*             - IP адрес, на который отправляются данные, считанные из CAN
6. <PORT_OUT>	 - char*             - UDP-порт, на который отправляются данные, считанные из CAN

Обратите внимание: параметры <CAN_NAME>, <CAN_ID>, <CAN_FD>, <IP_OUT>, <PORT_OUT> могут быть одинаковыми для разных интерфейсов,
но параметр <PORT_IN> должен быть уникальным для каждого интерфейса.

Ключи командной строки:
--path path_to_file	- путь к config.xml (по умолчанию - папка с исполняемым файлом)
