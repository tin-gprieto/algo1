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

/*
* NO TERMINADA
*Analisis: Calcula los puntos y actualiza el archivo del ranking segun la configuracion
*/
void actualizar_ranking(juego_t juego, int* puntos, char usuario[], char config[]);
/*
*NO TERMINADA
*Analisis: Abre el archivo de caminos y carga su informacion al nivel
*/
void configurar_camino_archivo(int nvl, nivel_t* nivel, configuracion_t configuracion);
/*
*Analisis: Evalua si estan los archivos obligatorios segun el modo del programa
*Pre: Modo del progrma calculado
*Post: Verdadero si esta el archivo, falso si no hay nada
*/
bool estan_los_archivos(int programa, char argumento[]);
/*
*Analisis: Devuelve un valor de que tipo de configuracion se usa para jugar y si se graba, junto con el nombre de sus archivos
*Pre: El estado del programa debe ser "jugar"
*Post: Modo (STANDARD_GRABANDO, STANDARD_SIN_GRABAR, CUSTOM_GRABANDO, CUSTOM_SIN_GRABAR)y nombres de archivo correspondientes a la configuracion y la grabacion
*/
int modo_juego(char* argv[], char config[], char grabacion[]);
/*
*Analisis: Devuelve un valor del estado del progrma segun el primer argumento por comando
*Pre: -
*Post: Estado (JUGAR, CREAR_CONFIGURACION, CREAR_CAMINOS, REPETICION, RANKING, ERROR(si no se pasa ningun comando))
*/
int estado_programa(char argumento[]);
/*
*Analisis: Segun el archivo pasado por el usuario guarda el estado del juego
*Pre: El modo de juego debe ser GRABANDO y haber pasado el archivo de grabacion correctamente
*Post: Advertencia si no se abre el archivo o archivo de texto actualizado con el ultimo turno
*/
void guardar_partida(juego_t juego, char grabacion[]);
/*
*Analisis: Segun el modo del juego carga la informacion de un archivo de txt a la configuracion
*Pre: Modo de juego calculado con el nombre del archivo de configuracion
*Post: Configuracion cargada
*/
void cargar_confirguracion(configuracion_t* configuracion, int modo, char config[]);
/*
*Analisis: Segun los comandos introducidos por el usuario devuelve el modo ejecutado (exceptuando jugar) o rechazado(si no cumple con los archivos)
*Pre: Estado del programa calculado
*Post: Modos de program ejecutado según los comandos
*/
void comandos(int argc, char* argv[]);

#endif /* __ARGUMENTOS_H__ */
