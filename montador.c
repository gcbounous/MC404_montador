#include <stdio.h>
#include <string.h>

#include "retornaTokens.h"

int main(int argc, char *argv[]) {

	char *nomeArqOut;

	if( argc < 2)
	{
		printf("Lançar o programa no formato:\n\t./montador arquivo_de_entrada [arquivo_de_saida]\n");
	}
	else if( argc == 2)
	{
		retornaTokens(argv[1], NULL);
	}
	else
	{
		nomeArqOut = argv[2];
		retornaTokens(argv[1], nomeArqOut);
	}

    return 0;
}