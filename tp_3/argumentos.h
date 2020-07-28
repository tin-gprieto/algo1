#ifndef __ARGUMENTOS_H__
#define __ARGUMENTOS_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*FUNCIONES QUE UTILCE EN EL MAIN DE DEFENFIENDO.case */
/*COMENTARIOS DE ESAS FUNCINONES*/
/*
*
*
*
int estado_programa(int tope_arg, char* arg[]);
*
*
*
bool estan_los_archivos(int programa, int tope_arg, char* arg[]);
*
*
*
*/
void crear_caminos(configuracion_t configuracion);
/*
*
*
*
*/
void crear_confirguracion (configuracion_t configuracion, int tope_arg, char* arg[]);
/*
*
*
*
*/
void poner_repeticion(int tope_arg, char* arg[]);
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

#endif /* __ARGUMENTOS_H__ */
