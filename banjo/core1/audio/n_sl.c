#include <libultraship/libultra.h>
#include "functions.h"
#include "variables.h"

#include "n_libaudio.h"


N_ALSynth *D_80276E80 = N64_NULL;
N_ALSynth *n_syn = N64_NULL;

void n_alInit(N_ALGlobals *g, ALSynConfig *config)
{
    if (D_80276E80 != N64_NULL)
        return;

    D_80276E80 = &g->drvr;

    if (n_syn != N64_NULL)
        return;

    n_syn = &g->drvr;

    n_alSynNew(config);
}

void n_alClose(N_ALGlobals *glob)
{
    if (D_80276E80)
    {
        n_alSynDelete();

        D_80276E80 = N64_NULL;
        n_syn = N64_NULL;
    }
}
