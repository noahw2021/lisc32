//
//  exports.h
//  lisc32_isn
//
//  Created by Noah Wooten on 11/25/24.
//

#ifndef exports_h
#define exports_h
#include "isn.h"

#define ISN_EXPORT_PRE

ISN_EXPORT_PRE void* IsnInit(void);
ISN_EXPORT_PRE void IsnShutdown(void* Ctx);

ISN_EXPORT_PRE void IsnLoadData(void* Ctx, char* Data);
ISN_EXPORT_PRE int IsnInstructionCount(void* Ctx);

ISN_EXPORT_PRE char* Psin2iGetInstructionName(int Id);
ISN_EXPORT_PRE BYTE  Psin2iGetInstructinOpcode(int Id);
ISN_EXPORT_PRE BYTE  Psin2iGetOperandType(int Id, BYTE OperandId);
ISN_EXPORT_PRE BYTE  Psin2iGetPhysicalSize(int Id, BYTE OperandId);
ISN_EXPORT_PRE BYTE  Psin2iGetAvailableSize(int Id, BYTE OperandId);
ISN_EXPORT_PRE char* Psin2iGetOperandName(int Id, BYTE OperandId);
ISN_EXPORT_PRE BYTE  Psin2iGetTotalSize(int Id);
ISN_EXPORT_PRE char* Psin2iGetDescription(int Id);
ISN_EXPORT_PRE int      Psin2iGetOperandCount(int Id);
ISN_EXPORT_PRE int   Psin2iGetInstructionByName(const char* Operand);
ISN_EXPORT_PRE int   Psin2iGetInstructionByOpcode(BYTE Opcode);

#endif /* exports_h */
