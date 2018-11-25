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

//Mapa que armazena as intruções do assembly inventado
std::map<string, int> i_map;
std::map<string, int>::iterator i_it;

int verifica_rotulo(string linha, int length_linha);
void traduz_linha(string linha, int* pos_linha, int length_linha);

//Função que cria o mapa onde são salvas informações das instruções
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

  string msg_erro = "'Operação causou Overflow'";
  string tamanho = "26";
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

//converte a string para maiúsculo
void str_upper(string &str){

  int i;
  int str_length = str.length();

  for(i = 0; i < str_length; i++){

    str[i] = toupper(str[i]);
  }
}

//verifica o próximo conjunto de CHAR até o ' ' ou fim de linha
string get_next(string &linha, int *pos_linha, int length_linha){

  string token;

  for (int i=*pos_linha; linha[i] != ' ' && i<length_linha; i++){

    *pos_linha = i+2;
    token += linha[i];
  }

  return token;
}

//Função que verifica se o conteudo da string passada corresponde a um numeral (inteiro)
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

void escreve_funcoes_extras(){//Função que escreve no arquivo de saída as funções escritas para output e input

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

void traducao(){

  //Solicita e verifica abertura do arquivo de saída
  arq_saida.open("arquivo.s");

  if (!arq_saida.is_open()){

    cout << "Erro ao abrir o arquivo de saída!" << endl;
    exit(0);
  }

  //Solicita e verifica abertura do arquivo de entrada
  arq_fonte.open("preprocessado.s");

  if (!arq_fonte.is_open()){

    cout << "Erro ao abrir o arquivo fonte!" << endl;
    exit(0);
  }

  string linha, rotulo;
  int length_linha, pos_linha;

  //Varre todo o arquivo, linha a linha
  while(getline(arq_fonte, linha)){

    length_linha = linha.length();
    pos_linha = 0;

    //Linha vazia ou somente comentário, continua
    if(length_linha == 0 || linha[0] == ';') continue;

    //Se existe rótulo
    if(verifica_rotulo(linha, length_linha) == 1){

      rotulo = get_next(linha, &pos_linha, length_linha); //Salva
      arq_saida << rotulo;  //Escreve no arquivo

      //Se era o único elemento da linha, continua
      if(pos_linha > length_linha){

        arq_saida << endl;
        rotulo.clear();
        continue;
      }

      //Se não era o único
      traduz_linha(linha, &pos_linha, length_linha);  //Prossegue com a tradução
    }

    //Se não existe rótulo
    else{

      traduz_linha(linha, &pos_linha, length_linha);  //Prossegue com a tradução
    }

    rotulo.clear();
  }

  escreve_funcoes_extras();

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

void traduz_linha(string linha, int* pos_linha, int length_linha){

  string mnemonico, operando1, operando2;

  //Lê o mnemonico da instrução e converte para upper case
  mnemonico = get_next(linha, pos_linha, length_linha);
  str_upper(mnemonico);

  i_it = i_map.find(mnemonico); //Procura pelo mnemonico no mapa de inctrucoes

  //Caso não exista, erro
  if(i_it == i_map.end()){

    cout << "Erro! Instrução desconhecida!" << endl;
    cout << mnemonico << endl;
    exit(1);
  }

  //Caso seja encontrado, o valor da chave mapeada é usado em um switch

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


      break;
    }
    case 13:{  //OUTPUT

      arq_saida << "13" << endl;
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
    case 18:{  //ADD

      stop();
      break;
    }
  }

  mnemonico.clear();
}

int pre_processamento(ifstream &arq_fonte ,fstream &arq_pre_processado){

  // Entradas:  arq_fonte = Arquivo assembly que vai ser pre processado
  // Saídas:    arq_pre_processado = Arquivo assembly já pre processado
  //            A função retorna um caso o pre processamento tenho sido sucesso e 0 caso não
  // Comentários: Essa função retira comentários do código fonte e trata as diretivas EQU e IF

  int i, length_linha, posicao, acumulador_erro, flag_rotulo, length_palavra, flag_IF, pular_proxima_linha = 0, contador_de_linha = 0;
  string linha, nova_linha, palavra, rotulo, valor_EQU;
  map<string, string> EQU_map; //mapa de EQU's definidos

  // Varre o arquivo fonte
  while(getline(arq_fonte,linha)){

    contador_de_linha++;
    acumulador_erro = 0;
    flag_IF = 0;
    flag_rotulo = 0; // Serve para saber se a linha lida tinha algum rótulo definido
    length_linha = linha.length();

    // Esse if faz com que caso a linha comece por comentário não fique um \n no arquivo pre processado
    if(linha[0] == ';'){
      continue;
    }

    // Esse if faz com que o pre processador ignore a próxima linha caso tenha um IF 0 antes dela
    if(pular_proxima_linha == 1){
      pular_proxima_linha = 0;
      continue;
    }

    // Varre a linha
    for(i=0; i<length_linha; i++){
      nova_linha += linha[i];
      palavra += linha[i];

      // Se for ';' deve parar de ler a linha já que é comentário
      if(linha[i] == ';'){
           // Apaga o ';'
           nova_linha.erase(nova_linha.end()-1);
           // Esse if apaga também o espaço q vem antes do ';' se tiver
           if(linha[i-1] == ' '){
             nova_linha.erase(nova_linha.end()-1);
           }
           break;
      }

      if(linha[i] ==  '\t'){
        linha[i] = ' ';
      }

      // Pega os rótulos presentes no código
      if(linha[i] == ':'){
        flag_rotulo = 1;
        posicao = i;
        rotulo += nova_linha;
        // Retira o ':' do rótulo
        rotulo.erase(rotulo.end()-1);
      }

      // Esse bloco identifica se foi lido um IF e seta a flag para tratar essa informação para 1
      if(linha[i] == ' ' && palavra.length()==3){
        if(linha[i-2] == 'I' && linha[i-1] == 'F'){
          flag_IF = 1;
        }
      }

      // Essa parte do código checa se existe algum EQU para ser substituído, esse if checa a palavra antes de um espaço em branco
      if(linha[i] == ' '){
        if(palavra.length() > 1){
          //remove espaço
          palavra.erase(palavra.end()-1);
          // Checa se a palavra lida é um EQU já definido, se for apagamos a palavra e escrevemos o seu valor no map de EQU's
          if (EQU_map.find(palavra) != EQU_map.end()){
            length_palavra = palavra.length();
            nova_linha.erase(i-length_palavra-acumulador_erro,length_palavra+1);
            nova_linha += EQU_map.find(palavra)->second;
            nova_linha += ' ';
            // Necessário para escrever a palavra certa no código de saída
            acumulador_erro += length_palavra-1;
          }
        }else{
          // Essa linha de código apaga espaços extras que aparecerem no código fonte
          nova_linha.erase(nova_linha.end()-1);
          acumulador_erro +=1;
        }
        palavra.clear();
      // Complemento da checagem de EQU's a serem substituídos, esse if checa uma palavra no final da linha
      }else if(i == (length_linha - 1)){
        // Checa se a palavra lida é um EQU já definido, se for apagamos a palavra e escrevemos o seu valor no map de EQU's
        if (EQU_map.find(palavra) != EQU_map.end()){
          length_palavra = palavra.length();
          nova_linha.erase(i-length_palavra+1-acumulador_erro,length_palavra);
          nova_linha += EQU_map.find(palavra)->second;
        }
        palavra.clear();
      }
    }

    // Checa se o rótulo era para um EQU ou outra coisa
    if(flag_rotulo == 1){
      // Verificar se existe um jeito melhor para isso \/
      if(nova_linha[posicao+2] == 'E' && nova_linha[posicao+3] == 'Q' && nova_linha[posicao+4] == 'U'){
        // Checa se o EQU foi declarado sem argumento
        if(nova_linha[posicao+5] == ' ' ){
          for(i=posicao+6;i<length_linha;i++){
            valor_EQU+=nova_linha[i];
          }
        }else{
          cout<< "Linha "<< contador_de_linha << ": Erro sintático! EQU definido sem argumento" << endl;
          return 0;
        }
        // Checa se o EQU já foi declarado anteriormente
        if(EQU_map.find(rotulo) == EQU_map.end()){
          // Se não, adicionar no map e continuar o pre processamento
          EQU_map.insert(make_pair(rotulo,valor_EQU));
          valor_EQU.clear();
          rotulo.clear();
          nova_linha.clear();
          continue;
        } else {
          // Se sim, erro
          cout<< "Linha "<< contador_de_linha << ": Erro semântico! EQU redefinido" << endl;
          return 0;
        }
      }
    }

    // Caso essa linha tenha um IF checamos para ver se ele é falso ou verdadeiro
    if(flag_IF == 1){
      for(i=3;i<nova_linha.length();i++){
        palavra+=nova_linha[i];
      }
      // Se for falso, devemos ignorar a próxima linha se verdadeiro seguir na leitura normalmente
      if(atoi(palavra.c_str()) == 0){
        pular_proxima_linha = 1;
      }
      // Depois de tratar o IF essa linha pode ser descartada
      valor_EQU.clear();
      rotulo.clear();
      nova_linha.clear();
      continue;
    }

    // Escreve no arquivo programa.pre a linha sem os comentarios, com EQU substituído
    arq_pre_processado << nova_linha << endl;

    // Limpa as strings utilizadas na função
    valor_EQU.clear();
    rotulo.clear();
    nova_linha.clear();
  }
  return 1;
}

/********MAIN********/

int main (){

  fstream arq_pre_processado;

  arq_fonte.open("teste.asm");
  arq_pre_processado.open("preprocessado.s",ios::out);

  if (!arq_fonte.is_open()||!arq_pre_processado.is_open())  {

    cout << "Erro ao abrir o arquivo!" << endl;
    exit(0);
  }

  if(pre_processamento(arq_fonte, arq_pre_processado) == 0){ //Se deu erro no preprocessamento o programa aborta
    return -1;
  }

  arq_pre_processado.close();
  arq_fonte.close();

  cria_map_instrucoes();
  traducao();

  //Apaga o arquivo preprocessado
  remove("preprocessado.s");

  /*//VERIFICA CONTEUDO DA MAPA DE INSTRUCOES
  for(i_it = i_map.begin(); i_it != i_map.end(); i_it++){

    cout << i_it->first << ' ' << i_it->second << endl;
  }*/

  return 0;
}
