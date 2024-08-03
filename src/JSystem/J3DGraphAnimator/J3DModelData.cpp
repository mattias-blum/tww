//
// Generated by dtk
// Translation Unit: J3DModelData.cpp
//

#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/J3DGraphAnimator/J3DShapeTable.h"
#include "JSystem/JUtility/JUTNameTab.h"
#include "dolphin/types.h"

/* 802ECF30-802ECF70       .text clear__12J3DJointTreeFv */
void J3DJointTree::clear() {
    mHierarchy = NULL;
    mFlags = 0;
    mModelDataType = 0;
    mRootNode = NULL;
    mBasicMtxCalc = NULL;
    mJointNum = NULL;
    mJointNodePointer = NULL;
    field_0x40 = NULL;
    mWEvlpMtxNum = 0;
    mWEvlpMixMtxNum = NULL;
    mWEvlpMixMtxIndex = NULL;
    mWEvlpMixWeight = NULL;
    mInvJointMtx = NULL;
    mJointName = NULL;
}

/* 802ECF70-802ED108       .text makeHierarchy__12J3DJointTreeFP7J3DNodePPC17J3DModelHierarchyP16J3DMaterialTablePP8J3DShape */
void J3DJointTree::makeHierarchy(J3DNode* pRootNode, const J3DModelHierarchy** pHierarchy, J3DMaterialTable* pMaterialTable, J3DShape** pShapeTable) {
    enum {
        kTypeEnd        = 0x00,
        kTypeBeginChild = 0x01,
        kTypeEndChild   = 0x02,
        kTypeJoint      = 0x10,
        kTypeMaterial   = 0x11,
        kTypeShape      = 0x12,
    };

    J3DNode * pCurNode = pRootNode;

    while (true) {
        J3DNode * pNewNode = NULL;
        J3DMaterial * pNewMaterial = NULL;
        J3DShape * pNewShape = NULL;
        const J3DModelHierarchy * inf = *pHierarchy;

        switch (inf->mType) {
        case kTypeBeginChild:
            *pHierarchy = inf + 1;
            makeHierarchy(pCurNode, pHierarchy, pMaterialTable, pShapeTable);
            break;
        case kTypeEndChild:
            *pHierarchy = inf + 1; 
            return;
        case kTypeEnd:
            return;
        case kTypeJoint:
            {
                J3DJoint ** pJoints = mJointNodePointer;
                *pHierarchy = inf + 1;
                pNewNode = pJoints[inf->mValue];
            }
            break;
        case kTypeMaterial:
            {
                *pHierarchy = inf + 1;
                pNewMaterial = pMaterialTable->getMaterialNodePointer(inf->getValue());
            }
            break;
        case kTypeShape:
            *pHierarchy = inf + 1;
            pNewShape = pShapeTable[inf->mValue];
            break;
        }

        if (pNewNode != NULL) {
            pCurNode = pNewNode;
            if (pRootNode == NULL)
                mRootNode = (J3DJoint*)pNewNode;
            else
                pRootNode->appendChild(pNewNode);
        } else if (pNewMaterial != NULL && pRootNode->getType() == 'NJNT') {
            ((J3DJoint*)pRootNode)->addMesh(pNewMaterial);
            pNewMaterial->mJoint = ((J3DJoint*)pRootNode);
        } else if (pNewShape != NULL && pRootNode->getType() == 'NJNT') {
            pNewMaterial = ((J3DJoint*)pRootNode)->getMesh();
            pNewMaterial->mShape = pNewShape;
            pNewShape->mMaterial = pNewMaterial;
        }
    }
}

/* 802ED108-802ED130       .text clear__12J3DModelDataFv */
void J3DModelData::clear() {
    mBinary = NULL;
    mFlags = 0;
    mbHasBumpArray = 0;
    mbHasBillboard = 0;
    mShapeTable.clear();
    mName = NULL;
    mVertexData.clear();
}

/* 802ED130-802ED1A8       .text __ct__12J3DModelDataFv */
J3DModelData::J3DModelData() {
    clear();
}

/* 802ED1A8-802ED238       .text __dt__12J3DModelDataFv */
J3DModelData::~J3DModelData() {
}

/* 802ED238-802ED2A4       .text initShapeNodes__12J3DModelDataFv */
void J3DModelData::initShapeNodes() {
    for (u16 i = 0; i < getShapeNum(); i++) {
        J3DShape *pShape = getShapeNodePointer(i);
        pShape->setDrawMtxDataPointer(getDrawMtxData());
        pShape->setVertexDataPointer(&getVertexData());
        pShape->makeVcdVatCmd();
    }
}

/* 802ED2A4-802ED340       .text sortVcdVatCmd__12J3DModelDataFv */
void J3DModelData::sortVcdVatCmd() {
    for (u16 i = 0; i < getShapeNum(); i++)
        for (u16 j = 0; j < i; j++)
            if (getShapeNodePointer(i)->isSameVcdVatCmd(getShapeNodePointer(j)))
                getShapeNodePointer(i)->setVcdVatCmd(getShapeNodePointer(j)->getVcdVatCmd());
}

/* 802ED340-802ED3E8       .text indexToPtr__12J3DModelDataFv */
void J3DModelData::indexToPtr() {
    j3dSys.setTexture(getTexture());

    GDLObj dlObj;
    for (u16 i = 0; i < getMaterialNum(); i++) {
        J3DDisplayListObj *pDLObj = getMaterialNodePointer(i)->getSharedDisplayListObj();
        GDInitGDLObj(&dlObj, pDLObj->getDisplayList(0), pDLObj->getDisplayListSize());
        GDSetCurrent(&dlObj);
        getMaterialNodePointer(i)->getTevBlock()->indexToPtr();
    }

    GDSetCurrent(NULL);
}

/* 802ED3E8-802ED434       .text isDeformablePositionFormat__12J3DModelDataCFv */
bool J3DModelData::isDeformablePositionFormat() const {
    GXVtxAttrFmtList *vtxAttr = getVtxAttrFmtList();

    for (; vtxAttr->mAttrib != GX_VA_NULL; vtxAttr++) {
        switch (vtxAttr->mAttrib) {
        case GX_VA_POS:
            if (vtxAttr->mCompType == GX_F32 && vtxAttr->mCompCnt == GX_POS_XYZ)
                return true;
            break;
        }
    }

    return false;
}

/* 802ED434-802ED4F4       .text setMaterialTable__12J3DModelDataFP16J3DMaterialTable19J3DMaterialCopyFlag */
void J3DModelData::setMaterialTable(J3DMaterialTable* pMaterialTable, J3DMaterialCopyFlag flag) {
    if (flag & J3DMatCopyFlag_Material) {
        for (u16 i = 0; i < pMaterialTable->getMaterialNum(); i++) {
            JUTNameTab *pMaterialName = getMaterialName();
            const char *pName = pMaterialTable->getMaterialName()->getName(i);
            s32 nameIndex = pMaterialName->getIndex(pName);
            if (nameIndex != -1)
                getMaterialNodePointer(nameIndex)->copy(pMaterialTable->getMaterialNodePointer(i));
        }
    }

    if ((flag & J3DMatCopyFlag_Texture) && pMaterialTable->getTexture()->getNum() != 0) {
        setTexture(pMaterialTable->getTexture());
        setTextureName(pMaterialTable->getTextureName());
    }
}
