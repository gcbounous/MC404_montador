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
int trataDiretivas(char* token, char *arg1, char *arg2, DiretivaSet var_setadas[], Posicao *enderecoAtual, char *dados, int *flag_org, int *flag_align);
int diretivaOrg(char *arg, Posicao *posicaoAtual);
int diretivaWord(char *arg, DiretivaSet var_setadas[], Posicao *posicaoAtual, char *dados, int flag_org);
int diretivaAlign(char *arg, Posicao *posicaoAtual);
int diretivaWfill(char *arg1, char *arg2, DiretivaSet var_setadas[], Posicao *posicaoAtual, char *dados, int flag_org);
int diretivaSet(char *arg1, char *arg2, DiretivaSet var_setadas[]);
void formatarPos(int pos, char *s_pos);

#endif