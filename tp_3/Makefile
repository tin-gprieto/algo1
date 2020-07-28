CC= gcc
CFLAGS= -std=c99 -Wall -Wconversion -Werror -g
CLIBRARY= utiles.o defendiendo_torres.c argumentos.c
CLIBRARYP= utiles.o defendiendo_torres.c 

build: juego.c
		$(CC) juego.c $(CLIBRARY) -o defendiendo $(CFLAGS)
test: pruebas.c
		$(CC) pruebas.c $(CLIBRARYP) -o prueba $(CFLAGS)
