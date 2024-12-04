//
//  mk_docs.c
//  lisc32_asm
//
//  Created by Noah Wooten on 11/27/24.
//

#include "mk.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

PMK_DOC MkNewDoc(void) {
	PMK_DOC Return = malloc(sizeof(MK_DOC));
	memset(Return, 0, sizeof(MK_DOC));
	return Return;
}

char* LastPointer = NULL;

char* MkiGetLine(void) {
	if (LastPointer) {
		free(LastPointer);
		LastPointer = NULL;
	}
    
	LastPointer	= malloc(4);
	switch (MkCtx->LineEnding) {
		case MKI_LINE_CR:
			strcpy(LastPointer, "\r");
			break;
		case MKI_LINE_LF:
			strcpy(LastPointer, "\n");
			break;
		case MKI_LINE_CRLF:
			strcpy(LastPointer, "\r\n");
			break;
		case MKI_LINE_LFCR:
			strcpy(LastPointer, "\n\r");
			break;
		default:
			strcpy(LastPointer, "???");
			break;
	}
    
	return LastPointer;
}
void MkiWriteStream(char* Writing, WORD32* Size, WORD32* Used, char* Stream) {
	WORD32 Length = strlen(Writing);
	
    if ((Length + (*Used)) > (*Size)) {
		Stream = realloc(Stream, (*Used) + Length);
		*Size = ((*Used) + Length);
	}
    
	*Used += Length;
	strcat(Stream, Writing);
}

char* MkCompile(PMK_DOC Document) {
	WORD32 CurrentSize = 20000;
	WORD32 Used = 0;
	char* Outstream = malloc(20000);
	memset(Outstream, 0, 20000);
	
	for (int i = 0; i < Document->ElementCount; i++) {
		MK_FIELD* CurField = &Document->Elements[i];
		WORD32 BufSize = 25 + ((CurField->Primary == NULL) ? 0 : strlen(CurField->Primary)) + ((CurField->Secondary == NULL) ? 0 : strlen(CurField->Secondary));
		char* TotalOutBuf = malloc(BufSize);
		
		switch (CurField->Type) {
			case _MK_HEADING1:
				sprintf(TotalOutBuf, "# %s%s", CurField->Primary, MkiGetLine());
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_HEADING2:
				sprintf(TotalOutBuf, "## %s%s", CurField->Primary, MkiGetLine());
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_HEADING3:
				sprintf(TotalOutBuf, "### %s%s", CurField->Primary, MkiGetLine());
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_TEXT:
				sprintf(TotalOutBuf, "%s%s", CurField->Primary, MkiGetLine());
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_LINK:
				sprintf(TotalOutBuf, "[%s](%s)%s", CurField->Secondary, CurField->Primary, MkiGetLine());
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_IMAGE:
				sprintf(TotalOutBuf, "![%s](%s)%s", CurField->Secondary, CurField->Primary, MkiGetLine());
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_BOLD:
				sprintf(TotalOutBuf, "**%s**%s", CurField->Primary, MkiGetLine());
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_ITALICS:
				sprintf(TotalOutBuf, "*%s*%s", CurField->Primary, MkiGetLine());
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_BLOCKQUOTE:
				sprintf(TotalOutBuf, "> %s%s", CurField->Primary, MkiGetLine());
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_CODE:
				sprintf(TotalOutBuf, "```%s%s%s```%s", CurField->Secondary, MkiGetLine(), CurField->Primary, MkiGetLine());
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_LINE:
				sprintf(TotalOutBuf, "%s", MkiGetLine());	
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_TABLE:
				sprintf(TotalOutBuf, "%s", CurField->Primary);
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			default:
				sprintf(TotalOutBuf, "! INVALID ELEMENT TYPE !%s", MkiGetLine());
				MkiWriteStream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			}
		free(TotalOutBuf);
		if (CurField->Primary)
			free(CurField->Primary);
		if (CurField->Secondary)
			free(CurField->Secondary);
	}
	free(Document->Elements);
	free(Document);
	return Outstream;
}

void MkdDeleteElement(PMK_DOC Document, int Reference) {
	PMK_FIELD NewFields = malloc(sizeof(MK_FIELD) * (Document->ElementCount - 1));
	memset(NewFields, 0, sizeof(MK_FIELD));
	for (int i = 0; i < Document->ElementCount; i++) {
		if (i == Reference) {
			if (Document->Elements[i].Primary)
				free(Document->Elements[i].Primary);
			if (Document->Elements[i].Secondary)
				free(Document->Elements[i].Secondary); // We don't need to also free the pointers, just this structure if the structure isn't being deleted.
			continue;
		}
		memcpy(&NewFields[i], &Document->Elements[i], sizeof(MK_FIELD));
	}
    
	free(Document->Elements);
	Document->Elements = NewFields;
	return;
}
