all: montador.o retornaTokens.o rotulo.o tradutor.o diretiva.o
	gcc montador.o retornaTokens.o rotulo.o tradutor.o diretiva.o -o montador

retornaTokens.o: retornaTokens.c
	gcc -c -Wall retornaTokens.c 

montador.o: montador.c
	gcc -c -Wall montador.c 

rotulo.o: rotulo.c
	gcc -c -Wall rotulo.c 

tradutor.o: tradutor.c
	gcc -c -Wall tradutor.c

diretiva.o: diretiva.c
	gcc -c -Wall diretiva.c

clean:
	rm *.o */*.hex montador