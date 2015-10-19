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

	interpretar(nomeSemSufixo, vetorTokens, rotulos);

	free(nomeSemSufixo);
	for(i = 0; i<10000; i++)
	{
		free(vetorTokens[i]);
	}
	free(vetorTokens);

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
	char *dados = malloc(sizeof(char*)*sizeof(char*));

	// VariavelSet variaveis[100];
	Posicao posicaoAtual;
	posicaoAtual.pos = 0;
	posicaoAtual.a_direita = 0;

	arq_saida = fopen(strcat(nomeSemSufixo, ".hex"), "w");

	//preenche rotulos com seus enderecos e escreve os dados
	preLeitura(tokens, rotulos, dados);

	int i = 0;
	while (strcmp(tokens[i],"") != 0)
	{
		strcpy(uma_linha, tokens[i]);

		int instrucao = istrucaoValida(uma_linha);
		formatarPos(posicaoAtual.pos, posicao);

		//coloca o endereco de memoria na linha a ser imprimida
		if(posicaoAtual.a_direita == 0)
		{
			strcpy(linha_hex, posicao);
			strcat(linha_hex, " ");
		}

		//verifica se é instrucao e escreve o codigo com o endereco da instrucao no .hex
		if (instrucao != 0)
		{
			int resposta_endereco = enderecoValido(tokens[i+1], endereco, rotulos);
			if (resposta_endereco == 1)
			{				
				traduzir(instrucao, endereco, 0, codigo);
				strcat(linha_hex, codigo);
				i++;
			}
			//caso o endereco seja um rotulo enderecoValido retorna 2 e podemos recuperar o a_direita do rotulo
			else if(resposta_endereco == 2)
			{
				int dir_rotulo = getDireitaRotulo(tokens[i+1]+2, rotulos);
				if(dir_rotulo != -1)
				{
					traduzir(instrucao, endereco, dir_rotulo, codigo);
					strcat(linha_hex, codigo);
					i++;
				} else printf("o rotulo %s nao existe.\n", tokens[i+1]);
			}
			else
			{
				traduzir(instrucao, "000", 0, codigo);
				strcat(linha_hex, codigo);
			}

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
		// verifica se é rotulo
		else if (rotuloValido(uma_linha))
		{
			//se for um rotulo a gente ignora
		}
		//verifica se é diretiva
		else if (diretivaValida(uma_linha))
		{
			int d = trataDiretivas(uma_linha, tokens[i+1], tokens[i+2], NULL, &posicaoAtual, NULL);
			i += d;
			printf("%s é uma diretiva valida, posicaoAtual: %d, %d e salta %d linhas\n", uma_linha, posicaoAtual.pos, posicaoAtual.a_direita, d);
		}
		else printf("%s nao é um token valido\n", uma_linha);

		//para a ultima istrucao, completa a linha ou para completar uma linha depois de um .org
		if((strcmp(tokens[i+1],"") == 0 && posicaoAtual.a_direita == 1) ||( (int)strlen(linha_hex) == 11 && posicaoAtual.a_direita == 0))
		{
			strcat(linha_hex, "00 000");
			fprintf(arq_saida, "%s\n",linha_hex );
		}

		i++;
	}
	fprintf(arq_saida, "\n%s\n",dados);

	free(linha_hex);
	free(codigo);
	free(posicao);
	free(endereco);
	free(dados);

	fclose(arq_saida);
}

/*
* Metodo que faz uma pre leitura do programa recuperando e preenchendo os rotulos e interpretando as diretivas
*/
void preLeitura(char **tokens, Rotulo rotulos[], char *dados)
{
	char uma_linha[100];
	//TODO: fazer!!! DiretivaSet *var_setadas

	Posicao posicaoAtual;
	posicaoAtual.pos = 0;
	posicaoAtual.a_direita = 0;

	recuperarRotulos(tokens, rotulos);

	int i = 0;
	while (strcmp(tokens[i],"") != 0)
	{
		strcpy(uma_linha, tokens[i]);

		int instrucao = istrucaoValida(uma_linha);

		//verifica se é instrucao e escreve o codigo com o endereco da instrucao no .hex
		if (instrucao != 0)
		{
			if(posicaoAtual.a_direita == 0)
			{
				posicaoAtual.a_direita = 1;

				if(strcmp(tokens[i+1], ".WORD") == 0 || strcmp(tokens[i+2], ".WORD") == 0)
					posicaoAtual.pos++;
			}
			else
			{
				posicaoAtual.a_direita = 0;
				posicaoAtual.pos++;
			}
		}
		// verifica se é rotulo
		else if (rotuloValido(uma_linha))
		{
			int j;
			for(j = 0; j < 50; j++)
			{
				if(strncmp(rotulos[j].nome, uma_linha, strlen(uma_linha)-1) == 0 && strlen(uma_linha)-1 == strlen(rotulos[j].nome))
				{
					rotulos[j].endereco = posicaoAtual.pos;
					rotulos[j].a_direita = posicaoAtual.a_direita;
					break;
				}
			}
		}
		//verifica se é diretiva
		else if (diretivaValida(uma_linha))
		{
			i += trataDiretivas(uma_linha, tokens[i+1], tokens[i+2], NULL, &posicaoAtual, dados);
		}
		i++;
	}
}

//Metodo retorna codigo do mnemonico(associado ao enum) se instrucao existir
int istrucaoValida(char *token)
{
	Mnemonico m;
	if(strncmp(token, "LDMQM", strlen("LDMQM")) == 0 && strlen("LDMQM") == strlen (token)){ m = LDMQM;}
    else if(strncmp(token, "LDMQ", strlen("LDMQ")) == 0 && strlen("LDMQ") == strlen (token)){ m = LDMQ;}
    else if(strncmp(token, "STR", strlen("STR")) == 0 && strlen("STR") == strlen (token)){ m = STR;}
    else if(strncmp(token, "LOAD", strlen("LOAD")) == 0 && strlen("LOAD") == strlen (token)){ m = LOAD;}
    else if(strncmp(token, "LDN", strlen("LDN")) == 0 && strlen("LDN") == strlen (token)){ m = LDN;}
    else if(strncmp(token, "LDABS", strlen("LDABS")) == 0 && strlen("LDABS") == strlen (token)){ m = LDABS;}
    else if(strncmp(token, "JMP", strlen("JMP")) == 0 && strlen("JMP") == strlen (token)){ m = JMP;}
    else if(strncmp(token, "JGEZ", strlen("JGEZ")) == 0 && strlen("JGEZ") == strlen (token)){ m = JGEZ;}
    else if(strncmp(token, "ADDABS", strlen("ADDABS")) == 0 && strlen("ADDABS") == strlen (token)){ m = ADDABS;}
    else if(strncmp(token, "ADD", strlen("ADD")) == 0 && strlen("ADD") == strlen (token)){ m = ADD;}
    else if(strncmp(token, "SUBABS", strlen("SUBABS")) == 0 && strlen("SUBABS") == strlen (token)){ m = SUBABS;}
    else if(strncmp(token, "SUB", strlen("SUB")) == 0 && strlen("SUB") == strlen (token)){ m = SUB;}
    else if(strncmp(token, "MUL", strlen("MUL")) == 0 && strlen("MUL") == strlen (token)){ m = MUL;}
    else if(strncmp(token, "DIV", strlen("DIV")) == 0 && strlen("DIV") == strlen (token)){ m = DIV;}
    else if(strncmp(token, "LSH", strlen("LSH")) == 0 && strlen("LSH") == strlen (token)){ m = LSH;}
    else if(strncmp(token, "RSH", strlen("RSH")) == 0 && strlen("RSH") == strlen (token)){ m = RSH;}
    else if(strncmp(token, "STM", strlen("STM")) == 0 && strlen("STM") == strlen (token)){ m = STM;}
    else
    	return 0;
    return m;
}

int enderecoValido(char *token, char *endereco, Rotulo rotulos[])
{
	if(isdigit(token[0]) && token[1] == 'X')
	{	
		token += 2;
		strcpy(endereco, token);
	}
	else if(token[0] == 'M')
	{
		token +=2;
		int i = 0 ;
		while(token[i]!='\0')
		{			
			if(token[i] == ')')
			{
				token[i] = '\0';
				break;
			}
			i++;
		}

		int end = getEnderecoRotulo(token, rotulos);
		if (end != -1)
		{
			formatarPos(end, endereco);
			//se rotulo valido retorna 2
			return 2;
		}
		else
		{
			token += 2;
			strcpy(endereco, token);
		}
	}
	else
	{
		// TODO: erro endereco nao valido
		return 0;
	}

	//endereco valido 
	return 1;
}

//retorna o endereco do rotulo achado
int getEnderecoRotulo(char *rotulo, Rotulo rotulos[])
{
	int i = estaEmRotulos(rotulo, rotulos);
	if(i != -1)
	{
		return rotulos[i].endereco;
	}
	return -1;
}

//retorna se rotulo esta a direita ou nao
int getDireitaRotulo(char *rotulo, Rotulo rotulos[])
{
	int i = estaEmRotulos(rotulo, rotulos);
	if(i != -1)
	{
		return rotulos[i].a_direita;
	}
	return -1;
}

//se estiver em rotulos[] retorna o indice, senao retorna -1
int estaEmRotulos(char *rotulo, Rotulo rotulos[])
{
	int i;
	for(i = 0; strcmp(rotulos[i].nome,"") != 0 && i<50; i++ )
	{
		if(strncmp(rotulos[i].nome, rotulo, strlen(rotulos[i].nome)) == 0 && strlen(rotulos[i].nome) == strlen(rotulo))
		{
			return i;
		}
	}
	return -1;
}
