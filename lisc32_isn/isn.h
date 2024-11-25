//
//  isn.h
//  lisc32_isn
//
//  Created by Noah Wooten on 11/25/24.
//

#ifndef isn_h
#define isn_h
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
    char InstructionDescription[256];
}ISN_INSTRUCTION, *PISN_INSTRUCTION;

typedef struct _ISN_CTX {
    int InstructionCount;
    PSIN_INSTRUCTION Instructions;
}ISN_CTX, *PISN_CTX;

#endif /* isn_h */
