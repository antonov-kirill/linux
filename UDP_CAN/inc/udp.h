#ifndef __UDP_H__
#define __UDP_H__

#ifdef __UDP_MAIN_H__

bool CreateInputSocket(Interface* i);
bool CreateOutputSocket(Interface* i);

#else

extern bool CreateInputSocket(Interface* i);
extern bool CreateOutputSocket(Interface* i);

#endif

#endif