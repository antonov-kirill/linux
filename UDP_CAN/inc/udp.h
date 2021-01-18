#ifndef __UDP_H__
#define __UDP_H__

#ifdef __UDP_MAIN_H__

bool UDP_CreateInputSocket(Interface* i);
bool UDP_CreateOutputSocket(Interface* i);
int UDP_ReceiveFrame(Interface* i);
bool UDP_CheckSocket(Interface* i);

#else

extern bool UDP_CreateInputSocket(Interface* i);
extern bool UDP_CreateOutputSocket(Interface* i);
extern int UDP_ReceiveFrame(Interface* i);

#endif

#endif