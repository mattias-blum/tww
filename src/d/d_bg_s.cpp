//
// Generated by dtk
// Translation Unit: d_bg_s.cpp
//

#include "d/d_bg_s.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_s_sph_chk.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"

#define CHECK_FLOAT_CLASS(line, x) JUT_ASSERT(line, !(((sizeof(x) == sizeof(float)) ? __fpclassifyf((float)(x)) : __fpclassifyd((double)(x)) ) == 1));
#define CHECK_FLOAT_RANGE(line, x) JUT_ASSERT(line, -1.0e32f < x && x < 1.0e32f);
#define CHECK_VEC3_RANGE(line, v) JUT_ASSERT(line, -1.0e32f < v.x && v.x < 1.0e32f && -1.0e32f < v.y && v.y < 1.0e32f && -1.0e32f < v.z && v.z < 1.0e32f)
#define CHECK_PVEC3_RANGE(line, v) JUT_ASSERT(line, -1.0e32f < v->x && v->x < 1.0e32f && -1.0e32f < v->y && v->y < 1.0e32f && -1.0e32f < v->z && v->z < 1.0e32f)

/* 800A0270-800A0290       .text Ct__4dBgSFv */
void dBgS::Ct() {
    cBgS::Ct();
}

/* 800A0290-800A02B0       .text Dt__4dBgSFv */
void dBgS::Dt() {
    cBgS::Dt();
}

/* 800A02B0-800A02E8       .text ClrMoveFlag__4dBgSFv */
void dBgS::ClrMoveFlag() {
    for (s32 i = 0; i < ARRAY_SIZE(m_chk_element); i++) {
        if (m_chk_element[i].ChkUsed()) {
            dBgW* bgwp = (dBgW*)m_chk_element[i].m_bgw_base_ptr;
            bgwp->mFlag &= ~1;
        }
    }
}

/* 800A02E8-800A0354       .text Move__4dBgSFv */
void dBgS::Move() {
    cBgS::Move();

    for (s32 i = 0; i < ARRAY_SIZE(m_chk_element); i++) {
        if (m_chk_element[i].ChkUsed()) {
            dBgW* bgwp = (dBgW*)m_chk_element[i].m_bgw_base_ptr;
            s16 shape_angle = m_chk_element[i].m_actor_ptr->shape_angle.y;
            bgwp->mRotYDelta = shape_angle - bgwp->mOldRotY;
            bgwp->mOldRotY = shape_angle;
        }
    }
}

/* 800A0354-800A03C4       .text Regist__4dBgSFP4cBgWP10fopAc_ac_c */
bool dBgS::Regist(cBgW* bgw, fopAc_ac_c* ac) {
    if (bgw == NULL)
        return true;

    if (ac != NULL && bgw->ChkMoveBg()) {
        dBgW* bgwp = (dBgW*)bgw;
        bgwp->mOldRotY = ac->shape_angle.y;
        bgwp->mRoomNo = fopAcM_GetRoomNo(ac);
    }

    return cBgS::Regist(bgw, fopAcM_GetID(ac), ac);
}

/* 800A03C4-800A0420       .text ChkMoveBG__4dBgSFR13cBgS_PolyInfo */
bool dBgS::ChkMoveBG(cBgS_PolyInfo& polyInfo) {
    dBgW* bgwp = (dBgW*)dComIfG_Bgsp()->GetBgWPointer(polyInfo);
    if (bgwp != NULL) {
        if (bgwp->ChkLock())
            return false;
        if (bgwp->ChkMoveBg())
            return true;
    }
    return false;
}

/* 800A0420-800A046C       .text ChkMoveBG_NoDABg__4dBgSFR13cBgS_PolyInfo */
bool dBgS::ChkMoveBG_NoDABg(cBgS_PolyInfo& polyInfo) {
    dBgW* bgwp = (dBgW*)dComIfG_Bgsp()->GetBgWPointer(polyInfo);
    if (bgwp != NULL) {
        if (bgwp->ChkMoveBg())
            return true;
    }
    return false;
}

/* 800A046C-800A0604       .text GetPolyId0__4dBgSFiiiUlUl */
int dBgS::GetPolyId0(int bg_index, int poly_index, int defv, u32 mask, u32 shift) {
    JUT_ASSERT(0x349, 0 <= bg_index && bg_index < 256);
    if (!m_chk_element[bg_index].ChkUsed())
        return defv;

    dBgW* bgwp = (dBgW*)m_chk_element[bg_index].m_bgw_base_ptr;
    u32 inf_id = bgwp->GetPolyInfId(poly_index);
    return (bgwp->GetPolyInf0(inf_id) & mask) >> shift;
}

/* 800A0604-800A0630       .text GetPolyCamId__4dBgSFii */
int dBgS::GetPolyCamId(int i_bg_index, int i_poly_index) {
    return GetPolyId0(i_bg_index, i_poly_index, 0xFF, 0x000000FF, 0);
}

/* 800A0630-800A0668       .text GetMtrlSndId__4dBgSFR13cBgS_PolyInfo */
u32 dBgS::GetMtrlSndId(cBgS_PolyInfo& polyInfo) {
    return GetPolyId0(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0x00, 0x00001F00, 8);
}

/* 800A0668-800A06A4       .text GetExitId__4dBgSFR13cBgS_PolyInfo */
int dBgS::GetExitId(cBgS_PolyInfo& polyInfo) {
    return GetPolyId0(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0x3F, 0x0007E000, 13);
}

/* 800A06A4-800A0708       .text GetPolyColor__4dBgSFR13cBgS_PolyInfo */
int dBgS::GetPolyColor(cBgS_PolyInfo& polyInfo) {
    if (!polyInfo.ChkSetInfo())
        return 0xFF;

    return GetPolyId0(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0xFF, 0x07F80000, 19);
}

/* 800A0708-800A07F4       .text GetGrpRoomInfId__4dBgSFR13cBgS_PolyInfo */
int dBgS::GetGrpRoomInfId(cBgS_PolyInfo& polyInfo) {
    s32 bg_index = polyInfo.GetBgIndex();
    JUT_ASSERT(0x3a9, 0 <= bg_index && bg_index < 256);
    if (!m_chk_element[bg_index].ChkUsed())
        return 0xFF;

    dBgW* bgwp = (dBgW*)m_chk_element[bg_index].m_bgw_base_ptr;
    s32 inf = bgwp->mRoomNo2;
    if (inf != 0xFF)
        return inf;

    s32 grp_id = GetTriGrp(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex());
    if (grp_id == -1)
        return 0xFF;
    return GetGrpInf(polyInfo, grp_id) & 0xFF;
}

/* 800A07F4-800A0858       .text GetGrpSoundId__4dBgSFR13cBgS_PolyInfo */
s32 dBgS::GetGrpSoundId(cBgS_PolyInfo& polyInfo) {
    s32 grp_id = GetTriGrp(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex());
    if (grp_id == -1)
        return -1;
    return (GetGrpInf(polyInfo, grp_id) >> 11) & 0xFF;
}

/* 800A0858-800A08C0       .text ChkGrpInf__4dBgSFR13cBgS_PolyInfoUl */
u32 dBgS::ChkGrpInf(cBgS_PolyInfo& polyInfo, u32 mask) {
    s32 grp_id = GetTriGrp(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex());
    if (grp_id == -1)
        return 0;

    u32 inf = GetGrpInf(polyInfo, grp_id);
    return inf & mask;
}

/* 800A08C0-800A0A5C       .text GetPolyId1__4dBgSFiiiUlUl */
int dBgS::GetPolyId1(int bg_index, int poly_index, int defv, u32 mask, u32 shift) {
    JUT_ASSERT(0x414, 0 <= bg_index && bg_index < 256);
    if (!m_chk_element[bg_index].ChkUsed())
        return defv;

    dBgW* bgwp = (dBgW*)m_chk_element[bg_index].m_bgw_base_ptr;
    u32 inf_id = bgwp->GetPolyInfId(poly_index);
    return (bgwp->GetPolyInf1(inf_id) & mask) >> shift;
}

/* 800A0A5C-800A0A94       .text GetLinkNo__4dBgSFR13cBgS_PolyInfo */
int dBgS::GetLinkNo(cBgS_PolyInfo& polyInfo) {
    return GetPolyId1(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0xFF, 0x000000FF, 0);
}

/* 800A0A94-800A0ACC       .text GetWallCode__4dBgSFR13cBgS_PolyInfo */
int dBgS::GetWallCode(cBgS_PolyInfo& polyInfo) {
    return GetPolyId1(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0x00, 0x00000F00, 8);
}

/* 800A0ACC-800A0B08       .text GetSpecialCode__4dBgSFR13cBgS_PolyInfo */
int dBgS::GetSpecialCode(cBgS_PolyInfo& polyInfo) {
    return GetPolyId1(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0x00, 0x0000F000, 12);
}

/* 800A0B08-800A0B28       .text dBgS_ChangeAttributeCode__FUlPUl */
void dBgS_ChangeAttributeCode(u32 code, u32* dst) {
    *dst &= 0xFFE0FFFF;
    *dst |= code << 16;
}

/* 800A0B28-800A0B60       .text GetAttributeCodeDirect__4dBgSFR13cBgS_PolyInfo */
s32 dBgS::GetAttributeCodeDirect(cBgS_PolyInfo& polyInfo) {
    return GetPolyId1(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0x00, 0x001F0000, 16);
}

static s32 atr_conv[0x20] = {
    /* 0x00 */ dBgS_Attr_NORMAL_e,
    /* 0x01 */ dBgS_Attr_DIRT_e,
    /* 0x02 */ dBgS_Attr_WOOD_e,
    /* 0x03 */ dBgS_Attr_STONE_e,
    /* 0x04 */ dBgS_Attr_GRASS_e,
    /* 0x05 */ dBgS_Attr_GIANT_FLOWER_e,
    /* 0x06 */ dBgS_Attr_LAVA_e,
    /* 0x07 */ dBgS_Attr_DIRT_e,
    /* 0x08 */ dBgS_Attr_VOID_e,
    /* 0x09 */ dBgS_Attr_DAMAGE_e,
    /* 0x0A */ dBgS_Attr_CARPET_e,
    /* 0x0B */ dBgS_Attr_SAND_e,
    /* 0x0C */ dBgS_Attr_WOOD_e,
    /* 0x0D */ dBgS_Attr_WOOD_e,
    /* 0x0E */ dBgS_Attr_WOOD_e,
    /* 0x0F */ dBgS_Attr_ICE_e,
    /* 0x10 */ dBgS_Attr_WOOD_e,
    /* 0x11 */ dBgS_Attr_METAL_e,
    /* 0x12 */ dBgS_Attr_DIRT_e,
    /* 0x13 */ dBgS_Attr_WATER_e,
    /* 0x14 */ dBgS_Attr_METAL_e,
    /* 0x15 */ dBgS_Attr_FREEZE_e,
    /* 0x16 */ dBgS_Attr_ELECTRICITY_e,
    /* 0x17 */ dBgS_Attr_WATERFALL_e,
    /* 0x18 */ dBgS_Attr_METAL_e,
    /* 0x19 */ dBgS_Attr_CARPET_e,
    /* 0x1A */ dBgS_Attr_WOOD_e,
    /* 0x1B */ dBgS_Attr_NORMAL_e,
    /* 0x1C */ dBgS_Attr_NORMAL_e,
    /* 0x1D */ dBgS_Attr_NORMAL_e,
    /* 0x1E */ dBgS_Attr_NORMAL_e,
    /* 0x1F */ dBgS_Attr_NORMAL_e,
};

/* 800A0B60-800A0BA8       .text GetAttributeCode__4dBgSFR13cBgS_PolyInfo */
s32 dBgS::GetAttributeCode(cBgS_PolyInfo& polyInfo) {
    s32 attr = GetAttributeCodeDirect(polyInfo);
    if (attr < 0 || attr >= (int)ARRAY_SIZE(atr_conv))
        return 0;
    return atr_conv[attr];
}

/* 800A0BA8-800A0BE0       .text GetGroundCode__4dBgSFR13cBgS_PolyInfo */
int dBgS::GetGroundCode(cBgS_PolyInfo& polyInfo) {
    return GetPolyId1(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0x00, 0x03E00000, 21);
}

/* 800A0BE0-800A0D7C       .text GetPolyId2__4dBgSFiiiUlUl */
int dBgS::GetPolyId2(int bg_index, int poly_index, int defv, u32 mask, u32 shift) {
    JUT_ASSERT(0x4c1, 0 <= bg_index && bg_index < 256);
    if (!m_chk_element[bg_index].ChkUsed())
        return defv;

    dBgW* bgwp = (dBgW*)m_chk_element[bg_index].m_bgw_base_ptr;
    u32 inf_id = bgwp->GetPolyInfId(poly_index);
    return (bgwp->GetPolyInf2(inf_id) & mask) >> shift;
}

/* 800A0D7C-800A0DB4       .text GetCamMoveBG__4dBgSFR13cBgS_PolyInfo */
int dBgS::GetCamMoveBG(cBgS_PolyInfo& polyInfo) {
    return GetPolyId2(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0xFF, 0x000000FF, 0);
}

/* 800A0DB4-800A0DF0       .text GetRoomCamId__4dBgSFR13cBgS_PolyInfo */
int dBgS::GetRoomCamId(cBgS_PolyInfo& polyInfo) {
    return GetPolyId2(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0xFF, 0x0000FF00, 8);
}

/* 800A0DF0-800A0E28       .text GetRoomPathId__4dBgSFR13cBgS_PolyInfo */
int dBgS::GetRoomPathId(cBgS_PolyInfo& polyInfo) {
    return GetPolyId2(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0xFF, 0x00FF0000, 16);
}

/* 800A0E28-800A0E30       .text dBgS_GetRoomPathPntNo__FUl */
u32 dBgS_GetRoomPathPntNo(u32 param) {
    return param >> 24;
}

/* 800A0E30-800A0E68       .text GetRoomPathPntNo__4dBgSFR13cBgS_PolyInfo */
int dBgS::GetRoomPathPntNo(cBgS_PolyInfo& polyInfo) {
    return GetPolyId2(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex(), 0xFF, 0xFF000000, 24);
}

/* 800A0E68-800A0F88       .text GetRoomId__4dBgSFR13cBgS_PolyInfo */
s32 dBgS::GetRoomId(cBgS_PolyInfo& polyInfo) {
    if (!polyInfo.ChkSetInfo())
        return -1;

    s32 id = polyInfo.GetBgIndex();
    JUT_ASSERT(0x51b, 0 <= id && id < 256);

    if (!ChkPolySafe(polyInfo))
        return -1;

    dBgW* bgwp = (dBgW*)m_chk_element[id].m_bgw_base_ptr;
    s32 roomNo = bgwp->mRoomNo;
    if (roomNo == 0xFFFF) {
        s32 grp = GetTriGrp(polyInfo.GetBgIndex(), polyInfo.GetPolyIndex());
        roomNo = GetGrpToRoomId(polyInfo.GetBgIndex(), grp);
        if (roomNo == 0xFFFF)
            return -1;
    }
    return roomNo;
}

/* 800A0F88-800A111C       .text ChkPolyHSStick__4dBgSFR13cBgS_PolyInfo */
u32 dBgS::ChkPolyHSStick(cBgS_PolyInfo& polyInfo) {
    s32 bg_index = (u16)polyInfo.GetBgIndex();
    JUT_ASSERT(0x583, 0 <= bg_index && bg_index < 256);
    if (!m_chk_element[bg_index].ChkUsed())
        return FALSE;

    dBgW* bgwp = (dBgW*)m_chk_element[bg_index].m_bgw_base_ptr;
    u32 inf_id = bgwp->GetPolyInfId(polyInfo.GetPolyIndex());
    return (bgwp->GetPolyInf3(inf_id) & 0x10);
}

/* 800A111C-800A12A4       .text LineCrossNonMoveBG__4dBgSFP11cBgS_LinChk */
bool dBgS::LineCrossNonMoveBG(cBgS_LinChk* chk) {
    bool ret = false;
    chk->ClearPi();
    chk->ClrHit();
    for (s32 bg_index = 0; bg_index < (s32)ARRAY_SIZE(m_chk_element); bg_index++) {
        cBgS_ChkElm* elm = &m_chk_element[bg_index];
        if (elm->ChkUsed() && elm->m_bgw_base_ptr->GetVtxTbl() != NULL && !chk->ChkSameActorPid(elm->m_actor_id) && !elm->m_bgw_base_ptr->ChkMoveBg()) {
            chk->PreCalc();
            if (elm->m_bgw_base_ptr->LineCheckGrpRp(chk, elm->m_bgw_base_ptr->m_rootGrpIdx, 1)) {
                chk->SetActorInfo(bg_index, elm->m_bgw_base_ptr, elm->m_actor_id);
                ret = true;
            }
        }
    }
    if (ret)
        chk->SetHit();
    return ret;
}

/* 800A12A4-800A13E0       .text WallCorrect__4dBgSFP9dBgS_Acch */
void dBgS::WallCorrect(dBgS_Acch* acch) {
    acch->CalcWallRR();
    acch->SetWallCir();
    acch->SetLin();
    acch->CalcWallBmdCyl();

    cBgS_ChkElm* elm;
    for (s32 prio = 0; prio < 3; prio++) {
        for (s32 bg_index = 0; bg_index < (s32)ARRAY_SIZE(m_chk_element); bg_index++) {
            elm = &m_chk_element[bg_index];
            if (elm->ChkUsed() && elm->m_bgw_base_ptr->GetVtxTbl() != NULL) {
                acch->SetNowActorInfo(bg_index, elm->m_bgw_base_ptr, elm->m_actor_id);
                if (!acch->ChkSameActorPid(elm->m_actor_id)) {
                    dBgW* bgwp = (dBgW*)elm->m_bgw_base_ptr;
                    if (bgwp->ChkPriority(prio))
                        bgwp->WallCorrectGrpRp(acch, bgwp->m_rootGrpIdx, 1);
                }
            }
        }
    }
}

/* 800A13E0-800A14FC       .text RoofChk__4dBgSFP12dBgS_RoofChk */
f32 dBgS::RoofChk(dBgS_RoofChk* chk) {
    chk->SetNowY(1e+09f);
    chk->ClearPi();
    cBgS_ChkElm* elm;
    for (s32 bg_index = 0; bg_index < (s32)ARRAY_SIZE(m_chk_element); bg_index++) {
        elm = &m_chk_element[bg_index];
        if (elm->ChkUsed() && elm->m_bgw_base_ptr->GetVtxTbl() != NULL && !chk->ChkSameActorPid(elm->m_actor_id)) {
            dBgW* bgwp = (dBgW*)elm->m_bgw_base_ptr;
            if (bgwp->RoofChkGrpRp(chk, elm->m_bgw_base_ptr->m_rootGrpIdx, 1)) {
                chk->SetActorInfo(bg_index, elm->m_bgw_base_ptr, elm->m_actor_id);
            }
        }
    }
    return chk->GetNowY();
}

/* 800A14FC-800A160C       .text SplGrpChk__4dBgSFP14dBgS_SplGrpChk */
bool dBgS::SplGrpChk(dBgS_SplGrpChk* chk) {
    bool ret = false;
    chk->Init();
    for (s32 bg_index = 0; bg_index < (s32)ARRAY_SIZE(m_chk_element); bg_index++) {
        cBgS_ChkElm* elm = &m_chk_element[bg_index];
        if (elm->ChkUsed() && elm->m_bgw_base_ptr->GetVtxTbl() != NULL && !chk->ChkSameActorPid(elm->m_actor_id)) {
            dBgW* bgwp = (dBgW*)elm->m_bgw_base_ptr;
            if (bgwp->SplGrpChkGrpRp(chk, elm->m_bgw_base_ptr->m_rootGrpIdx, 1)) {
                ret = true;
                chk->SetActorInfo(bg_index, elm->m_bgw_base_ptr, elm->m_actor_id);
                chk->OnFind();
            }
        }
    }
    return ret;
}

/* 800A160C-800A1730       .text SphChk__4dBgSFP11dBgS_SphChkPv */
bool dBgS::SphChk(dBgS_SphChk* chk, void* user) {
    cBgS_ChkElm* elm;
    bool ret = false;
    chk->Init();
    for (s32 bg_index = 0; bg_index < (s32)ARRAY_SIZE(m_chk_element); bg_index++) {
        elm = &m_chk_element[bg_index];
        if (elm->ChkUsed() && elm->m_bgw_base_ptr->GetVtxTbl() != NULL && !chk->ChkSameActorPid(elm->m_actor_id)) {
            dBgW* bgwp = (dBgW*)elm->m_bgw_base_ptr;
            if (bgwp->SphChkGrpRp(chk, user, elm->m_bgw_base_ptr->m_rootGrpIdx, 1)) {
                chk->SetActorInfo(bg_index, elm->m_bgw_base_ptr, elm->m_actor_id);
                ret = true;
            }
        }
    }
    return ret;
}

/* 800A1730-800A1954       .text WallCrrPos__4dBgSFP11dBgS_CrrPos */
bool dBgS::WallCrrPos(dBgS_CrrPos* crr) {
    crr->SetOldCyl();
    crr->SetCyl();
    crr->SetLin();
    crr->ClrPosVec();
    
    cBgS_ChkElm* elm;
    bool ret = false;
    for (s32 prio = 0; prio < 3; prio++) {
        for (s32 bg_index = 0; bg_index < (s32)ARRAY_SIZE(m_chk_element); bg_index++) {
            elm = &m_chk_element[bg_index];
            if (elm->ChkUsed() && elm->m_bgw_base_ptr->GetVtxTbl() != NULL) {
                if (crr->ChkSameActorPid(elm->m_actor_id))
                    continue;
                dBgW* bgwp = (dBgW*)elm->m_bgw_base_ptr;
                BOOL isPrio = bgwp->ChkPriority(prio);
                if (isPrio && bgwp->WallCrrPos(crr)) {
                    crr->SetWallActorInfo(bg_index, elm->m_bgw_base_ptr, elm->m_actor_id);
                    crr->GetPos()->x += crr->GetPosVec().x;
                    crr->GetPos()->y += crr->GetPosVec().y;
                    crr->GetPos()->z += crr->GetPosVec().z;
                    ret = true;
                }
            }
        }
    }
    return ret;
}

/* 800A1954-800A1A74       .text MoveBgCrrPos__4dBgSFR13cBgS_PolyInfobP4cXyzP5csXyzP5csXyz */
void dBgS::MoveBgCrrPos(cBgS_PolyInfo& polyInfo, bool accept, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
    if (!accept || !polyInfo.ChkBgIndex())
        return;

    s32 bg_index = polyInfo.GetBgIndex();
    JUT_ASSERT(1911, 0 <= bg_index && bg_index < 256);

    if (m_chk_element[bg_index].ChkUsed()) {
        dBgW* bgwp = (dBgW*)m_chk_element[bg_index].m_bgw_base_ptr;
        if (bgwp->mFlag & 1 && ChkPolySafe(polyInfo)) {
            bgwp->CrrPos(polyInfo, m_chk_element[bg_index].m_actor_ptr, accept, pos, angle, shape_angle);
        }
    }
}

/* 800A1A74-800A1B94       .text MoveBgTransPos__4dBgSFR13cBgS_PolyInfobP4cXyzP5csXyzP5csXyz */
void dBgS::MoveBgTransPos(cBgS_PolyInfo& polyInfo, bool accept, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
    if (!accept || !polyInfo.ChkBgIndex())
        return;

    s32 bg_index = polyInfo.GetBgIndex();
    JUT_ASSERT(1956, 0 <= bg_index && bg_index < 256);

    if (m_chk_element[bg_index].ChkUsed()) {
        dBgW* bgwp = (dBgW*)m_chk_element[bg_index].m_bgw_base_ptr;
        if (bgwp->mFlag & 1 && ChkPolySafe(polyInfo)) {
            bgwp->TransPos(polyInfo, m_chk_element[bg_index].m_actor_ptr, accept, pos, angle, shape_angle);
        }
    }
}

/* 800A1B94-800A1C98       .text MoveBgMatrixCrrPos__4dBgSFR13cBgS_PolyInfobP4cXyzP5csXyzP5csXyz */
void dBgS::MoveBgMatrixCrrPos(cBgS_PolyInfo& polyInfo, bool accept, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
    if (!accept || !polyInfo.ChkBgIndex())
        return;

    s32 bg_index = polyInfo.GetBgIndex();
    JUT_ASSERT(1999, 0 <= bg_index && bg_index < 256);

    if (m_chk_element[bg_index].ChkUsed()) {
        dBgW* bgwp = (dBgW*)m_chk_element[bg_index].m_bgw_base_ptr;
        if (bgwp->mFlag & 1) {
            bgwp->MatrixCrrPos(polyInfo, m_chk_element[bg_index].m_actor_ptr, accept, pos, angle, shape_angle);
        }
    }
}

/* 800A1C98-800A1D18       .text dBgS_MoveBGProc_Typical__FP4dBgWPvR13cBgS_PolyInfobP4cXyzP5csXyzP5csXyz */
void dBgS_MoveBGProc_Typical(dBgW* pbgw, void* user, cBgS_PolyInfo& polyInfo, bool accept, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
    Mtx inv;
    if (MTXInverse(pbgw->mOldMtx, inv)) {
        cXyz local, newPos;
        MTXMultVec(inv, pos, &local);
        MTXMultVec(*pbgw->GetBaseMtxP(), &local, &newPos);
        *pos = newPos;
    }
}

/* 800A1D18-800A1D4C       .text dBgS_MoveBGProc_RotY__FP4dBgWPvR13cBgS_PolyInfobP4cXyzP5csXyzP5csXyz */
void dBgS_MoveBGProc_RotY(dBgW* pbgw, void* user, cBgS_PolyInfo& polyInfo, bool accept, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
    if (shape_angle == NULL)
        return;

    s32 rot = pbgw->mRotYDelta;
    if (shape_angle != NULL)
        shape_angle->y += rot;
    if (angle != NULL)
        angle->y += rot;
}

/* 800A1D4C-800A1DB8       .text dBgS_MoveBGProc_TypicalRotY__FP4dBgWPvR13cBgS_PolyInfobP4cXyzP5csXyzP5csXyz */
void dBgS_MoveBGProc_TypicalRotY(dBgW* pbgw, void* user, cBgS_PolyInfo& polyInfo, bool accept, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
    dBgS_MoveBGProc_Typical(pbgw, user, polyInfo, accept, pos, angle, shape_angle);
    dBgS_MoveBGProc_RotY(pbgw, user, polyInfo, accept, pos, angle, shape_angle);
}

/* 800A1DB8-800A1DF8       .text dBgS_MoveBGProc_Trans__FP4dBgWPvR13cBgS_PolyInfobP4cXyzP5csXyzP5csXyz */
void dBgS_MoveBGProc_Trans(dBgW* pbgw, void*, cBgS_PolyInfo& polyInfo, bool, cXyz* pos, csXyz* angle, csXyz* shape_angle) {
    cXyz trans;
    pbgw->GetTrans(&trans);
    VECAdd(pos, &trans, pos);
}

/* 800A1DF8-800A1ED0       .text RideCallBack__4dBgSFR13cBgS_PolyInfoP10fopAc_ac_c */
void dBgS::RideCallBack(cBgS_PolyInfo& polyInfo, fopAc_ac_c* ac) {
    s32 bg_index = polyInfo.GetBgIndex();
    JUT_ASSERT(0x881, 0 <= bg_index && bg_index < 256);

    dBgW* bgwp = (dBgW*)m_chk_element[bg_index].m_bgw_base_ptr;
    if (bgwp->ChkUsed() && bgwp->mpRideCb != NULL)
        bgwp->mpRideCb(bgwp, m_chk_element[bg_index].m_actor_ptr, ac);
}

/* 800A1ED0-800A1FD8       .text PushPullCallBack__4dBgSFR13cBgS_PolyInfoP10fopAc_ac_csQ24dBgW13PushPullLabel */
fopAc_ac_c* dBgS::PushPullCallBack(cBgS_PolyInfo& polyInfo, fopAc_ac_c* ac, s16 inf, dBgW::PushPullLabel lbl) {
    s32 bg_index = polyInfo.GetBgIndex();
    JUT_ASSERT(0x8a2, 0 <= bg_index && bg_index < 256);

    dBgW* bgwp = (dBgW*)m_chk_element[bg_index].m_bgw_base_ptr;
    if (!bgwp->ChkUsed())
        return NULL;
    if (m_chk_element[bg_index].m_actor_ptr == NULL)
        return NULL;
    if (bgwp->mpPushPullCb == NULL)
        return NULL;
    return bgwp->mpPushPullCb(m_chk_element[bg_index].m_actor_ptr, ac, inf, lbl);
}

/* 800A1FD8-800A2550       .text CrrPos__11dBgS_CrrPosFR4dBgS */
void dBgS_CrrPos::CrrPos(dBgS& i_bgs) {
    if (mFlag & 1)
        return;
    
    ClrWallHit();
    ClrXCrr();
    ClrZCrr();
    CHECK_PVEC3_RANGE(2280, pm_pos);
    
    if (!(mFlag & 4)) {
        f32 dist2 = GetOldPos()->abs2(*pm_pos);
        bool inWall = false;
        if (dist2 > (0.65f*0.65f * GetWallR()*GetWallR())) {
            inWall = true;
            
            cBgS_LinChk linChk;
            cXyz startPos(*pm_old_pos);
            cXyz endPos(*pm_pos);
            startPos.y += GetWallH();
            endPos.y += GetWallH();
            linChk.Set2(&startPos, &endPos, GetActorPid());
            linChk.SetExtChk(*this);
            linChk.SetSttsGroundOff();
            
            if (i_bgs.LineCross(&linChk)) {
                *pm_pos = linChk.GetCross();
                cM3dGPla* plane = i_bgs.GetTriPla(linChk);
                pm_pos->x += plane->GetNP()->x;
                pm_pos->y += plane->GetNP()->y - mWallHeight;
                pm_pos->z += plane->GetNP()->z;
            }
        }
        
        if (i_bgs.WallCrrPos(this) && inWall) {
            cBgS_LinChk linChk;
            cXyz startPos(*pm_old_pos);
            cXyz endPos(*pm_pos);
            startPos.y += mWallHeight;
            endPos.y += mWallHeight;
            linChk.Set2(&startPos, &endPos, GetActorPid());
            linChk.SetExtChk(*this);
            linChk.SetSttsGroundOff();
            
            if (i_bgs.LineCross(&linChk)) {
                *pm_pos = linChk.GetCross();
                cM3dGPla* plane = i_bgs.GetTriPla(linChk);
                pm_pos->x += plane->GetNP()->x;
                pm_pos->y += plane->GetNP()->y - mWallHeight;
                pm_pos->z += plane->GetNP()->z;
            }
        }
    }
    
    if (!(mFlag & 2)) {
        field_0x60 = 0;
        mGndChk.SetExtChk(*this);
        cXyz pos = *pm_pos;
        pos.y += mGndUpY;
        mGndChk.SetPos(&pos);
        f32 f31 = pm_pos->y;
        mGroundH = i_bgs.GroundCross(&mGndChk);
        if (mGroundH != -1e+09f && mGroundH > f31) {
            pm_pos->y = mGroundH;
            if (field_0x58) {
                field_0x58->y = 0.0f;
            }
            field_0x60 = 1;
        }
    }
}
