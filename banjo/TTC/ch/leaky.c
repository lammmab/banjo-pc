#include <libultraship/libultra.h>
#include "functions.h"
#include "variables.h"

#include "n64_compat.h"

extern void func_8028E668(f32 [3], f32, f32, f32);
extern void func_8028F9DC(s32);
extern void func_803272D0(f32 arg0[3], f32 arg1, s32 arg2, int (*arg3)(Actor *));

static void __chLeaky_updateFunc(Actor *this);

/* .data */
ActorAnimationInfo gChLeakyAnimations[3] = {
    {N64_NULL, N64_NULL},
    {ASSET_239_ANIM_LEAKY_IDLE, 2.5f},
    {ASSET_239_ANIM_LEAKY_IDLE, 2.5f}
};

ActorInfo gChLeaky = { 
    MARKER_33_LEAKY,  ACTOR_1E_LEAKY, ASSET_51A_MODEL_LEAKY,
    0x1, gChLeakyAnimations,
    __chLeaky_updateFunc, actor_update_func_80326224, actor_draw,
    0, 0, 0.0f, 0
};

/* .code */
static bool __chLeaky_isCurrentModelShrapnel(Actor *this){
    return this->modelCacheIndex == ACTOR_56_SHRAPNEL;
}

static void __func_80388F88(void){
    static f32 D_8038C73C[3] = {2500.0f, 250.0f, 4600.0f};
    func_803272D0(D_8038C73C, 2000.0f, 2, __chLeaky_isCurrentModelShrapnel);
}

static void __chLeaky_updateFunc(Actor *this) {
    void *temp_v0_2;

    func_8028E668(this->position, 100.0f, -20.0f, 100.0f);
    if (!this->volatile_initialized) {
        this->volatile_initialized = true;
        this->marker->propPtr->unk8_3 = false;

        if (levelSpecificFlags_get(LEVEL_FLAG_5_TTC_UNKNOWN) != false) {
            levelSpecificFlags_set(LEVEL_FLAG_5_TTC_UNKNOWN, false);
            timedFunc_set_1(0.5f, (GenFunction_1)comusic_playTrack, COMUSIC_2D_PUZZLE_SOLVED_FANFARE);
        }

        if (levelSpecificFlags_get(LEVEL_FLAG_2_TTC_UNKNOWN) != false) {
            temp_v0_2 = func_8034C5AC(300);
            if (temp_v0_2 != 0) {
                func_8034E71C(temp_v0_2, -600, 0.0f);
            }
            this->state = 2;
        } else {
            this->state = 1;
        }
    }

    if( this->state == 1 
        && !this->has_met_before
        && subaddie_playerIsWithinSphereAndActive(this, 250) && !subaddie_playerIsWithinSphereAndActive(this, 160)
        && !player_movementGroup() 
        && gcdialog_showDialog(ASSET_A1A_DIALOG_LEAKY_FIRST_MEET, 0, N64_NULL, N64_NULL, N64_NULL, N64_NULL)
    ){
        this->has_met_before = true;
    }

    if (gcdialog_hasCurrentTextId() == 0) {
        if (actor_animationIsAt(this, 0.83f)) {
            func_8030E878(SFX_109_LOGGO_LID_CLAP, randf2(0.775f, 0.825f), 22000, this->position, 400.0f, 1000.0f);
            return;
        }
        if (actor_animationIsAt(this, 0.01f)) {
            func_8030E878(SFX_109_LOGGO_LID_CLAP, randf2(1.025f, 1.075f), 18000, this->position, 400.0f, 1000.0f);
            return;
        }
        if( actor_animationIsAt(this, 0.15f) 
            || actor_animationIsAt(this, 0.34f)
            || actor_animationIsAt(this, 0.53f)
            || actor_animationIsAt(this, 0.66f)
        ){
            func_8030E878(SFX_109_LOGGO_LID_CLAP, randf2(1.225f, 1.275f), 14000, this->position, 400.0f, 1000.0f);
        }
    }
}

static void __chLeaky_showDoneText(ActorMarker *caller, enum asset_e text_id, s32 arg2){
    Actor *this = marker_getActor(caller);
    Struct73s *temp_v0;
    subaddie_set_state(this, 2);
    temp_v0 = func_8034C5AC(300);
    if(temp_v0 != N64_NULL){
        func_8034E7B8(temp_v0, -600, 4.0f, 2, 10.0f);
    }

    func_80324E38(0.0f, 3);
    timed_setStaticCameraToNode(0.5f, 7);
    timedFunc_set_0(1.0f, __func_80388F88);
    func_80324E38(2.5f, 0);
    timedFunc_set_1(2.5f, func_8028F9DC, 2);
    timedFunc_set_3(2.5f, (GenFunction_3)transitionToMap, MAP_A_TTC_SANDCASTLE, 0, 0);
    func_803228D8();
}

bool chLeaky_eggCollision(ActorMarker *marker){
    Actor *this = marker_getActor(marker);

    if (levelSpecificFlags_get(LEVEL_FLAG_2_TTC_UNKNOWN)) {
        return true;
    }

    comusic_playTrack(COMUSIC_2B_DING_B);
    this->unk38_31++;

    if (this->unk38_31 < 2) {
        return true;
    }

    levelSpecificFlags_set(2, true);
    levelSpecificFlags_set(5, true);
    gcdialog_showDialog(ASSET_A28_DIALOG_LEAKY_DONE, 0x2a, this->position, this->marker, __chLeaky_showDoneText, N64_NULL);
    return true;
}
