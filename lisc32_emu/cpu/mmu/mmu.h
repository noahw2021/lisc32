//
//  mmu.h
//  lisc32_emu
//
//  Created by Noah Wooten on 12/6/24.
//

#ifndef mmu_h
#define mmu_h

#include "../../types.h"

void MmuInit(void);
void MmuShutdown(void);

BYTE MmuRead1(void);
WORD16 MmuRead2(void);
WORD32 MmuRead4(void);
WORD64 MmuRead8(void);

WORD32 MmuPull(void);
void MmuPush(WORD32 Source);

#endif /* mmu_h */
