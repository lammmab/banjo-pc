#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 player_getYaw();
AnimCtrl *player_getAnimCtrlPtr(void);

Actor *__chJigsawDance_draw(ActorMarker *this, Gfx **gdl, Mtx **mptr, Vtx **arg3);
void __chJigsawDance_update(Actor * this);

/* .data */
ActorAnimationInfo chJigsawDanceAnimations[] = {
    {0x00, 0.0f},
    {0x00, 2.0f},
    {ASSET_76_ANIM_JIGSAWDANCE_HOLD, 1.5f},
    {ASSET_76_ANIM_JIGSAWDANCE_HOLD, 1.5f},
    {ASSET_30_ANIM_JIGSAWDANCE_DANCE, 5.0f},
    {0x00, 2.0f}
};

ActorInfo chJigsawDance = {MARKER_68_JIGSAW_DANCE, ACTOR_5A_JIGSAW_DANCE, ASSET_35E_MODEL_JIGSAW_DANCE, 
    1, chJigsawDanceAnimations, 
    __chJigsawDance_update, actor_update_func_80326224, __chJigsawDance_draw,
    0, 0, 0.0f, 0
}; 


/* .code */
Actor *__chJigsawDance_draw(ActorMarker *this, Gfx **gdl, Mtx **mptr, Vtx **arg3){
    Actor *thisActor = marker_getActor(this);

    if(!thisActor->initialized){
        thisActor->initialized = TRUE;
        return thisActor;
    }
    else{
        return actor_draw(this, gdl, mptr, arg3);
    }
}

void __chJigsawDance_update(Actor * this){
    AnimCtrl *plyrMvmt;

    this->marker->collidable = FALSE;
    switch(this->state){
        case 1:
            break;
        case 2:
            player_getPosition(this->position);
            this->yaw = player_getYaw();
            plyrMvmt = player_getAnimCtrlPtr();
            anctrl_setSmoothTransition(this->anctrl, 0);
            anctrl_setIndex(this->anctrl, anctrl_getIndex(plyrMvmt));
            anctrl_setStart(this->anctrl,anctrl_getAnimTimer(plyrMvmt));
            anctrl_setDuration(this->anctrl, 1000.0f);
            anctrl_start(this->anctrl, "chjigsawdance.c", 0x59);
            break;
        case 3:
            plyrMvmt = player_getAnimCtrlPtr();
            anctrl_setSmoothTransition(this->anctrl, 0);
            anctrl_setStart(this->anctrl,anctrl_getAnimTimer(plyrMvmt));
            anctrl_setDuration(this->anctrl, 1000.0f);
            anctrl_start(this->anctrl, "chjigsawdance.c", 0x62);
            break;
        case 4:
            player_getPosition(this->position);
            this->yaw = player_getYaw();
            plyrMvmt = player_getAnimCtrlPtr();
            anctrl_setSmoothTransition(this->anctrl, 0);
            anctrl_setStart(this->anctrl,anctrl_getAnimTimer(plyrMvmt));
            anctrl_setDuration(this->anctrl, 1000.0f);
            anctrl_start(this->anctrl, "chjigsawdance.c", 0x6e);
            break;
        case 5:
            this->marker->propPtr->unk8_4 = 0;
            break;
    }
}

void chJigsawDance_setState(Actor * this, u32 arg1){
    switch(arg1){
        case 3:
            if(this->state == 1){
                subaddie_set_state(this, 2);
                anctrl_setPlaybackType(this->anctrl,  ANIMCTRL_ONCE);
            }
            break;
        case 2:
            subaddie_set_state(this, 3);
            break;
        case 1:
            subaddie_set_state(this, 4);
            break;
        case 4:
            player_getPosition(this->position);
            this->yaw = player_getYaw();
            anctrl_setSmoothTransition(this->anctrl, 0);
            anctrl_setStart(this->anctrl, anctrl_getAnimTimer(player_getAnimCtrlPtr()));
            anctrl_setDuration(this->anctrl, 1000.0f);
            anctrl_start(this->anctrl, "chjigsawdance.c", 0x97);
            break;
        case 5:
            subaddie_set_state(this, 5);
            this->marker->propPtr->unk8_4 = 0;
            break;
    }
}
