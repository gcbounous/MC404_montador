#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "diretiva.h"

int diretivaValida(char *token)
{
	if(token[0] == '.')
	{
		MnemonicoDiretiva mnemD;
		token += 1;
		if ( strncmp(token,"ORG", strlen("ORG")) == 0){mnemD = ORG;}
		else if (strncmp(token,"WORD", strlen("WORD")) == 0){mnemD = WORD;}
		else if (strncmp(token,"SET", strlen("SET")) == 0){mnemD = SET;}
		else if (strncmp(token,"WFILL", strlen("WFILL")) == 0){mnemD = WFILL;}
		else if (strncmp(token,"ALIGN", strlen("ALIGN")) == 0){mnemD = ALIGN;}
		return mnemD;
	}
	return 0;
}

/* Metodo que acha a diretiva a ser tratada e a aplica mudando a tabela de variaveis e a posicaoAtual
* Retorna a quantidade de tokens a ser saltado de acordo com a quantidade de argumentos usados pela diretiva
*/
int trataDiretivas(char* token, char *arg1, char *arg2, DiretivaSet *var_setadas, Posicao *posicaoAtual, char *dados, int *flag_org, int *flag_align)
{	
	int salto = 0; //quantidade de linhas a saltar (argumentos 1 e 2 caso forem solicitado)
	MnemonicoDiretiva mnemD = diretivaValida(token);
	switch (mnemD)
	{
		case ORG:
			if(diretivaOrg(arg1, posicaoAtual))
			{
				*flag_org = 1;
				*flag_align = 0;
				salto += 1;
			}
			break;
		case WORD:
			if(diretivaWord(arg1, var_setadas, posicaoAtual, dados, *flag_org))
			{
				*flag_org = 0;
				*flag_align = 0;
				salto += 1;
			}
			break;
		case SET:

			break;
		case WFILL:
			if(diretivaWfill(arg1, arg2, var_setadas, posicaoAtual, dados, *flag_org))
			{
				*flag_org = 0;
				*flag_align = 0;
				salto += 2;	
			}
			break;
		case ALIGN:
			if(diretivaAlign(arg1, posicaoAtual))
			{
				*flag_org = 0;
				*flag_align = 1;
				salto += 1;
			}	
			break;
		default:
				//TODO: erro diretiva inexistente (caso mnemD = 0)
			break;
	}
	return salto;
}

int diretivaOrg(char *arg, Posicao *posicaoAtual)
{
	arg += 2;
	int arg_int = strtol(arg, NULL, 10);
	if ((int)strlen(arg) == 3)
	{
		if(strncmp(arg,"000", strlen(arg)) == 0)
		{	
			posicaoAtual->pos = 0;
			return 1;
		}
		else if (arg_int > 0)
    	{
			posicaoAtual->pos = arg_int;
			return 1;
    	}
    	else
    	{
    		//TODO: erro, endereco invalido 
    	}
	}
    return 0;
}

int diretivaWord(char *arg, DiretivaSet diretivas[], Posicao *posicaoAtual, char *dados, int flag_org)
{
	if(isdigit(arg[0]))
	{
		if(dados != NULL)
		{	
			char *temp = malloc(sizeof(char*));		
			if(arg[0] == '0' && arg[1] == 'X')
			{				
				arg += 2;				
			}
			if(flag_org)
				formatarPos(posicaoAtual->pos, temp);
			else
				formatarPos(++posicaoAtual->pos, temp);
			strcat(dados, temp);

			if((int)strlen(arg) == 3)
			{
				strcat(dados, " 00 00 00 0");
				dados[(int)strlen(dados)] = arg[0];
				strcat(dados, " ");
				arg += 1;
			}
			else if((int)strlen(arg) == 2)
			{
				strcat(dados, " 00 00 00 00 ");
			}
			else if((int)strlen(arg) == 1)
			{
				strcat(dados, " 00 00 00 00 0");
			}
			else
			{
				// TODO: erro, constante nao valida
				free(temp);
				return 0;
			}
			strcat(dados, arg); 
			strcat(dados,"\n");
			free(temp);
		}
		return 1;
	}	
	else
	{
		//TODO: testar recebimento de variavel setada
    	// int end_dir = getDiretivaSetada( arg, diretivas);
    	// if (end_dir != -1)
    	// {
    	// 	posicaoAtual->pos = end_dir;
    	// 	posicaoAtual->a_direita = 0;
    	// 	return 1;
    	// }
    	// else
    	// {
    	// 	//TODO: erro, variavel nao existente
    	// }
	}
    return 0;
}

int diretivaAlign(char *arg, Posicao *posicaoAtual)
{
    int arg_int = strtol(arg, NULL, 10);
    if(arg_int == 1)
	{
		posicaoAtual->a_direita = 0;
		return 1;
	}
	else
		//TODO: erro, argumento nao valido
	return 0;
}


int diretivaWfill(char *arg1, char *arg2, DiretivaSet diretivas[], Posicao *posicaoAtual, char *dados, int flag_org)
{
	//TODO: erro de segmentacao com n grande de repeticoes
	int repeticoes = strtol(arg1, NULL, 10);	
	if(repeticoes > 0 && isdigit(arg2[0]))
	{
		if(dados != NULL)
		{	
			char *temp_valor = malloc(sizeof(char*));	
			char *temp = malloc(sizeof(char*));		
			if(arg2[0] == '0' && arg2[1] == 'X')
			{				
				arg2 += 2;				
			}
			if(!flag_org)
				posicaoAtual->pos++;

			if((int)strlen(arg2) == 3)
			{
				strcpy(temp_valor, " 00 00 00 0");
				temp_valor[(int)strlen(temp_valor)] = arg2[0];
				strcat(temp_valor, " ");
				arg2 += 1;
			}
			else if((int)strlen(arg2) == 2)
			{
				strcpy(temp_valor, " 00 00 00 00 ");
			}
			else if((int)strlen(arg2) == 1)
			{
				strcpy(temp_valor, " 00 00 00 00 0");
			}
			else
			{
				// TODO: erro, constante nao valida
				free(temp_valor);				
				free(temp);
				return 0;
			}
			strcat(temp_valor, arg2); 
			strcat(temp_valor,"\n");

			int i;
			for(i = 0; i < repeticoes; i++)
			{
				formatarPos(posicaoAtual->pos, temp);
				strcat(temp, temp_valor);
				strcat(dados, temp);
				posicaoAtual->pos++;
			}
			posicaoAtual->pos--;

			free(temp_valor);
			free(temp);
		}
		return 1;
	}	
	else
	{
		//TODO: testar recebimento de variavel setada
    	// int end_dir = getDiretivaSetada( arg2, diretivas);
    	// if (end_dir != -1)
    	// {
    	// 	posicaoAtual->pos = end_dir;
    	// 	posicaoAtual->a_direita = 0;
    	// 	return 1;
    	// }
    	// else
    	// {
    	// 	//TODO: erro, variavel nao existente
    	// }
	}
    return 0;
}

int getDiretivaSetada(char *nomeDiretiva, DiretivaSet *diretivas)
{
	int i = 0;
	while(strcmp(diretivas[i].nome, "") == 0)
	{
		if(strlen(nomeDiretiva) == strlen(diretivas[i].nome))
		{
			if(strcmp(diretivas[i].nome, nomeDiretiva) == 0)
				return strtol(diretivas[i].valor, NULL, 10);
		}
		i++;
	}
	//TODO: erro, varialvel nao setada
	return -1;
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


// int diretivaSet(char *arg2, char *arg2, Diretiva diretivas[]){
//     int i = 0, n;
//     if(mnemonicos(arg1) || mnemonicos(arg2))
//         return 0;

//     /* procura a primeira posicao que esteja
//     vazia no vetor de diretivas */
//     while(diretivas[i].nome != NULL)
//         i++;
//     /* caso os argumentos nao sejam instrucoes,
//      sao considerados validos
//      obs: vou refazer a funcao para verificar se
//      o argumento passado eh um mnemonico */

//     diretivas[i].nome = arg1;
//     sscanf(arg2, "%d", &n);
//     diretivas[i].valor = n;


//     return 1; /* caso de certo */
// }

