//
//  ops_general.c
//  lisc32_emu
//
//  Created by Noah Wooten on 11/25/24.
//

#include <stdio.h>
#include "../cpu.h"

void __LDI(void) {
    
} // __LDI 00-80 (R:04,08=__DEST) (I:64,64=__IMMD) : Loads Immediate to Registers

void __JMP(void) {
        
} // __JMP 01-16 (R:04,08=_REG) : Jumps to Register

void _CALL(void) {
            
} // _CALL 02-16 (R:04,08=_REG) : Calls to Register

void __RET(void) {
                
} // __RET 03-08 : Returns

void __CMP(void) {
                    
} // __CMP 04-16 (R:04,04=__CMP1) (R:04,04=__CMP2) : Compares two registers

void __MOV(void) {
                        
} // __MOV 05-16 (R:04,04=__DEST) (R:04,04=__SRC) : Moves register to another register

void NXCLR(void) {
                            
} // NXCLR 06-08 : NextExecute Clear

void NXEQL(void) {
                                
} // NXEQL 07-08 : NextExecute If Equal

void NXZRO(void) {
                                    
} // NXZRO 08-08 : NextExecute If Zero

void NXGRT(void) {
                                        
} // NXGRT 09-08 : NextExecute If Greater

void NXLST(void) {
                                            
} // NXLST 0A-08 : NextExecute If LessThan
