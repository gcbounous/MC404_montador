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


