//
//  codegen_parse.c
//  lisc32_asm
//
//  Created by Noah Wooten on 11/26/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "codegen.h"
#include "../isn/isn_imports.h"

void CgParseLine(char* _Line) {
    // MOV r0, r1
    // LDI r1, 43298h
    
    char* Line = _Line;
    CgCtx->CurrentLine++; // comments count as a line
    
    // Ignore Comments
    if (*Line == ';')
        return;
    if (strstr(Line, ";"))
        *strstr(Line, ";") = 0x00;
    
    // Remove New Lines
    if (strstr(Line, "\n"))
        *strstr(Line, "\n") = 0x00;
    if (strstr(Line, "\r"))
        *strstr(Line, "\r") = 0x00;
    
    // Parse Special Commands
    if (*Line == '-') {
        switch (Line[1]) {
            case 'a': // Address
                Line += 2;
                WORD64 NewAddr = 0;
                if (strstr(Line, "h")) { // Parse as Base 16
                    NewAddr = strtoull(Line, NULL, 16);
                } else { // Parse as Base 10
                    NewAddr = strtoull(Line, NULL, 10);
                }
                
                CgCtx->DataPosition = NewAddr;
                if (CgCtx->DataPosition > CgCtx->HighestCode)
                    CgCtx->HighestCode = CgCtx->DataPosition;
            case 'c':
                // Compile
                CgCompile();
                return;
            default:
                printf("Unknown special command '%s'.\n", Line);
                break;
        }
    }
    
    // Parse Subroutines
    if (strstr(Line, ":")) {
        
    }
    
    // Code Generation Variables
    BYTE Opcode = 0;
    WORD64 Argument1 = 0, Argument2 = 0;
    BYTE BothRegs = 0, HasImmd2 = 0;
    
    // Parse Mnemonic
    char Mnemonic[7];
    int i = 0;
    while (*Line != ' ') {
        Mnemonic[i++] = *Line;
        Line++;
        if (i == 7)
            break;
    }
    int IsnId = IsnGetInstructionByName(IsnCtx, Mnemonic);
    if (IsnId == -1) {
        CgError(CgCtx->CurrentLine, ERROR_LOGICAL_INVOP, "Invalid Operation");
        return;
    }
    Opcode = IsnGetInstructionOpcode(IsnCtx, IsnId);
    
    // Parse Operand 1
    char Operand1Text[256];
    i = 0;
    while (*Line && *Line != ',') {
        Operand1Text[i++] = *Line;
        Line++;
    }
    if (IsnGetOperandType(IsnCtx, IsnId, 0) == 0) { // Register
        Argument1 = atoi(Operand1Text + 1);
        BothRegs = 2;
    } else { // Immediate
        HasImmd2 = 1;
        if (InRange(*Operand1Text, '0', '9')) { // Integer
            if (strstr(Operand1Text, "h")) // parse as base 16
                Argument1 = strtoul(Operand1Text, NULL, 16);
            else
                Argument1 = strtoul(Operand1Text, NULL, 10);
        } else { // Symbol
            Argument1 = CgLinkGetSymbol(Operand1Text, 1); // Offset of 1 accounts for opcode
        }
    }
    
    // Parse Operand 2
    char Operand2Text[256];
    i = 0;
    while (*Line && *Line != ',') {
        Operand2Text[i++] = *Line;
        Line++;
    }
    if (IsnGetOperandType(IsnCtx, IsnId, 1) == 0) { // Register
        Argument1 = atoi(Operand2Text + 1);
        if (BothRegs == 2)
            BothRegs = 1;
    } else { // Immediate
        HasImmd2 = 1;
        if (InRange(*Operand2Text, '0', '9')) { // Integer
            if (strstr(Operand2Text, "h")) // parse as base 16
                Argument2 = strtoul(Operand2Text, NULL, 16);
            else
                Argument2 = strtoul(Operand2Text, NULL, 10);
        } else { // Symbol
            Argument2 = CgLinkGetSymbol(Operand2Text,
                1 + (IsnGetPhysicalSize(IsnCtx, IsnId, 0) / 8));
            // Offset of 1 accounts for opcode, + PhysSize of first operand
        }
    }
    
    // Generate Code
    CgPut1(Opcode);
    if (BothRegs == 1) {
        union {
            BYTE As8;
            struct {
                BYTE As4_0 : 4;
                BYTE As4_1 : 4;
            };
        }Output;
        Output.As4_0 = Argument1;
        Output.As4_1 = Argument2;
        
        CgPut1(Output.As8);
    } else {
        if (!HasImmd2) {
            CgPut1(Argument1); // just one register argument
        } else {
            CgPut1(Argument1); // emplace Arg1
            CgPutX(Argument2, IsnGetPhysicalSize(IsnCtx, IsnId, 1) / 8);
        }
    }
}
