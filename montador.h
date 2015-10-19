#ifndef MONTADOR_H_   
#define MONTADOR_H_

void interpretar(char *nomeSemSufixo, char **vetorTokens, Rotulo rotulos[]);
int istrucaoValida(char *token);
int enderecoValido(char *token, char *endereco, Rotulo rotulos[]);
int getEnderecoRotulo(char *rotulo, Rotulo rotulos[]);
int getDireitaRotulo(char *rotulo, Rotulo rotulos[]);
int estaEmRotulos(char *rotulo, Rotulo rotulos[]);
void preLeitura(char **tokens, Rotulo rotulos[], char *dado);

#endif