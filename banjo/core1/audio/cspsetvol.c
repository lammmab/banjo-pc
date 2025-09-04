#include <libultraship/libultra.h>
#include "functions.h"
#include "variables.h"

#include <libaudio.h>

void alCSPSetVol(ALCSPlayer *seqp, s16 vol)
{
    ALEvent       evt;

    evt.type            = AL_SEQP_VOL_EVT;
    evt.msg.spvol.vol   = vol;
    
    alEvtqPostEvent(&seqp->evtq, &evt, 0);
}

