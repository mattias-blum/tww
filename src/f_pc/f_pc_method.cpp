//
// Generated by dtk
// Translation Unit: f_pc_method.cpp
//

#include "f_pc/f_pc_method.h"

/* 8003EF00-8003EF38       .text fpcMtd_Method__FPFPv_iPv */
int fpcMtd_Method(process_method_func i_methodFunc, void* i_data) {
    if (i_methodFunc != NULL)
        return i_methodFunc(i_data);
    else
        return TRUE;
}

/* 8003EF38-8003EF5C       .text fpcMtd_Execute__FP20process_method_classPv */
BOOL fpcMtd_Execute(process_method_class* i_methods, void* i_data) {
    return fpcMtd_Method(i_methods->mpExecuteFunc, i_data);
}

/* 8003EF5C-8003EF80       .text fpcMtd_IsDelete__FP20process_method_classPv */
BOOL fpcMtd_IsDelete(process_method_class* i_methods, void* i_data) {
    return fpcMtd_Method(i_methods->mpIsDeleteFunc, i_data);
}

/* 8003EF80-8003EFA4       .text fpcMtd_Delete__FP20process_method_classPv */
BOOL fpcMtd_Delete(process_method_class* i_methods, void* i_data) {
    return fpcMtd_Method(i_methods->mpDeleteFunc, i_data);
}

/* 8003EFA4-8003EFC8       .text fpcMtd_Create__FP20process_method_classPv */
cPhs_State fpcMtd_Create(process_method_class* i_methods, void* i_data) {
    return fpcMtd_Method(i_methods->mpCreateFunc, i_data);
}
