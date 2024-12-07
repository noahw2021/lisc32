//
//  dbg_run.c
//  lisc32_emu
//
//  Created by Noah Wooten on 12/6/24.
//

#include <stdio.h>
#include "dbg.h"
#include "isn/isn_imports.h"

void DbgRun(BYTE Opcode) {
    if (!(GlobalFlags & FLAG_USEDEBUGGER))
        return;
    
    int IsnId = IsnGetInstructionByOpcode(IsnCtx, Opcode);
    // if (IsnId == -1) @TODO figure this out later 202412062151
    
    char Operand1[32];
    char Operand2[32];
    
    if (IsnGetOperandCount(IsnCtx, IsnId) == 2) {
        
    } else if (IsnGetOperandCount(IsnCtx, IsnId) == 1) {
        if (IsnGetOperandType(IsnCtx, IsnId, 0) == 0) { // Register
            BYTE Register = DbgRead1();
            printf("%s r%i\n", IsnGetInstructionName(IsnCtx, IsnId), Register);
        } else { // Immediate
            
        }
    } else { // 0 Operands
        printf("%s\n", IsnGetInstructionName(IsnCtx, IsnId));
    }
}
