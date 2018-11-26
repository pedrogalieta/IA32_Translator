%include 'io.mac'
section .text
global  _start
_start:
push EAX
push DWORD buffer_input
call Input
mov [B], EAX
pop EAX
push EAX
push DWORD buffer_input
call Input
mov [H], EAX
pop EAX
mov EAX,[B]
push EDX
mov EDX, [H]
imul EDX
pop EDX
jno nao_overflow
push DWORD erro
push DWORD 9
call EscreverString
mov EAX,1
mov EBX,0
int 0x80
push EDX
mov EDX, [H]
imul EDX
pop EDX
jno nao_overflow
 nao_overflow:
push ECX
mov ECX, [DOIS]
cdq
idiv ECX
pop ECX
mov [R], EAX
PutInt AX
mov EAX,1
mov EBX,0
int 0x80
section .bss
buffer_input resb 12
R resd 1
section .data
erro db 'Overflow!',0
B dd 3
H dd 4
DOIS dd 2
LeerChar: ;Função que pega um valor de char do teclado e guarda no endereço indicado por [argumento 1]

    push EBP
    mov  EBP,ESP	;Frame de pilha

    push EAX	;Guarda um eventual valor de EAX antes da função
    push EBX	;Guarda um eventual valor de EBX antes da função
    push ECX	;Guarda um eventual valor de ECX antes da função
    push EDX	;Guarda um eventual valor de EDX antes da função

    mov EAX,3 		 ;Chamada ao sistema para leitura
    mov EBX,0 		 ;Define onde será lido, no caso do teclado
    mov ECX,[EBP+8];Define onde será guardado o char lido
    mov EDX,1 		 ;Define quantos bytes serão lidos, no caso de um char é 1
    int 80h			   ;Invoca o SO

    pop EDX		;Retorna o valor de EDX
    pop ECX		;Retorna o valor de ECX
    pop EBX		;Retorna o valor de EBX
    pop EAX		;Retorna o valor de EAX

    pop EBP		;Desfaz o frame de pilha
    ret 4		  ;Retorna para o código desempilhando o argumento letra_digitada

EscreverChar: ;Função que pega um char de um endereço indicado por [argumento 1] e escreve na tela

  	push EBP
  	mov  EBP,ESP	;Frame de pilha

  	push EAX	;Guarda um eventual valor de EAX antes da função
  	push EBX	;Guarda um eventual valor de EBX antes da função
  	push ECX	;Guarda um eventual valor de ECX antes da função
  	push EDX	;Guarda um eventual valor de EDX antes da função

  	mov EAX,4 		  ;Chamada ao sistema para escrita
  	mov EBX,1 		  ;Define onde será escrito, no caso o monitor
  	mov ECX,[EBP+8] ;Define de onde será lido o char a ser escrito
  	mov EDX,1 		  ;Define quantos bytes serão escritos, no caso de um char é 1
  	int 80h		    	;Invoca o SO

  	pop EDX		;Retorna o valor de EDX
  	pop ECX		;Retorna o valor de ECX
  	pop EBX		;Retorna o valor de EBX
  	pop EAX		;Retorna o valor de EAX

  	pop EBP    ;Desfaz o frame de pilha
  	ret 4      ;Retorna para o código desempilhando o argumento letra_digitada

LeerString: ;Função que lê uma string com tamanho [argumento 2] e a guarda na posição [argumento 1]

  	push EBP
  	mov  EBP,ESP	;Frame de pilha

  	push EAX	;Guarda um eventual valor de EAX antes da função
  	push EBX	;Guarda um eventual valor de EBX antes da função
  	push ECX	;Guarda um eventual valor de ECX antes da função
  	push EDX	;Guarda um eventual valor de EDX antes da função

  	mov EAX,3 		   ;Chamada ao sistema para leitura
  	mov EBX,0 		   ;Define onde será lido, no caso do teclado
  	mov ECX,[EBP+12]  ;Define onde será guardado a palavra lida
  	mov EDX,[EBP+8] ;Define quantos bytes serão lidos, máximo 100
  	int 80h			     ;Invoca o SO

  	pop EDX		;Retorna o valor de EDX
  	pop ECX		;Retorna o valor de ECX
  	pop EBX		;Retorna o valor de EBX
  	pop EAX		;Retorna o valor de EAX

  	pop EBP		;Desfaz o frame de pilha
  	ret 8		  ;Retorna para o código desempilhando o argumento letra_digitada

EscreverString: ;Função que escreve uma string com tamanho [argumento 2] da posição [argumento 1]

  	push EBP
  	mov  EBP,ESP	;Frame de pilha

  	push EAX	;Guarda um eventual valor de EAX antes da função
  	push EBX	;Guarda um eventual valor de EBX antes da função
  	push ECX	;Guarda um eventual valor de ECX antes da função
  	push EDX	;Guarda um eventual valor de EDX antes da função

  	mov EAX,4 		   ;Chamada ao sistema para escrita
  	mov EBX,1 		   ;Define onde será escrito, no caso o monitor
  	mov ECX,[EBP+12]  ;Define de onde está o primeiro char da frase a ser escrita
  	mov EDX,[EBP+8] ;Define quantos bytes serão escritos
  	int 80h	     		  ;Invoca o SO

  	pop EDX		;Retorna o valor de EDX
  	pop ECX		;Retorna o valor de ECX
  	pop EBX		;Retorna o valor de EBX
  	pop EAX		;Retorna o valor de EAX

  	pop EBP	;Desfaz o frame de pilha
  	ret 8		;Retorna para o código desempilhando o argumento letra_digitada

    Input: ;Função que lê um inteiro sinalizado e guarda em EAX

    push EBP
    mov EBP,ESP	;Frame de pilha

    push EBX	;Guarda um eventual valor de EBX antes da função
    push ECX	;Guarda um eventual valor de ECX antes da função
    push EDX	;Guarda um eventual valor de EDX antes da função

    mov eax, 3        ;le da buffer_input
    mov ebx, 0
    mov ecx, [EBP + 8]
    mov edx, 12
    int 80h

    mov eax, 0        ;seta os registradores
    mov ecx, 0
    mov ebx, [buffer_input]

    find_last:                   ;enquanto não chega no '\n'
    mov EBX, [buffer_input+ECX]  ;move do lugar onde está escrito a entrada o char e guarda em ebx, ECX cresce byte a byte
    cmp BL, 45                   ;vê se o primeiro char é '-', se for vai para o loop negativo
    je negativo
    cmp BL, 10              ;vê se é '\n', se for termina o loop
    je calc1
    sub BL, 48              ;subtrai 48 para que o valor seja um inteiro e não um char (ex: '1' em ascii é 49, menos 48 = 1)
    movsx BX, BL            ;converte o valor de 8 para 16 bits extendendo o sinal
    movsx EBX, BX           ;converte o valor de 16 para 32 bits extendendo o sinal
    add EAX,EBX             ;soma esse valor em EAX
    push ECX
    mov ECX, 10
    mul ECX                 ;multiplica o que está em EAX por 10
    pop ECX
    inc ECX                 ;aumenta o ECX em 1 para ir pro próximo byte em buffer_input
    jmp find_last           ;repete

    negativo:
    inc ECX                 ;É análogo ao find_last só que n achei um jeito melhor de multiplicar por -1 no final sem ser criando outro loop
    find_last2:
    mov EBX, [buffer_input+ECX]
    cmp BL, 10
    je calc2
    sub BL, 48
    movsx BX, BL
    movsx EBX, BX
    add EAX,EBX
    push ECX
    mov ECX, 10
    mul ECX
    pop ECX
    inc ECX
    jmp find_last2

    calc1:
    push ecx
    mov ecx, 10
    idiv ecx
    pop ecx
    jmp fim

    calc2:
    push ECX
    mov ecx, 10
    idiv ecx
    pop ecx
    NEG EAX
    jmp fim

    fim:
    pop EDX		;Retorna o valor de EDX
    pop ECX		;Retorna o valor de ECX
    pop EBX		;Retorna o valor de EBX

    pop EBP		;Desfaz o frame de pilha
    ret 4		;Retorna para o código desempilhando o argumento letra_digitada
