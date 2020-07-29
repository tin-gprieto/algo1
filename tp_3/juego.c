#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "defendiendo_torres.h"
#include "utiles.h"
#include "argumentos.h"

const int TOPE_CAMPO_1=15;
const int TOPE_CAMPO_2=20;
const int NIVEL_1=0;
const int NIVEL_2=1;
const int NIVEL_3=2;
const int NIVEL_4=3;
const int TORRE_1=0;
const int TORRE_2=1;
const int GANADO=1;
const int JUGANDO=0;
const int PERDIDO=-1;
const char ENANO='G';
const char ELFO='L';
const char SI ='S';
const char NO ='N';

const int ORCOS_NVL_1=100;
const int ORCOS_NVL_2=200;
const int ORCOS_NVL_3=300;
const int ORCOS_NVL_4=500;

const int SALUD_TORRES = 600;
const int UNIDADES_EXTRA = 10;
const int DEFENSORES_NVL_1=5;
const int DEFENSORES_NVL_2=5;
const int DEFENSORES_NVL_3=3;
const int DEFENSORES_NVL_4=4;
const int COSTO_BONIFICACION=50;
const int EXTRA_1=25;
const int EXTRA_2=50;

#define MAX_LETRAS_DEFENSOR 15
#define MAX_NIVELES 4
#define MAX_TORRES 2

typedef struct campo{
	int tope;
	coordenada_t entrada_1;
	coordenada_t torre_1;
	coordenada_t entrada_2;
	coordenada_t torre_2;
	int bonificacion;
	int cantidad_elfos;
	int cantidad_enanos;
	int costo_G_extra[MAX_TORRES];
	int costo_L_extra[MAX_TORRES];

} campo_t;

typedef struct estructura{
	nivel_t nivel;
	campo_t campo;
} estructura_t;

/*
*Muestra por pantalla el menú de inicio
*/
void mostrar_inicio(){
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n");
  printf("     ________                                                ________ \n");
	printf("    (o.____.o)____                                      ____(o.____.o)\n");
	printf("      |    | /,--.                                     (,--.  |    |\n");
  printf("      |    |((  -` ___                               ___`   ))|    |\n");
	printf("      |    | || ,'',  `.                           .'  .``.// |    |\n");
	printf("      |    |  // (___,'.     _________________    .'.___)     |    |\n");
	printf("      |    | ;;))  ____) .   |               |  . (____  ((   |    |\n");
	printf("      |.__ | ||/ .'.--./     | THE _  _  _   |   /,--.`.   ;: | __,|\n");
	printf("      |`-,`;.| :/ /,'  `)-'  | |  | ||_)| |  | `-('  `.   : |.;',-'|\n");
	printf("      |   `..  ' /  __.'     | |__|_|| ||_/  |     .__/   `  ,.'   |\n");
	printf("      |    |,   /,           |               |          ,   /,|    |\n");
	printf("      |    ||: : )           | OF THE        |          ( : :||    |\n");
	printf("      |    |:; |/  .         |  _      _  _  |            | :;|    |\n");
	printf("      |.__ |/  :  ,/-        | |_)||/||_ (_  |            ;   | __,|\n");
	printf("      |`-.``:   `'/-.        | | ||| ||_| _) |            |  ;'',-'|\n");
	printf("      |   `.|   ,' `'        |_______________|            |  ,.'   |\n");
	printf("      |    ||  :              THE TWO TOWERS              :  ||    |\n");
	printf("      |    ||  |                                          |  ||    |\n");
	printf("      |    |'  |                                          |  `|    |\n");
	printf("      ;____:   `._                                     _, '   ;____:\n");
	printf("     {______}     |___________________________________|      {______}\n");
	printf("     |______|________________________________________________|______|\n\n");
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n");
	detener_el_tiempo(3);
}
/*
*Muestra por pantalla el nivel ganado
*/
void mostar_nvl_ganado(juego_t juego){
	system("clear");
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n\n\n\n\n\n\n");
	printf("                        -------------------\n");
	printf("                        NIVEL %i COMPLETADO\n", (juego.nivel_actual+1));
	printf("                        -------------------\n\n\n\n\n\n\n\n\n");
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n");
	detener_el_tiempo(2);
	system("clear");
}
/*
*Mustra por pantalla el juego perdido
*/
void mostrar_juego_perdido(){
	system("clear");
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n\n\n\n\n\n\n");
	printf("                        -------------------\n");
	printf("                             GAME OVER\n");
	printf("                        -------------------\n\n\n\n\n\n\n\n\n");
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n");
	detener_el_tiempo(2);
	system("clear");
}
/*
*Mustra por pantalla el juego ganado
*/
void mostrar_juego_ganado(){
	system("clear");
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n\n\n\n\n\n\n");
	printf("                        -------------------\n");
	printf("                        HAS GANADO EL JUEGO\n");
	printf("                        -------------------\n\n\n\n\n\n\n\n\n");
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n");
	detener_el_tiempo(2);
	system("clear");
}
/*
*Muestra el juego durante un tiempo determinado y luego limpia el sistema
*/
void mostrar_campo(juego_t juego, float velocidad){
	mostrar_juego(juego);
	detener_el_tiempo(velocidad);
	system("clear");
}
/*
*Análsis: Asigna la posicion de la entrada y la torre para el nivel 1
*Pre: -
*Post: Entrada y torre (principio y fin del camino) asignados
*/
void asignar_entrada_torre_nvl_1 (campo_t* campo){
	campo->entrada_1.fil = rand()%(campo->tope) + 0;
	campo->entrada_1.col = (campo->tope) - 1;
	campo->torre_1.fil = rand()%(campo->tope) + 0;
	campo->torre_1.col = 0;
}
/*
*Análsis: Asigna la posicion de la entrada y la torre para el nivel 2
*Pre: -
*Post: Entrada y torre (principio y fin del camino) asignados
*/
void asignar_entrada_torre_nvl_2 (campo_t* campo){
	campo->entrada_2.fil = rand()%(campo->tope) + 0;
	campo->entrada_2.col = 0;
	campo->torre_2.fil = rand()%(campo->tope) + 0;
	campo->torre_2.col = (campo->tope) - 1;
}
/*
*Análsis: Asigna la posicion de la entrada y la torre para el nivel 3
*Pre: -
*Post: Entrada y torre (principio y fin del camino) asignados
*/
void asignar_entradas_torres_nvl_3 (campo_t* campo){
	campo->entrada_1.fil = 0;
	campo->entrada_1.col = rand()%9 + 0;
	campo->torre_1.fil = (campo->tope) - 1;
	campo->torre_1.col = rand()%9 + 0;
	campo->entrada_2.fil = 0;
	campo->entrada_2.col = rand()%9 + 10;
	campo->torre_2.fil = (campo->tope) - 1;
	campo->torre_2.col = rand()%9 + 10;
}
/*
*Análsis: Asigna la posicion de la entrada y la torre para el nivel 4
*Pre: -
*Post: Entrada y torre (principio y fin del camino) asignados
*/
void asignar_entradas_torres_nvl_4 (campo_t* campo){
	campo->entrada_1.fil = (campo->tope) - 1;
	campo->entrada_1.col = rand()%9 + 0;
	campo->torre_1.fil = 0;
	campo->torre_1.col = rand()%9 + 0;
	campo->entrada_2.fil = (campo->tope) - 1;
	campo->entrada_2.col = rand()%9 + 10;
	campo->torre_2.fil = 0;
	campo->torre_2.col = rand()%9 + 10;
}
/*
*Análsis: Evalua si la posicion del defesor está por fuera del campo
*Pre: -
*Post: Verdadero si la posicion no exede los límites del campo
*/
bool posicion_valida(coordenada_t posicion, int coordenada_max){
	return (posicion.fil < coordenada_max) && (posicion.col < coordenada_max);
}
/*
*Análsis: Pregunta al usuario la posicion del defensor y lo agrega si su posicion es válida (No excede las dimensiones del campo ni coincide con otro defensor)
*Pre: Tipo válido ('G' o 'L')
*Post: Defensor agregado (hasta que se introduzcan bien los datos)
*/
void pedir_defesores(juego_t* juego, char defensor[MAX_LETRAS_DEFENSOR], char tipo, int cantidad_min, int coordenada_max){

	coordenada_t posicion;

	for (int i = 0; i < cantidad_min; ++i){
		printf("%sS para añadir: %i \n", defensor, cantidad_min - i );
		printf("Añadir %s ( %c ) n° %i: \n", defensor, tipo, i + 1);
		printf("Fila:");
		scanf("%i", &posicion.fil);
		printf("Columna:");
		scanf("%i", &posicion.col);
			while (agregar_defensor(&juego->nivel, posicion, tipo) != 0 || !posicion_valida(posicion, coordenada_max)){
				printf("POSICIÓN NO VÁLIDA, añadir nuevamente\n");
				printf("%sS para añadir: %i \n", defensor, cantidad_min - i );
				printf("Añadir %s ( %c ) n° %i: \n", defensor, tipo, i + 1);
				printf("Fila:");
				scanf("%i", &posicion.fil);
				printf("Columna:");
				scanf("%i", &posicion.col);
			}
		system("clear");
		mostrar_juego(*juego);
		}
}
/*
*Análsis: Según los defensores del nivel los asigna en el campo
*Pre: Nivel inicializado
*Post: Defensor agregado
*/
void asignar_defensores(juego_t* juego, campo_t campo){
	char defensor [MAX_LETRAS_DEFENSOR];

	if (campo.cantidad_enanos != 0){
		strcpy(defensor, "ENANO");
	    pedir_defesores(juego, defensor, ENANO, campo.cantidad_enanos, campo.tope);
	}
	if (campo.cantidad_elfos != 0){
		strcpy(defensor, "ELFO");
	    pedir_defesores(juego, defensor, ELFO, campo.cantidad_elfos, campo.tope);
	}
}
/*
*Análsis: Determina si corresponde una bonificación de defensor extra
*Pre: Nivel inicializado
*Post: Devuelve verdadero si debe tener un defensor extra.
*/
bool hay_bonificacion(juego_t juego, campo_t campo){
	if ((juego.nivel.tope_enemigos!=juego.nivel.max_enemigos_nivel)&&(((juego.nivel.tope_enemigos)%(campo.bonificacion)) == 0)){
		return true;
	 }else{
		return false;
	}
}
/*
*Análsis: Agrega un defensor con pedir_defensores y deja al juego en su estado correspondiente
*Pre: Tipo debe ser válido ('L' o 'G'), tope correspondiente al campo del nivel
*Post: Defensor agregado y el juego con sus valores cambiados
*/
void agregar_def_extra(juego_t* juego, campo_t campo, char tipo, char defensor[MAX_LETRAS_DEFENSOR], int tope){
		pedir_defesores(juego, defensor, tipo, 1, tope);
		if (tipo == ENANO){
			if(juego->nivel_actual==NIVEL_1){
				juego->torres.resistencia_torre_1 -= campo.costo_G_extra[TORRE_1];
				juego->torres.enanos_extra --;
			}else if(juego->nivel_actual==NIVEL_3 || juego->nivel_actual==NIVEL_4 ){
				juego->torres.resistencia_torre_1 -= campo.costo_G_extra[TORRE_1];
				juego->torres.resistencia_torre_2 -= campo.costo_G_extra[TORRE_2];
				juego->torres.enanos_extra --;
			}
		}else if (tipo == ELFO){
			if(juego->nivel_actual==NIVEL_2){
				juego->torres.resistencia_torre_2 -= campo.costo_L_extra[TORRE_2];
				juego->torres.elfos_extra --;
			}else if(juego->nivel_actual==NIVEL_3 || juego->nivel_actual==NIVEL_4 ){
				juego->torres.resistencia_torre_1 -= campo.costo_L_extra[TORRE_1];
				juego->torres.resistencia_torre_2 -= campo.costo_L_extra[TORRE_2];
				juego->torres.elfos_extra --;
			}
		}
}
/*
*Análsis: Pregunta el tipo de defensor que el usuario quiera agregar
*Pre: Debe querer agregar un defensor y el nivel_actual debe ser 3 o 4
*Post: Caracter del tipo por referiencia
*/
void preguntar_tipo (char* tipo){
	char eleccion;
	printf("Introduzca el tipo ('%c' para ELFO o '%c' para ENANO):", ELFO, ENANO);
	scanf(" %c", &eleccion);
	*tipo=eleccion;
}
/*
*Análsis
*Pre:
*Post:
*/
void preguntar_por_def_extra()
/*
*Análsis: Pregunta por un defensor extra según el nivel que corresponda (tipo y periodicidad)
*Pre: el nivel_actual del juego debe ser 1,2,3 o 4 y deben estar inicializados
*Post: Interacciona con el usuario y agrega o no un defensor según corresponda
*/
void bonificar_con_defesor(juego_t* juego, campo_t campo){
	char desicion;
	char defensor[MAX_LETRAS_DEFENSOR];
	if ((juego->nivel_actual==NIVEL_1)&&(juego->torres.enanos_extra > 0)){
		strcpy(defensor, "ENANO");
		printf("¿Desea agregar un %s extra? (costo: 50 salud de torre)(%c/%c):", defensor, SI, NO);
		scanf(" %c", &desicion);
		if (desicion==SI){
			agregar_def_extra(juego, campo, ENANO, defensor, campo.tope);
			system("clear");
		}
	}else if ((juego->nivel_actual==NIVEL_2) && (juego->torres.elfos_extra > 0)){
		strcpy(defensor, "ELFO");
		printf("¿Desea agregar un %s extra? (costo: 50 salud de torre)(%c/%c):", defensor, SI, NO);
		scanf(" %c", &desicion);
		if (desicion==SI){
			agregar_def_extra(juego, campo, ELFO, defensor, campo.tope);
			system("clear");
		}
	}else if ((juego->nivel_actual==NIVEL_3) || (juego->nivel_actual==NIVEL_4)){
		if ((juego->torres.enanos_extra > 0) || (juego->torres.elfos_extra > 0)){
			char tipo;
			printf("¿Desea agregar un defensor extra? (costo: 50 salud de torre)(%c/%c):", SI, NO);
			scanf(" %c", &desicion);
			if (desicion==SI){
				bool agrego_correctamente=false;
				while (!agrego_correctamente){
					preguntar_tipo(&tipo);
					if ((tipo==ENANO)&&(juego->torres.enanos_extra > 0)){
						strcpy(defensor, "ENANO");
						agregar_def_extra(juego, campo, ENANO, defensor, campo.tope);
						agrego_correctamente=true;
					}else if ((tipo==ELFO)&&(juego->torres.elfos_extra > 0)){
						strcpy(defensor, "ELFO");
						agregar_def_extra(juego, campo, ELFO, defensor, campo.tope);
						agrego_correctamente=true;
					}else{
						printf(" EL TIPO DE DEFENSOR NO ES CORRECTO, intente nuevamente...\n");
					}
				}
			}
		}else{
			printf(" NO TIENES DEFENSORES EXTRA\n");
		}
	}
}
/*
*
*
*
*/
void configurar_camino_aleatorio(int nvl, nivel_t* nivel, campo_t* campo){
	nivel_t nivel_aux;
	if (nvl==NIVEL_1){
		asignar_entrada_torre_nvl_1 (campo);
		obtener_camino(nivel_aux.camino_1, &nivel_aux.tope_camino_1, campo->entrada_1, campo->torre_1);
		*nivel=nivel_aux;
	}else if (nvl==NIVEL_2){
		asignar_entrada_torre_nvl_2 (campo);
		obtener_camino(nivel_aux.camino_2, &nivel_aux.tope_camino_2, campo->entrada_2, campo->torre_2);
		*nivel=nivel_aux;
	}else if (nvl==NIVEL_3){
		asignar_entradas_torres_nvl_3 (campo);
		obtener_camino(nivel_aux.camino_1, &nivel_aux.tope_camino_1, campo->entrada_1, campo->torre_1);
		obtener_camino(nivel_aux.camino_2, &nivel_aux.tope_camino_2, campo->entrada_2, campo->torre_2);
		*nivel=nivel_aux;
	}else if (nvl==NIVEL_4){
		asignar_entradas_torres_nvl_4 (campo);
		obtener_camino(nivel_aux.camino_1, &nivel_aux.tope_camino_1, campo->entrada_1, campo->torre_1);
		obtener_camino(nivel_aux.camino_2, &nivel_aux.tope_camino_2, campo->entrada_2, campo->torre_2);
		*nivel=nivel_aux;
	}

}
/*
*
*
*
*/
void configurar_campo(int nivel, campo_t* campo, configuracion_t config){
	campo->cantidad_enanos = config.cantidad_enanos[nivel];
	campo->cantidad_elfos = config.cantidad_elfos[nivel];
	campo->costo_G_extra[TORRE_1] = config.costo_G_extra[TORRE_1];
	campo->costo_G_extra[TORRE_2] = config.costo_G_extra[TORRE_2];
	campo->costo_L_extra[TORRE_1] = config.costo_G_extra[TORRE_1];
	campo->costo_L_extra[TORRE_2] = config.costo_G_extra[TORRE_2];
	if (nivel==NIVEL_1){
		campo->tope = TOPE_CAMPO_1;
		campo->bonificacion=EXTRA_1;
	}else if (nivel==NIVEL_2){
		campo->tope = TOPE_CAMPO_1;
		campo->bonificacion=EXTRA_1;
	}else if (nivel==NIVEL_3){
		campo->tope = TOPE_CAMPO_2;
		campo->bonificacion=EXTRA_2;
	}else if (nivel==NIVEL_4){
		campo->tope = TOPE_CAMPO_2;
		campo->bonificacion=EXTRA_2;
	}
}
/*
*
*
*
*/
void inicializar_niveles(estructura_t estructura[MAX_NIVELES], configuracion_t config){
	for (int nivel=NIVEL_1; nivel<MAX_NIVELES; nivel++){
		estructura[nivel].nivel.tope_enemigos=0;
		estructura[nivel].nivel.tope_defensores=0;
		campo_t campo_aux;
		nivel_t nivel_aux;
		configurar_campo(nivel, &campo_aux, config);
		configurar_camino_aleatorio(nivel ,&nivel_aux, &campo_aux);
		estructura[nivel].nivel=nivel_aux;
		estructura[nivel].campo=campo_aux;
		if (nivel==NIVEL_1){
			estructura[nivel].nivel.max_enemigos_nivel= ORCOS_NVL_1;
		}else if (nivel==NIVEL_2){
			estructura[nivel].nivel.max_enemigos_nivel= ORCOS_NVL_2;
		}else if (nivel==NIVEL_3){
			estructura[nivel].nivel.max_enemigos_nivel= ORCOS_NVL_3;
		}else if (nivel==NIVEL_4){
			estructura[nivel].nivel.max_enemigos_nivel= ORCOS_NVL_4;
		}
	}
}
/*
*
*
*
*/
void cargar_nivel(juego_t* juego, estructura_t estructura){
	juego->nivel=estructura.nivel;
	mostrar_juego(*juego);
	asignar_defensores(juego, estructura.campo);
}
/*
*
*
*
void jugar_turno_completo(juego_t* juego, estructura_t estructura[MAX_NIVELES], configuracion_t config){

}
*
*
*
*/
void configurar_por_defecto(configuracion_t* configuracion){
	configuracion->animo_legolas='B';
	configuracion->animo_gimli='B';
	configuracion->viento=25;
	configuracion->humedad=25;
	configuracion->torres.resistencia_torre_1=SALUD_TORRES;
	configuracion->torres.resistencia_torre_2=SALUD_TORRES;
	configuracion->torres.enanos_extra=10;
	configuracion->torres.elfos_extra=10;
	configuracion->costo_G_extra[TORRE_1]=COSTO_BONIFICACION;
	configuracion->costo_G_extra[TORRE_2]=COSTO_BONIFICACION;
	configuracion->costo_L_extra[TORRE_1]=COSTO_BONIFICACION;
	configuracion->costo_L_extra[TORRE_2]=COSTO_BONIFICACION;
	configuracion->cantidad_enanos[NIVEL_1]=DEFENSORES_NVL_1;
	configuracion->cantidad_enanos[NIVEL_2]=0;
	configuracion->cantidad_enanos[NIVEL_3]=DEFENSORES_NVL_3;
	configuracion->cantidad_enanos[NIVEL_4]=DEFENSORES_NVL_4;
	configuracion->cantidad_elfos[NIVEL_1]=0;
	configuracion->cantidad_elfos[NIVEL_2]=DEFENSORES_NVL_2;
	configuracion->cantidad_elfos[NIVEL_3]=DEFENSORES_NVL_3;
	configuracion->cantidad_elfos[NIVEL_4]=DEFENSORES_NVL_4;
	configuracion->es_aleatoreo[NIVEL_1]=true;
	configuracion->es_aleatoreo[NIVEL_2]=true;
	configuracion->es_aleatoreo[NIVEL_3]=true;
	configuracion->es_aleatoreo[NIVEL_4]=true;
	configuracion->velocidad=0.5;
}
int main (int argc, char* argv[]){
	srand((unsigned)time(NULL));

	juego_t juego;
	estructura_t estructura[MAX_NIVELES];
	configuracion_t configuracion;

	configurar_por_defecto(&configuracion);
	inicializar_juego(&juego, configuracion);
	inicializar_niveles(estructura, configuracion);

	mostrar_inicio();
	system("clear");

	cargar_nivel(&juego, estructura[juego.nivel_actual]);

	while(estado_juego(juego) == JUGANDO){
		if (estado_nivel(juego.nivel) == GANADO){
			mostar_nvl_ganado(juego);
			juego.nivel_actual++;
			cargar_nivel(&juego, estructura[juego.nivel_actual]);
		}
		jugar_turno(&juego);
		mostrar_campo(juego, configuracion.velocidad);
		if (hay_bonificacion(juego, estructura[juego.nivel_actual].campo)){
			mostrar_juego(juego);
			bonificar_con_defesor(&juego, estructura[juego.nivel_actual].campo);
			mostrar_campo(juego, configuracion.velocidad);
		}
	}
	if (estado_juego(juego) == GANADO)
		mostrar_juego_ganado();
	else if (estado_juego(juego) == PERDIDO)
		mostrar_juego_perdido();

	return 0;
}
