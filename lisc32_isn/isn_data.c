//
//  isn_data.c
//  lisc32_isn
//
//  Created by Noah Wooten on 11/25/24.
//

#include <stdio.h>
#include <string.h>
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

int IsnInstructionCount(void* _Ctx) {
    struct _ISN_CTX* Ctx = _Ctx;
    return Ctx->InstructionCount;
}

char* IsnGetInstructionName(void* _Ctx, int Id) {
    struct _ISN_CTX* Ctx = _Ctx;
    char* Return = Ctx->Instructions[Id].Instruction;
    Return[5] = 0x00;
    while (*Return == ' ' || *Return == '_')
        Return++;
    return Return;
}

BYTE IsnGetInstructionOpcode(void* _Ctx, int Id) {
    struct _ISN_CTX* Ctx = _Ctx;
    return Ctx->Instructions[Id].Opcode;
}

BYTE IsnGetOperandType(void* _Ctx, int Id, BYTE OperandId) {
    struct _ISN_CTX* Ctx = _Ctx;
    return Ctx->Instructions[Id].Operands[OperandId].Type;
}

BYTE IsnGetPhysicalSize(void* _Ctx, int Id, BYTE OperandId) {
    struct _ISN_CTX* Ctx = _Ctx;
    return Ctx->Instructions[Id].Operands[OperandId].PhysicalSize;
}

BYTE IsnGetVirtualSize(void* _Ctx, int Id, BYTE OperandId) {
    struct _ISN_CTX* Ctx = _Ctx;
    return Ctx->Instructions[Id].Operands[OperandId].VirtualSize;
}

char* IsnGetOperandName(void* _Ctx, int Id, BYTE OperandId) {
    struct _ISN_CTX* Ctx = _Ctx;
    Ctx->Instructions[Id].Operands[OperandId].OperandNames[6] = 0x00;
    char* Return = Ctx->Instructions[Id].Operands[OperandId].OperandNames;
    while (*Return == ' ' || *Return == '_')
        Return++;
    return Return;
}

BYTE IsnGetTotalSize(void* _Ctx, int Id) {
    struct _ISN_CTX* Ctx = _Ctx;
    return Ctx->Instructions[Id].InstructionSize;
}

char* IsnGetDescription(void* _Ctx, int Id) {
    struct _ISN_CTX* Ctx = _Ctx;
    return Ctx->Instructions[Id].InstructionDescription;
}

int IsnGetOperandCount(void* _Ctx, int Id) {
    struct _ISN_CTX* Ctx = _Ctx;
    return Ctx->Instructions[Id].OperandCount;
}

int IsnGetInstructionByName(void* _Ctx, const char* Operand) {
    struct _ISN_CTX* Ctx = _Ctx;
    for (int i = 0; i < Ctx->InstructionCount; i++) {
        if (!strcmp(Ctx->Instructions[i].Instruction, Operand))
            return i;
    }
    
    return -1;
}

int IsnGetInstructionByOpcode(void* _Ctx, BYTE Opcode) {
    struct _ISN_CTX* Ctx = _Ctx;
    for (int i = 0; i < Ctx->InstructionCount; i++) {
        if (Ctx->Instructions[i].Opcode == Opcode)
            return i;
    }
    
    return -1;
}
