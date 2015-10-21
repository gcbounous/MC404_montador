#ifndef MONTADOR_H_   
#define MONTADOR_H_

void interpretar(char *nomeSemSufixo, char **vetorTokens, Rotulo rotulos[]);
void preLeitura(char **tokens, Rotulo rotulos[], DiretivaSet variaveis[], char *dado, int *n_instrucoes);
int istrucaoValida(char *token);
int enderecoValido(char *token, char *endereco, Rotulo rotulos[]);
int getEnderecoRotulo(char *rotulo, Rotulo rotulos[]);
int getDireitaRotulo(char *rotulo, Rotulo rotulos[]);
int estaEmRotulos(char *rotulo, Rotulo rotulos[]);
char* getValorDiretivaSet(char *var, DiretivaSet var_setadas[]);
int estaEmVarSetadas(char *nomeDiretiva, DiretivaSet var_setadas[]);

#endif