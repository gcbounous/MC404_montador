all: montador.o retornaTokens.o
	gcc montador.o retornaTokens.o -o montador

retornaTokens.o: retornaTokens.c
	gcc -c -Wall retornaTokens.c 

montador.o: montador.c
	gcc -c -Wall montador.c 

clean:
	rm *.o *.out montador
