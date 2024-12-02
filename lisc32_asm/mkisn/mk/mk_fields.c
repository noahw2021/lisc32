//
//  mk_fields.c
//  lisc32_asm
//
//  Created by Noah Wooten on 11/27/24.
//

#include "mk.h"
#include <stdlib.h>
#include <string.h>

int mki_newelem(PMK_DOC Document, BYTE Type, const char* Primary, const char* Secondary) {
	Document->Elements = realloc(Document->Elements, (sizeof(MK_FIELD) * (Document->ElementCount + 1)));
	memset(&Document->Elements[Document->ElementCount], 0, sizeof(MK_FIELD));
	if (Primary)
		Document->Elements[Document->ElementCount].Primary = malloc(strlen(Primary) + 1);
	if (Secondary)
		Document->Elements[Document->ElementCount].Secondary = malloc(strlen(Secondary) + 1);
	
	Document->Elements[Document->ElementCount].Type = Type;
	if (Primary)
		strcpy(Document->Elements[Document->ElementCount].Primary, Primary);
	if (Secondary)
		strcpy(Document->Elements[Document->ElementCount].Secondary, Secondary);
	Document->ElementCount++;
	return (int)Document->ElementCount - 1;
}

int MkdAddHeading1(PMK_DOC Document, const char* Value) {
	return mki_newelem(Document, _MK_HEADING1, Value, NULL);
}
int MkdAddHeading2(PMK_DOC Document, const char* Value) {
	return mki_newelem(Document, _MK_HEADING2, Value, NULL);
}
int MkdAddHeading3(PMK_DOC Document, const char* Value) {
	return mki_newelem(Document, _MK_HEADING3, Value, NULL);
}
int MkdAddText(PMK_DOC Document, const char* Value) {
	return mki_newelem(Document, _MK_TEXT, Value, NULL);
}
int MkdAddLink(PMK_DOC Document, const char* Address, const char* Title) {
	return mki_newelem(Document, _MK_LINK, Address, Title);
}
int MkdAddImage(PMK_DOC Document, const char* Address, const char* Alt) {
	return mki_newelem(Document, _MK_IMAGE, Address, Alt);
}
int MkdAddBoldText(PMK_DOC Document, const char* Text) {
	return mki_newelem(Document, _MK_BOLD, Text, NULL);
}
int MkdAddItalicsText(PMK_DOC Document, const char* Title) {
	return mki_newelem(Document, _MK_ITALICS, Title, NULL);
}
int MkdAddCode(PMK_DOC Document, const char* Source, const char* LanguageStr) {
	return mki_newelem(Document, _MK_CODE, Source, LanguageStr);
}
int MkdAddLine(PMK_DOC Document) {
	return mki_newelem(Document, _MK_LINE, NULL, NULL);
}
