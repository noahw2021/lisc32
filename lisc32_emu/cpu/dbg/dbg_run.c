//
//  dbg_run.c
//  lisc32_emu
//
//  Created by Noah Wooten on 12/6/24.
//

#include <stdio.h>
#include "dbg.h"
#include "isn/isn_imports.h"

void DbgRun(BYTE Opcode) {
    if (!(GlobalFlags & FLAG_USEDEBUGGER))
        return;
    
    int IsnId = IsnGetInstructionByOpcode(IsnCtx, Opcode);
    // if (IsnId == -1) @TODO figure this out later 202412062151
    
    char Operand1[32];
    char Operand2[32];
    
    if (IsnGetOperandCount(IsnCtx, IsnId) == 2) {
        printf("%s ", IsnGetInstructionName(IsnCtx, IsnId));
        
        if (IsnGetOperandType(IsnCtx, IsnId, 0) == 0) { // Register
            if (IsnGetPhysicalSize(IsnCtx, IsnId, 0) == 4) { // Two registers per byte
                union {
                    BYTE As8;
                    struct {
                        BYTE As4_0 : 4;
                        BYTE As4_1 : 4;
                    };
                }DoubleByte;
                
                DoubleByte.As8 = DbgRead1();
                printf("r%i, r%i\n", DoubleByte.As4_0, DoubleByte.As4_1);
                return;
            } else {
                BYTE Operand1 = DbgRead1();
                WORD64 Immediate;
                switch (IsnGetPhysicalSize(IsnCtx, IsnId, 0))  {
                    default:
                    case 8:
                        Immediate = DbgRead1();
                        break;
                    case 16:
                        Immediate = DbgRead2();
                        break;
                    case 32:
                        Immediate = DbgRead4();
                        break;
                    case 64:
                        Immediate = DbgRead8();
                        break;
                };
                
                printf("r%i, %llXh", Operand1 & 0xF, Immediate);
                return;
                // Operand 2 must be an immediate
            }
        } else { // Immediate
            WORD64 Immediate;
            switch (IsnGetPhysicalSize(IsnCtx, IsnId, 0))  {
                default:
                case 8:
                    Immediate = DbgRead1();
                    break;
                case 16:
                    Immediate = DbgRead2();
                    break;
                case 32:
                    Immediate = DbgRead4();
                    break;
                case 64:
                    Immediate = DbgRead8();
                    break;
            };
            
            
        }
    } else if (IsnGetOperandCount(IsnCtx, IsnId) == 1) {
        if (IsnGetOperandType(IsnCtx, IsnId, 0) == 0) { // Register
            BYTE Register = DbgRead1();
            printf("%s r%i\n", IsnGetInstructionName(IsnCtx, IsnId), Register);
        } else { // Immediate
            WORD64 Immediate;
            switch (IsnGetPhysicalSize(IsnCtx, IsnId, 0))  {
                default:
                case 8:
                    Immediate = DbgRead1();
                    break;
                case 16:
                    Immediate = DbgRead2();
                    break;
                case 32:
                    Immediate = DbgRead4();
                    break;
                case 64:
                    Immediate = DbgRead8();
                    break;
            };
            
            printf("%s %llXh\n", IsnGetInstructionName(IsnCtx, IsnId), Immediate);
        }
    } else { // 0 Operands
        printf("%s\n", IsnGetInstructionName(IsnCtx, IsnId));
    }
    
    return;
}
