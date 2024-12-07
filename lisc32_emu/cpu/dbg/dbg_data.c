//
//  dbg_data.c
//  lisc32_emu
//
//  Created by Noah Wooten on 12/6/24.
//

#include <stdio.h>
#include "dbg.h"
#include "../mmu/mmu.h"
#include "../cpu.h"

void DbgInit(void) {
    
}

void DbgShutdown(void) {
    

}

BYTE DbgRead1(void) {
    BYTE Return = MmuRead1();
    CpuCtx->Registers->ip -= 1;
    return Return;
}

WORD16 DbgRead2(void) {
    BYTE Return = MmuRead2();
    CpuCtx->Registers->ip -= 2;
    return Return;
}

WORD32 DbgRead4(void) {
    BYTE Return = MmuRead4();
    CpuCtx->Registers->ip -= 4;
    return Return;
}

WORD64 DbgRead8(void) {
    BYTE Return = MmuRead8();
    CpuCtx->Registers->ip -= 8;
    return Return;
}
