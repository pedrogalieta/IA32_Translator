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

void traducao(){

  //Solicita e verifica abertura do arquivo de saída
  arq_saida.open("arquivo.s");

  if (!arq_saida.is_open()){

    cout << "Erro ao abrir o arquivo de saída!" << endl;
    exit(0);
  }

  //Solicita e verifica abertura do arquivo de entrada
  arq_fonte.open("teste.asm");

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

  //Lê o mnemonico da instrução e ocnverte para upper case
  mnemonico = get_next(linha, pos_linha, length_linha);
  str_upper(mnemonico);

  i_it = i_map.find(mnemonico); //Procura pelo mnemonico no mapa de inctrucoes

  //Caso não exista, erro
  if(i_it == i_map.end()){

    cout << "Erro! Instrução desconhecida!" << endl;
    exit(1);
  }

  //Caso seja encontrado, o valor da chave mapeada é usado em um switch

  switch(i_it->second){

    case 1:{  //ADD

      operando1 = get_next(linha, pos_linha, length_linha);
      //add(operando1);
      break;
    }
    case 2:{  //SUB

      operando1 = get_next(linha, pos_linha, length_linha);
      //sub(operando1);
      break;
    }
    case 3:{  //MULT

      operando1 = get_next(linha, pos_linha, length_linha);
      //mult(operando1);
      break;
    }
    case 4:{  //DIV

      operando1 = get_next(linha, pos_linha, length_linha);
      //div(operando1);
      break;
    }
    case 5:{  //JMP

      operando1 = get_next(linha, pos_linha, length_linha);
      //jmp(operando1);
      break;
    }
    case 6:{  //JMPN

      operando1 = get_next(linha, pos_linha, length_linha);
      //jmpn(operando1);
      break;
    }
    case 7:{  //JMPP

      operando1 = get_next(linha, pos_linha, length_linha);
      //jmpp(operando1);
      break;
    }
    case 8:{  //JMPZ

      operando1 = get_next(linha, pos_linha, length_linha);
      //jmpz(operando1);
      break;
    }
    case 9:{  //COPY

      operando1 = get_next(linha, pos_linha, length_linha);
      operando1.erase(operando1.end()-1); //Remove ','
      operando2 = get_next(linha, pos_linha, length_linha);
      //copy(operando1, operando2);
      break;
    }
    case 10:{  //LOAD

      operando1 = get_next(linha, pos_linha, length_linha);
      //load(operando1);
      break;
    }
    case 11:{  //STORE

      operando1 = get_next(linha, pos_linha, length_linha);
      //store(operando1);
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
      //c_input(operando1);
      break;
    }
    case 15:{  //C_OUTPUT

      operando1 = get_next(linha, pos_linha, length_linha);
      //c_output(operando1);
      break;
    }
    case 16:{  //S_INPUT

      operando1 = get_next(linha, pos_linha, length_linha);
      operando1.erase(operando1.end()-1); //Remove ','
      operando2 = get_next(linha, pos_linha, length_linha);
      //s_input(operando1, operando2);
      break;
    }
    case 17:{  //S_OUTPUT

      operando1 = get_next(linha, pos_linha, length_linha);
      operando1.erase(operando1.end()-1); //Remove ','
      operando2 = get_next(linha, pos_linha, length_linha);
      //s_output(operando1, operando2);
      break;
    }
    case 18:{  //ADD

      //stop();
      break;
    }
  }

  mnemonico.clear();
}

/********MAIN********/

int main (){

  cria_map_instrucoes();
  traducao();

  /*//VERIFICA CONTEUDO DA MAPA DE INSTRUCOES
  for(i_it = i_map.begin(); i_it != i_map.end(); i_it++){

    cout << i_it->first << ' ' << i_it->second << endl;
  }*/

  return 0;
}
