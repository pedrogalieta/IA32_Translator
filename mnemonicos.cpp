#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

int add(string &operando1){

  string linha_de_cod = "add EAX, " + operando1;
  arq_saida << linha_de_cod << endl;
}

int sub(string &operando1){

  string linha_de_cod = "sub EAX, " + operando1;
  arq_saida << linha_de_cod << endl;
}


int jmp(string &operando1){

  string linha_de_cod = "jmp [" + operando1 + "]";
  arq_saida << linha_de_cod << endl;

}

int jmpn(string &operando1){

  string linha_de_cod = "comp EAX, 0\njl [" + operando1 + "]";
  arq_saida << linha_de_cod << endl;

}

int jmpp(string &operando1){

  string linha_de_cod = "comp EAX, 0\njg [" + operando1 + "]";
  arq_saida << linha_de_cod << endl;
}

int jmpz(string &operando1){

    string linha_de_cod = "comp EAX,0\nje [" + operando1 + "]";
    arq_saida << linha_de_cod << endl;
}

int copy(string &operando1,string &operando2){

  string linha_de_cod = "mov " + operando2 + ', ' + operando1;
  arq_saida << linha_de_cod << endl;
}

int load(string &operando1){

  string linha_de_cod = "mov EAX,[" + operando1 + "]";
  arq_saida << linha_de_cod << endl;
}

int store(string &operando1){

  string linha_de_cod = "mov [" + operando1 + "], EAX";
  arq_saida << linha_de_cod << endl;
}

int c_input(string &operando1){

  string linha_de_cod = "push DWORD " + operando1 + "\ncall Leer_Char";
  arq_saida << linha_de_cod << endl;
}

int c_output(string &operando1){

  string linha_de_cod = "push DWORD " + operando1 + "\ncall Escrever_Char";
  arq_saida << linha_de_cod << endl;
}

int s_input(string &operando1,string &operando2){

  string linha_de_cod = "push DWORD " + operando1 + "\npush DWORD " + operando2 + "\ncall Leer_String";
  arq_saida << linha_de_cod << endl;
}

int s_output(string &operando1,string &operando2){

  string linha_de_cod = "push DWORD " + operando1 + "\npush DWORD "+ operando2 +"\ncall Escrever_String";
  arq_saida << linha_de_cod << endl;
}

int stop(){

  string linha_de_cod = "mov EAX,1\nmov EBX,0\nint 0x80";
  arq_saida << linha_de_cod << endl;
}

int mult(string &operando1){

  string msg_erro = "'Operação causou Overflow'";
  string tamanho = "26";

  string linha_de_cod = "mul " + operando1 + "\njno nao_overflow";
  arq_saida << linha_de_cod << endl;

  s_output(msg_erro,tamanho);
  stop();

  linha_de_cod.clear();
  linha_de_cod += "nao_overflow:";
  arq_saida << linha_de_cod << endl;
}

int div(string &operando1){

  string linha_de_cod = "cdq\ndiv " + operando1;
  arq_saida << linha_de_cod << endl;
}

int main(){

  fstream arq_saida;
  arq_saida.open("arq_saida",ios::out);
  string oi,tam,oi1,oi2,oi3,dest,orig;
  oi += "add1";
  oi1 += "label_pulo";
  oi2 += "sub1";
  oi3 += "label";
  dest += "dest";
  orig += "orig";
  tam += "1";

  mult(arq_saida,oi3);
  div(arq_saida,oi3);
  // add(arq_saida,oi);
  // sub(arq_saida,oi2);
  // jmp(arq_saida,oi1);
  // jmpn(arq_saida,oi1);
  // jmpp(arq_saida,oi1);
  // jmpz(arq_saida,oi1);
  // copy(arq_saida,orig,dest);
  // load(arq_saida,oi3);
  // store(arq_saida,oi3);
  // c_input(arq_saida,oi3);
  // c_output(arq_saida,oi3);
  // s_input(arq_saida,oi3,tam);
  // s_output(arq_saida,oi3,tam);
  // stop(arq_saida);
}
