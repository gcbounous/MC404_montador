#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "tradutor.h"

/**
* Metodo que traduz o mnemonico da instrucao e o endereco ligado a ele no formato hexadecimal
* Recebe de parametros:
* 	mnemonico: enum do mnemonico do codigo a ser traduzido
* 	endereco: endereco ligado ao mnemonico
* 	a_direita: 0 ou 1 definindo se sera usado a direita ou nao da palavra (usado para JMP, JGEZ ou STM)
* 	codigo: string que sera devolvido com o codigo hexadecimal da instrucao e seu endereco
**/
char* traduzir(int mnemonico, char* endereco, int a_direita, char *codigo)
{
	switch(mnemonico)
	{
		case LDMQ:
			printf("entrou\n");
			return retornaCodigoLDMQ(codigo);		
		case LDMQM:
			return retornaCodigoLDMQM(codigo, endereco);
		case STR:
			return retornaCodigoSTR(codigo, endereco);
		case LOAD:
			return retornaCodigoLOAD(codigo, endereco);
		case LDN:
			return retornaCodigoLDN(codigo, endereco);
		case LDABS:
			return retornaCodigoLDABS(codigo, endereco);
		case JMP:
			if(a_direita)
				return retornaCodigoJMPDireita(codigo, endereco);
			else
				return retornaCodigoJMPEsquerda(codigo, endereco);
		case JGEZ:		
			if(a_direita)
				return retornaCodigoJGEZDireita(codigo, endereco);
			else
				return retornaCodigoJGEZEsquerda(codigo, endereco);
		case ADD:
			return retornaCodigoADD(codigo, endereco);
		case ADDABS:
			return retornaCodigoADDABS(codigo, endereco);
		case SUB:
			return retornaCodigoSUB(codigo, endereco);
		case SUBABS:
			return retornaCodigoSUBABS(codigo, endereco);
		case MUL:
			return retornaCodigoMUL(codigo, endereco);
		case DIV:
			return retornaCodigoDIV(codigo, endereco);
		case LSH:
			return retornaCodigoLSH(codigo);
		case RSH:
			return retornaCodigoRSH(codigo);
		case STM:
			if(a_direita)
				return retornaCodigoSTMDireita(codigo, endereco);
			else
				return retornaCodigoSTMEsquerda(codigo, endereco);
		default:
			return "Mnemonico nao conhecido";
	}
}

char* retornaCodigoLDMQ(char *codigo)
{
	strcpy(codigo, "0A ");
	char *endereco = "000";
	return strcat(codigo, endereco);
}

char* retornaCodigoLDMQM(char *codigo, char *endereco)
{
	strcpy(codigo,"09 ");
	return strcat(codigo, endereco);
}

char* retornaCodigoSTR(char *codigo, char *endereco)
{
	strcpy(codigo,"21 ");
	return strcat(codigo, endereco);
}

char* retornaCodigoLOAD(char *codigo, char *endereco)
{
	strcpy(codigo,"01 ");
	return strcat(codigo, endereco);
}

char* retornaCodigoLDN(char *codigo, char *endereco)
{
	strcpy(codigo,"02 ");
	return strcat(codigo, endereco);
}

char* retornaCodigoLDABS(char *codigo, char *endereco)
{
	strcpy(codigo,"03 ");
	return strcat(codigo, endereco);
}

char* retornaCodigoJMPDireita(char *codigo, char *endereco)
{
	strcpy(codigo,"0D ");
	return strcat(codigo, endereco);
}

char* retornaCodigoJMPEsquerda(char *codigo, char *endereco)
{
	strcpy(codigo,"0E ");
	return strcat(codigo, endereco);
}

char* retornaCodigoJGEZDireita(char *codigo, char *endereco)
{
	strcpy(codigo,"0F ");
	return strcat(codigo, endereco);
}

char* retornaCodigoJGEZEsquerda(char *codigo, char *endereco)
{
	strcpy(codigo,"10 ");
	return strcat(codigo, endereco);
}

char* retornaCodigoADD(char *codigo, char *endereco)
{
	strcpy(codigo,"05 ");
	return strcat(codigo, endereco);
}

char* retornaCodigoADDABS(char *codigo, char *endereco)
{
	strcpy(codigo,"07 ");
	return strcat(codigo, endereco);
}

char* retornaCodigoSUB(char *codigo, char *endereco)
{
	strcpy(codigo,"06 ");
	return strcat(codigo, endereco);
}

char* retornaCodigoSUBABS(char *codigo, char *endereco)
{
	strcpy(codigo,"08 ");
	return strcat(codigo, endereco);
}

char* retornaCodigoMUL(char *codigo, char *endereco)
{
	strcpy(codigo,"0B ");
	return strcat(codigo, endereco);
}

char* retornaCodigoDIV(char *codigo, char *endereco)
{
	strcpy(codigo,"0C ");
	return strcat(codigo, endereco);
}

char* retornaCodigoLSH(char *codigo)
{
	strcpy(codigo,"14 ");
	char *endereco = "000";
	return strcat(codigo, endereco);
}

char* retornaCodigoRSH(char *codigo)
{
	strcpy(codigo,"15 ");
	char *endereco = "000";
	return strcat(codigo, endereco);
}

char* retornaCodigoSTMDireita(char *codigo, char *endereco)
{
	strcpy(codigo,"12 ");
	return strcat(codigo, endereco);
}

char* retornaCodigoSTMEsquerda(char *codigo, char *endereco)
{
	strcpy(codigo,"13 ");
	return strcat(codigo, endereco);
}
