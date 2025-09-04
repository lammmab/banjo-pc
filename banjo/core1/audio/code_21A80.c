#include "libultraship/libultra/types.h"

typedef struct N_ALCSPlayer N_ALCSPlayer;

u8 func_8025F4A0(N_ALCSPlayer *seqp, u8 chan)
{
    return seqp->chanState[chan].unkA;
}
