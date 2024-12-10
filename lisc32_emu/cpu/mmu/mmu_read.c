//
//  mmu_read.c
//  lisc32_emu
//
//  Created by Noah Wooten on 12/10/24.
//

#include <stdio.h>
#include "mmu.h"
#include "../cpu.h"

BYTE MmuRead1(void) {
    BYTE* Data = (BYTE*)(CpuCtx->Memory + Rs->ip);
    Data += 0x1;
    return *Data;
}

WORD16 MmuRead2(void) {
    WORD16* Data = (WORD16*)(CpuCtx->Memory + Rs->ip);
    Data += 0x2;
    return *Data;
}

WORD32 MmuRead4(void) {
    WORD32* Data = (WORD32*)(CpuCtx->Memory + Rs->ip);
    Data += 0x4;
    return *Data;
}

WORD64 MmuRead8(void) {
    WORD64* Data = (WORD64*)(CpuCtx->Memory + Rs->ip);
    Data += 0x8;
    return *Data;
}
