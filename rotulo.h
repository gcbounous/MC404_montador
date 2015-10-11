#ifndef ROTULO_H_   
#define ROTULO_H_


// struct rotulos
// {
// 	char *nome[];
// 	int endereco[];
// };

char** recuperarRotulos(char *arquivo, char** lista_rotulos);
int rotuloValido(char* token);

#endif