#include <libultraship/libultra.h>
#include "synthInternals.h"

#define aSaveBufferWrapper(pkt, d) \
    aSaveBuffer(pkt, 0, d, 1)  // DMEM offset=0, count=1

#define aInterleaveWrapper(pkt, l, r) \
    aInterleave(pkt, 0, l, r, 1)

#define aLoadBufferWrapper(pkt, s) \
    aLoadBuffer(pkt, s, 0, 1)


Acmd *alSavePull(void *filter, s16 *outp, s32 outCount, s32 sampleOffset,
                 Acmd *p) 

{
    Acmd        *ptr = p;
    ALSave *f = (ALSave *)filter;
    ALFilter    *source = f->filter.source;
    
    ptr = (*source->handler)(source, outp, outCount, sampleOffset, ptr);
    
    aSetBuffer (ptr++, 0, 0, 0, outCount<<1);
    aInterleaveWrapper(ptr++, AL_MAIN_L_OUT, AL_MAIN_R_OUT);
    aSetBuffer (ptr++, 0, 0, 0, outCount<<2);
    aSaveBufferWrapper(ptr++, f->dramout);
    return ptr;
}

s32 alSaveParam(void *filter, s32 paramID, void *param)
{
    ALSave *a = (ALSave *) filter;
    ALFilter *f = (ALFilter *) filter;
    s32 pp = (s32) param;

    switch (paramID) {
        case (AL_FILTER_SET_SOURCE):
            f->source = (ALFilter *) param;
            break;

        case (AL_FILTER_SET_DRAM): 
            a->dramout = pp;
            break;
            
        default:
            break;
    }
    return 0;
            
}
