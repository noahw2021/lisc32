//
//  cpu_ops.c
//  lisc32_emu
//
//  Created by Noah Wooten on 11/25/24.
//

#include <stdio.h>
#include "cpu.h"

DeclInstruction(__LDI);
DeclInstruction(__JMP);
DeclInstruction(_CALL);
DeclInstruction(__RET);
DeclInstruction(__CMP);
DeclInstruction(__MOV);
DeclInstruction(NXCLR);
DeclInstruction(NXEQL);
DeclInstruction(NXZRO);
DeclInstruction(NXGRT);
DeclInstruction(NXLST);
DeclInstruction(__ADD);
DeclInstruction(__SUB);
DeclInstruction(__MUL);
DeclInstruction(__DIV);
DeclInstruction(__MOD);
DeclInstruction(__AND);
DeclInstruction(___OR);
DeclInstruction(__XOR);

void(*Instructions[256])(void) = {
    ListInstruction(__LDI),
    ListInstruction(__JMP),
    ListInstruction(_CALL),
    ListInstruction(__RET),
    ListInstruction(__CMP),
    ListInstruction(__MOV),
    ListInstruction(NXCLR),
    ListInstruction(NXEQL),
    ListInstruction(NXZRO),
    ListInstruction(NXGRT),
    ListInstruction(NXLST),
    ListInstruction(__ADD),
    ListInstruction(__SUB),
    ListInstruction(__MUL),
    ListInstruction(__DIV),
    ListInstruction(__MOD),
    ListInstruction(__AND),
    ListInstruction(___OR),
    ListInstruction(__XOR)
};
