#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "diretiva.h"

int diretivaValida(char *token)
{
	if(token[0] == '.')
	{
		token += 1;
		if ( strncmp(token,"ORG", strlen("ORG")) == 0 || strncmp(token,"WORD", strlen("WORD")) == 0 || strncmp(token,"SET", strlen("SET")) == 0 || strncmp(token,"FILL", strlen("FILL")) == 0 || strncmp(token,"ALIGN", strlen("ALIGN")) == 0)
			return 1;
	}
	return 0;
}

// int trataDiretivas(Posicao posicaoAtual, Diretiva diretivas[], char **tokens){
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
//      // caso os argumentos nao sejam instrucoes,
//      // sao considerados validos
//      // obs: vou refazer a funcao para verificar se
//      // o argumento passado eh um mnemonico 

//     diretivas[i].nome = arg1;
//     sscanf(arg2, "%d", &n);
//     diretivas[i].valor = n;


//     return 1; /* caso de certo */
// }

int diretivaOrg(char *arg, Diretiva diretivas[], Posicao posicaoAtual){
    int n;

    if(mnemonicos(arg))
        return 0;
    /* trasnforma o arg em um numero */
    sscanf(arg, "%d", &n);
    if(n > 0)
        /* faz o set da posicao, onde deve comecar a escrever */
        posicaoAtual.linha += n;
    else
        return 0;
    return 1;
}

// int diretivaWord(char *arg, Diretiva diretivas[], Posicao posicaoAtual){
//     int i, achou = 0, n;
//     /* se o primeiro digito nao for um numero,
//     o argumento passado eh uma constante
//     que necessita ter seu valor inserido no vetor
//     de diretivas */
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
//         // pula n linhas e alinha a esquerda, escrevendo '0' no fim da linha atual 
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

