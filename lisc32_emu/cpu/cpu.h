//
//  cpu.h
//  lisc32_emu
//
//  Created by Noah Wooten on 11/22/24.
//

#ifndef cpu_h
#define cpu_h

#include "../types.h"

#define Instruction(Name) void Name(void)
#define ListInstruction(Name) [__##Name] = Name
#define DeclInstruction(Name) void Name(void);
extern void(*Instructions[256])(void);

enum {
    // General Instructions
    
    ____LDI = 0x00, // __LDI 00-80 (R:04,08=__DEST) (I:64,64=__IMMD) : Loads Immediate to Registers
    ____JMP = 0x01, // __JMP 01-16 (R:04,08=___REG) : Jumps to Register
    ___CALL = 0x02, // _CALL 02-16 (R:04,08=___REG) : Calls to Register
    ____RET = 0x03, // __RET 03-08 : Returns
    ____CMP = 0x04, // __CMP 04-16 (R:04,04=__CMP1) (R:04,04=__CMP2) : Compares two registers
    ____MOV = 0x05, // __MOV 05-16 (R:04,04=__DEST) (R:04,04=___SRC) : Moves register to another register
    __NXCLR = 0x06, // NXCLR 06-08 : NextExecute Clear
    __NXEQL = 0x07, // NXEQL 07-08 : NextExecute If Equal
    __NXZRO = 0x08, // NXZRO 08-08 : NextExecute If Zero
    __NXGRT = 0x09, // NXGRT 09-08 : NextExecute If Greater
    __NXLST = 0x0A, // NXLST 0A-08 : NextExecute If LessThan
    
    // Arithmetic & Bitwise
    ____ADD = 0x20, // __ADD 20-16 (R:04,04=__DEST) (R:04,04=___ARG) : Adds to Destination
    ____SUB = 0x21, // __SUB 21-16 (R:04,04=__DEST) (R:04,04=___ARG) : Subtracts from Destination
    ____MUL = 0x22, // __MUL 22-16 (R:04,04=__DEST) (R:04,04=___ARG) : Multiplies Destination
    ____DIV = 0x23, // __DIV 23-16 (R:04,04=__DEST) (R:04,04=___ARG) : Divides Destination by Argument, Quotient stored
    ____MOD = 0x24, // __MOD 24-16 (R:04,04=__DEST) (R:04,04=___ARG) : Divides Destination by Argument, Remainder stored
    ____AND = 0x25, // __AND 25-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise AND Destiation by Argument
    _____OR = 0x26, // ___OR 26-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise OR Destination by Argument
    ____XOR = 0x27, // __XOR 27-16 (R:04,04=__DEST) (R:04,04=___ARG) : Bitwise XOR Destination by Argument
};

typedef struct _CPU_REGS {
    union {
        struct {
            WORD32 GPRs[16];
            WORD32 SPRs[16];
        };
        
        struct {
            WORD32 r0, r1, r2, r3, r4, r5, r6, r7;
            WORD32 r8, r9, r10, r11, r12, r13, r14, r15;
            
            WORD32 ip, sp;
            WORD32 Reserved[14];
        };
    };
}CPU_REGS, *PCPU_REGS;

typedef struct _CPU_CTX {
    void* Memory;
    WORD32 MemorySize;
    PCPU_REGS Registers;
}CPU_CTX, *PCPU_CTX;

extern PCPU_CTX CpuCtx;
extern PCPU_REGS Rs;

#endif /* cpu_h */
