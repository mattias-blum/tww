/**
 * d_a_demo_item.cpp
 * Item - Cutscene Item
 */

#include "d/actor/d_a_demo_item.h"
#include "d/d_procname.h"
#include "d/d_drawlist.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "d/d_item.h"
#include "m_Do/m_Do_mtx.h"
#include "f_op/f_op_camera.h"

static u8 dummy[0x4C]; // TODO

const int daDitem_c::m_rot_time = 8*30;

u8 daDitem_c::m_effect_type[0x100] = {
    /* HEART            */ 0x04,
    /* GREEN_RUPEE      */ 0x03,
    /* BLUE_RUPEE       */ 0x03,
    /* YELLOW_RUPEE     */ 0x03,
    /* RED_RUPEE        */ 0x03,
    /* PURPLE_RUPEE     */ 0x03,
    /* ORANGE_RUPEE     */ 0x03,
    /* KAKERA_HEART     */ 0x00,
    /* UTUWA_HEART      */ 0x00,
    /* S_MAGIC          */ 0x04,
    /* L_MAGIC          */ 0x04,
    /* BOMB_5           */ 0x04,
    /* BOMB_10          */ 0x04,
    /* BOMB_20          */ 0x04,
    /* BOMB_30          */ 0x04,
    /* SILVER_RUPEE     */ 0x03,
    /* ARROW_10         */ 0x04,
    /* ARROW_20         */ 0x04,
    /* ARROW_30         */ 0x04,
    /* noentry19        */ 0x04,
    /* noentry20        */ 0x04,
    /* SMALL_KEY        */ 0x02,
    /* RECOVER_FAIRY    */ 0x04,
    /* noentry23        */ 0x04,
    /* noentry24        */ 0x04,
    /* noentry25        */ 0x04,
    /* SUB_DUN_RUPEE    */ 0x03,
    /* noentry27        */ 0x04,
    /* noentry28        */ 0x04,
    /* noentry29        */ 0x04,
    /* TRIPLE_HEART     */ 0x04,
    /* PENDANT          */ 0x01,
    /* TELESCOPE        */ 0x00,
    /* TNCL_WHITSL      */ 0x00,
    /* WIND_TACT        */ 0x00,
    /* CAMERA           */ 0x00,
    /* EMONO_BAG        */ 0x00,
    /* ROPE             */ 0x00,
    /* CAMERA2          */ 0x00,
    /* BOW              */ 0x00,
    /* PWR_GROOVE       */ 0x00,
    /* HVY_BOOTS        */ 0x00,
    /* DRGN_SHIELD      */ 0x00,
    /* WATER_BOOTS      */ 0x04,
    /* ESA_BAG          */ 0x00,
    /* BOOMERANG        */ 0x00,
    /* BARE_HAND        */ 0x04,
    /* HOOKSHOT         */ 0x00,
    /* WARASHIBE_BAG    */ 0x00,
    /* BOMB_BAG         */ 0x00,
    /* FUKU             */ 0x03,
    /* HUMMER           */ 0x00,
    /* DEKU_LEAF        */ 0x00,
    /* MAGIC_ARROW      */ 0x00,
    /* LIGHT_ARROW      */ 0x00,
    /* noentry55        */ 0x04,
    /* SWORD            */ 0x00,
    /* MASTER_SWORD     */ 0x00,
    /* LV3_SWORD        */ 0x04,
    /* SHIELD           */ 0x00,
    /* MIRROR_SHIELD    */ 0x00,
    /* DROPPED_SWORD    */ 0x00,
    /* MASTER_SWORD_EX  */ 0x04,
    /* KAKERA_HEART2    */ 0x01,
    /* noentry64        */ 0x04,
    /* noentry65        */ 0x04,
    /* PIRATES_OMAMORI  */ 0x00,
    /* HEROS_OMAMORI    */ 0x00,
    /* GRASS_BALL       */ 0x04,
    /* SKULL_NECKLACE   */ 0x01,
    /* BOKOBABA_SEED    */ 0x01,
    /* GOLDEN_FEATHER   */ 0x01,
    /* BOKO_BELT        */ 0x01,
    /* RED_JELLY        */ 0x01,
    /* GREEN_JELLY      */ 0x01,
    /* BLUE_JELLY       */ 0x01,
    /* MAP              */ 0x01,
    /* COMPASS          */ 0x01,
    /* BOSS_KEY         */ 0x00,
    /* EMPTY_BSHIP      */ 0x04,
    /* EMPTY_BOTTLE     */ 0x00,
    /* RED_BOTTLE       */ 0x02,
    /* GREEN_BOTTLE     */ 0x02,
    /* BLUE_BOTTLE      */ 0x02,
    /* BOTTLESHIP       */ 0x00,
    /* SOUP_BOTTLE      */ 0x00,
    /* BIN_IN_WATER     */ 0x02,
    /* FAIRY_BOTTLE     */ 0x02,
    /* FIREFLY_BOTTLE   */ 0x00,
    /* FWATER_BOTTLE    */ 0x02,
    /* UNK_BOTTLE_5A    */ 0x04,
    /* UNK_BOTTLE_5B    */ 0x04,
    /* UNK_BOTTLE_5C    */ 0x04,
    /* UNK_BOTTLE_5D    */ 0x04,
    /* UNK_BOTTLE_5E    */ 0x04,
    /* UNK_BOTTLE_5F    */ 0x04,
    /* UNK_BOTTLE_60    */ 0x04,
    /* TRIFORCE1        */ 0x00,
    /* TRIFORCE2        */ 0x00,
    /* TRIFORCE3        */ 0x00,
    /* TRIFORCE4        */ 0x00,
    /* TRIFORCE5        */ 0x00,
    /* TRIFORCE6        */ 0x00,
    /* TRIFORCE7        */ 0x00,
    /* TRIFORCE8        */ 0x00,
    /* PEARL1           */ 0x00,
    /* PEARL2           */ 0x00,
    /* PEARL3           */ 0x00,
    /* KNOWLEDGE_TF     */ 0x04,
    /* TACT_SONG1       */ 0x04,
    /* TACT_SONG2       */ 0x04,
    /* TACT_SONG3       */ 0x04,
    /* TACT_SONG4       */ 0x04,
    /* TACT_SONG5       */ 0x04,
    /* TACT_SONG6       */ 0x04,
    /* noentry115       */ 0x04,
    /* noentry116       */ 0x04,
    /* noentry117       */ 0x04,
    /* noentry118       */ 0x04,
    /* noentry119       */ 0x04,
    /* NORMAL_SAIL      */ 0x00,
    /* TRIFORCE_MAP1    */ 0x00,
    /* TRIFORCE_MAP2    */ 0x00,
    /* TRIFORCE_MAP3    */ 0x00,
    /* TRIFORCE_MAP4    */ 0x00,
    /* TRIFORCE_MAP5    */ 0x00,
    /* TRIFORCE_MAP6    */ 0x00,
    /* TRIFORCE_MAP7    */ 0x00,
    /* TRIFORCE_MAP8    */ 0x00,
    /* noentry129       */ 0x04,
    /* BIRD_ESA_5       */ 0x02,
    /* ANIMAL_ESA       */ 0x02,
    /* ESA1             */ 0x04,
    /* ESA2             */ 0x04,
    /* ESA3             */ 0x04,
    /* ESA4             */ 0x04,
    /* ESA5             */ 0x04,
    /* MAGIC_BEAN       */ 0x04,
    /* BIRD_ESA_10      */ 0x04,
    /* noentry139       */ 0x04,
    /* FLOWER_1         */ 0x02,
    /* FLOWER_2         */ 0x02,
    /* FLOWER_3         */ 0x02,
    /* HEROS_FLAG       */ 0x02,
    /* TAIRYO_FLAG      */ 0x02,
    /* SALES_FLAG       */ 0x02,
    /* WIND_FLAG        */ 0x02,
    /* RED_FLAG         */ 0x02,
    /* FOSSIL_HEAD      */ 0x02,
    /* WATER_STATUE     */ 0x02,
    /* POSTMAN_STATUE   */ 0x02,
    /* PRESIDENT_STATUE */ 0x02,
    /* LETTER00         */ 0x02,
    /* MAGIC_SEED       */ 0x02,
    /* MAGYS_LETTER     */ 0x02,
    /* MO_LETTER        */ 0x02,
    /* COTTAGE_PAPER    */ 0x00,
    /* KAISEN_PRESENT1  */ 0x02,
    /* KAISEN_PRESENT2  */ 0x02,
    /* SALVAGE_ITEM1    */ 0x00,
    /* SALVAGE_ITEM2    */ 0x04,
    /* SALVAGE_ITEM3    */ 0x04,
    /* XXX_039          */ 0x04,
    /* TINGLE_STATUE1   */ 0x00,
    /* TINGLE_STATUE2   */ 0x00,
    /* TINGLE_STATUE3   */ 0x00,
    /* TINGLE_STATUE4   */ 0x00,
    /* TINGLE_STATUE5   */ 0x00,
    /* TINGLE_STATUE6   */ 0x00,
    /* noentry169       */ 0x04,
    /* noentry170       */ 0x04,
    /* MAX_RUPEE_UP1    */ 0x00,
    /* MAX_RUPEE_UP2    */ 0x00,
    /* MAX_BOMB_UP1     */ 0x00,
    /* MAX_BOMB_UP2     */ 0x00,
    /* MAX_ARROW_UP1    */ 0x00,
    /* MAX_ARROW_UP2    */ 0x00,
    /* MAGIC_POWER      */ 0x04,
    /* MAX_MP_UP1       */ 0x04,
    /* TINCLE_RUPEE1    */ 0x03,
    /* TINCLE_RUPEE2    */ 0x03,
    /* TINCLE_RUPEE3    */ 0x03,
    /* TINCLE_RUPEE4    */ 0x03,
    /* TINCLE_RUPEE5    */ 0x03,
    /* TINCLE_RUPEE6    */ 0x03,
    /* LITHOGRAPH1      */ 0x04,
    /* LITHOGRAPH2      */ 0x04,
    /* LITHOGRAPH3      */ 0x04,
    /* LITHOGRAPH4      */ 0x04,
    /* LITHOGRAPH5      */ 0x04,
    /* LITHOGRAPH6      */ 0x04,
    /* COLLECT_MAP_64   */ 0x04,
    /* COLLECT_MAP_63   */ 0x04,
    /* COLLECT_MAP_62   */ 0x04,
    /* COLLECT_MAP_61   */ 0x00,
    /* COLLECT_MAP_60   */ 0x00,
    /* COLLECT_MAP_59   */ 0x00,
    /* COLLECT_MAP_58   */ 0x00,
    /* COLLECT_MAP_57   */ 0x00,
    /* COLLECT_MAP_56   */ 0x00,
    /* COLLECT_MAP_55   */ 0x00,
    /* COLLECT_MAP_54   */ 0x00,
    /* COLLECT_MAP_53   */ 0x00,
    /* COLLECT_MAP_52   */ 0x00,
    /* COLLECT_MAP_51   */ 0x00,
    /* COLLECT_MAP_50   */ 0x00,
    /* COLLECT_MAP_49   */ 0x00,
    /* COLLECT_MAP_48   */ 0x00,
    /* COLLECT_MAP_47   */ 0x00,
    /* COLLECT_MAP_46   */ 0x00,
    /* COLLECT_MAP_45   */ 0x00,
    /* COLLECT_MAP_44   */ 0x00,
    /* COLLECT_MAP_43   */ 0x00,
    /* COLLECT_MAP_42   */ 0x00,
    /* COLLECT_MAP_41   */ 0x00,
    /* COLLECT_MAP_40   */ 0x00,
    /* COLLECT_MAP_39   */ 0x00,
    /* COLLECT_MAP_38   */ 0x00,
    /* COLLECT_MAP_37   */ 0x00,
    /* COLLECT_MAP_36   */ 0x00,
    /* COLLECT_MAP_35   */ 0x00,
    /* COLLECT_MAP_34   */ 0x00,
    /* COLLECT_MAP_33   */ 0x00,
    /* COLLECT_MAP_32   */ 0x00,
    /* COLLECT_MAP_31   */ 0x00,
    /* COLLECT_MAP_30   */ 0x00,
    /* COLLECT_MAP_29   */ 0x00,
    /* COLLECT_MAP_28   */ 0x00,
    /* COLLECT_MAP_27   */ 0x00,
    /* COLLECT_MAP_26   */ 0x00,
    /* COLLECT_MAP_25   */ 0x00,
    /* COLLECT_MAP_24   */ 0x00,
    /* COLLECT_MAP_23   */ 0x00,
    /* COLLECT_MAP_22   */ 0x00,
    /* COLLECT_MAP_21   */ 0x00,
    /* COLLECT_MAP_20   */ 0x00,
    /* COLLECT_MAP_19   */ 0x00,
    /* COLLECT_MAP_18   */ 0x00,
    /* COLLECT_MAP_17   */ 0x00,
    /* COLLECT_MAP_16   */ 0x00,
    /* COLLECT_MAP_15   */ 0x00,
    /* COLLECT_MAP_14   */ 0x00,
    /* COLLECT_MAP_13   */ 0x00,
    /* COLLECT_MAP_12   */ 0x00,
    /* COLLECT_MAP_11   */ 0x00,
    /* COLLECT_MAP_10   */ 0x00,
    /* COLLECT_MAP_09   */ 0x00,
    /* COLLECT_MAP_08   */ 0x00,
    /* COLLECT_MAP_07   */ 0x00,
    /* COLLECT_MAP_06   */ 0x00,
    /* COLLECT_MAP_05   */ 0x00,
    /* COLLECT_MAP_04   */ 0x00,
    /* COLLECT_MAP_03   */ 0x00,
    /* COLLECT_MAP_02   */ 0x00,
    /* COLLECT_MAP_01   */ 0x00,
    /* NO_ITEM          */ 0x04,
};

/* 000000EC-00000320       .text setParticle__9daDitem_cFv */
void daDitem_c::setParticle() {
    cXyz unused_scale(1.0f, 1.0f, 1.0f);
    cXyz unused_pos(current.pos);
    
    if (mpEmitters[0] || mpEmitters[1] || mpEmitters[2] || mpEmitters[3]) {
        return;
    }
    if (chkArgFlag(0x02) || chkArgFlag(0x04) || chkArgFlag(0x08)) {
        return;
    }
    
    csXyz angle;
    angle.x = dCam_getAngleX(dComIfGp_getCamera(0)) - 0x2000;
    angle.y = dCam_getAngleY(dComIfGp_getCamera(0));
    angle.z = 0;
    
    switch (m_effect_type[m_itemNo]) {
    case 0:
        mpEmitters[0] = dComIfGp_particle_set(0x1F7, &current.pos, &angle);
    case 1:
        mpEmitters[1] = dComIfGp_particle_set(0x1F8, &current.pos, &angle);
    case 2:
        mpEmitters[2] = dComIfGp_particle_set(0x1F9, &current.pos, &angle);
    case 3:
        mpEmitters[3] = dComIfGp_particle_set(0x1FA, &current.pos, &angle);
    case 4:
        break;
    }
}

/* 0000035C-000003F0       .text CreateInit__9daDitem_cFv */
bool daDitem_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    hide();
    clrFlag();
    mArgFlag = daDitem_prm::getFlag(this);
    if (!chkArgFlag(0x02) && !chkArgFlag(0x04) && !chkArgFlag(0x08)) {
        current.angle.y = -0x2000;
    }
    for (int i = 0; i < ARRAY_SIZE(mpEmitters); i++) {
        mpEmitters[i] = NULL;
    }
    return true;
}

/* 000003F0-000004AC       .text set_effect__9daDitem_cFv */
void daDitem_c::set_effect() {
    s16 angleX = dCam_getAngleX(dComIfGp_getCamera(0)) - 0x2000;
    s16 angleY = dCam_getAngleY(dComIfGp_getCamera(0));
    for (int i = 0; i < (int)ARRAY_SIZE(mpEmitters); i++) {
        if (mpEmitters[i] == NULL) {
            continue;
        }
        JGeometry::TVec3<s16> rot;
        rot.set(angleX, angleY, 0);
        mpEmitters[i]->playCreateParticle();
        JGeometry::TVec3<f32> pos;
        pos.set(current.pos);
        mpEmitters[i]->setGlobalTranslation(pos);
        mpEmitters[i]->setGlobalRotation(rot);
    }
}

/* 000004AC-000006E4       .text set_pos__9daDitem_cFv */
void daDitem_c::set_pos() {
    static cXyz offset_tbl[3] = {
        cXyz(0.0f, 130.0f, 0.0f),
        cXyz(0.0f, 90.0f, 50.0f),
        cXyz(30.0f, 140.0f, 20.0f),
    };
    
    cXyz pos;
    cXyz offset;
    if (chkArgFlag(0x02)) {
        offset = offset_tbl[1];
    } else if (chkArgFlag(0x04)) {
        offset = offset_tbl[2];
    } else if (chkArgFlag(0x08)) {
        offset = mOffsetPos;
    } else {
        offset = offset_tbl[0];
    }
    
    if (!chkArgFlag(0x08)) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        mDoMtx_stack_c::ZXYrotS(player->current.angle.x, player->shape_angle.y, player->current.angle.z);
        mDoMtx_stack_c::multVec(&offset, &offset);
        pos = dComIfGp_getPlayer(0)->current.pos;
    } else {
        pos = home.pos;
    }
    
    pos += offset;
    current.pos = pos;
}

/* 000006E4-00000760       .text anim_control__9daDitem_cFv */
void daDitem_c::anim_control() {
    switch (m_itemNo) {
    case EMPTY_BSHIP:
    case EMPTY_BOTTLE:
    case RED_BOTTLE:
    case GREEN_BOTTLE:
    case BLUE_BOTTLE:
    case BOTTLESHIP:
    case SOUP_BOTTLE:
    case BIN_IN_WATER:
    case FAIRY_BOTTLE:
    case FIREFLY_BOTTLE:
    case FWATER_BOTTLE:
    case UNK_BOTTLE_5A:
    case UNK_BOTTLE_5B:
    case UNK_BOTTLE_5C:
    case UNK_BOTTLE_5D:
    case UNK_BOTTLE_5E:
    case UNK_BOTTLE_5F:
    case UNK_BOTTLE_60:
        if (field_0x634 > 30) {
            animPlay(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        }
        break;
    default:
        animPlay(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        break;
    }
}

/* 00000760-00000880       .text set_mtx__9daDitem_cFv */
void daDitem_c::set_mtx() {
    mpModel->setBaseScale(mScale);
    fopAcM_addAngleY(this, current.angle.y + 0x0111, 0x0111);
    
    if (chkArgFlag(0x02) || chkArgFlag(0x04) || chkArgFlag(0x08)) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
    } else {
        mDoMtx_stack_c::copy(dComIfGd_getInvViewMtx());
        mDoMtx_stack_c::ZrotM(current.angle.z);
        mDoMtx_stack_c::XrotM(0x12C0);
        mDoMtx_stack_c::YrotM(current.angle.y);
        mDoMtx_stack_c::now[0][3] = current.pos.x;
        mDoMtx_stack_c::now[1][3] = current.pos.y;
        mDoMtx_stack_c::now[2][3] = current.pos.z;
    }
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000880-000008F0       .text settingBeforeDraw__9daDitem_cFv */
void daDitem_c::settingBeforeDraw() {
    if (isBomb(m_itemNo) || m_itemNo == BOMB_BAG || m_itemNo == HUMMER || m_itemNo == SMALL_KEY) {
        dDlst_texSpecmapST(&mEyePos, &mTevStr, mpModel->getModelData(), 1.0f);
    }
}

/* 000008F0-000008F4       .text setListStart__9daDitem_cFv */
void daDitem_c::setListStart() {
}

BOOL daDitem_c::Delete() {
    if (!chkArgFlag(0x01)) {
        execItemGet(m_itemNo);
    }
    
    for (int i = 0; i < ARRAY_SIZE(mpEmitters); i++) {
        if (mpEmitters[i]) {
            mpEmitters[i]->setGlobalAlpha(0);
            mpEmitters[i]->becomeInvalidEmitter();
            mpEmitters[i] = NULL;
        }
    }
    
    return DeleteBase(dItem_data::getArcname(m_itemNo));
}

s32 daDitem_c::create() {
    fopAcM_SetupActor(this, daDitem_c);
    
    m_itemNo = daDitem_prm::getNo(this);
    
    char* arcName = dItem_data::getArcname(m_itemNo);
    if (dItem_data::getBmdIdx(m_itemNo) == -1 || arcName == NULL) {
        m_itemNo = GREEN_RUPEE;
    }
    
    s32 phase_state = dComIfG_resLoad(&mPhs, dItem_data::getArcname(m_itemNo));
    if (phase_state == cPhs_COMPLEATE_e) {
        u32 heap_size = dItem_data::getHeapSize(m_itemNo);
        if (!fopAcM_entrySolidHeap(this, CheckItemCreateHeap, heap_size)) {
            return cPhs_ERROR_e;
        }
        CreateInit();
    }
    
    return phase_state;
}

BOOL daDitem_c::draw() {
    return DrawBase();
}

BOOL daDitem_c::execute() {
    field_0x634++;
    
    if (chkDraw()) {
        setParticle();
        set_effect();
        fopAcM_onDraw(this);
    } else {
        fopAcM_offDraw(this);
    }
    
    anim_control();
    
    if (chkDead()) {
        fopAcM_delete(this);
    }
    
    set_pos();
    set_mtx();
    
    return TRUE;
}

/* 000008F4-00000994       .text daDitem_Delete__FP9daDitem_c */
static BOOL daDitem_Delete(daDitem_c* i_this) {
    return i_this->Delete();
}

/* 00000994-00000B6C       .text daDitem_Create__FP9daDitem_c */
static s32 daDitem_Create(daDitem_c* i_this) {
    return i_this->create();
}

/* 00000D94-00000DB4       .text daDitem_IsDelete__FP9daDitem_c */
static BOOL daDitem_IsDelete(daDitem_c* i_this) {
    return i_this->isdelete();
}

/* 00000DB4-00000E58       .text daDitem_Execute__FP9daDitem_c */
static BOOL daDitem_Execute(daDitem_c* i_this) {
    return i_this->execute();
}

/* 00000E58-00000E84       .text daDitem_Draw__FP9daDitem_c */
static BOOL daDitem_Draw(daDitem_c* i_this) {
    return i_this->draw();
}

/* 00000E84-00000E8C       .text isdelete__9daDitem_cFv */
BOOL daDitem_c::isdelete() {
    return TRUE;
}

static actor_method_class l_daDitem_Method = {
    (process_method_func)daDitem_Create,
    (process_method_func)daDitem_Delete,
    (process_method_func)daDitem_Execute,
    (process_method_func)daDitem_IsDelete,
    (process_method_func)daDitem_Draw,
};

actor_process_profile_definition g_profile_Demo_Item = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 7,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Demo_Item,
    /* Proc SubMtd  */ &g_fpcLf_Method.mBase,
    /* Size         */ sizeof(daDitem_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00FC,
    /* Actor SubMtd */ &l_daDitem_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
