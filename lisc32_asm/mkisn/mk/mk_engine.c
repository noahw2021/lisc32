//
//  mk_engine.c
//  lisc32_asm
//
//  Created by Noah Wooten on 11/27/24.
//

#include <stdlib.h>
#include <string.h>
#include "mk.h"
PMK_CTX MkCtx;

void MkInit(WORD16 LineEnding) {
	MkCtx = malloc(sizeof(MK_CTX));
	memset(MkCtx, 0, sizeof(MK_CTX));
	MkCtx->LineEnding = LineEnding;
}

void MkShutdown(void) {
	free(MkCtx);
}
