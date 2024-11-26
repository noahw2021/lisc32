//
//  codegen.h
//  lisc32_asm
//
//  Created by Noah Wooten on 11/26/24.
//

#ifndef codegen_h
#define codegen_h

#include "../types.h"
#include <stdio.h>

typedef struct _CODEGEN_ERROR {
    int ErrorCode;
    int Line;
}CODEGEN_ERROR, *PCODEGEN_ERROR

typedef struct _CODEGEN_CTX {
    int LineCount, CurrentLine;
    
    WORD64 DataPosition;
    WORD64 HighestCode;
    WORD64 ReferencePtr;
    
    int ErrorCount, ErrorMax;
    PCODEGEN_ERROR Errors;
    
    FILE* OutFile;
    
    int InFileCount, InFileMax;
    FILE** InFiles;
}CODEGEN_CTX, *PCODEGEN_CTX;
extern PCODEGEN_CTX CgCtx;

void CgInit(void);
void CgShutdown(void);

void CgParseLine(char* Line);
int CgGetErrorCount(void);
void CgCompile(void);

void CgPut1(BYTE Data);
void CgPut2(WORD16 Data);
void CgPut4(WORD32 Data);
void CgPut8(WORD64 Data);
void CgPutX(WORD64 Data, int n);

#endif /* codegen_h */
