#include <libultraship/libultra.h>
#include "functions.h"
#include "variables.h"

extern OSThread *__osRunningThread;//_osRunningThread;

s32 osRecvMesg(OSMesgQueue *mq, OSMesg *msg, s32 flags)
{
    register u32 saveMask;
    saveMask = __osDisableInt();

    while (MQ_IS_EMPTY(mq))
    {
        if (flags == OS_MESG_NOBLOCK)
        {
            __osRestoreInt(saveMask);
            return -1;
        }
        __osRunningThread->state = OS_STATE_WAITING;
        __osEnqueueAndYield(&mq->mtqueue);
    }

    if (msg != N64_NULL)
    {
        *msg = mq->msg[mq->first];
    }
    mq->first = (mq->first + 1) % mq->msgCount;
    mq->validCount--;
    if (mq->fullqueue->next != N64_NULL)
    {
        osStartThread(__osPopThread(&mq->fullqueue));
    }
    __osRestoreInt(saveMask);
    return 0;
}
