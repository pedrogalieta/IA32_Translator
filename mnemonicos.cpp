#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

int add(fstream &arquivo_saida,string &argumento){

  string linha_de_cod = "add EAX," + argumento;
  arquivo_saida << linha_de_cod << endl;
}

int sub(fstream &arquivo_saida,string &argumento){

  string linha_de_cod = "sub EAX," + argumento;
  arquivo_saida << linha_de_cod << endl;
}

int jmp(fstream &arquivo_saida,string &argumento){

  string linha_de_cod = "jmp [" + argumento + "]";
  arquivo_saida << linha_de_cod << endl;

}

int jmpn(fstream &arquivo_saida,string &argumento){

  string linha_de_cod = "comp EAX,0\njl [" + argumento + "]";
  arquivo_saida << linha_de_cod << endl;

}

int jmpp(fstream &arquivo_saida,string &argumento){

  string linha_de_cod = "comp EAX,0\njg [" + argumento + "]";
  arquivo_saida << linha_de_cod << endl;

}

int jmpz(fstream &arquivo_saida,string &argumento){

    string linha_de_cod = "comp EAX,0\nje [" + argumento + "]";
    arquivo_saida << linha_de_cod << endl;

}

int copy(fstream &arquivo_saida,string &argumento1,string &argumento2){

  string linha_de_cod = "mov " + argumento2 + ',' + argumento1;
  arquivo_saida << linha_de_cod << endl;

}

int load(fstream &arquivo_saida,string &argumento){

  string linha_de_cod = "mov EAX,[" + argumento + "]";
  arquivo_saida << linha_de_cod << endl;

}

int store(fstream &arquivo_saida,string &argumento){

  string linha_de_cod = "mov [" + argumento + "],EAX";
  arquivo_saida << linha_de_cod << endl;

}

int c_input(fstream &arquivo_saida,string &argumento){

  string linha_de_cod = "push DWORD " + argumento + "\ncall Leer_Char";
  arquivo_saida << linha_de_cod << endl;

}

int c_output(fstream &arquivo_saida,string &argumento){

  string linha_de_cod = "push DWORD " + argumento + "\ncall Escrever_Char";
  arquivo_saida << linha_de_cod << endl;

}

int s_input(fstream &arquivo_saida,string &argumento1,string &argumento2){

  string linha_de_cod = "push DWORD " + argumento1 + "\npush DWORD "+ argumento2 +"\ncall Leer_String";
  arquivo_saida << linha_de_cod << endl;

}

int s_output(fstream &arquivo_saida,string &argumento1,string &argumento2){

  string linha_de_cod = "push DWORD " + argumento1 + "\npush DWORD "+ argumento2 +"\ncall Escrever_String";
  arquivo_saida << linha_de_cod << endl;

}

int stop(fstream &arquivo_saida){

  string linha_de_cod = "mov EAX,1\nmov EBX,0\nint 0x80";
  arquivo_saida << linha_de_cod << endl;
}

int main(){

  fstream arquivo_saida;
  arquivo_saida.open("arquivo_saida",ios::out);
  string oi,tam,oi1,oi2,oi3,dest,orig;
  oi += "add1";
  oi1 += "label_pulo";
  oi2 += "sub1";
  oi3 += "label";
  dest += "dest";
  orig += "orig";
  tam += "1";

  add(arquivo_saida,oi);
  sub(arquivo_saida,oi2);
  jmp(arquivo_saida,oi1);
  jmpn(arquivo_saida,oi1);
  jmpp(arquivo_saida,oi1);
  jmpz(arquivo_saida,oi1);
  copy(arquivo_saida,orig,dest);
  load(arquivo_saida,oi3);
  store(arquivo_saida,oi3);
  c_input(arquivo_saida,oi3);
  c_output(arquivo_saida,oi3);
  s_input(arquivo_saida,oi3,tam);
  s_output(arquivo_saida,oi3,tam);
  stop(arquivo_saida);
}
