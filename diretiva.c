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
int trataDiretivas(char* token, char *arg1, char *arg2, DiretivaSet var_setadas[], Posicao *posicaoAtual, char *dados, int *flag_org, int *flag_align)
{	
	int salto = 0; //quantidade de linhas a saltar (argumentos 1 e 2 caso forem solicitado)
	MnemonicoDiretiva mnemD = diretivaValida(token);;

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
			if(diretivaSet(arg1, arg2, var_setadas))
			{
				*flag_org = 0;
				*flag_align = 0;
				salto += 2;	
			}
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

int diretivaWord(char *arg, DiretivaSet var_setadas[], Posicao *posicaoAtual, char *dados, int flag_org)
{
	if(isdigit(arg[0]))
	{
		if(dados != NULL)
		{	
			char *temp = malloc(sizeof(char*)*1000);		
			if(arg[0] == '0' && arg[1] == 'X')
			{				
				arg += 2;				
			}
			if(!flag_org)
				posicaoAtual->pos++;
			formatarPos(posicaoAtual->pos, temp);
			if((int)strlen(arg) == 3)
			{
				strcat(temp, " 00 00 00 0");
				temp[(int)strlen(temp)] = arg[0];
				strcat(temp, " ");
				arg += 1;
			}
			else if((int)strlen(arg) == 2)
			{
				strcat(temp, " 00 00 00 00 ");
			}
			else if((int)strlen(arg) == 1)
			{
				strcat(temp, " 00 00 00 00 0");
			}
			else
			{
				// TODO: erro, constante nao valida
				free(temp);
				return 0;
			}
			strcat(temp, arg); 
			strcat(temp,"\n");
			strcat(dados,temp);
			free(temp);
		}
		return 1;
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


int diretivaWfill(char *arg1, char *arg2, DiretivaSet var_setadas[], Posicao *posicaoAtual, char *dados, int flag_org)
{
	int repeticoes = strtol(arg1, NULL, 10);	
	if(repeticoes > 0 && isdigit(arg2[0]))
	{
		if(dados != NULL)
		{	
			char temp_valor[14];
			char *temp = (char*)malloc(sizeof(char*));	

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

			free(temp);
		}
		return 1;
	}
    return 0;
}

int diretivaSet(char *arg1, char *arg2, DiretivaSet var_setadas[])
{
	int bool_ok = 0;
	if(var_setadas != NULL)
	{
		if(isalpha(arg1[0]))
		{
			bool_ok = 1;
			int i = 1;
			while(i < strlen(arg1))
			{
				if(!isalnum(arg1[i]))
				{
					bool_ok = 0;
					break;
				}
				i++;
			}

			if(arg2[0] == '0' && arg2[1] == 'X')
			{				
				arg2 += 2;		
			}

			int arg_int = strtol(arg2, NULL, 10);
			if(arg_int < 0) 
				bool_ok = 0; 

			if(bool_ok)
			{
				for(i = 0; i<100; i++)
				{	
					if(strcmp(var_setadas[i].nome, "") == 0 || strcmp(var_setadas[i].valor, "") == 0)
					{
						strcpy(var_setadas[i].nome, arg1);
						strcpy(var_setadas[i].valor, arg2);
						break;
					}
					else if(strcmp(var_setadas[i].nome, arg1) == 0)
					{
						//TODO: erro, constante arg1 ja foi setada
						break;
					}
				}				
				return 1;
			}
		}
	}
	else 
	{
		return 1;
	}

   return 0;
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
