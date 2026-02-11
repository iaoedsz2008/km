
; nasm -f bin ISR64.asm

SECTION .text
BITS 64

PUSH RAX                        ; https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions
PUSH RCX                        ;
PUSH RDX                        ;
PUSH R8                         ;
PUSH R9                         ;
PUSH R10                        ;
PUSH R11                        ;
PUSH RSI                        ; Nonvolatile

MOV ECX, 0x11111111             ;
LEA RDX, [RSP + 0x40]           ;

MOV RSI, RSP                    ;
SUB RSP, 80H                    ; allocate
AND RSP, 0FFFFFFFFFFFFFFF0H     ; X64架构中函数入口处必须对齐.
CALL [REL Callback]             ;
MOV RSP, RSI                    ;

POP RSI                         ;
POP R11                         ;
POP R10                         ;
POP R9                          ;
POP R8                          ;
POP RDX                         ;
POP RCX                         ;
POP RAX                         ;
JMP [REL Procedure]             ;

ALIGN 8, DB 0x90

Callback  DQ 0x1111111111111111 ;
Procedure DQ 0x2222222222222222 ;

ALIGN 0x80, DB 0x90
