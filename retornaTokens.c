#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "retornaTokens.h"

void retornaTokens(char *nomeArqIn, char *nomeArqOut){
	char * nomeOut = (char *) malloc(100);

	if(nomeArqOut == NULL)
	{
		strcpy(nomeOut, limpaNomeArquivo(nomeArqIn));
		strcat(nomeOut, ".out");
		printf("%s\n", nomeArqIn);
		printf("%s\n", nomeOut);
	}
	else 
	{
		strcpy(nomeOut, limpaNomeArquivo(nomeArqOut));
		strcat(nomeOut, ".out");
		printf("%s\n", nomeArqIn);
		printf("%s\n", nomeOut);
	}

    // FILE *tokens;
    // FILE *arq;
    // char frase[1001];
    // char *token;

    // /* abre o arquivo */
    // arq = fopen(nomeArqIn, "r");
    // tokens = fopen("tokens.out", "w+");

    // while(fgets(frase, 1000, arq)){
    //     token = strtok(frase," \t\n");
    //     while(token != NULL && *token != '#' && *token != ';'){
    //         /* escreve o token */
    //         fprintf(tokens, "%s\n" ,token);
    //         token = strtok(NULL," \t\n");
    //     }
    // }

    // /* fecha os arquivos */
    // fclose(arq);
    // fclose(tokens);

    free(nomeOut);
}

char* limpaNomeArquivo(char *nomeCompleto){
	char * nome = (char *) malloc(100);
	strcpy(nome, nomeCompleto);
	int i = 0;


	while(nomeCompleto[i] != '\0')
	{
		if (nomeCompleto[i] == '.')
		{
			nome[i] = '\0';
			break;
		}		
		i++;
	}
	return nome;
}





