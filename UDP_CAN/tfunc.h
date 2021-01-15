#ifndef __TFUNC_H__
#define __TFUNC_H__

#ifdef __TFUNC_MAIN_H__

int kbhit(void);
int getch();

#else

extern int kbhit(void);
extern int getch();

#endif

#endif
