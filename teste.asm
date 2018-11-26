%include "io.mac"
section .data

section .bss
entrada resb 12
acc resb 4

section .text

global _start
_start:

mov eax, 3
mov ebx, 0
mov ecx, entrada
mov edx, 12
int 80h

mov eax, 0
mov ecx, 0
mov ebx, entrada
mov edx, 10

find_last:    ;itera até ebx apontar para o último caracter antes do enter
cmp [ebx+1], [dez]
je calc
inc ebx
jmp find_last

calc: mov eax, [ebx]  ;conteudo de ebx em eax
mul edx   ;multiplica pelo multiplo de 10
add ecx, eax  ;soma em ecx 

mov eax, 4
mov ebx, 1
mov ecx, acc
mov edx, 1
int 80h

nwln

mov eax, 1
mov ebx, 0
int 80h
