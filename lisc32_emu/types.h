//
//  types.h
//  lisc32_emu
//
//  Created by Noah Wooten on 11/22/24.
//

#ifndef types_h
#define types_h

typedef unsigned long long WORD64, *PWORD64;
typedef unsigned long WORD32, *PWORD32, SYSTEM_WORD, *PSYSTEM_WORD;
typedef unsigned short WORD16, *PWORD16;
typedef unsigned char BYTE, *PBYTE;

extern void* IsnCtx;
void IsniLoadData(void);

extern WORD64 GlobalFlags;
extern WORD32 GlobalMemorySize;
#define FLAG_USEDEBUGGER        0x0000000000000001
#define FLAG_SHOWSTACK          0x0000000000000002
#define FLAG_RESERVED02         0x0000000000000004
#define FLAG_RESERVED03         0x0000000000000008
#define FLAG_RESERVED04         0x0000000000000010
#define FLAG_RESERVED05         0x0000000000000020
#define FLAG_RESERVED06         0x0000000000000040
#define FLAG_RESERVED07         0x0000000000000080
#define FLAG_RESERVED08         0x0000000000000100
#define FLAG_RESERVED09         0x0000000000000200
#define FLAG_RESERVED10         0x0000000000000400
#define FLAG_RESERVED11         0x0000000000000800
#define FLAG_RESERVED12         0x0000000000001000
#define FLAG_RESERVED13         0x0000000000002000
#define FLAG_RESERVED14         0x0000000000004000
#define FLAG_RESERVED15         0x0000000000008000

#endif /* types_h */
