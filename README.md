# Tradutor Assembly Hipotetico
Programadores:  

				Pedro Saman D N Cesarino   15/0144890
				Pedro Victor Galieta Tomaz 15/0144938

O trabalho consistiu em implementar um algoritmo que deveria ser capaz de traduzir a linguagem hipotética aprendida em sala em assemply IA32. Foi desenvolvido usando Ubuntu 16.04 LTS na linguagem c++ em uma máquina de 64 bits.


Tradutor:

			Entradas: recebe como entrada, via linha de comando, um arquivo no formato assembly
			inventado utilizado na sala de aula.  

			Saídas: É gerada uma saída neste programa, com o mesmo nome do arquivo de entrada com a extensão '.s'.

Exemplo de uso do algoritmo:
  - Na mesma pasta com os arquivos trad deve haver o código assembly a ser traduzido.
  - Para compilar o trabalho basta escrever na linha  de comando: c++ tradutor.cpp -o tradutor
  - Se, por exemplo o nome do arquivo a ser traduzido se chamar: "fatorial.asm". O usuário deve rodar o programa como: ./tradutor fatorial.asm
  - Então ira aparecer um arquivo chamado "fatorial.s" que está na forma do assembly IA32.
  - Para montar esse programa basta escrever: nasm - elf -o fatorial.o fatorial.s
  - Então é preciso liga-lo dessa forma: ld -m elf_i386 -o fatorial fatorial.o
  - Por fim, para rodar basta digitar ./fatorial
