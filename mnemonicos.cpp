int add(string &operando1){

  string linha_de_cod = "add EAX, [" + operando1+"]";
  arq_saida << linha_de_cod << endl;
}

int sub(string &operando1){

  string linha_de_cod = "sub EAX, [" + operando1+"]";
  arq_saida << linha_de_cod << endl;
}


int jmp(string &operando1){

  string linha_de_cod = "jmp " + operando1;
  arq_saida << linha_de_cod << endl;

}

int jmpn(string &operando1){

  string linha_de_cod = "cmp EAX, 0\njl " + operando1;
  arq_saida << linha_de_cod << endl;

}

int jmpp(string &operando1){

  string linha_de_cod = "cmp EAX, 0\njg " + operando1;
  arq_saida << linha_de_cod << endl;
}

int jmpz(string &operando1){

    string linha_de_cod = "cmp EAX,0\nje "+ operando1;
    arq_saida << linha_de_cod << endl;
}

int copy(string &operando1,string &operando2){

  string linha_de_cod = "push EDX";//Guardar o valor de EDX

  linha_de_cod += "\nmov EDX, [" + operando1 +"]\nmov [" + operando2 + "],EDX";

  linha_de_cod += "\npop EDX";//Recuperar o valor de ECX

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

int input(string &operando1){

  string linha_de_cod = "push EAX\npush DWORD buffer_input\ncall Input\nmov ["+operando1+"], EAX\npop EAX";
  arq_saida << linha_de_cod << endl;

}

int c_input(string &operando1){

  string linha_de_cod = "push DWORD " + operando1 + "\ncall LeerChar";
  arq_saida << linha_de_cod << endl;
}

int c_output(string &operando1){

  string linha_de_cod = "push DWORD " + operando1 + "\ncall EscreverChar";
  arq_saida << linha_de_cod << endl;
}

int s_input(string &operando1,string &operando2){

  string linha_de_cod = "push DWORD " + operando1 + "\npush DWORD " + operando2 + "\ncall LeerString";
  arq_saida << linha_de_cod << endl;
}

int s_output(string &operando1,string &operando2){

  string linha_de_cod = "push DWORD " + operando1 + "\npush DWORD "+ operando2 +"\ncall EscreverString";
  arq_saida << linha_de_cod << endl;
}

int stop(){

  string linha_de_cod = "mov EAX,1\nmov EBX,0\nint 0x80";
  arq_saida << linha_de_cod << endl;
}

int mult(string &operando1){

  string msg_erro = "erro";
  string tamanho = "9";
  string linha_de_cod;

  linha_de_cod = "push EDX";//Guardar o valor de EDX
  linha_de_cod += "\nmov EDX, [" + operando1 +"]";

  linha_de_cod += "\nimul EDX\npop EDX\njno nao_overflow";
  arq_saida << linha_de_cod << endl;

  s_output(msg_erro,tamanho);
  stop();

  //linha_de_cod.clear();
  linha_de_cod += "\n nao_overflow:";
  arq_saida << linha_de_cod << endl;
}

int div(string &operando1){

  string linha_de_cod = "push ECX"; //Guardar o valor de ECX
  linha_de_cod += "\nmov ECX, [" + operando1 + "]\ncdq\nidiv ECX";
  linha_de_cod += "\npop ECX"; //Recuperar o valor de ECX
  arq_saida << linha_de_cod << endl;
}

int section(string &operando1){

  string linha_de_cod;

  if(operando1 == "DATA"){
    linha_de_cod = "section .data\nerro db 'Overflow!',0";
  }else if(operando1 == "BSS"){
    linha_de_cod = "section .bss\nbuffer_input resb 12";
    string linha_extra;
  }else if(operando1 == "TEXT"){
    linha_de_cod = "section .text\nglobal  _start\n_start:";
  }

  arq_saida << linha_de_cod << endl;

}

int space(string &operando1){

  string linha_de_cod = " ";

  linha_de_cod += "resd "+ operando1;
  arq_saida << linha_de_cod << endl;


}

int constante(string &operando1){

  string linha_de_cod = " ";

  linha_de_cod += "dd "+ operando1;
  arq_saida << linha_de_cod << endl;

}
