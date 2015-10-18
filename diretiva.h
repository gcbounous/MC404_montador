#ifndef DIRETIVA_H_   
#define DIRETIVA_H_

typedef enum mnemonicoDiretiva
{
	ORG = 1,
	WORD,
	ALIGN,
	WFILL,
	SET
}MnemonicoDiretiva;

typedef struct diretivaSet
{
	char *nome;
	char *valor;
}DiretivaSet;

typedef struct posicao
{
	int pos;
	int a_direita;
}Posicao;

int diretivaValida(char *token);
int trataDiretivas(char* token, char *arg1, char *arg2, DiretivaSet *var_setadas, Posicao *enderecoAtual);
int diretivaOrg(char *arg, DiretivaSet *var_setadas, Posicao *posicaoAtual);
int getDiretivaSetada(char *nomeDiretiva, DiretivaSet *var_setadas);

// int diretivaSet(char *arg1, char *arg2, DiretivaSet var_setadas[]);
// int diretivaWord(char *arg, DiretivaSet var_setadas[], Posicao posicaoAtual);
// int diretivaAlign(char *arg, DiretivaSet var_setadas[], Posicao posicaoAtual);
// int diretivaWfill(char *arg1, char *arg2, DiretivaSet var_setadas[], Posicao posicaoAtual);

#endif