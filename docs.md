<!---
--
--  docs.md
--  lisc32
--
--  Created by Noah Wooten on 12/4/24.
--

This file was generated by lisc32_asm.
Generate your own using lisc32_asm -g.
--->
# Instructions (List)
Instruction|Opcode|Operand Count|Instruction Size|
|---|---|---|---|
LDI|0x00|2|80|
JMP|0x01|1|16|
CALL|0x02|1|16|
RET|0x03|0|8|
CMP|0x04|2|16|
MOV|0x05|2|16|
NXCLR|0x06|0|8|
NXEQL|0x07|0|8|
NXZRO|0x08|0|8|
NXGRT|0x09|0|8|
NXLST|0x0A|0|8|
ADD|0x20|2|16|
SUB|0x21|2|16|
MUL|0x22|2|16|
DIV|0x23|2|16|
MOD|0x24|2|16|
AND|0x25|2|16|
OR|0x26|2|16|
# Instructions (Detailed)
## LDI
Loads Immediate to Registers

Opcode: 0x00 (80 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
DEST|Register|4|8|
IMMD|Immediate|64|64|

## JMP
Jumps to Register

Opcode: 0x01 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
REG|Register|4|8|


## CALL
Calls to Register

Opcode: 0x02 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
REG|Register|4|8|


## RET
Returns

Opcode: 0x03 (8 bits)
## CMP
Compares two registers

Opcode: 0x04 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
CMP1|Register|4|4|
CMP2|Register|4|4|

## MOV
Moves register to another register

Opcode: 0x05 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
DEST|Register|4|4|
SRC|Register|4|4|

## NXCLR
NextExecute Clear

Opcode: 0x06 (8 bits)
## NXEQL
NextExecute If Equal

Opcode: 0x07 (8 bits)
## NXZRO
NextExecute If Zero

Opcode: 0x08 (8 bits)
## NXGRT
NextExecute If Greater

Opcode: 0x09 (8 bits)
## NXLST
NextExecute If LessThan

Opcode: 0x0A (8 bits)
## ADD
Adds to Destination

Opcode: 0x20 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
DEST|Register|4|4|
ARG|Register|4|4|

## SUB
Subtracts from Destination

Opcode: 0x21 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
DEST|Register|4|4|
ARG|Register|4|4|

## MUL
Multiplies Destination

Opcode: 0x22 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
DEST|Register|4|4|
ARG|Register|4|4|

## DIV
Divides Destination by Argument, Quotient stored

Opcode: 0x23 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
DEST|Register|4|4|
ARG|Register|4|4|

## MOD
Divides Destination by Argument, Remainder stored

Opcode: 0x24 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
DEST|Register|4|4|
ARG|Register|4|4|

## AND
Bitwise AND Destiation by Argument

Opcode: 0x25 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
DEST|Register|4|4|
ARG|Register|4|4|

## OR
Bitwise OR Destination by Argument

Opcode: 0x26 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
DEST|Register|4|4|
ARG|Register|4|4|

## XOR
Bitwise XOR Destination by Argument

Opcode: 0x27 (16 bits)
Name|Type|Virtual Size|Physical Size|
|---|---|---|---|
DEST|Register|4|4|
ARG|Register|4|4|

