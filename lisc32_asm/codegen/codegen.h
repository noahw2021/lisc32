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
    char Msg[256];
}CODEGEN_ERROR, *PCODEGEN_ERROR;

typedef struct _CODEGEN_SYMBOL {
    WORD64 Resolution;
    char SymbolName[256];
    BYTE IsResolved;
    
    WORD64 LocationCount;
    PWORD64 Locations;
}CODEGEN_SYMBOL, *PCODEGEN_SYMBOL;

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
    BYTE ForceEOF[1024]; // shitty method
    int CurrentFile;
    
    WORD64 SymbolCount, SymbolMax;
    PCODEGEN_SYMBOL Symbols;
    BYTE CompileComplete;
}CODEGEN_CTX, *PCODEGEN_CTX;
extern PCODEGEN_CTX CgCtx;

// codegen_init.c
void CgInit(void);
void CgShutdown(void);

// codegen_parse.c
void CgParseLine(char* Line);

// codegen_compiler.c
int CgGetErrorCount(void);
void CgError(int Line, int Code, const char* Msg);
void CgCompile(void);
WORD64 CgLinkGetSymbol(char* SymbolName, int Offset);
void CgLinkResolveSymbol(char* SymbolName, WORD64 Ptr);

// codegen_files.c
void CgAddFile(char* FileName);
char* CgReadLine(char* Line, int Max);

// codegen_data.c
void CgPut1(BYTE Data);
void CgPut2(WORD16 Data);
void CgPut4(WORD32 Data);
void CgPut8(WORD64 Data);
void CgPutX(WORD64 Data, int n);

// error codes

enum {
    ERROR_PRAGMATICS = 0,
    
    ERROR_SEMTANICS = 1000,
    ERROR_SEMTANICS_BADFILE = 1001,
    
    ERROR_LINKER = 2000,
    ERROR_LINKER_UNRESOLVED = 2001,
    
    ERROR_LOGICAL = 3000,
    ERROR_LOGICAL_INVOP = 3001,
};

#endif /* codegen_h */
