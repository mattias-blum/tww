//
// Generated by dtk
// Translation Unit: d_a_tag_msg.cpp
//
#include "d/actor/d_a_tag_msg.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "global.h"

static Vec bss_3569;
// Not sure what these are, but they have size 1, and alignment 1 in the debug maps, but alignment 4 in the non-debug maps.
static u8 bss_1036 ALIGN_DECL(4);
static u8 bss_1034 ALIGN_DECL(4);
static u8 bss_1032 ALIGN_DECL(4);
static u8 bss_1031 ALIGN_DECL(4);
static u8 bss_1026 ALIGN_DECL(4);
static u8 bss_1024 ALIGN_DECL(4);
static u8 bss_1022 ALIGN_DECL(4);
static u8 bss_1021 ALIGN_DECL(4);
static u8 bss_984 ALIGN_DECL(4);
static u8 bss_982 ALIGN_DECL(4);
static u8 bss_980 ALIGN_DECL(4);
static u8 bss_979 ALIGN_DECL(4);
static u8 bss_941 ALIGN_DECL(4);
static u8 bss_939 ALIGN_DECL(4);
static u8 bss_937 ALIGN_DECL(4);
static u8 bss_936 ALIGN_DECL(4);
static u32 l_msgId;
static msg_class* l_msg;
static u8 msg_mode;

u32 daTag_Msg_c::getEventNo() {
    return mBase.mParameters >> 0x18;
}

u32 daTag_Msg_c::getSwbit() {
    return mBase.mParameters >> 8 & 0xff;
}

u32 daTag_Msg_c::getSwbit2() {
    return mBase.mParameters >> 0x10 & 0xff;
}

u32 daTag_Msg_c::getType2() {
    return mBase.mParameters >> 6 & 3;
}

const char* daTag_Msg_c::myDemoName() {
    dStage_EventInfo_c *pEventInfo;
    u32 eventNo;

    pEventInfo = dComIfGp_getStageEventInfo();
    eventNo = getEventNo() & 0xff;

    if (getMessage() == 0x1902) {
        return "RT_TALK";
    }
    if (pEventInfo == NULL || (int)eventNo == 0xff || pEventInfo->field_0x0 < (int)eventNo) {
        return "DEFAULT_MSG";
    }
    return pEventInfo->mName + eventNo * 0x18 + 1;
}

u16 daTag_Msg_c::getMessage() {
    return orig.angle.x;
}

u16 daTag_Msg_c::getEventFlag() {
    return orig.angle.z;
}

BOOL daTag_Msg_c::arrivalTerms() {
    int swBit;
    u16 eventFlag;
    swBit = (int)(getSwbit2() & 0xFF);
    eventFlag = getEventFlag();
    if ((s32)swBit != 0xff && dComIfGs_isSwitch(swBit, current.roomNo) == 0) {
        return FALSE;
    }
    else if (eventFlag != 0xffff && dComIfGs_isEventBit(eventFlag) == 0) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

/* 0000021C-000002FC       .text rangeCheck__11daTag_Msg_cFv */
BOOL daTag_Msg_c::rangeCheck() {
    daPy_lk_c* link;
    cXyz diff;

    link = daPy_getPlayerLinkActorClass();
    diff = link->current.pos - current.pos;

    if (diff.y < 0.0f) {
        diff.y = -diff.y;
    }
    if (diff.abs2XZ() < mScale.x * mScale.x * 10000.0f) {
        if(diff.y <= mScale.y * 100.0f) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL daTag_Msg_c::otherCheck() {
    daPy_lk_c *player;
    short diff;
    short actorAngle;

    actorAngle = fopAcM_searchActorAngleY(this, daPy_getPlayerActorClass());
    player = daPy_getPlayerLinkActorClass();
    if ((getType2() & 1) != 0) {
        return TRUE;
    }
    JUT_ASSERT(0xC8, player);
    if (getMessage() == 0x1902) {
        diff = (short)(actorAngle - this->orig.angle.y);
        if (diff < 0) {
            diff = -diff;
        }
        if (0x3000 < diff) {
            return FALSE;
        }
    }
    actorAngle = (short)(actorAngle + 0x7fff) - player->current.angle.y;
    if (actorAngle < 0) {
        actorAngle = (short)-actorAngle;
    }
    if (actorAngle > 0x1000) {
        return FALSE;
    }

    return TRUE;
}

static BOOL daTag_Msg_actionEvent(daTag_Msg_c* a_this) {
    int message = a_this->getMessage();
    switch (msg_mode / 1) {
    case 0:
        if (dComIfGp_checkCameraAttentionStatus(dComIfGp_getPlayerCameraID(0), 4)) {
            msg_mode++;
        }
        break;
    case 1:
        l_msgId = fopMsgM_messageSet(message, &a_this->mAttentionInfo.mPosition);
        if (l_msgId != fpcM_ERROR_PROCESS_ID_e) {
            msg_mode++;
        }
        break;
    case 2:
        l_msg = fopMsgM_SearchByID(l_msgId);
        if (l_msg != NULL) {
            msg_mode++;
        }
        break;
    case 3:
        JUT_ASSERT(0x13F, l_msg);
        if (l_msg->mMode == 6) {
            msg_mode++;
        }
        break;
    case 4:
        JUT_ASSERT(0x145, l_msg);
        if (l_msg->mMode == 0xe) {
            msg_mode++;
            l_msg->mMode = 0x10;
        }
        break;
    }
    if (l_msg != NULL && l_msg->mMode == 0x12) {
        l_msg->mMode = 0x13;
        dComIfGp_event_onEventFlag(8);
        if (a_this->getMessage() == 0x1902) {
            daPy_getPlayerLinkActorClass()->offPlayerNoDraw();
        }
        if (a_this->getType2() & 1) {
            a_this->setActio(0);
        } else {
            a_this->setActio(2);
        }
    }
    return TRUE;
}

static BOOL daTag_Msg_actionHunt(daTag_Msg_c* a_this) {
    u8 swBit;

    if (a_this->mEvtInfo.mCommand == dEvtCmd_INTALK_e) {
        a_this->setActio(3);
        swBit = a_this->getSwbit();
        if ((swBit & 0xff) != 0xff) {
            dComIfGs_onSwitch(swBit,a_this->current.roomNo);
        }
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        l_msg = 0;
        msg_mode = 0;
        if ((u32)a_this->getMessage() == 0x1902) {
            daPy_getPlayerLinkActorClass()->onPlayerNoDraw();
        }
    } else if (a_this->rangeCheck() != 0 && a_this->otherCheck() != 0) {
        if ((a_this->getType2() & 1) != 0) {
            fopAcM_orderSpeakEvent(a_this);
        }
        a_this->mEvtInfo.mCondition |= dEvtCnd_CANTALK_e;
    }
    return TRUE;
}

/* 00000754-000007B0       .text daTag_Msg_actionArrival__FP11daTag_Msg_c */
static BOOL daTag_Msg_actionArrival(daTag_Msg_c* a_this) {
    char *cutsceneName;

    if (a_this->arrivalTerms() != 0) {
        cutsceneName = (char*)a_this->myDemoName();
        a_this->mEvtInfo.setEventName(cutsceneName);
        a_this->setActio(2);
        daTag_Msg_actionHunt(a_this);
    }
    return TRUE;
}

static BOOL daTag_Msg_actionWait(daTag_Msg_c*) {
    return TRUE;
}

static BOOL daTag_Msg_Draw(daTag_Msg_c*) {
    return TRUE;
}

BOOL daTag_Msg_c::execute() {
    static ActionFunc* l_action[4] = {
        daTag_Msg_actionWait,
        daTag_Msg_actionArrival,
        daTag_Msg_actionHunt,
        daTag_Msg_actionEvent,
    };
    l_action[mAction](this);
    return TRUE;
}

s32 daTag_Msg_c::create() {
    int swBit;
    fopAcM_SetupActor(this, daTag_Msg_c);
    swBit = (int)(getSwbit() & 0xFF);
    if ((getMessage() == 0x9c5) && dComIfGs_isEventBit(0x502)) {
        setActio(0);
    } else if ((s32)swBit != 0xff && dComIfGs_isSwitch(swBit, current.roomNo) != 0) {
        setActio(0);
    } else {
        setActio(1);
    }
    shape_angle.z = 0;
    shape_angle.x = 0;
    current.angle.z = 0;
    current.angle.x = 0;
    mAttentionInfo.mFlags = fopAc_Attn_ACTION_TALK_e | fopAc_Attn_TALKFLAG_CHECK_e;
    if (getMessage() != 0x836) {
        mAttentionInfo.mPosition.y += 150;
        mEyePos.y += 150.0f;
    }
    return cPhs_COMPLEATE_e;
}

static BOOL daTag_Msg_Execute(daTag_Msg_c* a_this) {
    return a_this->execute();
}

static BOOL daTag_Msg_IsDelete(daTag_Msg_c*) {
    return TRUE;
}

static BOOL daTag_Msg_Delete(daTag_Msg_c* a_this) {
    a_this->~daTag_Msg_c();
    return TRUE;
}

static s32 daTag_Msg_Create(fopAc_ac_c* i_this) {
    daTag_Msg_c* a_this = (daTag_Msg_c*)i_this;
    return a_this->create();
}

static actor_method_class l_daTag_Msg_Method = {
    (process_method_func)daTag_Msg_Create,
    (process_method_func)daTag_Msg_Delete,
    (process_method_func)daTag_Msg_Execute,
    (process_method_func)daTag_Msg_IsDelete,
    (process_method_func)daTag_Msg_Draw,
};

actor_process_profile_definition g_profile_TAG_MSG = {
    fpcLy_CURRENT_e,
    7,
    fpcPi_CURRENT_e,
    PROC_TAG_MSG,
    &g_fpcLf_Method.mBase,
    sizeof(daTag_Msg_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x0121,
    &l_daTag_Msg_Method,
    fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_6_e,
};