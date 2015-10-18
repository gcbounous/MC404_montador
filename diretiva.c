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
int trataDiretivas(char* token, char *arg1, char *arg2, DiretivaSet *var_setadas, Posicao *posicaoAtual)
{	
	int salto = 0; //quantidade de linhas a saltar (argumentos 1 e 2 caso forem solicitado)
	MnemonicoDiretiva mnemD = diretivaValida(token);

	switch (mnemD)
	{
		case ORG:
			if(diretivaOrg(arg1, var_setadas, posicaoAtual))
			{
				salto += 1;
			}
			break;
		case WORD:

			break;
		case SET:

			break;
		case WFILL:

			break;
		case ALIGN:

			break;
		default:
				//TODO: erro diretiva inexistente (caso mnemD = 0)
			break;
	}
	return salto;
}

int diretivaOrg(char *arg, DiretivaSet *diretivas, Posicao *posicaoAtual)
{
	arg += 2;
	int arg_int = strtol(arg, NULL, 10);
	if (strncmp(arg,"000", strlen(arg)) == 0)
	{
		posicaoAtual->pos = 0;
		posicaoAtual->a_direita = 0;
		return 1;
	}
    else if (arg_int > 0)
    {
		posicaoAtual->pos = arg_int;
		posicaoAtual->a_direita = 0;
		return 1;
    }
    else
    {
    	//TODO: testar recebimento de variavel setada
    	int end_dir = getDiretivaSetada( arg, diretivas);
    	if (end_dir != -1)
    	{
    		posicaoAtual->pos = end_dir;
    		posicaoAtual->a_direita = 0;
    		return 1;
    	}
    }
    //TODO: erro, endereco invalido
    return 0;
}

int getDiretivaSetada(char *nomeDiretiva, DiretivaSet *diretivas)
{
	int i = 0;
	while(strcmp(diretivas[i].nome, "") == 0)
	{
		if(strlen(nomeDiretiva) == strlen(diretivas[i].nome) && strcmp(diretivas[i].nome, nomeDiretiva) == 0)
		{
			return strtol(diretivas[i].valor, NULL, 10);
		}
		i++;
	}
	//TODO: erro, varialvel nao setada
	return -1;
}

// int trataDiretivas(FILE *arq, Posicao posicaoAtual, Diretiva diretivas[], FILE *hex){
//     char token[101], diretiva[101];
//     char arg1[101], arg2[101];

//     while(fgets(token, 100, arq)){
//         if(token[0] == '.'){
//             sscanf(token, ".%s", diretiva);
//             if(!strcmp(diretiva, "SET")){
//                 fgets(arg1, 100, arq); /* le os argumentos para a diretiva */
//                 fgets(arg2, 100, arq);
//                 /* caso de errado */
//                 if(!diretivaSet(arg1, arg2, diretivas))
//                     return 0;
//             }
//             else if(!strcmp(diretiva, "ORG")){
//                 fgets(arg1, 100, arq);
//                 if(!diretivaOrg(arg1, diretivas, posicaoAtual))
//                     return 0;
//             }
//             else if(!strcmp(diretiva, "WORD")){
//                 fgets(arg1, 100, arq);
//                 if(!diretivaWord(arg1, diretivas, posicaoAtual))
//                     return 0;
//             }
//             else if(!strcmp(diretiva, "ALIGN")) {
//                 fgets(arg1, 100, arq);
//                 if(!diretivaAlign(arg1, diretivas, posicaoAtual))
//                     return 0;
//             }
//             else if(!strcmp(diretiva, "WFILL")){
//                 fgets(arg1, 100, arq);
//                 fgets(arg2, 100, arq);
//                 if(!diretivaWfill(arg1, arg2, diretivas, posicaoAtual))
//                     return 0;
//             }
//         }

//     }
//     return 1;
// }


// int diretivaSet(char *arg1, char *arg2, Diretiva diretivas[]){
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



// int diretivaWord(char *arg, Diretiva diretivas[], Posicao posicaoAtual){
//     int i, achou = 0, n;
//      se o primeiro digito nao for um numero,
//     o argumento passado eh uma constante
//     que necessita ter seu valor inserido no vetor
//     de diretivas 
//     if(mnemonicos(arg))
//         return 0;

//     if(isdigit(arg[0])){
//         for(i = 0; i < 1000 && !achou; i++)
//             if(!strcmp(arg, diretivas[i].nome)){
//                 n = diretivas[i].valor;
//                 achou = 1;
//                 break;
//             }
//         /* se nao achar */
//         if(!achou)
//             return 0;
//     }
//     else
//         sscanf(arg, "%d", &n);
//     /* printa no arquivo: posicaoAtual n
//      Exemplo posicaoAtual = 102 e n =3
//      102 00 00 00 03*/
//      return 1;
// }

// int diretivaAlign(char *arg, Diretiva diretivas[], Posicao posicaoAtual){
//     int n;
//     /* se for um nome, procura no vetor de diretivas */
//     if(mnemonicos(arg))
//         return 0;

//     sscanf(arg, "%d", &n);
//     if(n >= 0){
//         /* pula n linhas e alinha a esquerda, escrevendo '0' no fim da linha atual */
//         /* printa 0 na parte ainda nao preechida da linha */
//         posicaoAtual.linha += n;
//         posicaoAtual.direita = 0;
//     }
//     else
//         return 0;
//     return 1;
// }


// int diretivaWfill(char *arg1, char *arg2, Diretiva diretivas[], Posicao posicaoAtual){
// int i, achou = 0, n1, n2;
//     /* argumento1 eh necessariamente um numero */
//     /* argumento2 pode ser um nome, e se for procura no vetor */
//     /*if(mnemonicos(arg1) || mnemonicos(arg2))
//         return 0;*/

//     if(isdigit(arg2[0])){
//         for(i = 0; i < 1000 && !achou; i++)
//             if(!strcmp(arg2, diretivas[i].nome)){
//                 sscanf(arg2, "%d", &n2);
//                 achou = 1;
//                 break;
//             }
//         if(!achou)
//             return 0;
//     }
//     else
//         sscanf(arg2, "%d", &n2);

//     sscanf(arg1, "%d", &n1);
//     for(i = 0; i < n1; i++){
//         /* printa no arquivo hex a linha(posicaoAtual) e o valor de n2 */
//         posicaoAtual.linha++;
//     }
//     return 1;
// }



// int mnemonicos(char *token){
//     if(!(strcmp(token, "LDMQ")) || !(strcmp(token, "LDMQM")) || !(strcmp(token, "STR"))
//        || !(strcmp(token, "LOAD")) || !(strcmp(token, "LDN")) || !(strcmp(token, "LDABS"))
//        || !(strcmp(token, "JMP")) || !(strcmp(token, "JGEZ")) || !(strcmp(token, "ADD"))
//        || !(strcmp(token, "ADDABS")) || !(strcmp(token, "SUB")) || !(strcmp(token, "SUBABS"))
//        || !(strcmp(token, "MUL")) || !(strcmp(token, "DIV")) || !(strcmp(token, "LSH"))
//        || !(strcmp(token, "RSH")) || !(strcmp(token, "STM")))
//             return 0;

//     return 1;

// }

