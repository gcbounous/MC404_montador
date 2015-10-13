#ifndef DIRETIVA_H_   
#define DIRETIVA_H_

struct variavelSet
{
	char *nome;
	char *valor;
};
typedef struct variavelSet VariavelSet;

int diretivaValida(char *token);

#endif