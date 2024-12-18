//
//  ops_memory.c
//  lisc32_emu
//
//  Created by Noah Wooten on 12/17/24.
//

#include <stdio.h>
#include "../cpu.h"
#include "../mmu/mmu.h"

void LDMEM(void) {
    WORD32* Memory = CpuCtx->Memory;
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }Byte8;
    Byte8.As8 = MmuRead1();
    
    WORD32* Destination = &Rs->GPRs[Byte8.As4_0];
    *Destination = *((BYTE*)Memory + Rs->GPRs[Byte8.As4_1]);
    
    return;
} //LDMEM 40-16 (R:04,04=__DEST) (R:04,04=ADDRES) : Loads memory into a register

void STMEM(void) {
    WORD32* Memory = CpuCtx->Memory;
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }Byte8;
    Byte8.As8 = MmuRead1();
    
    WORD32* Destination = (WORD32*)((BYTE*)Memory +
        Rs->GPRs[Byte8.As4_1]);
    *Destination = Rs->GPRs[Byte8.As4_0];
    
    return;
} // STMEM 41-16 (R:04,04=__DEST) (R:04,04=SOURCE) : Stores memory from register
