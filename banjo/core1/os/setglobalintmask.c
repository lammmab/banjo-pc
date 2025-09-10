#include <libultraship/libultra.h>

#include "os_system.h"

void __osSetGlobalIntMask(OSHWIntr mask)
{
    register u32 saveMask = __osDisableInt();
    __OSGlobalIntMask |= mask;
    __osRestoreInt(saveMask);
}
