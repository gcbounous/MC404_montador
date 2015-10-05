#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "retornaTokens.h"

int main(int argc, char *argv[]) {
	char *nomeArqOut = (char *) malloc(100);
	//tratamento caso tenha o nome do arquivo de saida ou nao
	if( argc < 2)
	{
		printf("Lançar o programa no formato:\n\t./montador arquivo_de_entrada [arquivo_de_saida]\n");
	}
	else if( argc == 2)
	{
		strcpy(nomeArqOut, limpaNomeArquivo(argv[1]));
		retornaTokens(argv[1], nomeArqOut);
	}
	else
	{
		printf("1- %s\n", argv[2]);
		strcpy(nomeArqOut, limpaNomeArquivo(argv[2]));
		printf("1- %s\n", nomeArqOut);
		retornaTokens(argv[1], nomeArqOut);
	}

	free(nomeArqOut);
    return 0;
}