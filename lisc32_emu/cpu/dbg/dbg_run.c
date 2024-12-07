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
    int IsnId = IsnGetInstructionByOpcode(IsnCtx, Opcode);
    // if (IsnId == -1) @TODO figure this out later 202412062151
    
    
}
