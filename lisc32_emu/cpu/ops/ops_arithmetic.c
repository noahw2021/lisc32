//
//  ops_arithmetic.c
//  lisc32_emu
//
//  Created by Noah Wooten on 11/26/24.
//

#include <stdio.h>
#include "../cpu.h"
#include "../mmu/mmu.h"

void __ADD(void) {
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }DoubleByte;
    
    BYTE Register = MmuRead1();
    DoubleByte.As8 = Register;
    
    WORD32* Destination = &Rs->GPRs[DoubleByte.As4_0];
    WORD32* Source = &Rs->GPRs[DoubleByte.As4_1];
    
    *Destination += *Source;
    
    return;
} // __ADD 20-16 (R:04,04=__DEST) (R:04,04=___ARG) : Adds to Destination
    
void __SUB(void) {
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }DoubleByte;
    
    BYTE Register = MmuRead1();
    DoubleByte.As8 = Register;
    
    WORD32* Destination = &Rs->GPRs[DoubleByte.As4_0];
    WORD32* Source = &Rs->GPRs[DoubleByte.As4_1];
    
    *Destination -= *Source;
    
    return;
} // __SUB 21-16 (R:04,04=__DEST) (R:04,04=___ARG) : Subtracts from Destination

void __MUL(void) {
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }DoubleByte;
    
    BYTE Register = MmuRead1();
    DoubleByte.As8 = Register;
    
    WORD32* Destination = &Rs->GPRs[DoubleByte.As4_0];
    WORD32* Source = &Rs->GPRs[DoubleByte.As4_1];
    
    *Destination *= *Source;
    
    return;
} // __MUL 22-16 (R:04,04=__DEST) (R:04,04=___ARG) : Multiplies Destination

void __DIV(void) {
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }DoubleByte;
    
    BYTE Register = MmuRead1();
    DoubleByte.As8 = Register;
    
    WORD32* Destination = &Rs->GPRs[DoubleByte.As4_0];
    WORD32* Source = &Rs->GPRs[DoubleByte.As4_1];
    
    *Destination /= *Source;
    
    return;
} // __DIV 23-16 (R:04,04=__DEST) (R:04,04=___ARG) : Divides Destination by Argument, Quotient stored

void __MOD(void) {
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }DoubleByte;
    
    BYTE Register = MmuRead1();
    DoubleByte.As8 = Register;
    
    WORD32* Destination = &Rs->GPRs[DoubleByte.As4_0];
    WORD32* Source = &Rs->GPRs[DoubleByte.As4_1];
    
    *Destination %= *Source;
    
    return;
} // __MOD 24-16 (R:04,04=__DEST) (R:04,04=___ARG) : Divides Destination by Argument, Remainder stored

void __AND(void) {
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }DoubleByte;
    
    BYTE Register = MmuRead1();
    DoubleByte.As8 = Register;
    
    WORD32* Destination = &Rs->GPRs[DoubleByte.As4_0];
    WORD32* Source = &Rs->GPRs[DoubleByte.As4_1];
    
    *Destination &= *Source;
    
    return;
} // __AND 25-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise AND Destiation by Argument

void ___OR(void) {
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }DoubleByte;
    
    BYTE Register = MmuRead1();
    DoubleByte.As8 = Register;
    
    WORD32* Destination = &Rs->GPRs[DoubleByte.As4_0];
    WORD32* Source = &Rs->GPRs[DoubleByte.As4_1];
    
    *Destination |= *Source;
    
    return;
} // ___OR 26-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise OR Destination by Argument

void __XOR(void) {
    union {
        BYTE As8;
        struct {
            BYTE As4_0 : 4;
            BYTE As4_1 : 4;
        };
    }DoubleByte;
    
    BYTE Register = MmuRead1();
    DoubleByte.As8 = Register;
    
    WORD32* Destination = &Rs->GPRs[DoubleByte.As4_0];
    WORD32* Source = &Rs->GPRs[DoubleByte.As4_1];
    
    *Destination ^= *Source;
    
    return;
} // __XOR 27-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise XOR Destination by Argument
