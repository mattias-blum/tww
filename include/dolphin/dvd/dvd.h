#ifndef DVD_H
#define DVD_H

#include "global.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum DVDState {
    DVD_STATE_END = 0x0,
    DVD_STATE_BUSY = 0x1,
    DVD_STATE_WAITING = 0x2,
    DVD_STATE_COVER_CLOSED = 0x3,
    DVD_STATE_NO_DISK = 0x4,
    DVD_STATE_COVER_OPEN = 0x5,
    DVD_STATE_WRONG_DISK = 0x6,
    DVD_STATE_MOTOR_STOPPED = 0x7,
    DVD_STATE_IGNORED = 0x8,
    DVD_STATE_CANCELED = 0xa,  // lmao they skipped 9
    DVD_STATE_RETRY = 0xb,
    DVD_STATE_FATAL_ERROR = -1,
} DVDState;


typedef enum DVDResult {
    DVD_RESULT_GOOD = 0,
    DVD_RESULT_FATAL_ERROR = -1,
    DVD_RESULT_IGNORED = -2,
    DVD_RESULT_CANCELED = -3,
} DVDResult;

typedef struct DVDDirectory {
    /* 0x0 */ u32 entry_number;
    /* 0x4 */ u32 location;
    /* 0x8 */ u32 next;
} DVDDirectory;

typedef struct DVDDirectoryEntry {
    /* 0x0 */ u32 entry_number;
    /* 0x4 */ BOOL is_directory;
    /* 0x8 */ char* name;
} DVDDirectoryEntry;

typedef struct DVDDiskID {
    /* 0x00 */ char game_name[4];
    /* 0x04 */ char company[2];
    /* 0x06 */ u8 disk_number;
    /* 0x07 */ u8 game_version;
    /* 0x08 */ u8 is_streaming;
    /* 0x09 */ u8 streaming_buffer_size;
    /* 0x0A */ u8 padding[22];
} DVDDiskID;

struct DVDFileInfo;
struct DVDCommandBlock;
typedef struct DVDCommandBlock DVDCommandBlock;
typedef void (*DVDCBCallback)(s32 result, struct DVDCommandBlock* block);
typedef void (*DVDCallback)(s32 result, struct DVDFileInfo* info);

typedef void (*DVDCommandCheckerCallback)(u32);
typedef void (*DVDCommandChecker)(DVDCommandBlock*, DVDCommandCheckerCallback);

typedef struct DVDCommandBlock {
    /* 0x00 */ struct DVDCommandBlock* next;
    /* 0x04 */ struct DVDCommandBlock* prev;
    /* 0x08 */ u32 command;
    /* 0x0C */ s32 state;
    /* 0x10 */ u32 offset;
    /* 0x14 */ u32 length;
    /* 0x18 */ void* buffer;
    /* 0x1C */ u32 current_transfer_size;
    /* 0x20 */ u32 transferred_size;
    /* 0x24 */ DVDDiskID* disk_id;
    /* 0x28 */ DVDCBCallback callback;
    /* 0x2C */ void* user_data;
} DVDCommandBlock;

typedef struct DVDFileInfo {
    /* 0x00 */ DVDCommandBlock block;
    /* 0x30 */ u32 start_address;
    /* 0x34 */ u32 length;
    /* 0x38 */ DVDCallback callback;
} DVDFileInfo;

typedef struct DVDDriveInfo {
    /* 0x00 */ u16 revision_level;
    /* 0x02 */ u16 device_code;
    /* 0x04 */ u32 release_date;
    /* 0x08 */ u8 padding[24];
} DVDDriveInfo ALIGN_DECL(32);

typedef struct DVDBB1 {
    u32 appLoaderLength;
    void* appLoaderFunc1;
    void* appLoaderFunc2;
    void* appLoaderFunc3;
} DVDBB1;

typedef struct DVDBB2 {
    u32 bootFilePosition;
    u32 FSTPosition;
    u32 FSTLength;
    u32 FSTMaxLength;
    void* FSTAddress;
    u32 userPosition;
    u32 userLength;

    u32 padding0;
} DVDBB2;

#define DVD_RESULT_GOOD        0
#define DVD_RESULT_FATAL_ERROR -1
#define DVD_RESULT_IGNORED     -2
#define DVD_RESULT_CANCELED    -3

#define DVD_STATE_FATAL_ERROR   -1
#define DVD_STATE_END            0
#define DVD_STATE_BUSY           1
#define DVD_STATE_WAITING        2
#define DVD_STATE_COVER_CLOSED   3
#define DVD_STATE_NO_DISK        4
#define DVD_STATE_COVER_OPEN     5
#define DVD_STATE_WRONG_DISK     6
#define DVD_STATE_MOTOR_STOPPED  7
#define DVD_STATE_PAUSING        8
#define DVD_STATE_IGNORED        9
#define DVD_STATE_CANCELED       10
#define DVD_STATE_RETRY          11

#define DVD_MIN_TRANSFER_SIZE 32

// could be bitfields
#define DVD_INTTYPE_TC 1
#define DVD_INTTYPE_DE 2
// unk type 3
#define DVD_INTTYPE_CVR 4

// DVD Commands

#define DVD_COMMAND_NONE 0
#define DVD_COMMAND_READ 1
#define DVD_COMMAND_SEEK 2
#define DVD_COMMAND_CHANGE_DISK 3
#define DVD_COMMAND_BSREAD 4
#define DVD_COMMAND_READID 5
#define DVD_COMMAND_INITSTREAM 6
#define DVD_COMMAND_CANCELSTREAM 7
#define DVD_COMMAND_STOP_STREAM_AT_END 8
#define DVD_COMMAND_REQUEST_AUDIO_ERROR 9
#define DVD_COMMAND_REQUEST_PLAY_ADDR 10
#define DVD_COMMAND_REQUEST_START_ADDR 11
#define DVD_COMMAND_REQUEST_LENGTH 12
#define DVD_COMMAND_AUDIO_BUFFER_CONFIG 13
#define DVD_COMMAND_INQUIRY 14
#define DVD_COMMAND_BS_CHANGE_DISK 15

#define DVD_WATYPE_MAX 2

typedef void (*DVDOptionalCommandChecker)(DVDCommandBlock* block, void (*cb)(u32 intType));

#define DVDGetLength(fi) (fi)->length
#define DVDGetFileInfoStatus(fi) (DVDGetCommandBlockStatus(&(fi)->block))

void DVDInit(void);
BOOL DVDOpen(const char* filename, DVDFileInfo* fileinfo);
BOOL DVDClose(DVDFileInfo* fileinfo);
int DVDReadPrio(DVDFileInfo* fileinfo, void*, s32, s32, s32);
DVDDiskID* DVDGetCurrentDiskID(void);
BOOL DVDFastOpen(long, DVDFileInfo* fileinfo);
s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block);
BOOL DVDReadAsyncPrio(DVDFileInfo* fileinfo, void*, long, long, DVDCallback, long);
int DVDConvertPathToEntrynum(const char*);
s32 DVDGetDriveStatus(void);
BOOL DVDCheckDisk(void);
BOOL DVDChangeDir(const char* dirname);
BOOL DVDCloseDir(DVDDirectory* dir);
BOOL DVDOpenDir(const char*, DVDDirectory* dir);
BOOL DVDReadDir(DVDDirectory* dir, DVDDirectoryEntry* entry);
BOOL DVDPrepareStreamAsync(DVDFileInfo* fileinfo, u32 length, u32 offset, DVDCallback callback);
BOOL DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length, s32 offset,
                         DVDCBCallback callback, s32 prio);
BOOL DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length, s32 offset,
                          DVDCBCallback callback);
BOOL DVDReadDiskID(DVDCommandBlock* block, DVDDiskID* diskID, DVDCBCallback callback);
BOOL DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback);
BOOL DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback);
BOOL DVDGetStreamPlayAddrAsync(DVDCommandBlock* block, DVDCBCallback callback);
BOOL DVDInquiryAsync(DVDCommandBlock* block, DVDDriveInfo* info, DVDCBCallback callback);
void DVDReset(void);
BOOL DVDSetAutoInvalidation(BOOL autoInval);
void DVDResume(void);
static BOOL DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback);
s32 DVDCancel(DVDCommandBlock* block);
void __DVDPrepareResetAsync(DVDCBCallback callbac);
BOOL DVDCompareDiskID(DVDDiskID* id1, DVDDiskID* id2);
void __DVDAudioBufferConfig(struct DVDCommandBlock * block, unsigned long enable, unsigned long size, void (* callback)(long, struct DVDCommandBlock *));

DVDCommandBlock* __DVDPopWaitingQueue(void);

#define DVD_ASSERTMSGLINE(line, cond, msg) \
    if (!(cond)) \
        OSPanic(__FILE__, line, msg)

#define DVD_ASSERTMSG1LINE(line, cond, msg, arg1) \
    if (!(cond)) \
        OSPanic(__FILE__, line, msg, arg1)

#define DVD_ASSERTMSG2LINE(line, cond, msg, arg1, arg2) \
    if (!(cond)) \
        OSPanic(__FILE__, line, msg, arg1, arg2)

#ifdef __cplusplus
};
#endif

#endif /* DVD_H */
