//
//  mmu_stack.c
//  lisc32_emu
//
//  Created by Noah Wooten on 12/10/24.
//

#include <stdio.h>
#include "mmu.h"
#include "../cpu.h"

WORD32 MmuPull(void) {
    WORD32* Stack = (WORD32*)(CpuCtx->Memory + Rs->sp);
    Rs->sp -= 0x4;
    return *Stack;
}

void MmuPush(WORD32 Source) {
    WORD32* Stack = (WORD32*)(CpuCtx->Memory + Rs->sp);
    *Stack = Source;
    Rs->sp += 0x4;
    return;
}
