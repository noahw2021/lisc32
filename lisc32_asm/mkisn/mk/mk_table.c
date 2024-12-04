//
//  mk_table.c
//  lisc32_asm
//
//  Created by Noah Wooten on 11/27/24.
//

#include "mk.h"
#include <stdlib.h>
#include <string.h>

extern int MkiNewElement(PMK_DOC Document, BYTE Type, const char* Primary, const char* Secondary);
extern char* MkiGetLine(void);

int MkiNewTableElement(MK_TABLE* Table, BYTE Type, const char* Primary, int Row, int Column) {
	if (Table->CurrentRow < Row)
		Table->CurrentRow = Row;
	
    if (Table->CurrentColumn < Column)
		Table->CurrentColumn = Column;
	
    if (Type == _MK_HEADER) {
		Table->Headers = realloc(Table->Headers, (sizeof(MK_HEADER) * (Table->HeaderCount + 1)));
		Table->Headers[Table->HeaderCount].Reference = (Table->LastReference + 1);
		Table->Headers[Table->HeaderCount].Text = malloc(strlen(Primary) + 1);
		strcpy(Table->Headers[Table->HeaderCount].Text, Primary);
		Table->Headers[Table->HeaderCount].Column = Column;
		Table->HeaderCount++;
	} else if (Type == _MK_TABLEFIELD) {
		Table->Fields = realloc(Table->Fields, (sizeof(MK_TABLE_FIELD) * (Table->FieldCount + 1)));
		Table->Fields[Table->FieldCount].Reference = (Table->LastReference + 1);
		Table->Fields[Table->FieldCount].Column = Column;
		Table->Fields[Table->FieldCount].Row = Row;
		Table->Fields[Table->FieldCount].Data = malloc(strlen(Primary) + 1);
		strcpy(Table->Fields[Table->FieldCount].Data, Primary);
		Table->FieldCount++;
	}
    
	Table->LastReference++;
	return Table->LastReference;
}

int MkdAddTable(PMK_DOC Document, PMK_TABLE Table) {
	char* CompiledTable = MkiCompileTable(Table);
	int Return = MkiNewElement(Document, _MK_TABLE, CompiledTable, NULL);
	free(CompiledTable);
	free(Table);
	return Return;
}

int MkdtAddHeader(MK_TABLE* Table, const char* Source, int Column) {
	return MkiNewTableElement(Table, _MK_HEADER, Source, Column, Column);
}

int MkdtAddField(MK_TABLE* Table, const char* Field, int Row, int Column) {
	return MkiNewTableElement(Table, _MK_TABLEFIELD, Field, Row, Column);
}

void MkdtDeleteElement(MK_TABLE* Table, int Reference) {
	PMK_HEADER NewHeaders = malloc(sizeof(MK_HEADER) * (Table->HeaderCount - 1));
    PMK_TABLE_FIELD NewFields = malloc(sizeof(MK_TABLE_FIELD) * (Table->HeaderCount - 1));
	int RefCount = 0;
	
	for (int i = 0; i < Table->HeaderCount; i++) {
		if (Table->Headers[i].Reference == Reference) {
			if (Table->Headers[i].Text)
				free(Table->Headers[i].Text);
			continue;
		} else {
			memcpy(&NewHeaders[++RefCount], &Table[i], sizeof(MK_HEADER));
		}
	}
	
	RefCount = 0;
	for (int i = 0; i < Table->FieldCount; i++) {
		if (Table->Fields[i].Reference == Reference) {
			if (Table->Fields[i].Data)
				free(Table->Fields[i].Data);
			continue;
		} else {
			memcpy(&NewFields[++RefCount], &Table[i], sizeof(MK_HEADER));
		}
	}
	
	free(Table->Headers);
	free(Table->Fields);
	Table->Headers = NewHeaders;
	Table->Fields = NewFields;
    
    return;
}

MK_HEADER* MktdiGetHeaderByColumn(MK_HEADER* Headers, int Count, int Column) {
	for (int i = 0; i < Count; i++) {
		if (Headers[i].Column == Column)
			return &Headers[i];
	}
    
	return NULL;
}

PMK_TABLE_FIELD MktdiGetFieldByColumnRow(PMK_TABLE_FIELD Fields, int Count, int Column, int Row) {
    for (int i = 0; i < Count; i++) {
        if (Fields[i].Column == Column && Fields[i].Row == Row)
            return &Fields[i];
    }
    
	return NULL;
}

char* MkiCompileTable(MK_TABLE* Table) {
	int TableSizeLength = 75 + (Table->HeaderCount * 5) + (Table->FieldCount * 3);
	for (int i = 0; i < Table->HeaderCount; i++)
		TableSizeLength += strlen(Table->Headers[i].Text) + 1;
	for (int i = 0; i < Table->FieldCount; i++)
		TableSizeLength += strlen(Table->Fields[i].Data) + 1;
	TableSizeLength++;
	char* Return = malloc(TableSizeLength);
	
	MkdtAddHeader(Table, "Dummy", Table->CurrentColumn + 1);
	
	for (int i = 0; i < (Table->CurrentColumn); i++) {
		MK_HEADER* Header = MktdiGetHeaderByColumn(Table->Headers, Table->HeaderCount, i);
		strcat(Return, Header->Text);
		strcat(Return, "|");
	}
	strcat(Return, "\n");
	
    strcat(Return, "|");
    for (int i = 0; i < Table->ColumnCount; i++) {
        strcat(Return, "---|");
    }
    
    strcat(Return, MkiGetLine());
	for (int r = 1; r < (Table->CurrentRow); r++) {
		for (int c = 0; c < (Table->CurrentColumn); c++) {
            PMK_TABLE_FIELD Field = MktdiGetFieldByColumnRow(Table->Fields, Table->FieldCount, c, r);
			if (!Field)
				continue;
			strcat(Return, Field->Data);
			strcat(Return, "|");
		}
		strcat(Return, MkiGetLine());
	}
	
	return Return;
}

PMK_TABLE MkNewTable(int Columns) {
	PMK_TABLE Return = malloc(sizeof(MK_TABLE));
    memset(Return, 0, sizeof(MK_TABLE));
    Return->ColumnCount = Columns;
    return Return;
}
