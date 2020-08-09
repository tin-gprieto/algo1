#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "defendiendo_torres.h"

const int VELOCIDAD_ALTA = 75;
const int VELOCIDAD_MEDIA = 50;
const int VELOCIDAD_BAJA = 25;
const int HUMEDAD_ALTA = 75;
const int HUMEDAD_MEDIA = 50;
const int HUMEDAD_BAJA = 25;
const int VIDA_ORCO = 200;
const int VIDA_EXTRA_MAX = 100;
const int CRITICO_MALO = 0;
const int CRITICO_REGULAR = 10;
const int CRITICO_BUENO = 25;
const int ATAQUE_ENANO = 60;
const int ATAQUE_CRITICO_G =100;
const int ATAQUE_ELFO = 30;
const int ATAQUE_CRITICO_L = 70;
const char MALO = 'M';
const char REGULAR = 'R';
const char BUENO = 'B';
const char ORCO = 'O';
const char CAMINO = ' ';
const char FONDO = '"';
const char ENTRADA = 'E';
const char TORRE = 'T';

#define ELFO 'L'
#define ENANO 'G'
#define ORCOS_NVL_1 100
#define ORCOS_NVL_2 200
#define ORCOS_NVL_3 300
#define ORCOS_NVL_4 500
#define NIVEL_1 0
#define NIVEL_2 1
#define NIVEL_3 2
#define NIVEL_4 3

#define GANADO 1
#define JUGANDO 0
#define PERDIDO -1

#define MAX_CAMPO_FILA 20
#define MAX_CAMPO_COLUMNA 20
#define MAX_A_PEGAR 30

/*
*Análsis: Establece los valores de resistencia y defensores extra de las torres
*Pre: -
*Post: Valores de resistencia_torre_1, resistencia_torre_2, enanos_extra y elfos_extra
*/
void inicializar_torre(juego_t* juego, configuracion_t config){
	juego -> torres.resistencia_torre_1 = config.torres.resistencia_torre_1;
	juego -> torres.resistencia_torre_2 = config.torres.resistencia_torre_2;
	juego -> torres.enanos_extra = config.torres.enanos_extra;
	juego -> torres.elfos_extra= config.torres.elfos_extra;
}
/*
*Análsis: Recibe la salud de las torres y devuelve su estado
*Pre: resistecia de las torres inicializada
*Post: Verdadero si ambas están bien. Falso si alguna tiene resistencia menor a 0.
*/
bool estan_bien_las_torres (juego_t juego){
	return ((juego.torres.resistencia_torre_1 > 0) && (juego.torres.resistencia_torre_2) > 0);
}
/*
*Análsis: Recorre la matriz del campo y asigna el fondo
*Pre: tope de campo que sea 15 o 20
*Post: campo de batalla con fondo
*/
void asignar_fondo_en_campo(juego_t juego, int tope_campo, char campo_de_batalla[MAX_CAMPO_FILA][MAX_CAMPO_COLUMNA]){
	for (int i=0; i < tope_campo; i++){
		for (int j=0; j < tope_campo; j++){
			campo_de_batalla[i][j]=FONDO;
		}
	}
}
/*
*Análsis: Recorre el camino y asigna cada posicion al campo
*Pre: tope_camino correspondiente para el camino en cuestion
*Post: camino asignado al campo con su entrada y torre
*/
void asignar_camino_en_campo(juego_t juego, coordenada_t camino[], int tope_camino, char campo_de_batalla[MAX_CAMPO_FILA][MAX_CAMPO_COLUMNA]){
	for (int i=0; i<(tope_camino); i++){
		if (i == 0)
			campo_de_batalla[camino[i].fil][camino[i].col]= ENTRADA;
		else if(i == (tope_camino) - 1)
			campo_de_batalla[camino[i].fil][camino[i].col]= TORRE;
		else
			campo_de_batalla[camino[i].fil][camino[i].col]= CAMINO;
	}
}
/*
*Análsis: Recorre el vector de defensores y los asigna en el campo
*Pre: Defensor o defensores ya agregados
*Post: campo con sus defensores del tipo que corresponde  ('L' o 'G')
*/
void asignar_defensores_en_campo(juego_t juego, char campo_de_batalla[MAX_CAMPO_FILA][MAX_CAMPO_COLUMNA]){
	for (int i = 0; i < juego.nivel.tope_defensores; ++i){
		if (juego.nivel.defensores[i].tipo == ELFO)
			campo_de_batalla[juego.nivel.defensores[i].posicion.fil][juego.nivel.defensores[i].posicion.col] = ELFO;
		if (juego.nivel.defensores[i].tipo == ENANO)
			campo_de_batalla[juego.nivel.defensores[i].posicion.fil][juego.nivel.defensores[i].posicion.col] = ENANO;
	}
}
/*
*Análsis:  Recorre el vector de defensores y los asigna en al campo
*Pre: -
*Post: campo con enemigos
*/
void asignar_enemigos(juego_t juego, char campo_de_batalla[MAX_CAMPO_FILA][MAX_CAMPO_COLUMNA]){
	for (int i = 0; i < (juego.nivel.tope_enemigos); ++i){
		if((juego.nivel.enemigos[i].vida > 0)){
			if (juego.nivel.enemigos[i].camino==1){
				campo_de_batalla[juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_1[juego.nivel.enemigos[i].pos_en_camino].col]= ORCO;
			}else if(juego.nivel.enemigos[i].camino==2)
				campo_de_batalla[juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].fil][juego.nivel.camino_2[juego.nivel.enemigos[i].pos_en_camino].col]= ORCO;
		}
	}

}
/*
*Análsis: Mueve a todos los orcos según el camino en el que estén y si están en la torre hacen daño
*Pre: -
*Post: Nueva posicion de los orcos y la resistencia de la torre modificada si corresponde
*/
void mover_orcos(juego_t* juego){
	for (int i = 0; i < juego->nivel.tope_enemigos; i++){
		if (juego->nivel.enemigos[i].vida > 0){
			juego->nivel.enemigos[i].pos_en_camino++;
			if (juego->nivel.enemigos[i].camino==1){
				if ((juego->nivel.enemigos[i].pos_en_camino == juego->nivel.tope_camino_1 - 1)){
					juego->torres.resistencia_torre_1= juego->torres.resistencia_torre_1 - juego->nivel.enemigos[i].vida;
					juego->nivel.enemigos[i].vida = 0;
				}
			}else if (juego->nivel.enemigos[i].camino==2){
				if ((juego->nivel.enemigos[i].pos_en_camino == juego->nivel.tope_camino_2 - 1)){
					juego->torres.resistencia_torre_2= juego->torres.resistencia_torre_2 - juego->nivel.enemigos[i].vida;
					juego->nivel.enemigos[i].vida = 0;
				}
			}
		}
	}


}
/*
*Imprime por pantalla los valores del juego y el tablero del campo
*/
void dibujar_campo(juego_t juego, char campo_de_batalla[MAX_CAMPO_FILA][MAX_CAMPO_COLUMNA], int tope_campo){
	int salud_torre_1 = juego.torres.resistencia_torre_1;
	int salud_torre_2 = juego.torres.resistencia_torre_2;
	int enanos_extra = juego.torres.enanos_extra;
	int elfos_extra = juego.torres.elfos_extra;
	int enemigos = juego.nivel.tope_enemigos;
	int critico_enanos = juego.critico_gimli;
	int critico_elfos = juego.critico_legolas;
	int fallo_enanos = juego.fallo_gimli;
	int fallo_elfos = juego.fallo_legolas;

	printf("........................NIVEL %i......................... \n\n", (juego.nivel_actual+1));
	if(juego.nivel_actual==NIVEL_1){
		printf("SALUD TORRE 1: %i     ENEMIGOS RESTANTES: %i / %i \n", salud_torre_1, ORCOS_NVL_1 - enemigos, ORCOS_NVL_1);
		printf("CRÍTICO:  %i °/.       FALLO: %i  °/. \n", critico_enanos, fallo_enanos);
	}
	if(juego.nivel_actual==NIVEL_2){
		printf("SALUD TORRE 2: %i     ENEMIGOS RESTANTES: %i / %i \n", salud_torre_2, ORCOS_NVL_2 - enemigos, ORCOS_NVL_2);
		printf("CRÍTICO:  %i °/.       FALLO: %i  °/. \n", critico_elfos, fallo_elfos);
	}
	if(juego.nivel_actual==NIVEL_3){
		printf("SALUD TORRE 1: %i     SALUD TORRE 2: %i    ENEMIGOS RESTANTES: %i / %i \n", salud_torre_1, salud_torre_2, ORCOS_NVL_3 - enemigos, ORCOS_NVL_3);
		printf("CRÍTICO %c:  %i °/.      FALLO %c: %i  °/. \n", ENANO, critico_enanos, ENANO, fallo_enanos);
		printf("CRÍTICO %c:  %i °/.      FALLO %c: %i  °/. \n", ELFO, critico_elfos, ELFO, fallo_elfos);
	}
	if(juego.nivel_actual==NIVEL_4){
		printf("SALUD TORRE 1: %i     SALUD TORRE 2: %i    ENEMIGOS RESTANTES: %i / %i \n", salud_torre_1, salud_torre_2, ORCOS_NVL_4 - enemigos, ORCOS_NVL_4);
		printf("CRÍTICO %c:  %i °/.      FALLO %c: %i  °/. \n", ENANO, critico_enanos, ENANO, fallo_enanos);
		printf("CRÍTICO %c:  %i °/.      FALLO %c: %i  °/. \n", ELFO, critico_elfos, ELFO, fallo_elfos);
	}
	printf("ENANOS EXTRA:  %i      ELFOS EXTRA: %i  \n", enanos_extra, elfos_extra);
	if((juego.nivel_actual==NIVEL_1)||(juego.nivel_actual==NIVEL_2)){
		printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==\n");
		printf("==-=|| 00-01-02-03-04-05-06-07-08-09-10-11-12-13-14||=-==\n");
	}
	if((juego.nivel_actual==NIVEL_3)||(juego.nivel_actual==NIVEL_4)){
		printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==\n");
		printf("==-=|| 00-01-02-03-04-05-06-07-08-09-10-11-12-13-14-15-16-17-18-19||=-==\n");
	}

		for (int i=0; i < tope_campo; i++){
			if (i>=10)
					printf(" |%i| ", i);
				else
					printf(" |0%i| ", i);
			for (int j=0; j < tope_campo; j++){
				printf(" %c ", campo_de_batalla[i][j]);
			}
			if (i>=10)
					printf(" |%i| \n", i);
				else
					printf(" |0%i| \n", i);
		}

	if((juego.nivel_actual==NIVEL_1)||(juego.nivel_actual==NIVEL_2)){
		printf("==-=|| 00-01-02-03-04-05-06-07-08-09-10-11-12-13-14||=-==\n");
		printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==\n");
	}
	if ((juego.nivel_actual==NIVEL_3)||(juego.nivel_actual==NIVEL_4)){
		printf("==-=|| 00-01-02-03-04-05-06-07-08-09-10-11-12-13-14-15-16-17-18-19||=-==\n");
		printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==\n");
	}
}
/*
*Análsis: Recorre el vector de enemigos, si están todos muertos y ya se agregaron todos, devuelve verdadero
*Pre: -
*Post: Verdadero si no hay enemigos con vida mayor a 0 y se llegó al másimo de enemigos
*/
bool estan_todos_muertos(nivel_t nivel){
	bool estado=false;
	int contador_de_orcos=0;
	if (nivel.tope_enemigos>0){
		for (int i = 0; i < nivel.tope_enemigos; ++i){
			if (nivel.enemigos[i].vida <= 0)
				contador_de_orcos ++;
			}
		}
	if (contador_de_orcos == nivel.max_enemigos_nivel)
		estado=true;
	return estado;
}
/*
*Análsis: Verifica si la posicion pasada del defensor coincide con el camino
*Pre: tope de camino que corresponda al camino pasado
*Post: Si coincide devuelve falso, sino verdadero (estado)
*/
bool posicion_valida_camino(coordenada_t camino [], int tope_camino, coordenada_t posicion){
	bool estado = true;
	for (int i = 0; i < tope_camino; ++i){
		if ((posicion.fil == camino[i].fil)&&(posicion.col == camino[i].col))
			estado = false;
	}
	return estado;
}
/*
*Análsis: Verifica si la posicion del defesor no coincide con otro defensor
*Pre: -
*Post:  Si coincide devuelve falso, sino verdadero (estado)
*/
bool posicion_valida_defensores (defensor_t defensores[MAX_DEFENSORES], int tope_defensores, coordenada_t posicion){
	bool estado= true;

	for (int i = 0; i < tope_defensores; ++i){
		if ((posicion.fil == defensores[i].posicion.fil)&&(posicion.col == defensores[i].posicion.col))
			estado = false;
	}
	return estado;
}
/*
*Análsis: Recibe la posicion y el tipo del defensor y lo inicializa según el tipo que sea
*Pre: Posicion válida (no ser la misma que el camino o que otro defensor) y tipo válido ('L'o'G')
*Post: Defensor con sus atributos determinado
*/
void inicializar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo){
	defensor_t defensor;
	defensor.posicion.fil = posicion.fil;
	defensor.posicion.col = posicion.col;
	defensor.tipo = tipo;
	if (tipo == ENANO){
		defensor.fuerza_ataque = ATAQUE_ENANO;
	}else if (tipo == ELFO){
		defensor.fuerza_ataque = ATAQUE_ELFO;
	}
	nivel->defensores[nivel->tope_defensores]=defensor;
	nivel->tope_defensores ++;
}
/*
*Análsis: Según un número aleatorio del 0 al 100 determina si hay fallo
*Pre: Juego inicializado
*Post: Verdadero si para este caso hay fallo
*/
bool tiene_fallo(int porcentaje_fallo){
	srand((unsigned)time(NULL));
	int aleatorio=rand()%100 + 0;
	if (aleatorio <= porcentaje_fallo)
		return true;
	else
		return false;
}
/*
*Análsis: Según un número aleatorio del 0 al 100 determina si hay critico
*Pre: Juego inicializado
*Post: Verdadero si para este caso hay critico
*/
bool tiene_critico(int porcentaje_critico){
	srand((unsigned)time(NULL));
	int aleatorio=rand()%100 + 0;
	if (aleatorio <= porcentaje_critico)
		return true;
	else
		return false;
}
/*
*Análsis: Recibe la poscione del enemigo y evalua si está a 1 de distancia de la posicion del enano
*Pre: -
*Post: Verdadero si cumple con el rango
*/
bool condiciones_rango_G(coordenada_t pos_defensor, coordenada_t pos_enemigo){
	if ((pos_enemigo.fil==pos_defensor.fil - 1)&&(pos_enemigo.col==pos_defensor.col)){
		return true;
	}else if ((pos_enemigo.fil==pos_defensor.fil - 1)&&(pos_enemigo.col==pos_defensor.col + 1)){
		return true;
	}else if ((pos_enemigo.fil==pos_defensor.fil - 1)&&(pos_enemigo.col==pos_defensor.col - 1)){
		return true;
	}else if ((pos_enemigo.fil==pos_defensor.fil)&&(pos_enemigo.col==pos_defensor.col - 1)){
		return true;
	}else if ((pos_enemigo.fil==pos_defensor.fil)&&(pos_enemigo.col==pos_defensor.col + 1)){
		return true;
	}else if ((pos_enemigo.fil==pos_defensor.fil + 1)&&(pos_enemigo.col==pos_defensor.col)){
		return true;
	}else if ((pos_enemigo.fil==pos_defensor.fil + 1)&&(pos_enemigo.col==pos_defensor.col + 1)){
		return true;
	}else if ((pos_enemigo.fil==pos_defensor.fil + 1)&&(pos_enemigo.col==pos_defensor.col - 1)){
		return true;
	}
	return false;
}
/*
*Análsis: Según la posicion del defensor y el enemigo evalua si cumple el rango del enano
*Pre: El camino debe corresponder al camino del enemigo.
*Post: Verdadero si el enemigoe está en rango.
*/
bool esta_en_rango_G(juego_t juego, defensor_t defensor, enemigo_t enemigo, coordenada_t camino[MAX_LONGITUD_CAMINO]){
	coordenada_t pos_enemigo;
	coordenada_t pos_defensor;
	pos_enemigo.fil= (camino[enemigo.pos_en_camino].fil);
	pos_enemigo.col = (camino[enemigo.pos_en_camino].col);
	pos_defensor.fil = (defensor.posicion.fil);
	pos_defensor.col = (defensor.posicion.col);
	if(condiciones_rango_G(pos_defensor, pos_enemigo))
		return true;
	return false;
}
/*
*Análsis: Ataca a un solo orco en el rango del enano cuando hay un solo camino (si no hay fallo, y con crítico si lo hay)
*Pre: El nivel_actual debe ser 1 o 2. El camino debe corresponder para cada nivel.
*Post: Vida de los orcos modificada si cumplen el rango de ataque.
*/
void atacar_con_enanos_campo_1(juego_t* juego, coordenada_t camino[MAX_LONGITUD_CAMINO]){
	for (int i = 0; i < juego->nivel.tope_defensores; ++i){
		if (juego->nivel.defensores[i].tipo == ENANO){
			int j = 0;
			bool dio_golpe=false;
			while (j < juego->nivel.tope_enemigos && !dio_golpe){
				if (esta_en_rango_G(*juego, juego->nivel.defensores[i], juego->nivel.enemigos[j], camino)&&(juego->nivel.enemigos[j].vida > 0)){
					if (!tiene_fallo(juego->fallo_gimli)){
						if (tiene_critico(juego->critico_gimli)){
							juego->nivel.enemigos[j].vida -= ATAQUE_CRITICO_G;
							dio_golpe=true;
						}else{
							juego->nivel.enemigos[j].vida -= ATAQUE_ENANO;
							dio_golpe=true;
						}
					}
				}
				j++;
			}
		}
	}
}
/*
*Análsis: Ataca a un solo orco en el rango del enano cuando hay dos caminos (si no hay fallo, y con crítico si lo hay)
*Pre: El nivel_actual debe ser 3 o 4
*Post: Vida de los orcos modificada si cumplen el rango de ataque.
*/
void atacar_con_enanos_campo_2(juego_t* juego){
	for (int i = 0; i < juego->nivel.tope_defensores; ++i){
		if (juego->nivel.defensores[i].tipo == ENANO){
			int j = 0;
			bool dio_golpe_1=false;
			while (j < juego->nivel.tope_enemigos && !dio_golpe_1){
				if (esta_en_rango_G(*juego, juego->nivel.defensores[i], juego->nivel.enemigos[j], juego->nivel.camino_1)&&(juego->nivel.enemigos[j].vida > 0)){
					if (!tiene_fallo(juego->fallo_gimli)){
						if (tiene_critico(juego->critico_gimli)){
							juego->nivel.enemigos[j].vida -= ATAQUE_CRITICO_G;
							dio_golpe_1=true;
						}else{
							juego->nivel.enemigos[j].vida -= ATAQUE_ENANO;
							dio_golpe_1=true;
						}
					}
				}
				j+=2;
			}
			int k = 1;
			bool dio_golpe_2=false;
			while (k < juego->nivel.tope_enemigos && !dio_golpe_2){
				if (esta_en_rango_G(*juego, juego->nivel.defensores[i], juego->nivel.enemigos[k], juego->nivel.camino_2)&&(juego->nivel.enemigos[j].vida > 0)){
					if (!tiene_fallo(juego->fallo_gimli)){
						if (tiene_critico(juego->critico_gimli)){
							juego->nivel.enemigos[k].vida -= ATAQUE_CRITICO_G;
							dio_golpe_2=true;
						}else{
							juego->nivel.enemigos[k].vida -= ATAQUE_ENANO;
							dio_golpe_2=true;
						}
					}
				}
				k+=2;
			}
		}
	}
}
/*
*Análsis: Según la posicion del defensor y el enemigo evalua si cumple el rango de elfo
*Pre: El camino debe corresponder al camino del enemigo.
*Post: Verdadero si el enemigoe está en rango.
*/
bool esta_en_rango_L(juego_t juego, defensor_t defensor, enemigo_t enemigo, coordenada_t camino[MAX_LONGITUD_CAMINO]){
	int distancia=3;
	int filas = abs((defensor.posicion.fil)-(camino[enemigo.pos_en_camino].fil));
	int columnas = abs((defensor.posicion.col)-(camino[enemigo.pos_en_camino].col));
	if (filas + columnas <= distancia)
		return true;
	else
		return false;
}
/*
*Análsis: Ataca a todos los orcos en el rango del elfo cuando hay un solo camino (si no hay fallo, y con crítico si lo hay)
*Pre: El nivel_actual debe ser 1 o 2. El camino debe corresponder para cada nivel.
*Post: Vida de los orcos modificada si cumplen el rango de ataque.
*/
void atacar_con_elfos_campo_1(juego_t* juego, coordenada_t camino[MAX_LONGITUD_CAMINO]){
	for (int i = 0; i < juego->nivel.tope_defensores; ++i){
		if (juego->nivel.defensores[i].tipo == ELFO){
			for (int j = 0; j < juego->nivel.tope_enemigos; j++){
				if (esta_en_rango_L(*juego, juego->nivel.defensores[i], juego->nivel.enemigos[j], camino) && (juego->nivel.enemigos[j].vida > 0)){
					if (!tiene_fallo(juego->fallo_legolas)){
						if (tiene_critico(juego->critico_legolas)){
							juego->nivel.enemigos[j].vida -= ATAQUE_CRITICO_L;
						}else{
							juego->nivel.enemigos[j].vida -= ATAQUE_ELFO;
						}
					}
				}
			}
		}
	}
}
/*
*Análsis: Ataca a todos los orcos en el rango del elfo cuando hay dos caminos (si no hay fallo, y con crítico si lo hay)
*Pre: El nivel_actual debe ser 3 o 4
*Post: Vida de los orcos modificada si cumplen el rango de ataque.
*/
void atacar_con_elfos_campo_2(juego_t* juego){
	for (int i = 0; i < juego->nivel.tope_defensores; ++i){
		if (juego->nivel.defensores[i].tipo == ELFO){
			for (int j = 0; j < juego->nivel.tope_enemigos; j+=2){
				if (esta_en_rango_L(*juego, juego->nivel.defensores[i], juego->nivel.enemigos[j], juego->nivel.camino_1) && (juego->nivel.enemigos[j].vida > 0)){
					if (!tiene_fallo(juego->fallo_legolas)){
						if (tiene_critico(juego->critico_legolas)){
							juego->nivel.enemigos[j].vida -= ATAQUE_CRITICO_L;
						}else{
							juego->nivel.enemigos[j].vida -= ATAQUE_ELFO;
						}
					}
				}
			}
			for (int k = 1; k < juego->nivel.tope_enemigos; k+=2){
				if (esta_en_rango_L(*juego, juego->nivel.defensores[i], juego->nivel.enemigos[k], juego->nivel.camino_2) && (juego->nivel.enemigos[k].vida > 0)){
					if (!tiene_fallo(juego->fallo_legolas)){
						if (tiene_critico(juego->critico_legolas)){
							juego->nivel.enemigos[k].vida -= ATAQUE_CRITICO_L;
						}else{
							juego->nivel.enemigos[k].vida -= ATAQUE_ELFO;
						}
					}
				}
			}
		}
	}
}
/*
*Análsis: Establece el camino, la posicion y la vida de un orco según el nivel (modificando el tope)
*Pre: El nivel_actual debe se 1,2,3 o 4.
*Post: Vector de orcos con un nuevo elemento y con su tope modificado
*/
void agregar_orco(juego_t* juego){
	srand((unsigned)time(NULL));
	if (juego->nivel.tope_enemigos < juego->nivel.max_enemigos_nivel){
		if (juego->nivel_actual == NIVEL_1){
			juego->nivel.enemigos[juego->nivel.tope_enemigos].camino=1;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino=0;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = VIDA_ORCO + (rand()%VIDA_EXTRA_MAX + 0);
			juego->nivel.tope_enemigos++;
		}else if(juego->nivel_actual == NIVEL_2){
			juego->nivel.enemigos[juego->nivel.tope_enemigos].camino=2;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino=0;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = VIDA_ORCO + (rand()%VIDA_EXTRA_MAX + 0);
			juego->nivel.tope_enemigos++;
		}else if ((juego->nivel_actual == NIVEL_3)||(juego->nivel_actual == NIVEL_4)){
			juego->nivel.enemigos[juego->nivel.tope_enemigos].camino=1;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino=0;
			juego->nivel.enemigos[juego->nivel.tope_enemigos + 1].camino=2;
			juego->nivel.enemigos[juego->nivel.tope_enemigos + 1].pos_en_camino=0;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = VIDA_ORCO + (rand()%VIDA_EXTRA_MAX + 0);
			juego->nivel.enemigos[juego->nivel.tope_enemigos + 1].vida = VIDA_ORCO + (rand()%VIDA_EXTRA_MAX + 0);
			juego->nivel.tope_enemigos += 2;
		}
	}
}
void inicializar_juego(juego_t* juego, configuracion_t config){
	juego -> fallo_legolas = config.fallo_legolas;
	juego -> fallo_gimli = config.fallo_gimli;
	juego -> critico_legolas = config.critico_legolas;
	juego -> critico_gimli = config.critico_gimli;
	inicializar_torre(&*juego, config);
	juego -> nivel_actual= NIVEL_1;
}
int estado_juego(juego_t juego){
	if (!estan_bien_las_torres(juego))
		return PERDIDO;
	if ((juego.nivel_actual == NIVEL_4) && estan_bien_las_torres(juego)){
		if (estan_todos_muertos(juego.nivel))
			return GANADO;
		else
			return JUGANDO;
	}else
		return JUGANDO;
}
int estado_nivel(nivel_t nivel){
	if (estan_todos_muertos(nivel))
		return GANADO;
	else
		return JUGANDO;
}
int agregar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo){
	if (!posicion_valida_camino(nivel->camino_1, nivel->tope_camino_1, posicion) || !posicion_valida_camino(nivel->camino_2, nivel->tope_camino_2, posicion))
		return -1;
	if (!posicion_valida_defensores(nivel->defensores, nivel->tope_defensores, posicion))
		return -1;
	inicializar_defensor(nivel, posicion, tipo);
	return 0;
}
void jugar_turno(juego_t* juego){
	switch(juego->nivel_actual){
		case NIVEL_1:
			atacar_con_enanos_campo_1(juego, juego->nivel.camino_1);
			mover_orcos(juego);
			agregar_orco(juego);
		break;
		case NIVEL_2:
			atacar_con_elfos_campo_1(juego, juego->nivel.camino_2);
			agregar_orco(juego);
			mover_orcos(juego);
		break;
		case NIVEL_3:
			atacar_con_enanos_campo_2(juego);
			atacar_con_elfos_campo_2(juego);
			mover_orcos(juego);
			agregar_orco(juego);
		break;
		case NIVEL_4:
			atacar_con_enanos_campo_2(juego);
			atacar_con_elfos_campo_2(juego);
			mover_orcos(juego);
			agregar_orco(juego);
		break;
	}
}
void mostrar_juego(juego_t juego){
	char campo_de_batalla[MAX_CAMPO_FILA][MAX_CAMPO_COLUMNA];
	int tope_campo;
	int tope_camino_1 = juego.nivel.tope_camino_1;
	int tope_camino_2 = juego.nivel.tope_camino_2;

	switch (juego.nivel_actual){
		case NIVEL_1:
			tope_campo = 15;
			asignar_fondo_en_campo(juego, tope_campo, campo_de_batalla);
			asignar_camino_en_campo (juego, juego.nivel.camino_1, tope_camino_1, campo_de_batalla);
			asignar_defensores_en_campo (juego, campo_de_batalla);
			asignar_enemigos(juego, campo_de_batalla);
			dibujar_campo (juego, campo_de_batalla, tope_campo);
		break;

		case NIVEL_2:
			tope_campo = 15;
			asignar_fondo_en_campo (juego, tope_campo, campo_de_batalla);
			asignar_camino_en_campo (juego, juego.nivel.camino_2, tope_camino_2, campo_de_batalla);
			asignar_defensores_en_campo (juego, campo_de_batalla);
			asignar_enemigos(juego, campo_de_batalla);
			dibujar_campo (juego, campo_de_batalla, tope_campo);
		break;

		case NIVEL_3:
			tope_campo = 20;
			asignar_fondo_en_campo (juego, tope_campo, campo_de_batalla);
			asignar_camino_en_campo (juego, juego.nivel.camino_1, tope_camino_1, campo_de_batalla);
			asignar_camino_en_campo (juego, juego.nivel.camino_2, tope_camino_2, campo_de_batalla);
			asignar_defensores_en_campo (juego, campo_de_batalla);
			asignar_enemigos (juego, campo_de_batalla);
			dibujar_campo (juego, campo_de_batalla, tope_campo);

		break;

		case NIVEL_4:
			tope_campo = 20;
			asignar_fondo_en_campo (juego, tope_campo, campo_de_batalla);
			asignar_camino_en_campo (juego, juego.nivel.camino_1, tope_camino_1, campo_de_batalla);
			asignar_camino_en_campo (juego, juego.nivel.camino_2, tope_camino_2, campo_de_batalla);
			asignar_defensores_en_campo (juego, campo_de_batalla);
			asignar_enemigos (juego, campo_de_batalla);
			dibujar_campo(juego, campo_de_batalla, tope_campo);
		break;

	}
}
