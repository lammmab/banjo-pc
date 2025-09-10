#include <libultraship/libultra.h>
#include "functions.h"
#include "variables.h"

extern OSMgrArgs __osPiDevMgr;

OSMesgQueue *osPiGetCmdQueue(void){
    if (!__osPiDevMgr.initialized)
        return N64_NULL;
    return __osPiDevMgr.cmdQueue;
}
