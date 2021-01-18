#ifndef __CAN_H__
#define __CAN_H__

#ifdef __CAN_MAIN_H__

bool CAN_CreateSocket(Interface* i);
void* CAN_ThreadFunction(void* arg);
int CAN_ReceiveFrame(Interface i);
int CANFD_ReceiveFrame(Interface i);
bool CAN_CheckSocket(Interface i);
void CAN_SendFrame(Interface* i, int size);
void CANFD_SendFrame(Interface* i, int size);

#else

extern bool CAN_CreateSocket(Interface* i);
extern void* CAN_ThreadFunction(void* arg);
extern void CAN_SendFrame(Interface* i, int size);
extern void CANFD_SendFrame(Interface* i, int size);

extern std::timed_mutex* scan_mutex;

#endif

#endif