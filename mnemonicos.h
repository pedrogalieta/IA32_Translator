using namespace std;

#ifndef MNEMONICOS_H
#define MNEMONICOS_H

extern string operando1, operando2;
extern ofstream arq_saida;

int add(string &operando1);

int sub(string &operando1);

int jmp(string &operando1);

int jmpn(string &operando1);

int jmpp(string &operando1);

int jmpz(string &operando1);

int copy(string &operando1,string &operando2);

int load(string &operando1);

int store(string &operando1);

int c_input(string &operando1);

int c_output(string &operando1);

int s_input(string &operando1,string &operando2);

int s_output(string &operando1,string &operando2);

int stop();

int mult(string &operando1);

int div(string &operando1);

int section(string &operando1);

int space(string &operando1);

int constante(string &operando1);

#endif
