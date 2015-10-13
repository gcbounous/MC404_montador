#ifndef ROTULO_H_   
#define ROTULO_H_


struct Rotulo
{
	char nome[100];
	int endereco;
	int a_direita;
};
typedef struct Rotulo Rotulo;

void recuperarRotulos(char **tokens, Rotulo rotulos[]);
int rotuloValido(char* token);

#endif