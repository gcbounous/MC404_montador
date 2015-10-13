#ifndef TRADUTOR_H_   
#define TRADUTOR_H_

enum mnemonico
{
	LDMQ = 1,
	LDMQM,
	STR,
	LOAD,
	LDN,
	LDABS,
	JMP,
	JGEZ,
	ADD,
	ADDABS,
	SUB,
	SUBABS,
	MUL,
	DIV,
	LSH,
	RSH,
	STM
};
typedef enum mnemonico Mnemonico;

char* traduzir(int mnemonico, char* endereco, int a_direita, char *codigo);
char* retornaCodigoLDMQ(char *codigo);
char* retornaCodigoLDMQM(char *codigo, char *endereco);
char* retornaCodigoSTR(char *codigo, char *endereco);
char* retornaCodigoLOAD(char *codigo, char *endereco);
char* retornaCodigoLDN(char *codigo, char *endereco);
char* retornaCodigoLDABS(char *codigo, char *endereco);
char* retornaCodigoJMPDireita(char *codigo, char *endereco);
char* retornaCodigoJMPEsquerda(char *codigo, char *endereco);
char* retornaCodigoJGEZDireita(char *codigo, char *endereco);
char* retornaCodigoJGEZEsquerda(char *codigo, char *endereco);
char* retornaCodigoADD(char *codigo, char *endereco);
char* retornaCodigoADDABS(char *codigo, char *endereco);
char* retornaCodigoSUB(char *codigo, char *endereco);
char* retornaCodigoSUBABS(char *codigo, char *endereco);
char* retornaCodigoMUL(char *codigo, char *endereco);
char* retornaCodigoDIV(char *codigo, char *endereco);
char* retornaCodigoLSH(char *codigo);
char* retornaCodigoRSH(char *codigo);
char* retornaCodigoSTMDireita(char *codigo, char *endereco);
char* retornaCodigoSTMEsquerda(char *codigo, char *endereco);

#endif