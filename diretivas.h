#ifndef DIRETIVAS_H_INCLUDED
#define DIRETIVAS_H_INCLUDED

struct Diretiva{
    char *nome;
    int valor;
};

struct Posicao{
    int linha;
    int direita;
};

typedef struct Diretiva Diretiva;
typedef struct Posicao Posicao;

int trataDiretivas(FILE *arq, Posicao posicaoAtual, Diretiva diretivas[], FILE *hex);

int diretivaSet(char *arg1, char *arg2, Diretiva diretivas[]);

int diretivaOrg(char *arg, Diretiva diretivas[], Posicao posicaoAtual);

int diretivaWord(char *arg, Diretiva diretivas[], Posicao posicaoAtual);

int diretivaAlign(char *arg, Diretiva diretivas[], Posicao posicaoAtual);

int diretivaWfill(char *arg1, char *arg2, Diretiva diretivas[], Posicao posicaoAtual);

int mnemonicos(char *token);

#endif // DIRETIVAS_H_INCLUDED
