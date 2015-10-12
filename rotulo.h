#ifndef ROTULO_H_   
#define ROTULO_H_


struct rotulo
{
	char nome[100];
	int endereco;
	int a_direita;
};
typedef struct rotulo rotulo;

void recuperarRotulos(char *arquivo, rotulo rotulos[]);
int rotuloValido(char* token);

#endif