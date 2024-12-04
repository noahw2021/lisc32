//
//  codegen_files.c
//  lisc32_asm
//
//  Created by Noah Wooten on 11/26/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

void CgAddFile(char* FileName) {
    FILE* NewFile = fopen(FileName, "r");
    
    if (!NewFile) {
        CgError(CgCtx->CurrentLine, ERROR_SEMTANICS_BADFILE,
            "Could not open file.");
        return;
    }
    
    if (CgCtx->InFileCount == CgCtx->InFileMax) {
        CgCtx->InFileMax += 4;
        CgCtx->InFiles = realloc(CgCtx->InFiles,
            sizeof(FILE*) * CgCtx->InFileMax);
    }
    
    CgCtx->InFiles[CgCtx->InFileCount] = NewFile;
    CgCtx->InFileCount++;
    
    return;
}

char* CgReadLine(char* Line, int Max) {
    for (int i = 0; i < CgCtx->InFileCount; i++) {
        if (!feof(CgCtx->InFiles[i]) && !CgCtx->ForceEOF[i]) {
            fgets(Line, Max, CgCtx->InFiles[i]);
            CgCtx->CurrentFile = i;
            return Line;
        }
    }
    
    // no more files
    strcpy(Line, "-c ; __EOF");
    return Line;
}
