#include <libultraship/libultra.h>
#include "viint.h"
#include "osint.h"

#include "n64_compat.h"

OSMgrArgs __osViDevMgr = {0};

/* .bss */
/*static*/ OSThread viThread;
/*static*/ unsigned char viThreadStack[OS_VIM_STACKSIZE];
/*static*/ OSMesgQueue viEventQueue;
/*static*/ OSMesg viEventBuf[5];
/*static*/ OSIoMesg viRetraceMsg;
/*static*/ OSIoMesg viCounterMsg;

static void viMgrMain(void *arg);
void osCreateViManager(OSPri pri)
{
	u32 savedMask;
	OSPri oldPri;
	OSPri myPri;
	if (__osViDevMgr.initialized == 0)
	{
		__osTimerServicesInit();
		osCreateMesgQueue(&viEventQueue, viEventBuf, 5);
		viRetraceMsg.hdr.type = OS_MESG_TYPE_VRETRACE;
		viRetraceMsg.hdr.pri = OS_MESG_PRI_NORMAL;
		viRetraceMsg.hdr.retQueue = N64_NULL;
		viCounterMsg.hdr.type = OS_MESG_TYPE_COUNTER;
		viCounterMsg.hdr.pri = OS_MESG_PRI_NORMAL;
		viCounterMsg.hdr.retQueue = N64_NULL;
		osSetEventMesg(OS_EVENT_VI, &viEventQueue, (OSMesg) { .ptr = &viRetraceMsg });
		osSetEventMesg(OS_EVENT_COUNTER, &viEventQueue, (OSMesg) { .ptr = &viCounterMsg });
		oldPri = -1;
		myPri = osGetThreadPri(N64_NULL);
		if (myPri < pri)
		{
			oldPri = myPri;
			osSetThreadPri(N64_NULL, pri);
		}
		savedMask = __osDisableInt();
		__osViDevMgr.initialized = 1;
		__osViDevMgr.mgrThread = &viThread;
		__osViDevMgr.cmdQueue = &viEventQueue;
		__osViDevMgr.eventQueue = &viEventQueue;
		__osViDevMgr.accessQueue = N64_NULL;
		__osViDevMgr.piDmaCallback = N64_NULL;
		__osViDevMgr.epiDmaCallback = N64_NULL;
		osCreateThread(&viThread, 0, viMgrMain, &__osViDevMgr, &viThreadStack[OS_VIM_STACKSIZE], pri);
		__osViInit();
		osStartThread(&viThread);
		__osRestoreInt(savedMask);
		if (oldPri != -1)
		{
			osSetThreadPri(0, oldPri);
		}
	}
}
u16 retrace;
static void viMgrMain(void *arg)
{
	__OSViContext *vc;
	OSMgrArgs *dm;
	OSIoMesg *mb;
	// static u16 retrace;
	s32 first;
	u32 count;

	mb = N64_NULL;
	first = 0;
	vc = __osViGetCurrentContext();
	retrace = vc->retraceCount;
	if (retrace == 0)
		retrace = 1;
	dm = (OSMgrArgs *)arg;
	while (true)
	{
		osRecvMesg(dm->eventQueue, (OSMesg *)&mb, OS_MESG_BLOCK);
		switch (mb->hdr.type)
		{
		case OS_MESG_TYPE_VRETRACE:
			__osViSwapContext();
			retrace--;
			if (retrace == 0)
			{
				vc = __osViGetCurrentContext();
				if (vc->msgq != N64_NULL)
					osSendMesg(vc->msgq, vc->msg, OS_MESG_NOBLOCK);
				retrace = vc->retraceCount;
			}
			__osViIntrCount++;
			if (first)
			{

				count = osGetCount();
				__osCurrentTime = count;
				first = 0;
			}
			count = __osBaseCounter;
			__osBaseCounter = osGetCount();
			count = __osBaseCounter - count;
			__osCurrentTime = __osCurrentTime + count;
			break;
		case OS_MESG_TYPE_COUNTER:
			__osTimerInterrupt();
			break;
		}
	}
}
