#ifndef F_F_OP_KANKYO_MNG_H_
#define F_F_OP_KANKYO_MNG_H_

#include "SSystem/SComponent/c_xyz.h"
#include "f_pc/f_pc_manager.h"

class kankyo_class;

struct fopKyM_prm_class {
    /* 0x00 */ cXyz mPos;
    /* 0x0C */ cXyz mScale;
    /* 0x18 */ int mParam;
};  // Size: 0x1C

typedef int (*fopKyM_CreateFunc)(void*);

void fopKyM_Delete(void* param_1);
fpc_ProcID fopKyM_Create(s16 param_1, fopKyM_CreateFunc param_2 = NULL, void* param_3 = NULL);
fpc_ProcID fopKyM_create(s16 i_procName, int i_param, cXyz* i_pos = NULL, cXyz* i_scale = NULL,
                  fopKyM_CreateFunc i_createFunc = NULL);
kankyo_class* fopKyM_SearchByID(fpc_ProcID id);
base_process_class* fopKyM_fastCreate(s16 param_0, int param_1, cXyz* param_2, cXyz* param_3,
                                      fopKyM_CreateFunc);
fpc_ProcID fopKyM_createWpillar(cXyz const* i_pos, f32 scaleXZ, f32 scaleY, int i_param);
int fopKyM_createMpillar(cXyz const* i_pos, f32 i_size);

inline fopKyM_prm_class* fopKyM_GetAppend(void* param_0) {
    return (fopKyM_prm_class*)fpcM_GetAppend(param_0);
}

#endif
