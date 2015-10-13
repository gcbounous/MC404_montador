#ifndef MONTADOR_H_   
#define MONTADOR_H_

struct Posicao
{
	int pos;
	int a_direita;
};
typedef struct Posicao Posicao;

void interpretar(char *nomeSemSufixo, char **vetorTokens, Rotulo rotulos[]);
void formatarPos(int pos, char *s_pos);
int istrucaoValida(char *token);
int enderecoValido(char *token, char *endereco);

#endif