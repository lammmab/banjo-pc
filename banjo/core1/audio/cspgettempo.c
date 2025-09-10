#include <libultraship/libultra.h>
#include "functions.h"
#include "variables.h"

#include <libaudio.h>

s32 alCSPGetTempo(ALCSPlayer *seqp){
    if(seqp->target == N64_NULL)
        return 0;
    return seqp->uspt / seqp->target->qnpt;
}

