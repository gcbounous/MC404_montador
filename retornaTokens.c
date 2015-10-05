#include <stdio.h>
#include <string.h>

#include "retornaTokens.h"

void retornaTokens(char *nomeArq){

    FILE *tokens;
    FILE *arq;
    char frase[1001];
    char *token;

    /* abre o arquivo */
    arq = fopen(nomeArq, "r");
    tokens = fopen("tokens.out", "w+");

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
}




