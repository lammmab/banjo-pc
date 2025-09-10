#include <libultraship/libultra.h>
#include "functions.h"
#include "variables.h"

extern OSThread *__osRunningThread;

OSPri osGetThreadPri(OSThread *thread)
{
    if (thread == N64_NULL)
        thread = __osRunningThread;
    return thread->priority;
}
