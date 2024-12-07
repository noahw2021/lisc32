//
//  main.c
//  lisc32_emu
//
//  Created by Noah Wooten on 11/22/24.
//

#include <stdio.h>
#include <string.h>
#include "types.h"
#include "cpu/dbg/isn/isn_imports.h"

WORD64 GlobalFlags;

int main(int argc, char** argv) {
    GlobalFlags = 0x00;
    
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            printf("%s: Help & Usage\n", argv[0]);
            printf("%s (-h | --help) : Displays this message.\n", argv[0]);
            printf("%s (-d | --debug) : Enables transcription of executed instructions.\n", argv[0]);
            printf("%s (-sd | --stack-debug) : Enables reading of the immediate stack.\n", argv[0]);
            
        }
        
        if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--debug")) {
            GlobalFlags |= FLAG_USEDEBUGGER;
        }
        
        if (!strcmp(argv[i], "-sd") || !strcmp(argv[i], "--stack-debug")) {
            GlobalFlags |= FLAG_SHOWSTACK;
        }
    }
    
    return 0;
}
