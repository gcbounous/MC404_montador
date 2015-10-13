#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "retornaTokens.h"

/*
* Metodo que recebe o nome do arquivo de entrada e de saida (opcional) e limpa o codigo dos comentarios e retira dele os tokens necessarios para o tratamento. 
* Os tokens sao registrados em um arquivo .out
*/
char** retornaTokens(char *nomeArqIn, char **vet_tokens){
    FILE *arq;
    char frase[1001];
    char *token;

    /* abre o arquivo */
    arq = fopen(nomeArqIn, "r");

    int i = 0;
    while(fgets(frase, 1000, arq)){
        token = strtok(frase," \t\n");
        while(token != NULL && *token != '#' && *token != ';'){
            int j = 0;
            while(token[j] != '\0'){
                if(token[j] >= 97 && token[j] <= 122)
                    token[j] -= 32;
                    j++;
            }
            /* escreve o token */
            strcpy(vet_tokens[i], token);
            // printf("%s\n", vet_tokens[i]);
            token = strtok(NULL," \t\n");
            i++;
        }
    }
    /* fecha os arquivos */
    fclose(arq);

    return vet_tokens;
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





