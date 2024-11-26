//
//  isn_data.c
//  lisc32_isn
//
//  Created by Noah Wooten on 11/25/24.
//

#include <stdio.h>
#include "isn.h"
#include "types.h"

int IsnInstructionCount(void* _Ctx) {
    PSIN_CTX Ctx = _Ctx;
    return Ctx->InstructionCount;
}

char* IsnGetInstructionName(void* _Ctx, int Id) {
    PSIN_CTX Ctx = _Ctx;
    return Ctx->Instructions[Id].Instruction;
}

BYTE IsnGetInstructinOpcode(void* _Ctx, int Id) {
    PSIN_CTX Ctx = _Ctx;
    return Ctx->Instructions[Id].Opcode;
}

BYTE IsnGetOperandType(void* _Ctx, int Id, BYTE OperandId) {
    PSIN_CTX Ctx = _Ctx;
    return Ctx->Instructions[Id].Operands[OperandId].Type;
}

BYTE IsnGetPhysicalSize(void* _Ctx, int Id, BYTE OperandId) {
    PSIN_CTX Ctx = _Ctx;
    return Ctx->Instructions[Id].Operands[OperandId].PhysicalSize;
}

BYTE IsnGetUsableSize(void* _Ctx, int Id, BYTE OperandId) {
    PSIN_CTX Ctx = _Ctx;
    return Ctx->Instructions[Id].Operands[OperandId].VirtualSize;
}

char* IsnGetOperandName(void* _Ctx, int Id, BYTE OperandId) {
    PSIN_CTX Ctx = _Ctx;
    return Ctx->Instructions[Id].Operands[OperandId].OperandNames;
}

BYTE IsnGetTotalSize(void* _Ctx, int Id) {
    PSIN_CTX Ctx = _Ctx;
    return Ctx->Instructions[Id].InstructionSize;
}

char* IsnGetDescription(void* _Ctx, int Id) {
    PSIN_CTX Ctx = _Ctx;
    return Ctx->Instructions[Id].InstructionDescription;
}

int IsnGetOperandCount(void* Ctx, int Id) {
    PSIN_CTX Ctx = _Ctx;
    return Ctx->Instructions[Id].OperandCount;
}

int IsnGetInstructionByName(void* Ctx, const char* Operand) {
    PSIN_CTX Ctx = _Ctx;
    for (int i = 0; i < Ctx->InstructionCount; i++) {
        if (!strcmp(Ctx->Instructions[i].Instruction, Operand))
            return i;
    }
    
    return -1;
}

int IsnGetInstructionByOpcode(void* Ctx, BYTE Opcode) {
    PSIN_CTX Ctx = _Ctx;
    for (int i = 0; i < Ctx->InstructionCount; i++) {
        if (Ctx->Instructions[i].Opcode == Opcode)
            return i;
    }
    
    return -1;
}
