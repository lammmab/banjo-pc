#include <libultraship/libultra.h>
#include "piint.h"

#include "n64_compat.h"

s32 osEPiRawStartDma(OSPiHandle *pihandle, s32 direction, u32 devAddr, void *dramAddr, u32 size);
extern s32 osPiRawStartDma(s32, u32, void *, u32);
extern u32 __osPiAccessQueueEnabled;

OSMgrArgs __osPiDevMgr = {0};
OSPiHandle *__osPiTable = N64_NULL;
OSPiHandle *__osCurrentHandle[2] = {&CartRomHandle, &LeoDiskHandle};

/* .bss */
OSThread piThread;
char piThreadStack[OS_PIM_STACKSIZE];
OSMesgQueue piEventQueue;
OSMesg piEventBuf;

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt)
{
	u32 savedMask;
	OSPri oldPri;
	OSPri myPri;
	if (!__osPiDevMgr.initialized)
	{
		osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
		osCreateMesgQueue(&piEventQueue, (OSMesg*)&piEventBuf, 1);
		if (!__osPiAccessQueueEnabled)
			__osPiCreateAccessQueue();
		osSetEventMesg(OS_EVENT_PI, &piEventQueue, (OSMesg){0x22222222});
		oldPri = -1;
		myPri = osGetThreadPri(N64_NULL);
		if (myPri < pri)
		{
			oldPri = myPri;
			osSetThreadPri(N64_NULL, pri);
		}
		savedMask = __osDisableInt();
		__osPiDevMgr.initialized = 1;
		__osPiDevMgr.mgrThread = &piThread;
		__osPiDevMgr.cmdQueue = cmdQ;
		__osPiDevMgr.eventQueue = &piEventQueue;
		__osPiDevMgr.accessQueue = &__osPiAccessQueue;
		__osPiDevMgr.piDmaCallback = osPiRawStartDma;
		__osPiDevMgr.epiDmaCallback = osEPiRawStartDma;
		osCreateThread(&piThread, 0, __osDevMgrMain, &__osPiDevMgr, &piThreadStack[OS_PIM_STACKSIZE], pri);
		osStartThread(&piThread);
		__osRestoreInt(savedMask);
		if (oldPri != -1)
		{
			osSetThreadPri(N64_NULL, oldPri);
		}
	}
}
