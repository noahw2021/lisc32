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
    printf("\n\nBeginning Compilation...\n");
    
    // link binary
    for (int i = 0; i < CgCtx->SymbolCount; i++) {
        PCODEGEN_SYMBOL ThisSymbol = &CgCtx->Symbols[i];
        if (!ThisSymbol->IsResolved) {
            char ErrorMsg[256];
            sprintf(ErrorMsg, "Unresolved Symbol: %s", ThisSymbol->SymbolName);
            CgError(CgCtx->LineCount, ERROR_LINKER_UNRESOLVED, ErrorMsg);
        }
        
        if (ThisSymbol->Locations)
            free(ThisSymbol->Locations);
    }
    
    if (CgCtx->Symbols)
        free(CgCtx->Symbols);
    
    if (CgCtx->InFiles)
        free(CgCtx->InFiles);
    
    for (int i = 0; i < CgCtx->ErrorCount; i++) {
        PCODEGEN_ERROR ThisError = &CgCtx->Errors[i];
        
        printf("[E%04i]: %s (Line %i)\n", ThisError->ErrorCode,
            ThisError->Msg, ThisError->Line);
    }
    
    if (CgCtx->Errors)
        free(CgCtx->Errors);
    
    for (int i = 0; i < CgCtx->InFileCount; i++) {
        if (CgCtx->InFiles[i])
            fclose(CgCtx->InFiles[i]);
    }
    
    if (CgCtx->InFiles)
        free(CgCtx->InFiles);
    
    printf("Compiled. Producted %04llX bytes.\n", CgCtx->HighestCode);
    return;
}

WORD64 CgLinkGetSymbol(char* SymbolName, int Offset) {
    for (int i = 0; i < CgCtx->SymbolCount; i++) {
        PCODEGEN_SYMBOL ThisSymbol = &CgCtx->Symbols[i];
        
        // if the symbol exists
        if (!strcmp(ThisSymbol->SymbolName, SymbolName)) {
            if (ThisSymbol->IsResolved) {
                return ThisSymbol->Resolution;
            } else {
                // Vector Pusback
                if (!ThisSymbol->Locations) {
                    ThisSymbol->Locations = malloc(sizeof(WORD64));
                    ThisSymbol->Locations[0] = CgCtx->DataPosition + Offset;
                    ThisSymbol->LocationCount = 1;
                    return ThisSymbol->Resolution;
                } else {
                    ThisSymbol->Locations = realloc(ThisSymbol->Locations,
                        sizeof(WORD64) * (ThisSymbol->LocationCount + 1));
                    ThisSymbol->Locations[ThisSymbol->LocationCount] =
                        CgCtx->DataPosition + Offset;
                    ThisSymbol->LocationCount++;
                    return ThisSymbol->Resolution;
                }
            }
        }
    }
    
    // if it doesn't
    
    if (CgCtx->SymbolCount == CgCtx->SymbolMax) {
        CgCtx->SymbolMax += 512;
        CgCtx->Symbols = realloc(CgCtx->Symbols,
            sizeof(CODEGEN_SYMBOL) * CgCtx->SymbolMax);
    }
    
    PCODEGEN_SYMBOL NewSymbol = &CgCtx->Symbols[CgCtx->SymbolCount];
    CgCtx->SymbolCount++;
    memset(NewSymbol, 0, sizeof(CODEGEN_SYMBOL));
    
    strlcpy(NewSymbol->SymbolName, SymbolName, 256);
    NewSymbol->LocationCount = 1;
    NewSymbol->Locations = malloc(sizeof(WORD64));
    NewSymbol->Locations[0] = CgCtx->DataPosition + Offset;
    
    return NewSymbol->Resolution;
}

void CgLinkResolveSymbol(char* SymbolName, WORD64 Ptr) {
    for (int i = 0; i < CgCtx->SymbolCount; i++) {
        PCODEGEN_SYMBOL ThisSymbol = &CgCtx->Symbols[i];
        if (!strcmp(ThisSymbol->SymbolName, SymbolName)) {
            // the symbol exists
            ThisSymbol->Resolution = Ptr;
            ThisSymbol->IsResolved = 1;
            
            for (int l = 0; l < ThisSymbol->LocationCount; l++) {
                fseek(CgCtx->OutFile, ThisSymbol->Locations[l], SEEK_SET);
                fwrite(&Ptr, 8, 1, CgCtx->OutFile);
            }
            
            return;
        }
    }
    
    // it doesn't
    if (CgCtx->SymbolCount == CgCtx->SymbolMax) {
        CgCtx->SymbolMax += 512;
        CgCtx->Symbols = realloc(CgCtx->Symbols,
            sizeof(CODEGEN_SYMBOL) * CgCtx->SymbolMax);
    }
    
    PCODEGEN_SYMBOL NewSymbol = &CgCtx->Symbols[CgCtx->SymbolCount];
    CgCtx->SymbolCount++;
    memset(NewSymbol, 0, sizeof(CODEGEN_SYMBOL));
    
    strlcpy(NewSymbol->SymbolName, SymbolName, 256);
    NewSymbol->IsResolved = 1;
    NewSymbol->Resolution = Ptr;
    
    return;
}
