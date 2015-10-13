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

	preencherRotulos(vetorTokens, rotulos);

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
				int r = estaEmRotulos(tokens[i+1]+2, rotulos);
				if(r != -1)
				{
					traduzir(instrucao, endereco, rotulos[r].a_direita, codigo);
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
			//TODO: verificar qual diretiva é e chamar o metodo correspondente
			printf("%s é uma diretiva valida\n", uma_linha);
		}
		else printf("%s nao é um token valido\n", uma_linha);

		//para a ultima istrucao, completa a linha
		if(strcmp(tokens[i+1],"") == 0 && posicaoAtual.a_direita == 1)
		{
			strcat(linha_hex, "00 000");
			fprintf(arq_saida, "%s\n",linha_hex );
		}

		i++;
	}

	fclose(arq_saida);
	free(linha_hex);
	free(codigo);
	free(posicao);
}

void preencherRotulos(char **tokens, Rotulo rotulos[])
{
	char uma_linha[100];

	Posicao posicaoAtual;
	posicaoAtual.pos = 0;
	posicaoAtual.a_direita = 0;

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
			//TODO: verificar qual diretiva é e chamar o metodo correspondente
			printf("%s é uma diretiva valida\n", uma_linha);
		}

		i++;
	}

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

		i = estaEmRotulos(token, rotulos);
		if (i != -1)
		{
			formatarPos(rotulos[i].endereco, endereco);
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
		return 0;
	//endereco valido 
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