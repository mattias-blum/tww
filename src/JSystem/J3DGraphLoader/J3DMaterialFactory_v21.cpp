//
// Generated by dtk
// Translation Unit: J3DMaterialFactory_v21.cpp
//

#include "JSystem/J3DGraphLoader/J3DMaterialFactory_v21.h"
#include "JSystem/J3DGraphLoader/J3DModelLoader.h"
#include "JSystem/J3DGraphBase/J3DMatBlock.h"
#include "JSystem/JSupport/JSupport.h"

/* 802F9A88-802F9C68       .text __ct__22J3DMaterialFactory_v21FRC20J3DMaterialBlock_v21 */
J3DMaterialFactory_v21::J3DMaterialFactory_v21(const J3DMaterialBlock_v21& block) {
    mMaterialNum = block.mMaterialNum;
    mpMaterialInitData = JSUConvertOffsetToPtr<J3DMaterialInitData_v21>(&block, block.mpMaterialInitData);
    mpMaterialID = JSUConvertOffsetToPtr<u16>(&block, block.mpMaterialID);

    mpCullMode = JSUConvertOffsetToPtr<GXCullMode>(&block, block.mpCullMode);
    mpMatColor = JSUConvertOffsetToPtr<GXColor>(&block, block.mpMatColor);
    mpColorChanNum = JSUConvertOffsetToPtr<u8>(&block, block.mpColorChanNum);
    mpColorChanInfo = JSUConvertOffsetToPtr<J3DColorChanInfo>(&block, block.mpColorChanInfo);
    mpTexGenNum = JSUConvertOffsetToPtr<u8>(&block, block.mpTexGenNum);
    mpTexCoordInfo = JSUConvertOffsetToPtr<J3DTexCoordInfo>(&block, block.mpTexCoordInfo);
    mpTexCoord2Info = JSUConvertOffsetToPtr<J3DTexCoord2Info>(&block, block.mpTexCoord2Info);
    mpTexMtxInfo = JSUConvertOffsetToPtr<J3DTexMtxInfo>(&block, block.mpTexMtxInfo);
    field_0x28 = JSUConvertOffsetToPtr<J3DTexMtxInfo>(&block, block.field_0x44);
    mpTexNo = JSUConvertOffsetToPtr<u16>(&block, block.mpTexNo);
    mpTevOrderInfo = JSUConvertOffsetToPtr<J3DTevOrderInfo>(&block, block.mpTevOrderInfo);
    mpTevColor = JSUConvertOffsetToPtr<GXColorS10>(&block, block.mpTevColor);
    mpTevKColor = JSUConvertOffsetToPtr<GXColor>(&block, block.mpTevKColor);
    mpTevStageNum = JSUConvertOffsetToPtr<u8>(&block, block.mpTevStageNum);
    mpTevStageInfo = JSUConvertOffsetToPtr<J3DTevStageInfo>(&block, block.mpTevStageInfo);
    mpTevSwapModeInfo = JSUConvertOffsetToPtr<J3DTevSwapModeInfo>(&block, block.mpTevSwapModeInfo);
    mpTevSwapModeTableInfo = JSUConvertOffsetToPtr<J3DTevSwapModeTableInfo>(&block, block.mpTevSwapModeTableInfo);
    mpFogInfo = JSUConvertOffsetToPtr<J3DFogInfo>(&block, block.mpFogInfo);
    mpAlphaCompInfo = JSUConvertOffsetToPtr<J3DAlphaCompInfo>(&block, block.mpAlphaCompInfo);
    mpBlendInfo = JSUConvertOffsetToPtr<J3DBlendInfo>(&block, block.mpBlendInfo);
    mpZModeInfo = JSUConvertOffsetToPtr<J3DZModeInfo>(&block, block.mpZModeInfo);
    mpZCompLoc = JSUConvertOffsetToPtr<u8>(&block, block.mpZCompLoc);
    mpDither = JSUConvertOffsetToPtr<u8>(&block, block.mpDither);
    mpNBTScaleInfo = JSUConvertOffsetToPtr<J3DNBTScaleInfo>(&block, block.mpNBTScaleInfo);
}

/* 802F9C68-802F9C8C       .text countUniqueMaterials__22J3DMaterialFactory_v21Fv */
u16 J3DMaterialFactory_v21::countUniqueMaterials() {
    u16 num = 0;
    for (; num < mMaterialNum; num++)
        ;
    return num;
}

/* 802F9C8C-802F9CC4       .text countTexGens__22J3DMaterialFactory_v21CFi */
u32 J3DMaterialFactory_v21::countTexGens(int idx) const {
    u8 no = mpMaterialInitData[mpMaterialID[idx]].mTexGenNumIdx;
    if (no != 0xFF)
        return mpTexGenNum[no];
    return 0;
}

/* 802F9CC4-802F9D4C       .text countStages__22J3DMaterialFactory_v21CFi */
u32 J3DMaterialFactory_v21::countStages(int idx) const {
    J3DMaterialInitData_v21* initData = &mpMaterialInitData[mpMaterialID[idx]];

    u32 texGenNum = 0;
    u32 tevStageNum = 0;

    u8 no = initData->mTevStageNumIdx;
    if (no != 0xFF)
        tevStageNum = mpTevStageNum[no];

    for (s32 i = 0; i < 8; i++)
        if (initData->mTexNoIdx[i] != 0xFFFF)
            texGenNum++;

    if (tevStageNum != texGenNum && texGenNum != 0) {
        return tevStageNum > texGenNum ? tevStageNum : texGenNum;
    } else {
        return tevStageNum;
    }
}

/* 802F9D4C-802FA4C0       .text create__22J3DMaterialFactory_v21CFP11J3DMaterialiUl */
J3DMaterial* J3DMaterialFactory_v21::create(J3DMaterial* i_material, int i_idx, u32 i_flags) const {
    u32 stages = countStages(i_idx);
    u32 tev_stage_num = getMdlDataFlag_TevStageNum(i_flags);
    u32 tev_stage_num_max = stages > tev_stage_num ? stages : tev_stage_num;
    u32 tex_num = tev_stage_num_max > 8 ? 8 : tev_stage_num_max;
    u32 texgens = countTexGens(i_idx);
    u32 texgen_flag = texgens > 4 ? getMdlDataFlag_TexGenFlag(0) : getMdlDataFlag_TexGenFlag(i_flags);
    u32 color_flag = getMdlDataFlag_ColorFlag(i_flags);
    u32 pe_flag = getMdlDataFlag_PEFlag(i_flags);
    BOOL ind_flag = (i_flags & 0x1000000) ? TRUE : FALSE;
    if (i_material == NULL) {
        i_material = new J3DMaterial();
    }
    i_material->mColorBlock = J3DMaterial::createColorBlock(color_flag);
    i_material->mTexGenBlock = J3DMaterial::createTexGenBlock(texgen_flag);
    i_material->mTevBlock = J3DMaterial::createTevBlock((u16)tev_stage_num_max);
    i_material->mIndBlock = J3DMaterial::createIndBlock(ind_flag);
    i_material->mPEBlock = J3DMaterial::createPEBlock(pe_flag, getMaterialMode(i_idx));
    i_material->mIndex = i_idx;
    i_material->mMaterialMode = getMaterialMode(i_idx);
    i_material->mColorBlock->setColorChanNum(newColorChanNum(i_idx));
    i_material->mColorBlock->setCullMode(newCullMode(i_idx));
    i_material->mTexGenBlock->setTexGenNum(newTexGenNum(i_idx));
    i_material->mTexGenBlock->setNBTScale(newNBTScale(i_idx));
    i_material->mPEBlock->setFog(newFog(i_idx));
    i_material->mPEBlock->setAlphaComp(newAlphaComp(i_idx));
    i_material->mPEBlock->setBlend(newBlend(i_idx));
    i_material->mPEBlock->setZMode(newZMode(i_idx));
    i_material->mPEBlock->setZCompLoc(newZCompLoc(i_idx));
    i_material->mPEBlock->setDither(newDither(i_idx));
    i_material->mTevBlock->setTevStageNum(newTevStageNum(i_idx));
    for (u8 i = 0; i < tex_num; i++) {
        i_material->mTevBlock->setTexNo(i, newTexNo(i_idx, i));
    }
    for (u8 i = 0; i < tev_stage_num_max; i++) {
        i_material->mTevBlock->setTevOrder(i, newTevOrder(i_idx, i));
    }
    for (u8 i = 0; i < tev_stage_num_max; i++) {
        J3DMaterialInitData_v21* material_init_data = &mpMaterialInitData[mpMaterialID[i_idx]];
        i_material->mTevBlock->setTevStage(i, newTevStage(i_idx, i));
        if (material_init_data->mTevSwapModeIdx[i] != 0xffff) {
            i_material->mTevBlock->getTevStage(i)->setTexSel(
                mpTevSwapModeInfo[material_init_data->mTevSwapModeIdx[i]].mTexSel);
            i_material->mTevBlock->getTevStage(i)->setRasSel(
                mpTevSwapModeInfo[material_init_data->mTevSwapModeIdx[i]].mRasSel);
        }
    }
    for (u8 i = 0; i < 4; i++) {
        i_material->mTevBlock->setTevKColor(i, newTevKColor(i_idx, i));
    }
    for (u8 i = 0; i < 4; i++) {
        i_material->mTevBlock->setTevColor(i, newTevColor(i_idx, i));
    }
    for (u8 i = 0; i < 4; i++) {
        i_material->mTevBlock->setTevSwapModeTable(i, newTevSwapModeTable(i_idx, i));
    }
    for (u8 i = 0; i < 2; i++) {
        i_material->mColorBlock->setMatColor(i, newMatColor(i_idx, i));
    }
    for (u8 i = 0; i < 4; i++) {
        J3DColorChan color_chan = newColorChan(i_idx, i);
        i_material->mColorBlock->setColorChan(i, color_chan);
    }
    for (u8 i = 0; i < texgens; i++) {
        J3DTexCoord tex_coord = newTexCoord(i_idx, i);
        i_material->mTexGenBlock->setTexCoord(i, &tex_coord);
    }
    for (u8 i = 0; i < 8; i++) {
        i_material->mTexGenBlock->setTexMtx(i, newTexMtx(i_idx, i));
    }
    J3DMaterialInitData_v21* material_init_data = &mpMaterialInitData[mpMaterialID[i_idx]];
    for (u8 i = 0; i < tev_stage_num_max; i++) {
        if (material_init_data->mTevKColorSel[i] != 0xff) {
            i_material->mTevBlock->setTevKColorSel(i, material_init_data->mTevKColorSel[i]);
        } else {
            i_material->mTevBlock->setTevKColorSel(i, 0xc);
        }
    }
    for (u8 i = 0; i < tev_stage_num_max; i++) {
        if (material_init_data->mTevKAlphaSel[i] != 0xff) {
            i_material->mTevBlock->setTevKAlphaSel(i, material_init_data->mTevKAlphaSel[i]);
        } else {
            i_material->mTevBlock->setTevKAlphaSel(i, 0x1c);
        }
    }
    return i_material;
}

/* 802FA4C0-802FA550       .text newMatColor__22J3DMaterialFactory_v21CFii */
J3DGXColor J3DMaterialFactory_v21::newMatColor(int idx, int stage) const {
    GXColor _ret = { 0xFF, 0xFF, 0xFF, 0xFF };
    J3DGXColor ret(_ret);
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mMatColorIdx[stage];
    if (no != 0xFFFF)
        return mpMatColor[no];
    else
        return ret;
}

/* 802FA550-802FA588       .text newColorChanNum__22J3DMaterialFactory_v21CFi */
u8 J3DMaterialFactory_v21::newColorChanNum(int idx) const {
    u8 no = mpMaterialInitData[mpMaterialID[idx]].mColorChanNumIdx;
    if (no != 0xFF)
        return mpColorChanNum[no];
    else
        return 0;
}

/* 802FA588-802FA72C       .text newColorChan__22J3DMaterialFactory_v21CFii */
J3DColorChan J3DMaterialFactory_v21::newColorChan(int idx, int stage) const {
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mColorChanIdx[stage];
    if (no != 0xFFFF)
        return J3DColorChan(mpColorChanInfo[no]);
    else
        return J3DColorChan();
}

/* 802FA72C-802FA764       .text newTexGenNum__22J3DMaterialFactory_v21CFi */
u32 J3DMaterialFactory_v21::newTexGenNum(int idx) const {
    u8 no = mpMaterialInitData[mpMaterialID[idx]].mTexGenNumIdx;
    if (no != 0xFF)
        return mpTexGenNum[no];
    else
        return 0;
}

/* 802FA764-802FA7D8       .text newTexCoord__22J3DMaterialFactory_v21CFii */
J3DTexCoord J3DMaterialFactory_v21::newTexCoord(int idx, int stage) const {
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mTexCoordIdx[stage];
    if (no != 0xFFFF)
        return J3DTexCoord(mpTexCoordInfo[no]);
    else
        return J3DTexCoord();
}

/* 802FA7D8-802FA8E8       .text newTexMtx__22J3DMaterialFactory_v21CFii */
J3DTexMtx* J3DMaterialFactory_v21::newTexMtx(int idx, int stage) const {
    J3DTexMtx* ret = NULL;
    J3DMaterialInitData_v21* initData = &mpMaterialInitData[mpMaterialID[idx]];
    if (initData->mTexMtxIdx[stage] != 0xFFFF)
        ret = new J3DTexMtx(mpTexMtxInfo[initData->mTexMtxIdx[stage]]);
    return ret;
}

/* 802FA8E8-802FA928       .text newCullMode__22J3DMaterialFactory_v21CFi */
u8 J3DMaterialFactory_v21::newCullMode(int idx) const {
    u8 no = mpMaterialInitData[mpMaterialID[idx]].mCullModeIdx;
    if (no != 0xFF)
        return mpCullMode[no];
    else
        return 0xFF;
}

/* 802FA928-802FA970       .text newTexNo__22J3DMaterialFactory_v21CFii */
u16 J3DMaterialFactory_v21::newTexNo(int idx, int stage) const {
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mTexNoIdx[stage];
    if (no != 0xFFFF)
        return mpTexNo[no];
    else
        return 0xFFFF;
}

/* 802FA970-802FA9E4       .text newTevOrder__22J3DMaterialFactory_v21CFii */
J3DTevOrder J3DMaterialFactory_v21::newTevOrder(int idx, int stage) const {
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mTevOrderIdx[stage];
    if (no != 0xFFFF)
        return J3DTevOrder(mpTevOrderInfo[no]);
    else
        return J3DTevOrder();
}

/* 802FA9E4-802FAA7C       .text newTevColor__22J3DMaterialFactory_v21CFii */
J3DGXColorS10 J3DMaterialFactory_v21::newTevColor(int idx, int stage) const {
    GXColorS10 _ret = { 0x00, 0x00, 0x00, 0x00 };
    J3DGXColorS10 ret(_ret);
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mTevColorIdx[stage];
    if (no != 0xFFFF)
        return mpTevColor[no];
    else
        return ret;
}

/* 802FAA7C-802FAB0C       .text newTevKColor__22J3DMaterialFactory_v21CFii */
J3DGXColor J3DMaterialFactory_v21::newTevKColor(int idx, int stage) const {
    GXColor _ret = { 0xFF, 0xFF, 0xFF, 0xFF };
    J3DGXColor ret(_ret);
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mTevKColorIdx[stage];
    if (no != 0xFFFF)
        return mpTevKColor[no];
    else
        return ret;
}

/* 802FAB0C-802FAB44       .text newTevStageNum__22J3DMaterialFactory_v21CFi */
u8 J3DMaterialFactory_v21::newTevStageNum(int idx) const {
    u8 no = mpMaterialInitData[mpMaterialID[idx]].mTevStageNumIdx;
    if (no != 0xFF)
        return mpTevStageNum[no];
    else
        return 0xFF;
}

/* 802FAB44-802FABA4       .text newTevStage__22J3DMaterialFactory_v21CFii */
J3DTevStage J3DMaterialFactory_v21::newTevStage(int idx, int stage) const {
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mTevStageIdx[stage];
    if (no != 0xFFFF)
        return J3DTevStage(mpTevStageInfo[no]);
    else
        return J3DTevStage();
}

/* 802FABA4-802FAC40       .text newTevSwapModeTable__22J3DMaterialFactory_v21CFii */
J3DTevSwapModeTable J3DMaterialFactory_v21::newTevSwapModeTable(int idx, int stage) const {
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mTevSwapModeTableIdx[stage];
    if (no != 0xFFFF)
        return J3DTevSwapModeTable(mpTevSwapModeTableInfo[no]);
    else
        return J3DTevSwapModeTable(j3dDefaultTevSwapModeTable);
}

/* 802FAC40-802FADC4       .text newFog__22J3DMaterialFactory_v21CFi */
J3DFog* J3DMaterialFactory_v21::newFog(int idx) const {
    J3DMaterialInitData_v21* initData = &mpMaterialInitData[mpMaterialID[idx]];
    if (initData->mFogIdx != 0xFFFF)
        return new J3DFog(mpFogInfo[initData->mFogIdx]);
    else
        return new J3DFog();
}

/* 802FADC4-802FAE44       .text newAlphaComp__22J3DMaterialFactory_v21CFi */
J3DAlphaComp J3DMaterialFactory_v21::newAlphaComp(int idx) const {
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mAlphaCompIdx;
    if (no != 0xFFFF)
        return J3DAlphaComp(mpAlphaCompInfo[no]);
    else
        return J3DAlphaComp(0xFFFF);
}

/* 802FAE44-802FAEC0       .text newBlend__22J3DMaterialFactory_v21CFi */
J3DBlend J3DMaterialFactory_v21::newBlend(int idx) const {
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mBlendIdx;
    if (no != 0xFFFF)
        return J3DBlend(mpBlendInfo[no]);
    else
        return J3DBlend();
}

/* 802FAEC0-802FAF20       .text newZMode__22J3DMaterialFactory_v21CFi */
J3DZMode J3DMaterialFactory_v21::newZMode(int idx) const {
    u8 no = mpMaterialInitData[mpMaterialID[idx]].mZModeIdx;
    if (no != 0xFF)
        return J3DZMode(mpZModeInfo[no]);
    else
        return J3DZMode();
}

/* 802FAF20-802FAF58       .text newZCompLoc__22J3DMaterialFactory_v21CFi */
u8 J3DMaterialFactory_v21::newZCompLoc(int idx) const {
    u8 no = mpMaterialInitData[mpMaterialID[idx]].mZCompLocIdx;
    if (no != 0xFF)
        return mpZCompLoc[no];
    else
        return 0;
}

/* 802FAF58-802FAF90       .text newDither__22J3DMaterialFactory_v21CFi */
u8 J3DMaterialFactory_v21::newDither(int idx) const {
    u8 no = mpMaterialInitData[mpMaterialID[idx]].mDitherIdx;
    if (no != 0xFF)
        return mpDither[no];
    else
        return 1;
}

/* 802FAF90-802FB034       .text newNBTScale__22J3DMaterialFactory_v21CFi */
J3DNBTScale J3DMaterialFactory_v21::newNBTScale(int idx) const {
    J3DNBTScale ret;
    u16 no = mpMaterialInitData[mpMaterialID[idx]].mNBTScaleIdx;
    if (no != 0xFFFF)
        return J3DNBTScale(mpNBTScaleInfo[no]);
    else
        return ret;
}
