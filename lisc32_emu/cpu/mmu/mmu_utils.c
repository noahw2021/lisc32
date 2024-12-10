//
//  mmu_utils.c
//  lisc32_emu
//
//  Created by Noah Wooten on 12/10/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mmu.h"
#include "../cpu.h"

void MmuInit(void) {
    CpuCtx->Memory = malloc(GlobalMemorySize);
    memset(CpuCtx->Memory, 0, GlobalMemorySize);
    
    return;
}

void MmuShutdown(void) {
    return;
}
