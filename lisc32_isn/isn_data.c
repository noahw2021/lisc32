//
//  isn_data.c
//  lisc32_isn
//
//  Created by Noah Wooten on 11/25/24.
//

#include <stdio.h>
#include <string.h>
#include "isn.h"

void* IsnInit(void) {
    PISN_CTX Ctx;
    Ctx = malloc(sizeof(ISN_CTX));
    memset(Ctx, 0, sizeof(ISN_CTX));
    
    return Ctx;
}
void IsnShutdown(void* Ctx) {
    free(Ctx->Instructions);
    free(Ctx);
    
    return;
}

void IsnLoadData(void* _Ctx, char* _Data) {
    PSIN_CTX Ctx = _Ctx;
    if (Data[0] == '/')
        return;
    
    if (!Ctx->Instructions) {
        Ctx->Instructions = malloc(sizeof(ISN_INSTRUCTION));
    } else {
        Ctx->Instructions = realloc(Ctx->Instructions,
            sizeof(ISN_INSTRUCTION) * (Ctx->InstructionCount + 1));
    }
    
    PISN_INSTRUCTION NewInst = &Ctx->Instructions[Ctx->InstructionCount++];
    char* Data = _Data;
    
    // __LDI 00-80 (R:04,08=__DEST) (I:64,64=__IMMD) : Loads Immediate to Registers
    
    // Parse Instruction Mnemonic
    for (int i = 0; i < 5; i++) {
        NewInst->Instruction[i] = *Data;
        Data++;
    }
    
    // Parse Opcode
    NewInst->Opcode = strtoul(Data, NULL, 16);
    Data += 3;
    
    // Parse Instruction Size
    NewInst->InstructionSize = strtoull(Data, NULL, 10);
    Data += 3;
    
    // Parse Operand 1 (if Present)
    if (*Data == '(') {
        // Operand Present
        Data++;
        
        // Parse Type
        if (*Data == 'R')
            NewInst->Operands[0] = 0;
        else
            NewInst->Operands[0] = 1;
        Data += 2;
        
        // Parse Virtual Size
        NewInst->Operands[0].VirtualSize = strtoull(Data, NULL, 10);
        Data += 3;
        
        // Parse Physical Size
        NewInst->Operands[0].PhysicalSize = strtoull(Data, NULL, 10);
        Data += 3;
        
        // Parse Operand Name
        for (int i = 0; i < 6; i++) {
            NewInst->Operands[0].OperandNames[i] = *Data;
            Data++;
        }
        
        // Account for ') '
        Data += 2;
    }
    
    // Parse Operand 2 (if Present)
    if (*Data == '(') {
        // Operand Present
        Data++;
        
        // Parse Type
        if (*Data == 'R')
            NewInst->Operands[1] = 0;
        else
            NewInst->Operands[1] = 1;
        Data += 2;
        
        // Parse Virtual Size
        NewInst->Operands[1].VirtualSize = strtoull(Data, NULL, 10);
        Data += 3;
        
        // Parse Physical Size
        NewInst->Operands[1].PhysicalSize = strtoull(Data, NULL, 10);
        Data += 3;
        
        // Parse Operand Name
        for (int i = 0; i < 6; i++) {
            NewInst->Operands[1].OperandNames[i] = *Data;
            Data++;
        }
        
        // Account for ') '
        Data += 2;
    }
    
    // Parse Instruction Description
    while (*Data != ':')
        Data++;
    Data++;
    
    strlcpy(NewInst->InstructionDescription, 256, Data);
    
    return;
}
