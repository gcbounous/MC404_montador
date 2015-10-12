#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "rotulo.h"

void recuperarRotulos(char *arquivo, Rotulo rotulos[])
{
	FILE *arq_stream;
	char uma_linha[100];

	arq_stream = fopen(arquivo, "r");

	int i = 0;
	while( fgets (uma_linha , 100 , arq_stream) != NULL ) //recupera a linha e grava em uma_linha
	{
		if (rotuloValido(uma_linha))
		{
			int j = 0;
			while(uma_linha[j] != ':')
			{
				rotulos[i].nome[j] = uma_linha[j];
				j++;
			}
		}
		i++;
	}
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
