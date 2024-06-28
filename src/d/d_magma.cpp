//
// Generated by dtk
// Translation Unit: d_magma.cpp
//

#include "d/d_magma.h"
#include "d/d_com_inf_game.h"
#include "d/d_path.h"
#include "d/res/res_magma.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_lib.h"
#include "JSystem/JKernel/JKRHeap.h"

Mtx l_kuroOrthoMtx;
Mtx l_colOrthoMtx;
GXTexObj dMagma_packet_c::mKuroTexObj;
Mtx dMagma_packet_c::mKuroMtx;
GXTexObj dMagma_packet_c::mColTexObj;
Mtx dMagma_packet_c::mFloorMtx;
Mtx dMagma_packet_c::mBallMtx;

Vec l_YfloorPos[4] = {};
u8 l_YfloorDL[0x27] = {};
u8 l_YfloorMatDL[0x55] = {};
Vec l_YballPos[0x21] = {};
u8 l_YballMatDL[0x4b] = {};

/* 800755A4-800756B8       .text draw__13dMagma_ball_cFv */
void dMagma_ball_c::draw() {
    /* Nonmatching */
}

/* 800756B8-800757D4       .text rangeCheck__13dMagma_ball_cFR4cXyzPf */
BOOL dMagma_ball_c::rangeCheck(cXyz&, f32*) {
    /* Nonmatching */
}

/* 800757D4-80075878       .text calc__17dMagma_ballPath_cFfUci */
void dMagma_ballPath_c::calc(float, unsigned char, int) {
    /* Nonmatching */
}

/* 80075878-800758B4       .text update__17dMagma_ballPath_cFv */
void dMagma_ballPath_c::update() {
    /* Nonmatching */
}

/* 800758B4-80075A6C       .text setup__17dMagma_ballPath_cFfUci */
void dMagma_ballPath_c::setup(float, unsigned char, int) {
    /* Nonmatching */
}

/* 80075A6C-80075CB8       .text draw__14dMagma_floor_cFv */
void dMagma_floor_c::draw() {
    GXSetArray(GX_VA_POS, l_YfloorPos, sizeof(*l_YfloorPos));
    GXLoadTexMtxImm(mTexMtx0, GX_TEXMTX2, GX_MTX3x4);
    GXLoadTexMtxImm(dMagma_packet_c::mKuroMtx, (u32)GX_PTTEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX2, GX_FALSE, GX_PTTEXMTX0);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, GXGetTexObjWidth(&dMagma_packet_c::mKuroTexObj), GXGetTexObjHeight(&dMagma_packet_c::mKuroTexObj));
    GXSetTexCoordBias(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
    GXCallDisplayList(&l_YfloorMatDL, 0x40);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXLoadPosMtxImm(mPosMtx, GX_PNMTX0);
    GXCallDisplayList(&l_YfloorDL, 0x20);
    GXSetArray(GX_VA_POS, l_YballPos, sizeof(*l_YballPos));
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXA, GX_CC_HALF, GX_CC_ONE, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_COMP_RGB8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_TEXC, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXCallDisplayList(l_YballMatDL, 0x40);
    GXLoadTexMtxImm(mBallPostMtx0, (u32)GX_PTTEXMTX1, GX_MTX3x4);

    dMagma_ball_c** ball = &mpBalls[0];
    for (s32 i = 0; i < mBallNum; ball++, i++)
        (*ball)->draw();
}

/* 80075CB8-80075DD8       .text calc__14dMagma_floor_cFi */
void dMagma_floor_c::calc(int i_roomNo) {
    mDoMtx_stack_c::scaleS(1.0f, 0.05f, 1.0f);
    if (strcmp(dComIfGp_getStartStageName(), "MDrag_B") == 0 || strcmp(dComIfGp_getStartStageName(), "Xboss0") == 0)
        mDoMtx_stack_c::transM(0.0f, -(mBallPos.y + 20.0f), 0.0f);
    else
        mDoMtx_stack_c::transM(0.0f, -(mBallPos.y + 30.0f), 0.0f);
    mDoMtx_concat(l_colOrthoMtx, mDoMtx_stack_c::get(), mBallPostMtx0);
    dMagma_ball_c** ball = &mpBalls[0];
    for (s32 i = 0; i < mBallNum; ball++, i++)
        (*ball)->calc(mBallPos.y, mPathNo, i_roomNo);
}

/* 80075DD8-80075E50       .text update__14dMagma_floor_cFv */
void dMagma_floor_c::update() {
    mDoMtx_concat(j3dSys.getViewMtx(), mTexMtx0, mPosMtx);
    dMagma_ball_c** ball = &mpBalls[0];
    for (s32 i = 0; i < mBallNum; ball++, i++)
        (*ball)->update();
}

/* 80075E50-80076038       .text create__14dMagma_floor_cFR4cXyzR4cXyzsUci */
dMagma_ball_c** dMagma_floor_c::create(cXyz&, cXyz&, short, unsigned char, int) {
    /* Nonmatching */
}

/* 80076038-80076080       .text __dt__13dMagma_ball_cFv */
dMagma_ball_c::~dMagma_ball_c() {
}

/* 80076080-80076100       .text remove__14dMagma_floor_cFv */
void dMagma_floor_c::remove() {
    dMagma_ball_c** ball = &mpBalls[0];
    for (s32 i = 0; i < mBallNum; ball++, i++)
        delete *ball;

    delete mpBalls;
    mpBalls = NULL;
}

/* 80076100-80076110       .text newFloor__13dMagma_room_cFP14dMagma_floor_c */
void dMagma_room_c::newFloor(dMagma_floor_c* floor) {
    floor->mpNext = mpFirst;
    mpFirst = floor;
}

/* 80076110-80076158       .text deleteFloor__13dMagma_room_cFv */
void dMagma_room_c::deleteFloor() {
    while (mpFirst != NULL) {
        mpFirst->remove();
        mpFirst = mpFirst->mpNext;
    }
}

/* 80076158-800762D0       .text __ct__15dMagma_packet_cFv */
dMagma_packet_c::dMagma_packet_c() {
    dComIfG_setObjectRes("Magma", JKRArchive::DEFAULT_MOUNT_DIRECTION, NULL);

    ResTIMG* kuro = (ResTIMG*)dComIfG_getObjectRes("Magma", MAGMA_BTI_MAG_KURO);
    mDoLib_setResTimgObj(kuro, &mKuroTexObj, 0, NULL);

    C_MTXLightOrtho(l_kuroOrthoMtx, 1.0f, -1.0f, -1.0f, 1.0f, 0.5f, -0.5f, 0.5f, 0.5f);
    mDoMtx_copy(l_kuroOrthoMtx, l_colOrthoMtx);

    ResTIMG* col = (ResTIMG*)dComIfG_getObjectRes("Magma", MAGMA_BTI_MAG_COL);
    mDoLib_setResTimgObj(col, &mColTexObj, 0, NULL);
    mDoMtx_identity(mFloorMtx);
    mDoMtx_identity(mBallMtx);
    mTimer = 0.0f;
}

/* 800762D0-800762DC       .text __ct__13dMagma_room_cFv */
dMagma_room_c::dMagma_room_c() : mpFirst() {
}

/* 800762DC-80076318       .text __dt__14dMagma_floor_cFv */
dMagma_floor_c::~dMagma_floor_c() {
}

/* 80076318-80076324       .text __ct__14dMagma_floor_cFv */
dMagma_floor_c::dMagma_floor_c() {
    mpBalls = NULL;
}

/* 80076324-800763CC       .text __dt__15dMagma_packet_cFv */
dMagma_packet_c::~dMagma_packet_c() {
    dComIfG_deleteObjectRes("Magma");
}

/* 800763CC-800764EC       .text draw__15dMagma_packet_cFv */
void dMagma_packet_c::draw() {
    j3dSys.reinitGX();
    GXSetNumIndStages(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXLoadTexObj(&mKuroTexObj, GX_TEXMAP0);
    GXLoadTexObj(&mColTexObj, GX_TEXMAP1);
    dKy_GxFog_set();
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_GREATER, 0);
    GXSetTevColor(GX_TEVREG1, mColor1);
    GXSetCurrentMtx(GX_PNMTX0);

    dMagma_floor_c* floor = &mFloor[0];
    for (s32 i = 0; i < 8; i++, floor++) {
        if (floor->mpBalls != NULL)
            floor->draw();
    }

    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_FALSE, 0, 0);
    J3DShape::resetVcdVatCache();
}

/* 800764EC-800764FC       .text morfCalc__Ffff */
f32 morfCalc(f32 min, f32 max, f32 v) {
    return (max - min) * v + min;
}

/* 800764FC-80076770       .text calc__15dMagma_packet_cFv */
void dMagma_packet_c::calc() {
    /* Nonmatching */
    l_kuroOrthoMtx[0][3] += 0.001f;
    if (l_kuroOrthoMtx[0][3] >= 1.5f)
        l_kuroOrthoMtx[0][3] -= 1.0f;
    l_kuroOrthoMtx[1][3] = l_kuroOrthoMtx[0][3];

    mDoMtx_stack_c::scaleS(0.0022f, 0.0018f, 0.0017f);
    mDoMtx_stack_c::XrotM(0x4000);
    mDoMtx_concat(l_kuroOrthoMtx, mDoMtx_stack_c::get(), mKuroMtx);

    dMagma_room_c* room = mRoom;
    for (s32 i = 0; i < ARRAY_SIZE(mRoom); i++, room++)
        for (dMagma_floor_c* floor = room->mpFirst; floor != NULL; floor = floor->mpNext)
            if (floor->mpBalls != NULL)
                floor->calc(i);

    mTimer += 1.0f;
    if (mTimer >= 119.0f)
        mTimer -= 119.0f;

    static GXColor l_keyColor[] = {
        { 0x00, 0x00, 0x00, 0x00 },
        { 0xFF, 0x96, 0x00, 0x3C },
        { 0x00, 0x00, 0x00, 0x77 },
    };

    GXColor* color = &l_keyColor[1];
    for (s32 i = 1; i < ARRAY_SIZE(l_keyColor); i++, color++) {
        if (mTimer < color->a)
            break;
    }

    GXColor* color0 = &color[0];
    GXColor* color1 = &color[1];

    f32 t = (mTimer - color0->a) / (color1->a - color0->a);
    mColor1.r = morfCalc(color0->r, color1->r, t);
    mColor1.g = morfCalc(color0->g, color1->g, t);
    mColor1.b = morfCalc(color0->b, color1->b, t);
}

/* 80076770-800767E4       .text update__15dMagma_packet_cFv */
void dMagma_packet_c::update() {
    dMagma_floor_c* floor = &mFloor[0];
    for (s32 i = 0; i < 8; i++, floor++) {
        if (floor->mpBalls != NULL)
            floor->update();
    }
    j3dSys.getDrawBuffer(0)->entryImm(this, 0);
}

/* 800767E4-80076924       .text checkYpos__15dMagma_packet_cFR4cXyz */
f32 dMagma_packet_c::checkYpos(cXyz& pos) {
    /* Nonmatching */
    f32 ret = -100000000.0f;
    dMagma_floor_c* floor = mFloor;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mFloor); floor++, i++) {
        dMagma_ball_c** ball = floor->mpBalls;
        if (ball == NULL)
            continue;

        if (fabsf(pos.y - floor->mBallPos.y) <= 236.8309f && fabsf(pos.x - floor->mBallPos.x) <= floor->mDistX * 500.0f && fabsf(pos.z - floor->mBallPos.z) <= floor->mDistZ * 500.0f) {
            for (s32 j = 0; j < floor->mBallNum; ball++, j++) {
                f32 y;
                if ((*ball)->rangeCheck(pos, &y)) {
                    if (y < floor->mBallPos.y)
                        y = floor->mBallPos.y;

                    if (y > ret)
                        ret = y;
                }
            }
        }
    }

    return ret;
}

/* 80076924-80076AA4       .text newFloor__15dMagma_packet_cFR4cXyzR4cXyzis */
dMagma_floor_c* dMagma_packet_c::newFloor(cXyz& p0, cXyz& p1, int i_roomNo, s16 i_pathNo) {
    JUT_ASSERT(0x36e, 0 <= i_roomNo && i_roomNo < 64);

    dMagma_floor_c* floor = mFloor;
    for (s32 i = 0; i < ARRAY_SIZE(mFloor); i++, floor++) {
        if (floor->mpBalls == NULL) {
            s32 param = 0;
            if (i_pathNo < 0) {
                param = -i_pathNo;
            } else {
                dPath* path = dPath_GetRoomPath(i_pathNo, i_roomNo);
                if (path == NULL)
                    return NULL;

                dPath__Point* pnt = path->mpPnt;
                for (s32 j = 0; j < path->m_num; j++)
                    param += (s32)(pnt->mArg3 * 4.0f); // bug? forgot to increment pnt
            }

            dMagma_ball_c** balls = floor->create(p0, p1, i_pathNo, param, i_roomNo);
            if (balls == NULL)
                return NULL;

            mRoom[i_roomNo].newFloor(floor);
            return floor;
        }
    }

    return NULL;
}

/* 80076AA4-80076B00       .text __dt__17dMagma_ballPath_cFv */
dMagma_ballPath_c::~dMagma_ballPath_c() {
    /* Nonmatching */
}

