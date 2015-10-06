all: montador.o retornaTokens.o rotulo.o
	gcc montador.o retornaTokens.o rotulo.o -o montador

retornaTokens.o: retornaTokens.c
	gcc -c -Wall retornaTokens.c 

montador.o: montador.c
	gcc -c -Wall montador.c 

rotulo.o: rotulo.c
	gcc -c -Wall rotulo.c 

clean:
	rm *.o *.out montador
