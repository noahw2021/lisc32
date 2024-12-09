//
//  cpu_clock.c
//  lisc32_emu
//
//  Created by Noah Wooten on 12/9/24.
//

#include <stdio.h>
#include "cpu.h"
#include "mmu/mmu.h"
#include "dbg/dbg.h"

void CpuClock(void) {
    BYTE Instruction = MmuRead1();
    DbgRun(Instruction);
    
    Instructions[Instruction]();
    return;
}

void CpuLoop(void) {
    while (1) {
        if (Rs->flags & CPUFLAG_HALT) {
            if (!(Rs->flags & CPUFLAG_INTS))
                return;
            
            CpuRunInts();
            return;
        }

        if (Rs->flags & CPUFLAG_INTS)
            CpuRunInts();
        
        // Main CPU Clock
        CpuClock();
        
        // Devices Clock
        
        // @TODO Delay Mechanism 202412091317PST
    }

    return;
}

void CpuSetup(void) {
    Rs->ip = 0x200;
    return;
}
