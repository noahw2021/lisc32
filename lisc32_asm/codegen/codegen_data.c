//
//  codegen_data.c
//  lisc32_asm
//
//  Created by Noah Wooten on 11/26/24.
//

#include <stdio.h>
#include "codegen.h"

void CgPut1(BYTE Data) {
    fseek(CgCtx->OutFile, CgCtx->DataPosition, SEEK_SET);
    fwrite(&Data, 1, 1, CgCtx->OutFile);
    CgCtx->DataPosition++;
    if (CgCtx->DataPosition > CgCtx->HighestCode)
        CgCtx->HighestCode = CgCtx->DataPosition;
    
    return;
}

void CgPut2(WORD16 Data) {
    CgPutX(Data, 2);
    return;
}

void CgPut4(WORD32 Data) {
    CgPutX(Data, 4);
    return;
}

void CgPut8(WORD64 Data) {
    CgPutX(Data, 8);
    return;
}

void CgPutX(WORD64 Data, int n) {
    union {
        WORD64 As64;
        BYTE As8[8];
    }Data8;
    Data8.As64 = Data;
    
    for (int i = 0; i < n; i++)
        CgPut1(Data8.As8[i]);
    
    return;
}
