#include <libultraship/libultra.h>
#include "osint.h"

int osStopTimer(OSTimer *t)
{
    register u32 savedMask;
    OSTimer *timep;

    if (t->next == N64_NULL)
        return -1;
    savedMask = __osDisableInt();
    timep = t->next;
    if (timep != __osTimerList)
    {
        timep->value += t->value;
    }
    t->prev->next = t->next;
    t->next->prev = t->prev;
    t->next = N64_NULL;
    t->prev = N64_NULL;
    if (__osTimerList->next == __osTimerList)
    {
        __osSetCompare(0);
    }
    __osRestoreInt(savedMask);
    return 0;
}
