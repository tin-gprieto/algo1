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

const char SEPARADO[MAX_TORRES]="=";

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
void mostrar_inicio(char configuracion[], char grabacion[], configuracion_t config){
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
	printf("GRABACION: %s\n", grabacion);
	printf("CONFIGURACION: %s\n", configuracion);
	printf("-TORRES SALUD: %i %i \n", config.torres.resistencia_torre_1, config.torres.resistencia_torre_2 );
	printf("-ENANOS_INICIO: %i %i %i %i\n", config.cantidad_enanos[0], config.cantidad_enanos[1], config.cantidad_enanos[2], config.cantidad_enanos[3]);
	printf("-ELFOS_INICIO: %i %i %i %i\n", config.cantidad_elfos[0], config.cantidad_elfos[1], config.cantidad_elfos[2], config.cantidad_elfos[3]);
	printf("-ENANOS_EXTRA: %i %i %i\n", config.torres.enanos_extra, config.costo_G_extra[0], config.costo_G_extra[1]);
	printf("-ELFOS_EXTRA: %i %i %i \n", config.torres.elfos_extra, config.costo_L_extra[0], config.costo_L_extra[1]);
	printf("-ENANOS_ANIMO: %i %i\n", config.fallo_gimli, config.critico_gimli);
	printf("-ELFOS_ANIMO: %i %i\n", config.fallo_legolas, config.critico_legolas );
	printf("-VELOCIDAD: %f \n", config.velocidad);
	if(config.hay_caminos){
			printf("-RUTA CAMINO: %s \n", config.ruta_camino);
	}else{
		printf("CAMINOS ALEATORIOS\n");
	}
	detener_el_tiempo(2);
}
/*
*Muestra por pantalla el nivel ganado
*/
void mostrar_nvl_ganado(juego_t juego){
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
void mostrar_juego_perdido(ranking_t ranking){
	system("clear");
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n\n\n\n\n\n\n");
	printf("                        -------------------\n");
	printf("                             GAME OVER\n");
	printf("                        -------------------\n");
	printf("                         %s      %i PTS\n\n\n\n\n\n\n\n", ranking.usuario, ranking.puntos);
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n");
	detener_el_tiempo(3);
	system("clear");
}
/*
*Mustra por pantalla el juego ganado
*/
void mostrar_juego_ganado(ranking_t ranking){
	system("clear");
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n\n\n\n\n\n\n");
	printf("                        -------------------\n");
	printf("                        HAS GANADO EL JUEGO\n");
	printf("                        -------------------\n");
	printf("                         %s      %i PTS\n\n\n\n\n\n\n\n", ranking.usuario, ranking.puntos);
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n");
	detener_el_tiempo(2);
	system("clear");
}
/*
*Muestra el juego durante un tiempo determinado y luego limpia el sistema
*/
void mostrar_campo(juego_t juego, float velocidad, ranking_t ranking){
	printf("USUARIO: %s  \n", ranking.usuario);
	printf("PUNTAJE: %i           ORCOS MUERTOS: %d \n", ranking.puntos, ranking.orcos_muertos);
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
*Analisis:
*Pre:
*Post:
*/
void pedir_posicion_def(char defensor[], char tipo, int cantidad_min, int cantidad_puesta, coordenada_t* posicion){
	printf("%sS para añadir: %i \n", defensor, cantidad_min - cantidad_puesta );
	printf("Añadir %s ( %c ) n° %i: \n", defensor, tipo, cantidad_puesta + 1);
	printf("Fila:");
	scanf("%i", &(posicion->fil));
	printf("Columna:");
	scanf("%i", &(posicion->col));
}
/*
*Análsis: Pregunta al usuario la posicion del defensor y lo agrega si su posicion es válida (No excede las dimensiones del campo ni coincide con otro defensor)
*Pre: Tipo válido ('G' o 'L')
*Post: Defensor agregado (hasta que se introduzcan bien los datos)
*/
void pedir_defesores(juego_t* juego, char defensor[MAX_LETRAS_DEFENSOR], char tipo, int cantidad_min, int coordenada_max){
	coordenada_t posicion;
	for (int i = 0; i < cantidad_min; ++i){
			pedir_posicion_def(defensor, tipo, cantidad_min, i, &posicion);
			while (agregar_defensor(&juego->nivel, posicion, tipo) != 0 || !posicion_valida(posicion, coordenada_max)){
				printf("POSICIÓN NO VÁLIDA, añadir nuevamente\n");
				pedir_posicion_def(defensor, tipo, cantidad_min, i, &posicion);
			}
		system("clear");
		mostrar_juego(*juego);
		}
		system("clear");
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
*Analisis:
*Pre:
*Post:
*/
void quitar_resistecia_torres(juego_t* juego, int costo[]){
	if(juego->nivel_actual == NIVEL_1){
		juego->torres.resistencia_torre_1 -= costo[TORRE_1];
	}else if (juego->nivel_actual == NIVEL_2){
		juego->torres.resistencia_torre_2 -= costo[TORRE_2];
	}else if ((juego->nivel_actual == NIVEL_3) || (juego->nivel_actual == NIVEL_4)){
		juego->torres.resistencia_torre_1 -= costo[TORRE_1];
		juego->torres.resistencia_torre_2 -= costo[TORRE_2];
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
			quitar_resistecia_torres(juego, campo.costo_G_extra);
			juego->torres.enanos_extra --;
		}else if (tipo == ELFO){
			quitar_resistecia_torres(juego, campo.costo_L_extra);
			juego->torres.elfos_extra --;
		}
}
/*
*Analisis:
*Pre:
*Post:
*/
bool estado_costo(juego_t juego, int costo[]){
	if((juego.nivel_actual == NIVEL_1) && (costo[TORRE_1] != 0)){
		return true;
	}else if ((juego.nivel_actual == NIVEL_2) && (costo[TORRE_2] != 0)){
		return true;
	}else if((juego.nivel_actual == NIVEL_3) || (juego.nivel_actual == NIVEL_4)){
		return true;
	}else{
		return false;
	}
}
/*
*Analisis:
*Pre:
*Post:
*/
bool tipo_correcto(char tipo, juego_t juego, campo_t campo){
	if (tipo == ENANO){
		return estado_costo(juego, campo.costo_G_extra);
	}else if(tipo == ELFO){
		return estado_costo(juego, campo.costo_L_extra);
	}else{
		return false;
	}
}
/*
*Análsis: Pregunta el tipo de defensor que el usuario quiera agregar
*Pre: Debe querer agregar un defensor y el nivel_actual debe ser 3 o 4
*Post: Caracter del tipo por referiencia
*/
void preguntar_tipo (char* tipo, juego_t juego, campo_t campo){
	char eleccion;
	printf("Introduzca el tipo ('%c' para ELFO o '%c' para ENANO):", ELFO, ENANO);
	scanf(" %c", &eleccion);
	while(!tipo_correcto(eleccion, juego, campo)){
			printf(" EL TIPO DE DEFENSOR NO ES CORRECTO, intente nuevamente...\n");
			if((juego.nivel_actual == NIVEL_1) || (juego.nivel_actual == NIVEL_2)){
				printf(" (recordá que si no hace daño a la torre del nivel no es válido)\n");
			}
			printf("Introduzca el tipo ('%c' para ELFO o '%c' para ENANO):", ELFO, ENANO);
			scanf(" %c", &eleccion);
	}
	*tipo=eleccion;
}
/*
*Analisis:
*Pre:
*Post:
*/
bool desicion_valida(char desicion){
	return ((desicion == SI) || (desicion == NO));
}
/*
*Analisis:
*Pre:
*Post:
*/
void preguntar_decision(char* desicion, campo_t campo){
	char aux;
	printf(" PENALIZACION  |   TORRE 1   |   TORRE 2   \n");
	printf("_______________|_____________|_____________\n");
	printf("    ENANOS     |     %i      |     %i       \n", campo.costo_G_extra[TORRE_1], campo.costo_G_extra[TORRE_2]);
	printf("    ELFOS      |     %i      |     %i       \n", campo.costo_L_extra[TORRE_1], campo.costo_L_extra[TORRE_2]);
	printf("-------------------------------------------\n");
	printf("¿Desea agregar un defensor extra?(%c/%c):", SI, NO);
	scanf(" %c", &aux);
	while(!desicion_valida(aux)){
		printf("La desicion no es correcta, recordá %c/%c ...\n", SI, NO);
		printf("¿Desea agregar un defensor extra?(%c/%c):", SI, NO);
		scanf(" %c", &aux);
	}
	(*desicion)=aux;
}
/*
*Análsis: Pregunta por un defensor extra según el nivel que corresponda (tipo y periodicidad)
*Pre: el nivel_actual del juego debe ser 1,2,3 o 4 y deben estar inicializados
*Post: Interacciona con el usuario y agrega o no un defensor según corresponda
*/
void bonificar_con_defesor(juego_t* juego, campo_t campo){
	char desicion;
	char defensor[MAX_LETRAS_DEFENSOR];
	if ((juego->torres.enanos_extra > 0) || (juego->torres.elfos_extra > 0)){
		char tipo;
		preguntar_decision(&desicion, campo);
		if (desicion==SI){
			preguntar_tipo(&tipo, *juego, campo);
			if ((tipo==ENANO)&&(juego->torres.enanos_extra > 0)){
				strcpy(defensor, "ENANO");
				agregar_def_extra(juego, campo, ENANO, defensor, campo.tope);
			}else if ((tipo==ELFO)&&(juego->torres.elfos_extra > 0)){
				strcpy(defensor, "ELFO");
				agregar_def_extra(juego, campo, ELFO, defensor, campo.tope);
			}
		}
	}else{
		printf(" NO TIENES DEFENSORES EXTRA\n");
	}
}
/*
*Analisis:
*Pre:
*Post:
*/
void configurar_orcos_iniciales(int nivel, estructura_t* estructura){
	if (nivel==NIVEL_1){
		estructura->nivel.max_enemigos_nivel= ORCOS_NVL_1;
	}else if (nivel==NIVEL_2){
		estructura->nivel.max_enemigos_nivel= ORCOS_NVL_2;
	}else if (nivel==NIVEL_3){
		estructura->nivel.max_enemigos_nivel= ORCOS_NVL_3;
	}else if (nivel==NIVEL_4){
		estructura->nivel.max_enemigos_nivel= ORCOS_NVL_4;
	}
}
/*
*Analisis: Configura los caminos de forma aleatoria con utiles.o
*Pre: Nivel correspondiente
*Post: Nivel cargado con sus caminos
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
*Analisis: Configura el campo segun la configuracion  y el nivel en el que se encuentre
*Pre: Configuracion cargada y nivel correspondiente
*Post: Campo del nivel configurado
*/
void configurar_campo(int nivel, campo_t* campo, configuracion_t config){
	campo->cantidad_enanos = config.cantidad_enanos[nivel];
	campo->cantidad_elfos = config.cantidad_elfos[nivel];
	campo->costo_G_extra[TORRE_1] = config.costo_G_extra[TORRE_1];
	campo->costo_G_extra[TORRE_2] = config.costo_G_extra[TORRE_2];
	campo->costo_L_extra[TORRE_1] = config.costo_L_extra[TORRE_1];
	campo->costo_L_extra[TORRE_2] = config.costo_L_extra[TORRE_2];
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
*Analisis: Dado un vector estructura_t carga todos los niveles correspondientes segun cada posicion
*Pre: Configuracion ya cargada
*Post: Vector de estructuras cargado con todos los niveles
*/
void inicializar_niveles(estructura_t estructura[MAX_NIVELES], configuracion_t config){
	for (int nivel=NIVEL_1; nivel<MAX_NIVELES; nivel++){
		estructura[nivel].nivel.tope_enemigos=0;
		estructura[nivel].nivel.tope_defensores=0;
		configurar_campo(nivel, &(estructura[nivel].campo), config);
		if(config.hay_caminos){
			configurar_camino_archivo(nivel, &(estructura[nivel].nivel), config);
		}else{
			configurar_camino_aleatorio(nivel ,&(estructura[nivel].nivel), &(estructura[nivel].campo));
		}
		configurar_orcos_iniciales(nivel, &(estructura[nivel]));
	}
}
/*
*Analisis: Segun el nivel actual del juego carga la estructura correspondiente
*Pre: Niveles inicializados
*Post: Juego con su nivel cargado(con defensores)
*/
void cargar_nivel(juego_t* juego, estructura_t estructura){
	juego->nivel=estructura.nivel;
	mostrar_juego(*juego);
	asignar_defensores(juego, estructura.campo);
}
/*
*Analisis: Juega un turno completo
*Pre: Juego inicializado y con el primer nivel cargado
*Post: Muestra por pantalla un turno completo y lo ejecuta
*/
void jugar_turno_completo(juego_t* juego, estructura_t estructura[MAX_NIVELES], configuracion_t configuracion, ranking_t ranking){
	if (estado_nivel(juego->nivel) == GANADO){
		mostrar_nvl_ganado(*juego);
		juego->nivel_actual++;
		cargar_nivel(juego, estructura[juego->nivel_actual]);
	}
	jugar_turno(juego);
	mostrar_campo(*juego, configuracion.velocidad, ranking);
	if (hay_bonificacion(*juego, estructura[juego->nivel_actual].campo)){
		mostrar_juego(*juego);
		bonificar_con_defesor(juego, estructura[juego->nivel_actual].campo);
		mostrar_campo(*juego, configuracion.velocidad, ranking);
	}
}
/*
*Analisis: Configuracion inicial del juego
*Pre: Configuracion y estructuras cargadas
*Post: Juego inicializado y con el nivel 1 cargado, ranking con el usuario
*/
void configurar_juego(juego_t* juego, configuracion_t configuracion, estructura_t estructura[], ranking_t* ranking) {
	inicializar_juego(juego, configuracion);
	inicializar_niveles(estructura, configuracion);
	printf("Introduzca su nombre: ");
	scanf("%[^\n]", ranking->usuario);
	ranking->puntos=0;
	ranking->orcos_muertos=0;
	system("clear");
	cargar_nivel(juego, estructura[juego->nivel_actual]);
}
int main (int argc, char* argv[]){
	srand((unsigned)time(NULL));

	configuracion_t configuracion;
	juego_t juego;
	estructura_t estructura[MAX_NIVELES];
	ranking_t ranking;
	char archivo_config[MAX_ARGUMENTO];
	char archivo_grabacion[MAX_ARGUMENTO];

	if (argc>1){
		int programa=estado_programa(argv[1]);
		if ((programa != JUGAR) && (programa != ERROR)){
			comandos(programa, argv);
			return 0;
		}else if (programa==JUGAR){
			system("clear");
			int modo=modo_juego(argv, archivo_config, archivo_grabacion);
			cargar_confirguracion(&configuracion, modo, archivo_config);
			mostrar_inicio(archivo_config, archivo_grabacion, configuracion);
			configurar_juego(&juego, configuracion, estructura, &ranking);
			while(estado_juego(juego) == JUGANDO){
				jugar_turno_completo(&juego, estructura, configuracion, ranking);
				calcular_puntaje(juego, configuracion, &ranking);
				if ((modo == STANDARD_GRABANDO) || (modo == CUSTOM_GRABANDO)){
					guardar_partida(juego, archivo_grabacion);
					printf("grabando...\n");
				}
			}
			if (estado_juego(juego) == GANADO){
				mostrar_juego_ganado(ranking);
			}else if (estado_juego(juego) == PERDIDO){
				mostrar_juego_perdido(ranking);
			}
			actualizar_ranking(juego, ranking, archivo_config);
			return 0;
		}else{
			printf("Hubo un error con los comandos, revisar si se ingresó correctamente.\n Más informacion comando '--help'.\n");
			return -1;
		}
	}else{
		printf("No ingresaste ningun comando\n Más informacion comando '--help'.\n");
		return -1;
	}
}
