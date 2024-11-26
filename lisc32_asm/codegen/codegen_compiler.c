//
//  codegen_compiler.c
//  lisc32_asm
//
//  Created by Noah Wooten on 11/26/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

int CgGetErrorCount(void) {
    return CgCtx->ErrorCount;
}

void CgError(int Line, int Code, const char* Msg) {
    if (CgCtx->ErrorCount == CgCtx->ErrorMax) {
        CgCtx->ErrorMax += 256;
        CgCtx->Errors = realloc(CgCtx->Errors,
            sizeof(CODEGEN_ERROR) * CgCtx->ErrorMax);
    }
    
    PCODEGEN_ERROR NewError = &CgCtx->Errors[CgCtx->ErrorCount];
    CgCtx->ErrorCount++;
    
    NewError->ErrorCode = Code;
    NewError->Line = Line;
    strlcpy(NewError->Msg, Msg, 256);
    
    return;
}

void CgCompile(void) {
    	
}
