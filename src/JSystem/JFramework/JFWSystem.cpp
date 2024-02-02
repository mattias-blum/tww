//
// Generated by dtk
// Translation Unit: JFWSystem.cpp
//

#include "JSystem/JFramework/JFWSystem.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JUtility/JUTVideo.h"
#include "JSystem/JUtility/JUTGraphFifo.h"
#include "JSystem/JUtility/JUTGamePad.h"
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "JSystem/JUtility/JUTException.h"
#include "JSystem/JUtility/JUTResFont.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTFontData_Ascfont_fix12.h"
#include "dolphin/os/OS.h"
#include "dolphin/dvd/dvd.h"
#include "dolphin/gx/GXFrameBuf.h"
#include "dolphin/types.h"

s32 JFWSystem::CSetUpParam::maxStdHeaps = 2;
u32 JFWSystem::CSetUpParam::sysHeapSize = 0x400000;
u32 JFWSystem::CSetUpParam::fifoBufSize = 0x40000;
u32 JFWSystem::CSetUpParam::aramAudioBufSize = 0x800000;
u32 JFWSystem::CSetUpParam::aramGraphBufSize = 0x600000;
u32 JFWSystem::CSetUpParam::streamPriority = 8;
u32 JFWSystem::CSetUpParam::decompPriority = 7;
u32 JFWSystem::CSetUpParam::aPiecePriority = 6;
ResFONT* JFWSystem::CSetUpParam::systemFontRes = (ResFONT*)JUTResFONT_Ascfont_fix12;
GXRenderModeObj* JFWSystem::CSetUpParam::renderMode = &GXNtsc480IntDf;
u32 JFWSystem::CSetUpParam::exConsoleBufferSize = 0x24F8;

JKRExpHeap* JFWSystem::rootHeap = 0;
JKRExpHeap* JFWSystem::systemHeap = 0;
JKRThread* JFWSystem::mainThread = 0;
JUTDbPrint* JFWSystem::debugPrint = 0;
JUTResFont* JFWSystem::systemFont = 0;
JUTConsoleManager* JFWSystem::systemConsoleManager = 0;
JUTConsole* JFWSystem::systemConsole = 0;
bool JFWSystem::sInitCalled = false;

/* 80254DD0-80254E54       .text firstInit__9JFWSystemFv */
void JFWSystem::firstInit() {
    JUT_ASSERT(80, rootHeap == 0);

    OSInit();
    DVDInit();
    rootHeap = JKRExpHeap::createRoot(CSetUpParam::maxStdHeaps, false);
    systemHeap = JKRExpHeap::create(CSetUpParam::sysHeapSize, rootHeap, false);
    
    return;
}

/* 80254E54-802551C0       .text init__9JFWSystemFv */
void JFWSystem::init() {
    /* Nonmatching - regalloc */
    JUT_ASSERT(101, sInitCalled == false);

    if(rootHeap == 0) {
        firstInit();
    }

    sInitCalled = true;

    JKRAram::create(CSetUpParam::aramAudioBufSize,CSetUpParam::aramGraphBufSize, CSetUpParam::streamPriority,CSetUpParam::decompPriority, CSetUpParam::aPiecePriority);
    mainThread = new JKRThread(OSGetCurrentThread(), 4);

    JUTVideo::createManager(CSetUpParam::renderMode);
    JUTCreateFifo(CSetUpParam::fifoBufSize);

    JUTGamePad::init();

    JUTDirectPrint* dirPrint = JUTDirectPrint::start();
    JUTAssertion::create();
    JUTException::create(dirPrint);

    systemFont = new JUTResFont(CSetUpParam::systemFontRes, 0);

    debugPrint = JUTDbPrint::start(0, 0);
    debugPrint->changeFont(systemFont);
    
    systemConsoleManager = JUTConsoleManager::createManager(0);
    systemConsole = JUTConsole::create(0x3C, 200, 0);
    systemConsole->setFont(systemFont);
    if(CSetUpParam::renderMode->efb_height < 300) {
        systemConsole->setFontSize(systemFont->getWidth() * 0.85f, systemFont->getHeight() * 0.5f);
        systemConsole->setPosition(20, 25);
    }
    else {
        systemConsole->setFontSize(systemFont->getWidth() * 0.85f, systemFont->getHeight());
        systemConsole->setPosition(20, 50);
    }
    systemConsole->setHeight(25);
    systemConsole->setVisible(false);
    systemConsole->setOutput(3);
    JUTSetReportConsole(systemConsole);
    JUTSetWarningConsole(systemConsole);

    void* buf = systemHeap->alloc(CSetUpParam::exConsoleBufferSize, 4);
    JUTException::createConsole(buf, CSetUpParam::exConsoleBufferSize);

    return;
}
