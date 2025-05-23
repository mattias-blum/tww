
#ifndef F_PC_PRIORITY_H_
#define F_PC_PRIORITY_H_

#include "f_pc/f_pc_method_tag.h"

enum {
    fpcPi_CURRENT_e = 0xFFFD,
    fpcPi_SPECIAL_e = 0xFFFE,
};

typedef struct process_priority_queue_info {
    u32 mLayer;
    u16 mListID;
    u16 mListPrio;
} process_priority_queue_info;

typedef struct process_priority_class {
    /* 0x00 */ create_tag_class base;
    /* 0x14 */ process_method_tag_class mMtdTag;
    /* 0x30 */ process_priority_queue_info mInfoQ;
    /* 0x38 */ process_priority_queue_info mInfoCurr;
} process_priority_class;

BOOL fpcPi_IsInQueue(process_priority_class* pPi);
s32 fpcPi_QueueTo(process_priority_class* pPi);
s32 fpcPi_ToQueue(process_priority_class* pPi);
process_priority_class* fpcPi_GetFromQueue(void);
BOOL fpcPi_Delete(process_priority_class* pPi);
s32 fpcPi_IsNormal(uint i_layer, u16 i_listID, u16 i_priority);
s32 fpcPi_Change(process_priority_class* i_procPriority, uint i_layer, u16 i_listID,
                 u16 i_priority);
s32 fpcPi_Handler(void);
s32 fpcPi_Init(process_priority_class* i_procPriority, void* pUserData, uint i_layer, u16 i_listID,
               u16 i_priority);

#endif
