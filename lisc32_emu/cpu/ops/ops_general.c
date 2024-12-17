//
//  ops_general.c
//  lisc32_emu
//
//  Created by Noah Wooten on 11/25/24.
//

#include <stdio.h>
#include "../cpu.h"
#include "../mmu/mmu.h"

void __LDI(void) {
    BYTE Register = MmuRead1();
    WORD32* Destination = &Rs->GPRs[Register & 0xF];
    WORD32 Immediate = MmuRead4();
    
    *Destination = Immediate;
    return;
} // __LDI 00-80 (R:04,08=__DEST) (I:32,32=__IMMD) : Loads Immediate to Registers

void __JMP(void) {
    BYTE Register = MmuRead1();
    WORD32* Source = &Rs->GPRs[Register & 0xF];
    
    Rs->ip = *Source;
    return;
} // __JMP 01-16 (R:04,08=_REG) : Jumps to Register

void _CALL(void) {
    BYTE Register = MmuRead1();
    WORD32* Source = &Rs->GPRs[Register & 0xF];
    
    MmuPush(Rs->ip);
    Rs->ip = *Source;
    
    return;
} // _CALL 02-16 (R:04,08=_REG) : Calls to Register

void __RET(void) {
    WORD32 Ret = MmuPull();
    Rs->ip = Ret;
    return;
} // __RET 03-08 : Returns

void __CMP(void) {
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }DoubleByte;
    DoubleByte.As8 = MmuRead1();
    
    WORD32* Argument1 = &Rs->GPRs[DoubleByte.As4_0];
    WORD32* Argument2 = &Rs->GPRs[DoubleByte.As4_1];
    
    if (*Argument1 == *Argument2)
        Rs->flags |= CPUFLAG_EQUAL;
    if (*Argument1 > *Argument2)
        Rs->flags |= CPUFLAG_GREATTHAN;
    if (*Argument1 < *Argument2)
        Rs->flags |= CPUFLAG_LESSTHAN;
    
    return;
        
} // __CMP 04-16 (R:04,04=__CMP1) (R:04,04=__CMP2) : Compares two registers

void __MOV(void) {
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }DoubleByte;
    DoubleByte.As8 = MmuRead1();
    
    WORD32* Destination = &Rs->GPRs[DoubleByte.As4_0];
    WORD32* Source = &Rs->GPRs[DoubleByte.As4_1];
    
    *Destination = *Source;
    return;
} // __MOV 05-16 (R:04,04=__DEST) (R:04,04=__SRC) : Moves register to another register

void NXCLR(void) {
    Rs->flags &= ~CPUFLAG_NXSKIP;
    return;
} // NXCLR 06-08 : NextExecute Clear

void NXEQL(void) {
    Rs->flags = !(Rs->flags & CPUFLAG_EQUAL);
    return;
} // NXEQL 07-08 : NextExecute If Equal

void NXZRO(void) {
    Rs->flags = !(Rs->flags & CPUFLAG_ZERO);
    return;
} // NXZRO 08-08 : NextExecute If Zero

void NXGRT(void) {
    Rs->flags = !(Rs->flags & CPUFLAG_GREATTHAN);
    return;
} // NXGRT 09-08 : NextExecute If Greater

void NXLST(void) {
    Rs->flags = !(Rs->flags & CPUFLAG_LESSTHAN);
    return;
} // NXLST 0A-08 : NextExecute If LessThan

void CLFLG(void) {
    Rs->flags ^= Rs->flags;
    return;
} // CLFLG 0B-08 : Clear Flags

void CPFLG(void) {
    WORD32 Immediate = MmuRead4();
    Rs->flags = Immediate;
    return;
} // CPFLG 0C-40 : Copy Flags
