#ifndef MONTADOR_H_   
#define MONTADOR_H_

void interpretar(char *nomeSemSufixo, char **vetorTokens, Rotulo rotulos[]);
void formatarPos(int pos, char *s_pos);
int istrucaoValida(char *token);
int enderecoValido(char *token, char *endereco, Rotulo rotulos[]);
int getEnderecoRotulo(char *rotulo, Rotulo rotulos[]);
int getDireitaRotulo(char *rotulo, Rotulo rotulos[]);
int estaEmRotulos(char *rotulo, Rotulo rotulos[]);
void preencherRotulos(char **tokens, Rotulo rotulos[]);

#endif