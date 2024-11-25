//
//  imports.h
//  lisc32_isn
//
//  Created by Noah Wooten on 11/25/24.
//

#ifndef imports_h
#define imports_h
#include "types.h"

#define ISN_IMPORT_PRE

ISN_IMPORT_PRE void* IsnInit(void);
ISN_IMPORT_PRE void IsnShutdown(void* Ctx);
ISN_IMPORT_PRE void IsnLoadData(void* Ctx, char* Data);
ISN_IMPORT_PRE int IsnInstructionCount(void* Ctx);
ISN_IMPORT_PRE char* IsnGetInstructionName(void* Ctx, int Id);
ISN_IMPORT_PRE BYTE IsnGetInstructinOpcode(void* Ctx, int Id);
ISN_IMPORT_PRE BYTE IsnGetOperandType(void* Ctx, int Id, BYTE OperandId);
ISN_IMPORT_PRE BYTE IsnGetPhysicalSize(void* Ctx, int Id, BYTE OperandId);
ISN_IMPORT_PRE BYTE IsnGetUsableSize(void* Ctx, int Id, BYTE OperandId);
ISN_IMPORT_PRE char* IsnGetOperandName(void* Ctx, int Id, BYTE OperandId);
ISN_IMPORT_PRE BYTE IsnGetTotalSize(void* Ctx, int Id);
ISN_IMPORT_PRE char* IsnGetDescription(void* Ctx, int Id);
ISN_IMPORT_PRE int  IsnGetOperandCount(void* Ctx, int Id);
ISN_IMPORT_PRE int  IsnGetInstructionByName(void* Ctx, const char* Operand);
ISN_IMPORT_PRE int  IsnGetInstructionByOpcode(void* Ctx, BYTE Opcode);

#endif /* imports_h */
