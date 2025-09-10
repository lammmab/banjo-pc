#include <libultraship/libultra.h>
#include "n_synth.h"


void n_alSynDelete(void){
    n_syn->head = N64_NULL;
    n_syn->n_seqp1 = N64_NULL;
    n_syn->n_seqp2 = N64_NULL;
    n_syn->unk5C = N64_NULL;
    n_syn->unk60 = N64_NULL;
    n_syn->unk64 = N64_NULL;
    n_syn->unk68 = N64_NULL;
    n_syn->unk6C = N64_NULL;
    n_syn->unk70 = N64_NULL;
    n_syn->n_sndp = N64_NULL;
}
