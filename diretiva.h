#ifndef DIRETIVA_H_   
#define DIRETIVA_H_

struct diretiva
{
	char *nome;
	char *valor;
};
typedef struct diretiva Diretiva;

struct Posicao
{
	int pos;
	int a_direita;
};
typedef struct Posicao Posicao;

int diretivaValida(char *token);

int diretivaSet(char *arg1, char *arg2, Diretiva diretivas[]);

int diretivaOrg(char *arg, Diretiva diretivas[], Posicao posicaoAtual);

int diretivaWord(char *arg, Diretiva diretivas[], Posicao posicaoAtual);

int diretivaAlign(char *arg, Diretiva diretivas[], Posicao posicaoAtual);

int diretivaWfill(char *arg1, char *arg2, Diretiva diretivas[], Posicao posicaoAtual);

#endif