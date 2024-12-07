//
//  dbg.h
//  lisc32_emu
//
//  Created by Noah Wooten on 12/4/24.
//

#ifndef dbg_h
#define dbg_h

#include "../../types.h"

void DbgRun(void);

BYTE DbgRead1(void);
WORD16 DbgRead2(void);
WORD32 DbgRead4(void);
WORD64 DbgRead8(void);

#endif /* dbg_h */
