#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "rotulo.h"

void recuperarRotulos(char **tokens, Rotulo rotulos[])
{
	char uma_linha[100];
	int i = 0;
	int k = 0;
	while (strcmp(tokens[i],"") != 0)
	{
		strcpy(uma_linha, tokens[i]);
		if (rotuloValido(uma_linha))
		{
			int j = 0;
			while(uma_linha[j] != ':')
			{
				rotulos[k].nome[j] = uma_linha[j];
				j++;
			}
			k++;
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
				if(i+1 == strlen(token))
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
