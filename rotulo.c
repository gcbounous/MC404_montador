#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "rotulo.h"

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
		if (rotuloValido(uma_linha))
		{
			//TODO: retirar : do rotulo
			memcpy(uma_linha, uma_linha, strlen(uma_linha)-2);
			printf("%s\n", uma_linha);
			strcpy(lista_rotulos[i],uma_linha);	
			printf("%s\n", lista_rotulos[i]);
		}
		i++;
	}
	 return lista_rotulos;
}

int rotuloValido(char* token)
{
	if(isalpha(token[0]) || token[0] == '_')
	{ 
		int i=0;
		while(token[i] != '\0')
		{
			if(isalnum(token[i]) || token[i] == '_')
			{
				i++;
			}
			else if(token[i] == ':')
			{
				if(i+2 == strlen(token))
				{
					return 1;
				}
				else break;
			}
			else break;			
		}
	}
	return 0;
}