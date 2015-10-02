#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]) {

    return 0;
}

FILE* retornaTokens(FILE *arq, char *nomeArq){

    FILE *tokens;
    char frase[1001], aux;
    char *token;
    int i, quebra = 0;

    /* abre o arquivo */
    arq = fopen(nomeArq, "r");
    tokens = fopen("tokens.txt", "w");

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

    return tokens;
}
