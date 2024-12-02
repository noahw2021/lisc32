//
//  mk.h
//  lisc32_asm
//
//  Created by Noah Wooten on 11/27/24.
//

#ifndef md_h
#define md_h
#include "../../types.h"

#define _MK_HEADING1	0x00
#define _MK_HEADING2	0x01
#define _MK_HEADING3	0x02
#define _MK_TEXT		0x03
#define _MK_LINK		0x04
#define _MK_IMAGE		0x05
#define _MK_BOLD		0x06
#define _MK_ITALICS		0x07
#define _MK_BLOCKQUOTE	0x08
#define _MK_CODE		0x09
#define _MK_LINE		0x0A
#define _MK_TABLE		0x0B
#define _MK_HEADER		0x0C
#define _MK_TABLEFIELD	0x0D

#define MKI_LINE_CR		0x1000
#define MKI_LINE_LF		0x0100
#define MKI_LINE_CRLF   0x1100
#define MKI_LINE_LFCR   0x110F

typedef struct _MK_CTX {
	WORD16 LineEnding;
}MK_CTX, *PMK_CTX;

typedef struct _MK_FIELD {
	BYTE Type;
	char* Primary;
	char* Secondary;
}MK_FIELD, *PMK_FIELD;

typedef struct _MK_DOC {
	int ElementCount;
	PMK_FIELD Elements;
}MK_DOC, *PMK_DOC;

typedef struct _MK_CTX_HEADER {
	int Reference;
	int Column;
	char* Text;
}MK_HEADER, *PMK_HEADER;

typedef struct _MK_CTX_TABLE_FIELD {
	int Reference;
	int Row;
	int Column;
	char* Data;
}MK_TABLE_FIELD, *PMK_TABLE_FIELD;

typedef struct _MK_CTX_TABLE {
    PMK_HEADER Headers;
	int HeaderCount;
    PMK_TABLE_FIELD Fields;
	int FieldCount;
	int CurrentRow;
	int CurrentColumn;
	int LastReference;
}MK_TABLE, *PMK_TABLE;

void mk_init(WORD16 LineEnding);
void mk_shutdown(void);

PMK_DOC MkNewDoc(void);
PMK_TABLE MkNewTable(void);
char* MkCompile(PMK_DOC Document);
char* MkiCompileTable(MK_TABLE* Table);

int MkdAddHeading1(PMK_DOC Document, const char* Value);
int MkdAddHeading2(PMK_DOC Document, const char* Value);
int MkdAddHeading3(PMK_DOC Document, const char* Value);
int MkdAddText(PMK_DOC Document, const char* Value);
int MkdAddLink(PMK_DOC Document, const char* Address, const char* Title);
int MkdAddImage(PMK_DOC Document, const char* Address, const char* Alt);
int MkdAddBoldText(PMK_DOC Document, const char* Text);
int MkdAddItalicsText(PMK_DOC Document, const char* Title);
int MkdAddCode(PMK_DOC Document, const char* Source, const char* LanguageStr);
int MkdAddLine(PMK_DOC Document);
int MkdAddTable(PMK_DOC Document, PMK_TABLE Table);

int MkdtAddHeader(MK_TABLE* Table, const char* Source, int Column);
int MkdtAddField(MK_TABLE* Table, const char* Field, int Row, int Column);
void MkdtDeleteElement(MK_TABLE* Table, int Reference);

void MkdDeleteElement(PMK_DOC Document, int Reference);

extern PMK_CTX MkCtx;

#endif /* md_h */
