/**
 * @Date:   2020-08-10T17:17:20-03:00
 * @Last modified time: 2020-08-11T00:42:07-03:00
 */



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
#define HELP 5
#define ERROR -1
#define STANDARD_SIN_GRABAR 0
#define STANDARD_GRABANDO 1
#define CUSTOM_SIN_GRABAR 2
#define CUSTOM_GRABANDO 3
#define NIVEL_1 0
#define NIVEL_2 1
#define NIVEL_3 2
#define NIVEL_4 3
#define TORRE_1 0
#define TORRE_2 1
#define MAX_LETRAS_DEFENSOR 15
#define MAX_NIVELES 4
#define MAX_TORRES 2
#define MAX_ARGUMENTO 20
#define MAX_USUARIO 20
#define ARG_HELP "--help"

typedef struct ranking{
	char usuario[MAX_USUARIO];
	int puntos;
	int orcos_muertos;
} ranking_t;
/*
*Analisis: Calcula el puntaje segun la configuracion y la cantidad de orcos muertos
*Pre: Estar en modo_programa JUGAR(con juego inicializado) y configuracion inicializada
*Post: puntos y orcos_muertos del ranking actualizados
*/
void calcular_puntaje(juego_t juego, configuracion_t config, ranking_t* ranking);
/*
*Analisis: actualiza el archivo del ranking segun la configuracion y el ranking
*Pre: estado_juego GANADO o PERDIDO, ranking con puntos calculados y usuario ya pedido
*Post: archivo del ranking (segúin la config) con el nuevo ranking de usuario ya agregado ordenadamente
*/
void actualizar_ranking(juego_t juego, ranking_t ranking, char config[]);
/*
*Analisis: Segun el archivo pasado por el usuario guarda el estado del juego
*Pre: El modo de juego debe ser GRABANDO y haber pasado el archivo de grabacion correctamente
*Post: Advertencia si no se abre el archivo o archivo de texto actualizado con el ultimo turno
*/
void guardar_partida(juego_t juego, char grabacion[]);
/*
*Analisis: Abre el archivo de caminos y carga su informacion al nivel
*Pre: Configuracion ya cargada y nvl == NIVEL_1, NIVEL_2, NIVEL_3 o NIVEL_4
*Post: Camino/s del nivel configurado a partir del archivo de caminos
*/
void configurar_camino_archivo(int nvl, nivel_t* nivel, configuracion_t configuracion);
/*
*Analisis: Segun el modo del juego carga la informacion de un archivo de txt a la configuracion
*Pre: Modo de juego calculado con el nombre del archivo de configuracion
*Post: Configuracion cargada
*/
void cargar_confirguracion(configuracion_t* configuracion, int modo, char config[]);
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
*Analisis: Segun los comandos introducidos por el usuario devuelve el modo ejecutado (exceptuando jugar) o rechazado(si no cumple con los archivos)
*Pre: Estado del programa calculado
*Post: Modos de program ejecutado según los comandos
*/
void comandos(int argc, char* argv[]);

#endif /* __ARGUMENTOS_H__ */
