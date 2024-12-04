//
//  isn_parse.c
//  lisc32_isn
//
//  Created by Noah Wooten on 11/25/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "isn.h"
#include "types.h"

typedef struct _ISN_OPERAND {
    char OperandNames[7];
    BYTE PhysicalSize, VirtualSize;
    BYTE Type; // 0 = Register, 1 = IMMD
}ISN_OPERAND, *PISN_OPERAND;

typedef struct _ISN_INSTRUCTION {
    char Instruction[6];
    BYTE Opcode;
    int InstructionSize;
    ISN_OPERAND Operands[2];
    int OperandCount;
    char InstructionDescription[256];
}ISN_INSTRUCTION, *PISN_INSTRUCTION;

typedef struct _ISN_CTX {
    int InstructionCount;
    PISN_INSTRUCTION Instructions;
}ISN_CTX, *PISN_CTX;

void* IsnInit(void) {
    PISN_CTX Ctx;
    Ctx = malloc(sizeof(ISN_CTX));
    memset(Ctx, 0, sizeof(ISN_CTX));
    
    return Ctx;
}
void IsnShutdown(void* _Ctx) {
    struct _ISN_CTX* Ctx = _Ctx;
    
    free(Ctx->Instructions);
    free(Ctx);
    
    return;
}

void IsnLoadData(void* _Ctx, char* _Data) {
    struct _ISN_CTX* Ctx = _Ctx;
    char* Data = _Data;
    
    if (Data[0] == '/')
        return;
    
    if (!Ctx->Instructions) {
        Ctx->Instructions = malloc(sizeof(ISN_INSTRUCTION));
    } else {
        Ctx->Instructions = realloc(Ctx->Instructions,
            sizeof(ISN_INSTRUCTION) * (Ctx->InstructionCount + 1));
    }
    
    PISN_INSTRUCTION NewInst = &Ctx->Instructions[Ctx->InstructionCount++];
    
    // __LDI 00-80 (R:04,08=__DEST) (I:64,64=__IMMD) : Loads Immediate to Registers
    
    // Parse Instruction Mnemonic
    for (int i = 0; i < 5; i++) {
        NewInst->Instruction[i] = *Data;
        if (NewInst->Instruction[i] == '_')
            NewInst->Instruction[i] = ' ';
        Data++;
    }
    
    // Count whitespace
    int i = 0;
    for (i = 0; i < 5; i++) {
        if (NewInst->Instruction[i] != ' ')
            break;
    }
    
    // account for whitespace
    char NewInst2[6];
    strlcpy(NewInst2, NewInst->Instruction + i , 6);
    strcpy(NewInst->Instruction, NewInst2);
    
    // Parse Opcode
    NewInst->Opcode = strtoul(Data, NULL, 16);
    Data += 3;
    
    // Parse Instruction Size
    NewInst->InstructionSize = (int)strtoull(Data, NULL, 10);
    NewInst->InstructionSize = abs(NewInst->InstructionSize);
    Data += 4;
    
    // Parse Operand 1 (if Present)
    if (*Data == '(') {
        // Operand Present
        Data++;
        
        // Parse Type
        if (*Data == 'R')
            NewInst->Operands[0].Type = 0;
        else
            NewInst->Operands[0].Type = 1;
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
        NewInst->OperandCount = 1;
    }
    
    // Parse Operand 2 (if Present)
    if (*Data == '(') {
        // Operand Present
        Data++;
        
        // Parse Type
        if (*Data == 'R')
            NewInst->Operands[1].Type = 0;
        else
            NewInst->Operands[1].Type = 1;
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
        NewInst->OperandCount = 2;
    }
    
    // Parse Instruction Description
    while (*Data != ':')
        Data++;
    Data += 2;
    
    strlcpy(NewInst->InstructionDescription, Data, 256);
    
    return;
}
