Pedro:mul saman
jno nao_overflow
push DWORD 'Operação causou Overflow'
push DWORD 26
call Escrever_String
mov EAX,1
mov EBX,0
int 0x80
nao_overflow:
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