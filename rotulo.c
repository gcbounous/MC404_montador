#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "rotulo.h"

char** recuperarRotulos(char *arquivo, char **lista_rotulos)
{
	// char **rotulos = malloc(sizeof(char)*sizeof(char));
	FILE *arq_stream;
	char uma_linha[100];

	arq_stream = fopen(arquivo, "r");

	int i=0;
	while( fgets (uma_linha , 100 , arq_stream) != NULL ) //recupera a linha e grava em uma_linha
	{
		//TODO: Porra, estou recuprando as diretivas e nao os rotulos
		if (uma_linha[0] == '.')
		{
			strcpy(lista_rotulos[i],uma_linha);	
			printf("%s\n", lista_rotulos[i]);
		}
		i++;
	}
	 return lista_rotulos;
}
