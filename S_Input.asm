%include "io.mac"
.DATA
;letra_digitada db 'a',0
msg1 db 'Escreva uma palavra: ',0
msg2 db 'Palavra digitada: ',0
msg3 db '|',0
tamanho_palavra dd 5
.UDATA
palavra_digitada resb 100
.CODE
.STARTUP
;PutInt SP
PutStr msg1
push DWORD palavra_digitada	;Argumento da função S_Input
push DWORD  [tamanho_palavra]  	;Argumento da função S_Input
call S_Input 				;Chamada da função
PutStr msg3
mov eax,4
mov ebx,1
mov ecx, palavra_digitada+2
mov edx, 1
int 80h
PutStr msg3
;PutInt SP
Fim: .EXIT

S_Input: ;Função que lê uma string com tamanho [argumento 1] e a guarda na posição [argumento 2]

	push EBP
	mov EBP,ESP	;Frame de pilha

	push EAX	;Guarda um eventual valor de EAX antes da função
	push EBX	;Guarda um eventual valor de EBX antes da função
	push ECX	;Guarda um eventual valor de ECX antes da função
	push EDX	;Guarda um eventual valor de EDX antes da função

	mov EAX,3 		;Chamada ao sistema para leitura
	mov EBX,0 		;Define onde será lido, no caso do teclado
	mov ECX,[EBP+12] ;Define onde será guardado a palavra lida
	mov EDX,[EBP+8]  ;Define quantos bytes serão lidos, máximo 100
	int 80h			;Invoca o SO

	pop EDX		;Retorna o valor de EDX
	pop ECX		;Retorna o valor de ECX
	pop EBX		;Retorna o valor de EBX
	pop EAX		;Retorna o valor de EAX

	pop EBP		;Desfaz o frame de pilha
	ret 8		;Retorna para o código desempilhando o argumento letra_digitada
