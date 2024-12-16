//
//  main.c
//  lisc32_emu
//
//  Created by Noah Wooten on 11/22/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "cpu/dbg/isn/isn_imports.h"
#include "cpu/cpu.h"
#include "cpu/dbg/dbg.h"

WORD64 GlobalFlags;
WORD32 GlobalMemorySize;
void* IsnCtx;

int main(int argc, char** argv) {
    GlobalFlags = 0x00;
    WORD32 MemorySize = (1 << 24); // 16 MiB
    
    IsnCtx = IsnInit();
    IsniLoadData();
    
    FILE* Bios = NULL;
    char BiosName[128] = "bios.bin";
    
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            printf("%s: Help & Usage\n", argv[0]);
            printf("%s (-h | --help) : Displays this message.\n", argv[0]);
            printf("%s (-d | --debug) : Enables transcription of executed instructions.\n", argv[0]);
            printf("%s (-sd | --stack-debug) : Enables reading of the immediate stack.\n", argv[0]);
            
            
            printf("%s: Options\n", argv[0]);
            printf("%s (-m=1024 | --memory=1024) : Sets the physical memory allocation.\n", argv[0]);
            printf("%s (-b=bios.bin | --bios=bios.bin) : Sets the BIOS binary file.\n", argv[0]);
        }
        
        if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--debug")) {
            GlobalFlags |= FLAG_USEDEBUGGER;
        }
        
        if (!strcmp(argv[i], "-sd") || !strcmp(argv[i], "--stack-debug")) {
            GlobalFlags |= FLAG_SHOWSTACK;
        }
        
        if (strstr(argv[i], "-m=") || strstr(argv[i], "--memory=")) {
            char* Source = NULL;
            if (strstr(argv[i], "-m=")) {
                Source = strstr(argv[i], "-m=");
                Source += 3;
            } else if (strstr(argv[i], "--memory=")) {
                Source = strstr(argv[i], "--memory=");
                Source += 9;
            }
            
            MemorySize = atoi(Source);
        }
        
        if (strstr(argv[i], "-b=") || strstr(argv[i], "--bios=")) {
            char* BiosFile = NULL;
            if (strstr(argv[i], "-b=")) {
                BiosFile = strstr(argv[i], "-m=");
                BiosFile += 3;
            } else if (strstr(argv[i], "--bios=")) {
                BiosFile = strstr(argv[i], "--bios=");
                BiosFile += 7;
            }
            
            strlcpy(BiosName, BiosFile, 128);
        }
    }
    
    GlobalMemorySize = MemorySize;
    
    Bios = fopen(BiosName, "rb");
    if (!Bios) {
        printf("[ERR]: Could not open BIOS file.\n");
        IsnShutdown(IsnCtx);
        return 0;
    }
    
    CpuInit();
    CpuSetup();
    
    // load bios (should be in cpu setup @TODO 202412161232)
    fread(CpuCtx->Memory + 0x200, 0x1000, 1, Bios);
    fclose(Bios);
    
    CpuLoop();
    
    return 0;
}
