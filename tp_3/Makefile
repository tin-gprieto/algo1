CC= gcc
CFLAGS= -std=c99 -Wall -Wconversion -Werror -g
CERROR= -std=c99 -g
CLIBRARY= utiles.o defendiendo_torres.c argumentos.c

build: juego.c
		$(CC) juego.c $(CLIBRARY) -o defendiendo $(CFLAGS)
error: juego.c
		$(CC) juego.c $(CLIBRARY) -o defendiendo $(CERROR)
