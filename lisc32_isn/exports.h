//
//  exports.h
//  lisc32_isn
//
//  Created by Noah Wooten on 11/25/24.
//

#ifndef exports_h
#define exports_h
#include "isn.h"
#include "types.h"

#define ISN_EXPORT_PRE

ISN_EXPORT_PRE void* IsnInit(void);
ISN_EXPORT_PRE void IsnShutdown(void* Ctx);

ISN_EXPORT_PRE void IsnLoadData(void* Ctx, char* Data);
ISN_EXPORT_PRE int IsnInstructionCount(void* Ctx);

ISN_EXPORT_PRE char* IsnGetInstructionName(void* Ctx, int Id);
ISN_EXPORT_PRE BYTE IsnGetInstructinOpcode(void* Ctx, int Id);
ISN_EXPORT_PRE BYTE IsnGetOperandType(void* Ctx, int Id, BYTE OperandId);
ISN_EXPORT_PRE BYTE IsnGetPhysicalSize(void* Ctx, int Id, BYTE OperandId);
ISN_EXPORT_PRE BYTE IsnGetUsableSize(void* Ctx, int Id, BYTE OperandId);
ISN_EXPORT_PRE char* IsnGetOperandName(void* Ctx, int Id, BYTE OperandId);
ISN_EXPORT_PRE BYTE IsnGetTotalSize(void* Ctx, int Id);
ISN_EXPORT_PRE char* IsnGetDescription(void* Ctx, int Id);
ISN_EXPORT_PRE int  IsnGetOperandCount(void* Ctx, int Id);
ISN_EXPORT_PRE int  IsnGetInstructionByName(void* Ctx, const char* Operand);
ISN_EXPORT_PRE int  IsnGetInstructionByOpcode(void* Ctx, BYTE Opcode);

#endif /* exports_h */
