//
//  types.h
//  lisc32_asm
//
//  Created by Noah Wooten on 11/26/24.
//

#ifndef types_h
#define types_h

typedef unsigned long long WORD64, *PWORD64;
typedef unsigned long WORD32, *PWORD32;
typedef unsigned short WORD16, *PWORD16;
typedef unsigned char BYTE, *PBYTE;

extern void* IsnCtx;
void IsniLoadData(void);

#define InRange(x, min, max) (x >= min && x <= max)

#endif /*types_h */
