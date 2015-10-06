#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rotulo.h"
#include "retornaTokens.h"

int main(int argc, char *argv[]) {
	char *nomeArqOut = (char *) malloc(100);
	char **rotulos = malloc(1000*sizeof(char*));
	int i;
	//alocaçao da memoria para cada string na tabela
	for(i = 0; i<1000; i++)
	{
		rotulos[i] = malloc(100*sizeof(char));
	}

	//rotulo rotulos = {}

	//tratamento caso tenha o nome do arquivo de saida ou nao
	if( argc < 2)
	{
		printf("Lançar o programa no formato:\n\t./montador arquivo_de_entrada [arquivo_de_saida]\n");
		// return 0;
	}
	else if( argc == 2)
	{
		strcpy(nomeArqOut, limpaNomeArquivo(argv[1]));
		retornaTokens(argv[1], nomeArqOut);
	}
	else
	{
		strcpy(nomeArqOut, limpaNomeArquivo(argv[2]));
		retornaTokens(argv[1], nomeArqOut);
	}

	strcat(nomeArqOut, ".out");
	rotulos = recuperarRotulos(nomeArqOut, &(*rotulos));

	free(nomeArqOut);
	free(rotulos);
    return 0;
}