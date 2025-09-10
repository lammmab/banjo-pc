#include <libultraship/libultra.h>
#include "n_synth.h"

#define aSaveBufferWrapper(pkt, d) \
    aSaveBuffer(pkt, 0, d, 1)  // DMEM offset=0, count=1

#define aInterleaveWrapper(pkt, l, r) \
    aInterleave(pkt, 0, l, r, 1)

Acmd *n_alSavePull( s32 sampleOffset, Acmd *p) 
{
    Acmd        *ptr = p;

    ptr = n_alMainBusPull(sampleOffset, ptr);
    
#ifndef N_MICRO
    aSetBuffer (ptr++, 0, 0, 0, FIXED_SAMPLE<<1);
    aInterleaveWrapper(ptr++, AL_MAIN_L_OUT, AL_MAIN_R_OUT);
    aSetBuffer (ptr++, 0, 0, 0, FIXED_SAMPLE<<2);
    aSaveBufferWrapper(ptr++, n_syn->sv_dramout);
#else
#include "n_save_add01.c_"
#endif
    return ptr;
}
