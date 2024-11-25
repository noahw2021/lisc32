//
//  cpu.h
//  lisc32_emu
//
//  Created by Noah Wooten on 11/22/24.
//

#ifndef cpu_h
#define cpu_h

#define Instruction(Name) void Name(void)
#define ListInstruction(Name) [__##Name] = Name
#define DeclInstruction(Name) void Name(void);
extern void(*Instructions[256])(void);

enum {
    // General Instructions
    
    ____LDI = 0x00, // __LDI 00-80 (R:04,08=__DEST) (I:64,64=__IMMD)
    ____JMP = 0x01, // __JMP 01-16 (R:04,08=___REG)
    ___CALL = 0x02, // _CALL 02-16 (R:04,08=___REG)
    ____RET = 0x03, // __RET 03-08
    ____CMP = 0x04, // __CMP 04-16 (R:04,04=__CMP1) (R:04,04=__CMP2)
    ____MOV = 0x05, // __MOV 05-16 (R:04,04=__DEST) (R:04,04=___SRC)
    __NXCLR = 0x06, // NXCLR 06-08
    __NXEQL = 0x07, // NXEQL 07
    __NXZRO = 0x08, // NXZRO 08
    __NXGRT = 0x09, // NXGRT 09
    __NXLST = 0x0A, // NXLST 0A
    
    // Arithmetic & Bitwise
    ____ADD = 0x20, // __ADD 20
    ____SUB = 0x21, // __SUB 21
    ____MUL = 0x22, // __MUL 22
    ____DIV = 0x23, // __DIV 23
    ____MOD = 0x24, // __MOD 24
    ____AND = 0x25, // __AND 25
    _____OR = 0x26, // ___OR 26
    ____XOR = 0x27, // __XOR 27
};

#endif /* cpu_h */
