#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rotulo.h"
#include "retornaTokens.h"
#include "tradutor.h"
#include "diretivas.h"


int main(int argc, char *argv[])
{
	// exemplo de codigo de traduçao de uma instrucao
	// char *codigo = malloc(sizeof(char*)*10);
	// enum mnemonico mnemonico = JMP;
	// char *endereco = "074";
	// printf("O codigo para a instrucao JMP para o end %s é: ", endereco);
	// printf("%s\n", traduzir(mnemonico, endereco, 0, codigo));
	// free(codigo);

	char *nomeArqOut = (char *) malloc(100);
	char *nomeSemSufixo = (char *) malloc(100);
	Rotulo rotulos[50];

	//tratamento caso tenha o nome do arquivo de saida ou nao
	if( argc < 2)
	{
		printf("Lançar o programa no formato:\n\t./montador arquivo_de_entrada [arquivo_de_saida]\n");
		return 0;
	}
	else if( argc == 2)
	{
		strcpy(nomeArqOut, argv[1]);
		retornaTokens(argv[1], nomeArqOut);
	}
	else
	{
		strcpy(nomeArqOut, argv[2]);
		retornaTokens(argv[1], nomeArqOut);
	}

	strcpy(nomeSemSufixo, nomeArqOut);
	strcat(nomeArqOut, ".out");
	recuperarRotulos(nomeArqOut, rotulos);

	remove(nomeArqOut);
	free(nomeSemSufixo);
	free(nomeArqOut);
    return 0;
}
