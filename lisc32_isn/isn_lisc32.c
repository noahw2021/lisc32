//
//  isn_lisc32.c
//  lisc32_isn
//
//  Created by Noah Wooten on 12/17/24.
//

#include <stdio.h>
#include "isn.h"
#include "exports.h"

void IsniLoadLisc32(void* Ctx) {
    IsnLoadData(Ctx, "__LDI 00-40 (R:04,08=__DEST) (I:32,32=__IMMD) : Loads Immediate to Registers");
    IsnLoadData(Ctx, "__JMP 01-16 (R:04,08=___REG) : Jumps to Register");
    IsnLoadData(Ctx, "_CALL 02-16 (R:04,08=___REG) : Calls to Register");
    IsnLoadData(Ctx, "__RET 03-08 : Returns");
    IsnLoadData(Ctx, "__CMP 04-16 (R:04,04=__CMP1) (R:04,04=__CMP2) : Compares two registers");
    IsnLoadData(Ctx, "__MOV 05-16 (R:04,04=__DEST) (R:04,04=___SRC) : Moves register to another register");
    IsnLoadData(Ctx, "NXCLR 06-08 : NextExecute Clear");
    IsnLoadData(Ctx, "NXEQL 07-08 : NextExecute If Equal");
    IsnLoadData(Ctx, "NXZRO 08-08 : NextExecute If Zero");
    IsnLoadData(Ctx, "NXGRT 09-08 : NextExecute If Greater");
    IsnLoadData(Ctx, "NXLST 0A-08 : NextExecute If LessThan");
    IsnLoadData(Ctx, "CLFLG 0B-08 : Clear Flags");
    IsnLoadData(Ctx, "CPFLG 0C-40 (R:04,08=_FLAGS) : Copy Flags");
    IsnLoadData(Ctx, "__ADD 20-16 (R:04,04=__DEST) (R:04,04=___ARG) : Adds to Destination");
    IsnLoadData(Ctx, "__SUB 21-16 (R:04,04=__DEST) (R:04,04=___ARG) : Subtracts from Destination");
    IsnLoadData(Ctx, "__MUL 22-16 (R:04,04=__DEST) (R:04,04=___ARG) : Multiplies Destination");
    IsnLoadData(Ctx, "__DIV 23-16 (R:04,04=__DEST) (R:04,04=___ARG) : Divides Destination by Argument, Quotient stored");
    IsnLoadData(Ctx, "__MOD 24-16 (R:04,04=__DEST) (R:04,04=___ARG) : Divides Destination by Argument, Remainder stored");
    IsnLoadData(Ctx, "__AND 25-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise AND Destiation by Argument");
    IsnLoadData(Ctx, "___OR 26-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise OR Destination by Argument");
    IsnLoadData(Ctx, "__XOR 27-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise XOR Destination by Argument");
    IsnLoadData(Ctx, "LDMEM 40-16 (R:04,04=__DEST) (R:04,04=ADDRES) : Loads memory into a register");
    IsnLoadData(Ctx, "STMEM 41-16 (R:04,04=__DEST) (R:04,04=SOURCE) : Stores memory from register");
    
}
