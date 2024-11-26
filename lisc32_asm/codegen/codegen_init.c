//
//  codegen_init.c
//  lisc32_asm
//
//  Created by Noah Wooten on 11/26/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

PCODEGEN_CTX CgCtx;

void CgInit(void) {
    CgCtx = malloc(sizeof(CODEGEN_CTX));
    memset(CgCtx, 0, sizeof(CODEGEN_CTX));
    
    CgCtx->ErrorMax = 1024;
    CgCtx->Errors = malloc(sizeof(CODEGEN_ERROR) * CgCtx->ErrorMax);
    memset(CgCtx->Errors, 0, sizeof(CODEGEN_ERROR) * CgCtx->ErrorMax);
    
    CgCtx->InFileMax = 16;
    CgCtx->InFiles = malloc(sizeof(FILE*) * CgCtx->InFileMax);
    memset(CgCtx->InFiles, 0, sizeof(FILE*) * CgCtx->InFileMax);
    
    CgCtx->SymbolMax = 1024;
    CgCtx->Symbols = malloc(sizeof(CODEGEN_SYMBOL) * CgCtx->SymbolMax);
    memset(CgCtx->Symbols, 0, sizeof(CODEGEN_SYMBOL) * CgCtx->SymbolMax);
    
    return;
}

void CgShutdown(void) {
    if (CgCtx) {
        if (CgCtx->Errors)
            free(CgCtx->Errors);
        
        for (int i = 0; i < CgCtx->InFileMax; i++) {
            if (CgCtx->InFiles[i])
                fclose(CgCtx->InFiles[i]);
        }
        
        if (CgCtx->InFiles)
            free(CgCtx->InFiles);
        
        free(CgCtx);
    }
    
    return;
}
