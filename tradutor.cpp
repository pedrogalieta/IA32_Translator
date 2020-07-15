#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <sstream>
#include <list>
#include <cmath>

using namespace std;

ifstream arq_fonte;
ofstream arq_saida;
fstream arq_pre_processado;

//Map storing invented assembly instructions
std::map<string, int> i_map;
std::map<string, int>::iterator i_it;

int verifica_rotulo(string linha, int length_linha);
void traduz_linha(string linha, int* pos_linha, int length_linha,int flag_rotulo);
void escreve_funcoes_extras();

//initializes a map with instructions information
void cria_map_instrucoes(){

  i_map.insert(make_pair("ADD", 1));
  i_map.insert(make_pair("SUB", 2));
  i_map.insert(make_pair("MULT", 3));
  i_map.insert(make_pair("DIV", 4));
  i_map.insert(make_pair("JMP", 5));
  i_map.insert(make_pair("JMPN", 6));
  i_map.insert(make_pair("JMPP", 7));
  i_map.insert(make_pair("JMPZ", 8));
  i_map.insert(make_pair("COPY", 9));
  i_map.insert(make_pair("LOAD", 10));
  i_map.insert(make_pair("STORE", 11));
  i_map.insert(make_pair("INPUT", 12));
  i_map.insert(make_pair("OUTPUT", 13));
  i_map.insert(make_pair("C_INPUT", 14));
  i_map.insert(make_pair("C_OUTPUT", 15));
  i_map.insert(make_pair("S_INPUT", 16));
  i_map.insert(make_pair("S_OUTPUT", 17));
  i_map.insert(make_pair("STOP", 18));
  i_map.insert(make_pair("SECTION", 19));
  i_map.insert(make_pair("SPACE", 20));
  i_map.insert(make_pair("CONST", 21));
}

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

int output(string &operando1){

  string linha_de_cod = "push DWORD ["+ operando1 +"]\ncall Output";
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
  escreve_funcoes_extras();

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

  linha_de_cod.clear();
  linha_de_cod = "mov EAX,1\nmov EBX,0\nint 0x80";

  linha_de_cod += "\n nao_overflow:";
  arq_saida << linha_de_cod << endl;
}

int div(string &operando1){

  string linha_de_cod = "push ECX"; //Stores ECX value
  linha_de_cod += "\nmov ECX, [" + operando1 + "]\ncdq\nidiv ECX";
  linha_de_cod += "\npop ECX"; //Retrieves ECX value
  arq_saida << linha_de_cod << endl;
}

int section(string &operando1){

  string linha_de_cod;

  if(operando1 == "DATA"){
    linha_de_cod = "section .data\nerro db 'Overflow!',0";
    arq_saida << linha_de_cod << endl;
  }else if(operando1 == "BSS"){
    linha_de_cod = "section .bss\nbuffer_input resb 12\naux2_do_output resd 100\naux1_do_output resd 1";
    arq_saida << linha_de_cod << endl;
  }else if(operando1 == "TEXT"){
    linha_de_cod = "section .text";
    arq_saida << linha_de_cod << endl;
    linha_de_cod = "\nglobal  _start\n_start:";
    arq_saida << linha_de_cod << endl;
  }
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


//Converts string to upper
void str_upper(string &str){

  int i;
  int str_length = str.length();

  for(i = 0; i < str_length; i++){

    str[i] = toupper(str[i]);
  }
}

//Check next chars until whitespace or \n
string get_next(string &linha, int *pos_linha, int length_linha){

  string token;

  for (int i=*pos_linha; linha[i] != ' ' && i<length_linha; i++){

    *pos_linha = i+2;
    token += linha[i];
  }

  return token;
}

//Check if int
int check_int(string &operando){

  int i = 5;

  std::istringstream iss(operando);
  iss >> i;
  if (iss.eof() == false){

    return 0;
  }
  else {

    return 1;
  }
}

//Writes on output file translated input/output functions
void escreve_funcoes_extras(){

  ifstream arq_extra;
  string linha;

  arq_extra.open("Funcoes.txt");

  if (!arq_extra.is_open()){

    cout << "Erro ao abrir o arquivo com as funções criadas, verifique se existe o arquivo Funcoes.txt no diretório!" << endl;
    exit(0);
  }


  while(getline(arq_extra, linha)){
    arq_saida << linha << endl;
  }
  arq_extra.close();
}

void traducao(string &nome_do_arq){

  //Checks opening output file
  nome_do_arq.erase(nome_do_arq.end()-1);
  nome_do_arq.erase(nome_do_arq.end()-1);
  nome_do_arq.erase(nome_do_arq.end()-1);
  nome_do_arq += "s";
  arq_saida.open(&nome_do_arq[0]);

  if (!arq_saida.is_open()){

    cout << "Erro ao abrir o arquivo de saída!" << endl;
    exit(0);
  }

  //Checks opening input file
  arq_fonte.open("preprocessado.s");

  if (!arq_fonte.is_open()){

    cout << "Erro ao abrir o arquivo fonte!" << endl;
    exit(0);
  }

  string linha, rotulo;
  int length_linha, pos_linha, flag_rotulo;

  //Iterate line by line
  while(getline(arq_fonte, linha)){

    flag_rotulo = 0;
    length_linha = linha.length();
    pos_linha = 0;

    //Empty or comented line, continue
    if(length_linha == 0 || linha[0] == ';') continue;

    //If there's a label
    if(verifica_rotulo(linha, length_linha) == 1){

      rotulo = get_next(linha, &pos_linha, length_linha); //Salva
      rotulo.erase(rotulo.end()-1); //Remove ':'
      flag_rotulo = 1;
      arq_saida << rotulo;  //Escreve no arquivo

      //If line ended
      if(pos_linha > length_linha){

        arq_saida << ":" <<endl;
        rotulo.clear();
        continue;
      }

      //If line didn't end
      traduz_linha(linha, &pos_linha, length_linha,flag_rotulo);  //Prossegue com a tradução
    }

    //If there's no label
    else{

      traduz_linha(linha, &pos_linha, length_linha,flag_rotulo);  //Prossegue com a tradução
    }

    rotulo.clear();
  }

  arq_saida.close();
  arq_fonte.close();
}


int verifica_rotulo(string linha, int length_linha){

  for (int i=0; i<length_linha; i++){

    if (linha[i] == ':'){

      return 1;
    }
  }

  return 0;
}

void traduz_linha(string linha, int* pos_linha, int length_linha, int flag_rotulo){

  string mnemonico, operando1, operando2;

  //Reads instruction mnemonic and converts to upper case
  mnemonico = get_next(linha, pos_linha, length_linha);
  str_upper(mnemonico);

  i_it = i_map.find(mnemonico); //Procura pelo mnemonico no mapa de inctrucoes

  //If don't exist, error
  if(i_it == i_map.end()){

    cout << "Erro! Instrução desconhecida!" << endl;
    cout << mnemonico << endl;
    exit(1);
  }

  //If there's a label and instruction is not CONST or SPACE
  if(i_it->second < 20 && flag_rotulo == 1){
    arq_saida << ":" <<endl;
  }

  //If found, map key value is used in a switch

  switch(i_it->second){

    case 1:{  //ADD

      operando1 = get_next(linha, pos_linha, length_linha);
      add(operando1);
      break;
    }
    case 2:{  //SUB

      operando1 = get_next(linha, pos_linha, length_linha);
      sub(operando1);
      break;
    }
    case 3:{  //MULT

      operando1 = get_next(linha, pos_linha, length_linha);
      mult(operando1);
      break;
    }
    case 4:{  //DIV

      operando1 = get_next(linha, pos_linha, length_linha);
      div(operando1);
      break;
    }
    case 5:{  //JMP

      operando1 = get_next(linha, pos_linha, length_linha);
      jmp(operando1);
      break;
    }
    case 6:{  //JMPN

      operando1 = get_next(linha, pos_linha, length_linha);
      jmpn(operando1);
      break;
    }
    case 7:{  //JMPP

      operando1 = get_next(linha, pos_linha, length_linha);
      jmpp(operando1);
      break;
    }
    case 8:{  //JMPZ

      operando1 = get_next(linha, pos_linha, length_linha);
      jmpz(operando1);
      break;
    }
    case 9:{  //COPY

      operando1 = get_next(linha, pos_linha, length_linha);
      operando1.erase(operando1.end()-1); //Remove ','
      operando2 = get_next(linha, pos_linha, length_linha);
      copy(operando1, operando2);
      break;
    }
    case 10:{  //LOAD

      operando1 = get_next(linha, pos_linha, length_linha);
      load(operando1);
      break;
    }
    case 11:{  //STORE

      operando1 = get_next(linha, pos_linha, length_linha);
      store(operando1);
      break;
    }
    case 12:{  //INPUT

      operando1 = get_next(linha, pos_linha, length_linha);
      input(operando1);
      break;
    }
    case 13:{  //OUTPUT

      //arq_saida << 13 << endl;
      operando1 = get_next(linha, pos_linha, length_linha);
      output(operando1);
      break;
    }
    case 14:{  //C_INPUT

      operando1 = get_next(linha, pos_linha, length_linha);
      c_input(operando1);
      break;
    }
    case 15:{  //C_OUTPUT

      operando1 = get_next(linha, pos_linha, length_linha);
      c_output(operando1);
      break;
    }
    case 16:{  //S_INPUT

      operando1 = get_next(linha, pos_linha, length_linha);
      operando1.erase(operando1.end()-1); //Remove ','
      operando2 = get_next(linha, pos_linha, length_linha);
      s_input(operando1, operando2);
      break;
    }
    case 17:{  //S_OUTPUT

      operando1 = get_next(linha, pos_linha, length_linha);
      operando1.erase(operando1.end()-1); //Remove ','
      operando2 = get_next(linha, pos_linha, length_linha);
      s_output(operando1, operando2);
      break;
    }
    case 18:{  //STOP

      stop();
      break;
    }
    case 19:{ //SECTION
      operando1 = get_next(linha, pos_linha, length_linha);
      section(operando1);
      break;
    }
    case 20:{ //SPACE
      operando1 = get_next(linha, pos_linha, length_linha);
      space(operando1);
      break;
    }
    case 21:{ //CONST
      operando1 = get_next(linha, pos_linha, length_linha);
      constante(operando1);
      break;
    }
  }

  mnemonico.clear();
}

int pre_processamento(string &nome_do_arq){

  // Input:  arq_fonte = assembly file to be processed
  // Output:    arq_pre_processado = pre processed assembly file
  //            Return 1 if sucessfull and 0 if not
  // Comment: function removes comments and deals with EQU and IF statements

  int i, length_linha, posicao, acumulador_erro, flag_rotulo, length_palavra, flag_IF, pular_proxima_linha = 0, contador_de_linha = 0;
  string linha, nova_linha, palavra, rotulo, valor_EQU;
  map<string, string> EQU_map; //EQU maps

  arq_fonte.open(&nome_do_arq[0]);
  arq_pre_processado.open("preprocessado.s",ios::out);

  if (!arq_fonte.is_open()||!arq_pre_processado.is_open())  {

    cout << "Erro ao abrir o arquivo!" << endl;
    exit(0);
  }

  //Iterates over file
  while(getline(arq_fonte,linha)){

    contador_de_linha++;
    acumulador_erro = 0;
    flag_IF = 0;
    flag_rotulo = 0; //Flag about existing label
    length_linha = linha.length();

    //Jump line if comment
    if(linha[0] == ';'){
      continue;
    }

    //Deals with IF statement jumping line (IF 0) 
    if(pular_proxima_linha == 1){
      pular_proxima_linha = 0;
      continue;
    }

    //Iterates line
    for(i=0; i<length_linha; i++){
      nova_linha += linha[i];
      palavra += linha[i];

      //If comment found, stop
      if(linha[i] == ';'){
           //Erases ';'
           nova_linha.erase(nova_linha.end()-1);
           //Erases whitespace (if exists)
           if(linha[i-1] == ' '){
             nova_linha.erase(nova_linha.end()-1);
           }
           break;
      }

      if(linha[i] ==  '\t'){
        linha[i] = ' ';
      }

      //Get label
      if(linha[i] == ':'){
        flag_rotulo = 1;
        posicao = i;
        rotulo += nova_linha;
        //Erases ':' from label
        rotulo.erase(rotulo.end()-1);
      }

      //Check if there's an IF and sets a flag
      if(linha[i] == ' ' && palavra.length()==3){
        if(linha[i-2] == 'I' && linha[i-1] == 'F'){
          flag_IF = 1;
        }
      }

      //Check if there's an EQU to be replaced
      if(linha[i] == ' '){
        if(palavra.length() > 1){
          //remove whitespace
          palavra.erase(palavra.end()-1);
          //Check if it's a defined EQU and replace it if true
          if (EQU_map.find(palavra) != EQU_map.end()){
            length_palavra = palavra.length();
            nova_linha.erase(i-length_palavra-acumulador_erro,length_palavra+1);
            nova_linha += EQU_map.find(palavra)->second;
            nova_linha += ' ';
            // Necessário para escrever a palavra certa no código de saída
            acumulador_erro += length_palavra-1;
          }
        }else{
          //Erase extra whitespaces
          nova_linha.erase(nova_linha.end()-1);
          acumulador_erro +=1;
        }
        palavra.clear();
      //Complement to EQU check till end of line
      }else if(i == (length_linha - 1)){
        //Check if it's a defined EQU and replace it if true
        if (EQU_map.find(palavra) != EQU_map.end()){
          length_palavra = palavra.length();
          nova_linha.erase(i-length_palavra+1-acumulador_erro,length_palavra);
          nova_linha += EQU_map.find(palavra)->second;
        }
        palavra.clear();
      }
    }

    //Check label meaning
    if(flag_rotulo == 1){

      if(nova_linha[posicao+2] == 'E' && nova_linha[posicao+3] == 'Q' && nova_linha[posicao+4] == 'U'){
        //Check if EQU has an argument
        if(nova_linha[posicao+5] == ' ' ){
          for(i=posicao+6;i<length_linha;i++){
            valor_EQU+=nova_linha[i];
          }
        }else{
          cout<< "Linha "<< contador_de_linha << ": Erro sintático! EQU definido sem argumento" << endl;
          return 0;
        }
        //Check if it's a defined EQU
        if(EQU_map.find(rotulo) == EQU_map.end()){
          //If not, insert in map and continue
          EQU_map.insert(make_pair(rotulo,valor_EQU));
          valor_EQU.clear();
          rotulo.clear();
          nova_linha.clear();
          continue;
        } else {
          //If yes, error
          cout<< "Linha "<< contador_de_linha << ": Erro semântico! EQU redefinido" << endl;
          return 0;
        }
      }
    }

    //If there's an IF check for true or false
    if(flag_IF == 1){
      for(i=3;i<nova_linha.length();i++){
        palavra+=nova_linha[i];
      }
      //If false, skip next line
      if(atoi(palavra.c_str()) == 0){
        pular_proxima_linha = 1;
      }
      //After solving if, discard
      valor_EQU.clear();
      rotulo.clear();
      nova_linha.clear();
      continue;
    }

    //Writes translated line on file programa.pre 
    arq_pre_processado << nova_linha << endl;

    // Limpa as strings utilizadas na função
    valor_EQU.clear();
    rotulo.clear();
    nova_linha.clear();
  }


  arq_pre_processado.close();
  arq_fonte.close();

  return 1;
}

/********MAIN********/

int main(int argc, char const *argv[]) {

  string concatenador;

  if(argc < 2){
    cout << "Para rodar o programa ponha no terminal o nome do arquivo a ser traduzido no formato: 'arquivo.asm'"<<endl;
    return -1;
  }

  concatenador += argv[1];

  if(pre_processamento(concatenador) == 0){ //If pre processing error
    return -1;
  }

  cria_map_instrucoes();
  traducao(concatenador);

  //Erases pre processed file
  remove("preprocessado.s");

  return 0;
}
