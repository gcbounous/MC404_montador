#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "retornaTokens.h"

/*
* Metodo que recebe o nome do arquivo de entrada e de saida (opcional) e limpa o codigo dos comentarios e retira dele os tokens necessarios para o tratamento. 
* Os tokens sao registrados em um arquivo .out
*/
void retornaTokens(char *nomeArqIn, char *nomeArqOut){
	FILE *tokens;
    FILE *arq;
    char *nomeOut = (char *) malloc(100);
    char frase[1001];
    char *token;

    strcpy(nomeOut, nomeArqOut);
    strcat(nomeOut, ".out");
    
    /* abre o arquivo */
    arq = fopen(nomeArqIn, "r");
    tokens = fopen(nomeOut, "w+");

    while(fgets(frase, 1000, arq)){
        token = strtok(frase," \t\n");
        while(token != NULL && *token != '#' && *token != ';'){
            /* escreve o token */
            fprintf(tokens, "%s\n" ,token);
            token = strtok(NULL," \t\n");
        }
    }

    /* fecha os arquivos */
    fclose(arq);
    fclose(tokens);

    free(nomeOut);
}

/*
* Metodo que recupera o nome de um arquivo e tira a extençao, o retornando "limpo" para ser tratado
*/
char* limpaNomeArquivo(char *nomeCompleto){
	char *nome = (char *) malloc(100);
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





