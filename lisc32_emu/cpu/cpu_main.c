//
//  cpu_main.c
//  lisc32_emu
//
//  Created by Noah Wooten on 12/9/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

PCPU_CTX CpuCtx;
PCPU_REGS Rs;

void CpuInit(void) {
    CpuCtx = malloc(sizeof(CPU_CTX));
    CpuCtx->Registers = malloc(sizeof(CPU_REGS));
    Rs = CpuCtx->Registers;
    
    memset(CpuCtx, 0, sizeof(CPU_CTX));
    memset(CpuCtx->Registers, 0, sizeof(CPU_REGS));
    return;
}

void CpuShutdown(void) {
    if (CpuCtx->Registers)
        free(CpuCtx->Registers);
    if (CpuCtx->Memory)
        free(CpuCtx->Memory);
    
    if (CpuCtx)
        free(CpuCtx);	
    return;
}
