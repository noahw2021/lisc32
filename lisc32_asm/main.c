//
//  main.c
//  lisc32_asm
//
//  Created by Noah Wooten on 11/22/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "codegen/codegen.h"
#include "isn/isn_imports.h"

void* IsnCtx;

int main(int argc, char** argv) {
    FILE* InFile = stdin;
    FILE* OutFile = NULL;
    
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            printf("%s: Help & Usage\n", argv[0]);
            printf("%s (-h | --help) : Displays this message.\n", argv[0]);
            
            printf("%s : Options\n", argv[0]);
            printf("-f= | --infile= : Accepts a text input to assemble.\n");
            printf("-o= | --outfile= : Outputs a binary.\n");
        }
        
        if (!strcmp(argv[i], "-f=") || !strcmp(argv[i], "--infile=")) {
            char* Equals = strstr(argv[i], "=") + 1;
            InFile = fopen(Equals, "r");
        }
        
        if (!strcmp(argv[i], "-o=") || !strcmp(argv[i], "--outfile=")) {
            char* Equals2 = strstr(argv[i], "=") + 1;
            OutFile = fopen(Equals2, "wb+");
        }
    }
    
    if (!OutFile)
        OutFile = fopen("assemout.bin", "wb+");
    
    IsnCtx = IsnInit();
    IsniLoadData();
    
    CgInit();
    CgCtx->OutFile = OutFile;
    CgCtx->InFiles[0] = InFile;
    CgCtx->InFileCount = 1;
    
    char* InputRequest = malloc(1024);
    
    while (!CgCtx->CompileComplete) {
        printf("[%04llX]: ", CgCtx->DataPosition);
        CgParseLine(CgReadLine(InputRequest, 1024));
    }
    
    free(InputRequest);
    return 0;
}
