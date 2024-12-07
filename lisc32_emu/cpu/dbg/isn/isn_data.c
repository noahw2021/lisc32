//
//  isn_data.c
//  lisc32_emu
//
//  Created by Noah Wooten on 12/6/24.
//

#include <stdio.h>
#include "isn_imports.h"

void IsniLoadData(void) {
    IsnLoadData(IsnCtx, "__LDI 00-80 (R:04,08=__DEST) (I:64,64=__IMMD) : Loads Immediate to Registers");
    IsnLoadData(IsnCtx, "__JMP 01-16 (R:04,08=___REG) : Jumps to Register");
    IsnLoadData(IsnCtx, "_CALL 02-16 (R:04,08=___REG) : Calls to Register");
    IsnLoadData(IsnCtx, "__RET 03-08 : Returns");
    IsnLoadData(IsnCtx, "__CMP 04-16 (R:04,04=__CMP1) (R:04,04=__CMP2) : Compares two registers");
    IsnLoadData(IsnCtx, "__MOV 05-16 (R:04,04=__DEST) (R:04,04=___SRC) : Moves register to another register");
    IsnLoadData(IsnCtx, "NXCLR 06-08 : NextExecute Clear");
    IsnLoadData(IsnCtx, "NXEQL 07-08 : NextExecute If Equal");
    IsnLoadData(IsnCtx, "NXZRO 08-08 : NextExecute If Zero");
    IsnLoadData(IsnCtx, "NXGRT 09-08 : NextExecute If Greater");
    IsnLoadData(IsnCtx, "NXLST 0A-08 : NextExecute If LessThan");
    IsnLoadData(IsnCtx, "__ADD 20-16 (R:04,04=__DEST) (R:04,04=___ARG) : Adds to Destination");
    IsnLoadData(IsnCtx, "__SUB 21-16 (R:04,04=__DEST) (R:04,04=___ARG) : Subtracts from Destination");
    IsnLoadData(IsnCtx, "__MUL 22-16 (R:04,04=__DEST) (R:04,04=___ARG) : Multiplies Destination");
    IsnLoadData(IsnCtx, "__DIV 23-16 (R:04,04=__DEST) (R:04,04=___ARG) : Divides Destination by Argument, Quotient stored");
    IsnLoadData(IsnCtx, "__MOD 24-16 (R:04,04=__DEST) (R:04,04=___ARG) : Divides Destination by Argument, Remainder stored");
    IsnLoadData(IsnCtx, "__AND 25-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise AND Destiation by Argument");
    IsnLoadData(IsnCtx, "___OR 26-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise OR Destination by Argument");
    IsnLoadData(IsnCtx, "__XOR 27-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise XOR Destination by Argument");
    
    return;
}
