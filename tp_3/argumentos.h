#ifndef __ARGUMENTOS_H__
#define __ARGUMENTOS_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define JUGAR 0
#define CREAR_CONFIGURACION 1
#define CREAR_CAMINOS 2
#define REPETICION 3
#define RANKING 4
#define ERROR -1

/*FUNCIONES QUE UTILCE EN EL MAIN DE DEFENFIENDO.case */
/*COMENTARIOS DE ESAS FUNCINONES*/
/*
*
*
*
*/
int estado_programa(char argumento[]);
/*
*
*
*
*/
bool estan_los_archivos(int programa, char argumento[]);
/*
*
*
*
*/
void actualizar_ranking(juego_t juego);
/*
*
*
*
*/
void guardar_partida(juego_t juego, int tope_arg, char* arg[]);
/*
*
*
*
*/
void cargar_confirguracion(configuracion_t* configuracion, char arg[]);
/*
*
*
*
*/
void comandos(int argc, char* argv[]);
#endif /* __ARGUMENTOS_H__ */
