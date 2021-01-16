#ifndef __CAN_H__
#define __CAN_H__

#ifdef __CAN_MAIN_H__

void* CAN_ThreadFunction(void* arg);

#else

extern void* CAN_ThreadFunction(void* arg);

#endif

#endif