#ifndef _SIINT_H
#define _SIINT_H
#include <libultraship/libultra.h>

void __osSiGetAccess(void);
void __osSiRelAccess(void);
int __osSiDeviceBusy(void);
void __osSiCreateAccessQueue(void);
#endif
