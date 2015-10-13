#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "rotulo.h"
#include "retornaTokens.h"
#include "tradutor.h"
#include "montador.h"
#include "diretiva.h"

int main(int argc, char *argv[])
{
	char *nomeSemSufixo = (char *) malloc(100);
	Rotulo rotulos[50];
	char **vetorTokens = malloc(10000*sizeof(char*));
	int i;
	//alocaçao da memoria para cada string na tabela
	for(i = 0; i<10000; i++)
	{
		vetorTokens[i] = malloc(sizeof(char*));
	}

	//tratamento caso tenha o nome do arquivo de saida ou nao
	if( argc < 2)
	{
		printf("Lançar o programa no formato:\n\t./montador arquivo_de_entrada [arquivo_de_saida]\n");
		return 0;
	}
	else if( argc == 2)
	{
		strcpy(nomeSemSufixo, argv[1]);
		vetorTokens = retornaTokens(argv[1], vetorTokens);
	}
	else 
	{
		strcpy(nomeSemSufixo, argv[2]);
		vetorTokens = retornaTokens(argv[1], vetorTokens);
	}

	recuperarRotulos(vetorTokens, rotulos);

	interpretar(nomeSemSufixo, vetorTokens, rotulos);

	free(nomeSemSufixo);
    return 0;
}

void interpretar(char *nomeSemSufixo, char **tokens, Rotulo rotulos[])
{
	FILE *arq_saida;
	char uma_linha[100];
	char *linha_hex = malloc(sizeof (char*));
	char *codigo = malloc(sizeof(char*));
	char *posicao = malloc(sizeof(char*));
	char *endereco = malloc(sizeof(char*));

	// VariavelSet variaveis[100];
	Posicao posicaoAtual;
	posicaoAtual.pos = 0;
	posicaoAtual.a_direita = 0;

	arq_saida = fopen(strcat(nomeSemSufixo, ".hex"), "w");

	int i = 0;
	while (strcmp(tokens[i],"") != 0)
	{
		strcpy(uma_linha, tokens[i]);

		int instrucao = istrucaoValida(uma_linha);
		formatarPos(posicaoAtual.pos, posicao);

		if(posicaoAtual.a_direita == 0)
		{
			strcpy(linha_hex, posicao);
			strcat(linha_hex, " ");
		}

		if (instrucao != 0)
		{
			if (enderecoValido(tokens[i+1], endereco))
			{
				// strcpy(endereco, tokens[i+1]);
				traduzir(instrucao, endereco, posicaoAtual.a_direita, codigo);
				strcat(linha_hex, codigo);

			}
			else
			{
				traduzir(instrucao, "000", posicaoAtual.a_direita, codigo);
				strcat(linha_hex, codigo);
			}
			printf("%s é uma instrucao \n", uma_linha);
			printf("%s\n", linha_hex);

			if(posicaoAtual.a_direita == 0)
			{
				posicaoAtual.a_direita = 1;
				strcat(linha_hex, " ");
			}
			else
			{
				posicaoAtual.a_direita = 0;
				posicaoAtual.pos++;
				fprintf(arq_saida, "%s\n",linha_hex );
			}

		}
		else 
			if (rotuloValido(uma_linha))
		{
			printf("%s é um rotulo \n", uma_linha);
		}
		else if (diretivaValida(uma_linha))
		{
			printf("%s é uma diretiva valida\n", uma_linha);
		}
		else printf("%s nao é um token valido\n", uma_linha);
		i++;
	}

	fclose(arq_saida);
	free(linha_hex);
	free(codigo);
	free(posicao);
}

//Metodo retorna codigo do mnemonico(associado ao enum) se instrucao existir
int istrucaoValida(char *token)
{
	Mnemonico m;
	if(strncmp(token, "LDMQM", strlen("LDMQM")) == 0){ m = LDMQM;}
    else if(strncmp(token, "LDMQ", strlen("LDMQ")) == 0){ m = LDMQ;}
    else if(strncmp(token, "STR", strlen("STR")) == 0){ m = STR;}
    else if(strncmp(token, "LOAD", strlen("LOAD")) == 0){ m = LOAD;}
    else if(strncmp(token, "LDN", strlen("LDN")) == 0){ m = LDN;}
    else if(strncmp(token, "LDABS", strlen("LDABS")) == 0){ m = LDABS;}
    else if(strncmp(token, "JMP", strlen("JMP")) == 0){ m = JMP;}
    else if(strncmp(token, "JGEZ", strlen("JGEZ")) == 0){ m = JGEZ;}
    else if(strncmp(token, "ADDABS", strlen("ADDABS")) == 0){ m = ADDABS;}
    else if(strncmp(token, "ADD", strlen("ADD")) == 0){ m = ADD;}
    else if(strncmp(token, "SUBABS", strlen("SUBABS")) == 0){ m = SUBABS;}
    else if(strncmp(token, "SUB", strlen("SUB")) == 0){ m = SUB;}
    else if(strncmp(token, "MUL", strlen("MUL")) == 0){ m = MUL;}
    else if(strncmp(token, "DIV", strlen("DIV")) == 0){ m = DIV;}
    else if(strncmp(token, "LSH", strlen("LSH")) == 0){ m = LSH;}
    else if(strncmp(token, "RSH", strlen("RSH")) == 0){ m = RSH;}
    else if(strncmp(token, "STM", strlen("STM")) == 0){ m = STM;}
    else
    	return 0;
    return m;
}

int enderecoValido(char *token, char *endereco)
{
	if(isdigit(token[0]) && token[1] == 'X')
	{	
		token += 2;
		strcpy(endereco, token);
	}
	else if (rotuloValido(token))
	{
		//acharRotulo()
		//copiar endereco em endereco
	}
	else if(token[0] == 'M')
	{
		int i ;
		for(i = 4; i < 7; i++)
		{
			endereco[i-4] = token[i];
		}
	}
	else return 0;

	return 1;
}

void formatarPos(int pos, char *s_pos)
{
	char *prefixo = malloc(sizeof (char*));
	sprintf(s_pos,"%d",pos);
	if(pos < 10)
	{
		strcpy(prefixo, "00");
		strcat(prefixo, s_pos);
		strcpy(s_pos, prefixo);
	}
	else if(pos < 100)
	{
		strcpy(prefixo, "0");
		strcat(prefixo, s_pos);
		strcpy(s_pos, prefixo);
	}
	free(prefixo);
}