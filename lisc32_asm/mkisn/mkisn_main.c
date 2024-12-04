//
//  mkisn_main.c
//  lisc32_asm
//
//  Created by Noah Wooten on 12/2/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "../isn/isn_imports.h"
#include "mk/mk.h"

void MkIsnGenerate(void) {
    FILE* Output = fopen("table.md", "w+");
    if (!Output)
        return;
    
    char* NameBfr = malloc(512);
    MkInit(MKI_LINE_LF);
    
    PMK_DOC Document = MkNewDoc();
    MkdAddHeading1(Document, "Instructions");
    
    /*
     InstructionName
     Opcode
     InstructionSize Bits
     Operand Count
     InstructionDescription
     
     Operands[2] {
        OperandName
        PhysicalSize, VirtualSize
        Type
     }
     */
    
    int InstructionCnt = IsnInstructionCount(IsnCtx);
    for (int i = 0; i < InstructionCnt; i++) {
        MkdAddHeading2(Document, IsnGetInstructionName(IsnCtx, i));
        sprintf(NameBfr, "0x%02hhX (%i bits)",
                IsnGetInstructionOpcode(IsnCtx, i), IsnGetTotalSize(IsnCtx, i));
        MkdAddText(Document, IsnGetDescription(IsnCtx, i));
        MkdAddText(Document, NameBfr);
        
        int OperandCnt = IsnGetOperandCount(IsnCtx, i);
        
        if (OperandCnt != 0) {
            PMK_TABLE Table = MkNewTable();
            MkdtAddHeader(Table, "Name", 0);
            MkdtAddHeader(Table, "Type", 1);
            MkdtAddHeader(Table, "Virtual Size", 2);
            MkdtAddHeader(Table, "Physical Size", 3);
        
            // Operand 1
            MkdtAddField(Table, IsnGetOperandName(IsnCtx, i, 0), 1, 0);
            if (IsnGetOperandType(IsnCtx, i, 0))
                MkdtAddField(Table, "Immediate", 1, 1);
            else
                MkdtAddField(Table, "Register", 1, 1);
            
            sprintf(NameBfr, "%i", IsnGetVirtualSize(IsnCtx, i, 0));
            MkdtAddField(Table, NameBfr, 1, 2);
            sprintf(NameBfr, "%i", IsnGetPhysicalSize(IsnCtx, i, 0));
            MkdtAddField(Table, NameBfr, 1, 3);
            
            if (OperandCnt == 2) {
                // Operand 2
                MkdtAddField(Table, IsnGetOperandName(IsnCtx, i, 1), 2, 0);
                if (IsnGetOperandType(IsnCtx, i, 1))
                    MkdtAddField(Table, "Immediate", 2, 1);
                else
                    MkdtAddField(Table, "Register", 2, 1);
                
                sprintf(NameBfr, "%i", IsnGetVirtualSize(IsnCtx, i, 1));
                MkdtAddField(Table, NameBfr, 2, 2);
                sprintf(NameBfr, "%i", IsnGetPhysicalSize(IsnCtx, i, 1));
                MkdtAddField(Table, NameBfr, 2, 3);
            }
            
            MkdAddTable(Document, Table);
        }
    }
    
    PMK_TABLE OpcodeList = MkNewTable();
    MkdtAddHeader(OpcodeList, "Instruction", 0);
    MkdtAddHeader(OpcodeList, "Opcode", 1);
    MkdtAddHeader(OpcodeList, "Operand Count", 2);
    MkdtAddHeader(OpcodeList, "Instruction Size", 3);
    
    for (int i = 0; i < InstructionCnt; i++) {
        MkdtAddField(OpcodeList, IsnGetInstructionName(IsnCtx, i), i + 1, 0);
        sprintf(NameBfr, "0x%02hhX", IsnGetInstructionOpcode(IsnCtx, i));
        MkdtAddField(OpcodeList, NameBfr, i + 1, 1);
        sprintf(NameBfr, "0x%02hhX", IsnGetOperandCount(IsnCtx, i));
        MkdtAddField(OpcodeList, NameBfr, i + 1, 2);
        sprintf(NameBfr, "0x%02hhX", IsnGetTotalSize(IsnCtx, i));
        MkdtAddField(OpcodeList, NameBfr, i + 1, 3);
    }
    
    free(NameBfr);
}
