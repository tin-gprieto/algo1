/**
 * @Date:   2020-08-10T17:17:20-03:00
 * @Last modified time: 2020-08-13T01:34:21-03:00
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "defendiendo_torres.h"
#include "argumentos.h"
#include "utiles.h"

#define MAX_SEPARADOR 2
#define MAX_ARCHIVO 50
#define MAX_CLAVE 50
#define MAX_DIRECCION 50
#define MAX_LONGITUD_CAMINO 200
#define MAX_RANKING 100
#define MAX_CAMPO 20

#define ARG_JUGAR "jugar"
#define ARG_CREAR_CONFIGURACION "crear_configuracion"
#define ARG_CREAR_CAMINOS "crear_caminos"
#define ARG_RANKING "ranking"
#define ARG_REPETICION "poneme_la_repe"

#define COLOR_CYAN "\x1b[36m"
#define COLOR_VERDE "\x1b[32m"
#define COLOR_ROJO "\x1b[31m"
#define COLOR_RESET "\x1b[0m"

#define FORMATO_CLAVE "%[^=]"
#define FORMATO_CLAVE_ESCRITURA "%s"
#define FORMATO_TORRES "=%i;%i\n"
#define FORMATO_INICIO "=%i;%i;%i;%i\n"
#define FORMATO_EXTRA "=%i;%i;%i\n"
#define FORMATO_ANIMO "=%i;%i\n"
#define FORMATO_VELOCIDAD "=%f\n"
#define FORMATO_CAMINO "=%s\n"

#define FORMATO_CREAR_CAMINO "NIVEL=%i\nCAMINO=%i\n"
#define FORMATO_CREAR_CAMINO_ESCRITURA "%s=%i\n"
#define FORMATO_VALOR "=%i\n"
#define FORMATO_COORDENADA "%i;%i\n"

#define FORMATO_RANKING "%[^;];%d\n"
#define FORMATO_RANKING_ESCRITURA "%s;%d\n"

#define ARCHIVO_RANKING "ranking_"
#define EXTENSION_RANKING ".csv"
#define SEPARADOR_EXTENSION "."
#define ARCHIVO_RANKING_STANDARD "ranking.csv"
#define ARCHIVO_CONFIG_STANDARD "configuracion_standard.txt"

#define CLAVE_TORRES "RESISTENCIA_TORRES"
#define CLAVE_G_INICIO "ENANOS_INICIO"
#define CLAVE_L_INICIO "ELFOS_INICIO"
#define CLAVE_G_EXTRA "ENANOS_EXTRA"
#define CLAVE_L_EXTRA "ELFOS_EXTRA"
#define CLAVE_G_ANIMO "ENANOS_ANIMO"
#define CLAVE_L_ANIMO "ELFOS_ANIMO"
#define CLAVE_VELOCIDAD "VELOCIDAD"
#define CLAVE_CAMINO "CAMINOS"
#define CLAVE_CREAR_CAMINO "CAMINO"
#define CLAVE_NIVEL "NIVEL"

#define TOPE_CAMPO_1 15
#define TOPE_CAMPO_2 20
#define ORCOS_NVL_1 100
#define ORCOS_NVL_2 200
#define ORCOS_NVL_3 300
#define ORCOS_NVL_4 500

const int TOPE_NIVELES=4;
const int CONFIG_VACIA=-1;
const int CAMINO_1=1;
const int CAMINO_2=2;
const int HORIZONTAL=0;
const int VERTICAL=1;
const int RANKING_COMPLETO=0;
const int RANKING_LISTADO=1;
const int SIN_DEFINIR=-1;
const int MULTIPLICADOR=1000;
const char SEPARADOR[MAX_SEPARADOR]= "=";
const char IZQ='a';
const char DER='d';
const char ARRIBA='w';
const char ABAJO='s';
const char COMIENZO= 'E';
const char FINAL= 'T';
const char CAMINITO= ' ';
const char CAMPO= '.';
const char LIMITE= '*';
const char PROHIBIDO= 'X';
  /*FUNCIONES calcular_puntaje*/
/*
*Analisis: Calcula la cantidad de orcos muertos segun el nivel actual y los va sumando al ranking
*
*/
void calcular_orcos_muertos(juego_t juego, int* orcos){
  int contador=0;
  for(int pos=0; pos<juego.nivel.tope_enemigos; pos++){
    if(juego.nivel.enemigos[pos].vida <= 0){
      contador++;
    }
  }
  if (juego.nivel_actual==NIVEL_1){
    *orcos=contador;
  }else if (juego.nivel_actual==NIVEL_2){
    *orcos=contador+ORCOS_NVL_1;
  }else if (juego.nivel_actual==NIVEL_3){
    *orcos=contador+ORCOS_NVL_1+ORCOS_NVL_2;
  }else if (juego.nivel_actual==NIVEL_4){
    *orcos=contador+ORCOS_NVL_1+ORCOS_NVL_2+ORCOS_NVL_3;
  }
}
/*FUNCIONES actualizar_ranking*/
/*
*Analisis: A partir de la configuracion devuelve el nombre del archivo ranking
*Pre: Tipo de configuracion cargada al string "configuracion"
*Post: Nombre del archivo de ranking cargado al string "direc_ranking"
*/
void obtener_direc_ranking(char configuracion[], char direc_ranking[]){
  if(strcmp(configuracion, ARCHIVO_CONFIG_STANDARD)==0){
    strcpy(direc_ranking, ARCHIVO_RANKING_STANDARD);
  }else{
    strcpy(direc_ranking, ARCHIVO_RANKING);
    strcat(direc_ranking, strtok(configuracion, SEPARADOR_EXTENSION));
    strcat(direc_ranking, EXTENSION_RANKING);
  }
}
/*
*Analisis: Abre un nuevo archivo de ranking para pasar el vector de ranking actualizado y lo renombra como el archivo sin actualizar
*Pre:  Direccion del archivo original y vector lista con el nuevo ranking ya agregado ordenadamente
*Post: archivo de ranking con el nuevo usuario y puntos agregado en el lugar indicado
*/
void reescribir_ranking(ranking_t lista[], int tope_lista, char direc_ranking[]){
  FILE* nuevo_ranking=fopen("nuevo_ranking.txt", "w");
  if(!nuevo_ranking){
    printf("No se pudo abrir el ranking para escribirlo\n");
  }else{
    for (int i = 0; i < tope_lista; i++) {
      fprintf(nuevo_ranking, FORMATO_RANKING_ESCRITURA, lista[i].usuario, lista[i].puntos);
    }
    fclose(nuevo_ranking);
    rename("nuevo_ranking.txt", direc_ranking);

  }
}
/*
*Analisis: Pasa los campos del ranking segundo al ranking primero
*Pre: El ranking segundo debe tener datos de usuario y puntos
*Post: Ranking primero con los datos del ranking segundo
*/
void cambiar_valores_ranking(ranking_t* primero, ranking_t segundo){
  primero->puntos=segundo.puntos;
  strcpy(primero->usuario, segundo.usuario);
}
/*
*Analisis: Añade el ranking al vector de manera ordenada segun los puntos (a igual puntos, orden alfabetico)
*Pre: Lista cargado con el orden del archivo y el tope con la cantidad de elementos que tiene
(en el caso de no tener caraga la lista lo añade al primer lugar, condicion: tope=0)
*Post: Vector con el nuevo ranking y el tope de lista modificado
*/
void agregar_en_lista(ranking_t lista[], int* tope_lista, ranking_t ranking){
  bool agrego = false;
  int pos = *tope_lista;
  while (!agrego && pos>0) {
    if(lista[pos-1].puntos > ranking.puntos){
      cambiar_valores_ranking(&lista[pos], ranking);
      agrego = true;
    }else if(lista[pos-1].puntos == ranking.puntos){
      if(strcmp(lista[pos-1].usuario, ranking.usuario) < 0){
        cambiar_valores_ranking(&lista[pos], ranking);
        agrego = true;
      }
    }else{
      cambiar_valores_ranking(&lista[pos], lista[pos-1]);
    }
    pos--;
  }
  if(!agrego)
  cambiar_valores_ranking(&lista[0], ranking);
  (*tope_lista)++;
}
/*
*Analisis: Carga el vector lista con la informacion del archivo de ranking en el orden en el que se encuentra
*Pre: Archico ranking vacio o ya ordenado de mayor a menor
*Post: Lista con el ranking y tope_lista con la cantidad de elementos
*/
void obtener_lista(char direc_ranking[], ranking_t lista[], int* tope_lista){
  FILE* archivo_ranking=fopen(direc_ranking, "r");
  if(!archivo_ranking){
    printf("Primera vez en usar el ranking\n");
  }else{
    int tope_aux = *tope_lista;
    int leido=fscanf(archivo_ranking, FORMATO_RANKING, lista[tope_aux].usuario, &lista[tope_aux].puntos);
    while(leido==2){
      tope_aux++;
      leido=fscanf(archivo_ranking, FORMATO_RANKING, lista[tope_aux].usuario, &lista[tope_aux].puntos);
    }
    *tope_lista=tope_aux;
    fclose(archivo_ranking);
  }
}
/*
*Analisis: Añade ordenadmente el nuevo ranking al archivo
*Pre: Rankinga con informacion de usuario (puntos ya calculados y nombre de usuario)
*Post: Archivo de ranking con los nuevos datos
*/
void agregar_en_ranking(char direc_ranking[], ranking_t ranking){
  ranking_t lista[MAX_RANKING];
  int tope_lista=0;
  obtener_lista(direc_ranking, lista, &tope_lista);
  agregar_en_lista(lista, &tope_lista, ranking);
  reescribir_ranking(lista, tope_lista, direc_ranking);
}
/*FUNCIONES configurar_camino_archivo*/
/*
*Analisis: Lee todas las coordenadas de un camino y las guarda en un vector de coordenada_t
*Pre: Abrir el archivo y enviar con el stream ya puesto para leer coordenadas
*Post: vector con todas las coordenadas de un camino y su tope correspondiente
*/
void cargar_vector_camino(FILE* archivo, coordenada_t camino[], int* tope_camino){
  int tope=0;
  int posicion=0;
  int leido=fscanf(archivo, FORMATO_COORDENADA, &(camino[posicion].fil), &(camino[posicion].col));
  while(leido==2){
    posicion++;
    tope++;
    leido=fscanf(archivo, FORMATO_COORDENADA, &(camino[posicion].fil), &(camino[posicion].col));
  }
  *tope_camino=tope;
}
/*
*Analisis: Según el nivel y el camino carga un vector de coordenadas al nivel
*Pre: El camino se debe corresponder al nivel que se pase y el archivo a la direccion donde se encuentren los caminos (en la configuracion)
*Post: Nivel inicializado con el recorrido de un camino
*/
void cargar_camino(FILE* archivo, int nvl, int camino, nivel_t* nivel){
  int nivel_archivo;
  int camino_archivo;
  fscanf(archivo, FORMATO_CREAR_CAMINO, &nivel_archivo, &camino_archivo);
  while((nivel_archivo!=nvl)&&(camino_archivo!=camino)){
    fscanf(archivo, FORMATO_CREAR_CAMINO, &nivel_archivo, &camino_archivo);
  }
  if(camino==CAMINO_1){
    cargar_vector_camino(archivo, nivel->camino_1, &(nivel->tope_camino_1));
  }else if (camino==CAMINO_2){
    cargar_vector_camino(archivo, nivel->camino_2, &(nivel->tope_camino_2));
  }
}
/*FUNCIONES cargar_confirguracion*/
/*
*Analisis: Chequear si el valor pasado es -1, si es así lo reemplaza po el valor por defecto
*Pre: Entero cargado con el valor del archivo y standard con el valor por defecto
*Post: Valor final que pasa a configuracion
*/
void chequear_entero(int* entero, int standard){
  if(*entero==CONFIG_VACIA){
    *entero=standard;
  }
}
/*
*Analisis: Cheaque toda la configuracion pasada por archivo, si hay algun valor -1 lo reemplaza
*Pre: Configuracion con la informacion del archivo y standard con la informacion por defecto
*Post: Configuracion lista para ser pasada al juego
*/
void chequear_configuracion(configuracion_t* configuracion, configuracion_t standard){
  chequear_entero(&(configuracion->torres.resistencia_torre_1), standard.torres.resistencia_torre_1);
  chequear_entero(&(configuracion->torres.resistencia_torre_2), standard.torres.resistencia_torre_2);
  for(int nivel=NIVEL_1; nivel<TOPE_NIVELES; nivel++){
    chequear_entero(&(configuracion->cantidad_enanos[nivel]), standard.cantidad_enanos[nivel]);
  }
  for(int nivel=NIVEL_1; nivel<TOPE_NIVELES; nivel++){
    chequear_entero(&(configuracion->cantidad_elfos[nivel]), standard.cantidad_elfos[nivel]);
  }
  chequear_entero(&(configuracion->torres.enanos_extra), standard.torres.enanos_extra);
  chequear_entero(&(configuracion->torres.elfos_extra), standard.torres.elfos_extra);
  chequear_entero(&(configuracion->costo_G_extra[TORRE_1]), standard.costo_G_extra[TORRE_1]);
  chequear_entero(&(configuracion->costo_G_extra[TORRE_2]), standard.costo_G_extra[TORRE_2]);
  chequear_entero(&(configuracion->costo_L_extra[TORRE_1]), standard.costo_L_extra[TORRE_1]);
  chequear_entero(&(configuracion->costo_L_extra[TORRE_2]), standard.costo_L_extra[TORRE_2]);
  chequear_entero(&(configuracion->fallo_gimli), standard.fallo_gimli);
  chequear_entero(&(configuracion->critico_gimli), standard.critico_gimli);
  chequear_entero(&(configuracion->fallo_legolas), standard.fallo_legolas);
  chequear_entero(&(configuracion->critico_legolas), standard.critico_legolas);
  if (configuracion->velocidad == CONFIG_VACIA){
    configuracion->velocidad = standard.velocidad;
  }
}
/*
*Analisis: Abre un archivo de configuracion, lo lee segun formato y lo pasa por parametro
*Pre: Archivo de la configuracion por defecto o uno pasado por el usuario
*Post: Configuracion cargada con los datos de archivo
*/
void leer_configuracion(FILE* archivo, configuracion_t* config){
  char clave[MAX_CLAVE];
  int leido=fscanf(archivo,FORMATO_CLAVE, clave);
  while(leido==1){
    if (strcmp(clave,CLAVE_TORRES)==0){
      fscanf(archivo,FORMATO_TORRES, &(config->torres.resistencia_torre_1), &(config->torres.resistencia_torre_2));
    }else if (strcmp(clave, CLAVE_G_INICIO)==0){
      fscanf(archivo,FORMATO_INICIO, &(config->cantidad_enanos[NIVEL_1]), &(config->cantidad_enanos[NIVEL_2]), &(config->cantidad_enanos[NIVEL_3]), &(config->cantidad_enanos[NIVEL_4]));
    }else if (strcmp(clave, CLAVE_L_INICIO)==0){
      fscanf(archivo,FORMATO_INICIO, &(config->cantidad_elfos[NIVEL_1]), &(config->cantidad_elfos[NIVEL_2]), &(config->cantidad_elfos[NIVEL_3]), &(config->cantidad_elfos[NIVEL_4]));
    }else if (strcmp(clave, CLAVE_G_EXTRA)==0){
      fscanf(archivo,FORMATO_EXTRA, &(config->torres.enanos_extra), &(config->costo_G_extra[TORRE_1]), &(config->costo_G_extra[TORRE_2]));
    }else if (strcmp(clave, CLAVE_L_EXTRA)==0){
      fscanf(archivo,FORMATO_EXTRA, &(config->torres.elfos_extra), &(config->costo_L_extra[TORRE_1]), &(config->costo_L_extra[TORRE_2]));
    }else if (strcmp(clave, CLAVE_G_ANIMO)==0){
      fscanf(archivo,FORMATO_ANIMO, &(config->fallo_gimli), &(config->critico_gimli));
    }else if (strcmp(clave, CLAVE_L_ANIMO)==0){
      fscanf(archivo,FORMATO_ANIMO, &(config->fallo_legolas), &(config->critico_legolas));
    }else if (strcmp(clave, CLAVE_VELOCIDAD)==0){
      fscanf(archivo,FORMATO_VELOCIDAD, &(config->velocidad));
    }else if (strcmp(clave, CLAVE_CAMINO)==0){
      fscanf(archivo,FORMATO_CAMINO, config->ruta_camino);
      if(atoi(config->ruta_camino)==CONFIG_VACIA){
        (config->hay_caminos)=false;
      }else{
        (config->hay_caminos)=true;
      }
    }
    memset(clave,'\0',MAX_CLAVE);
    leido=fscanf(archivo,FORMATO_CLAVE, clave);
  }
}
/*FUNCIONES comandos*/
/*
*Analisis: Muestra por pantalla los comandos posibles que tiene el usuario para realizar
*Pre: Primer argumento pasado por la consola sea ARG_HELP
*Post: Informacion por pantalla
*/
void mostrar_ayuda(){
  printf("COMANDOS:\n");
  printf(COLOR_CYAN"*  %s\n"COLOR_RESET, ARG_CREAR_CONFIGURACION);
  printf("    <nombre del archivo a crear>    (obligatorio)\n");
  printf(COLOR_CYAN"*  %s \n"COLOR_RESET, ARG_CREAR_CAMINOS);
  printf("    <nombre del archivo a crear>    (obligatorio)\n");
  printf(COLOR_CYAN"*  %s \n"COLOR_RESET, ARG_REPETICION);
  printf("    grabacion=<nombre del archivo de la repeticion>   (obligatorio)\n    velocidad=<numero entero o racional positivo>   (opcional)(1 por defecto)\n");
  printf(COLOR_CYAN"*  %s \n"COLOR_RESET, ARG_RANKING);
  printf("    listar=<cantidad de jugadores para ver>   (opcional)(todos por defecto)\n    config=<nombre de la configuracion>   (opcional)(standard por defecto)\n");
  printf(COLOR_CYAN"*  %s \n"COLOR_RESET, ARG_JUGAR);
  printf("    config=<nombre de la configuracion>   (opcional)(standard por defecto)\n    grabacion=<archivo para guardar la repeticion>   (opcional)(no se graba por defecto)\n");
}
/*
*Analisis: Imprime por pantalla los datos del archivo de ranking
*Pre: Archivo de ranking con informacion(y que exista, sino hay advertencia) y archivo pasado por comandos
*Post: Datos del archivo del raking pasado mostrado por pantalla
*/
void mostra_ranking(char ranking[], int tope){
  char usuario[MAX_USUARIO];
  int puntos;
  FILE* archivo_ranking=fopen(ranking, "r");
  if(!archivo_ranking){
    printf("No se pudo abrir el archivo del ranking. No se jugó con esa configuracion o no exite\n");
  }else{
    if (tope==CONFIG_VACIA){
      int leido=fscanf(archivo_ranking, FORMATO_RANKING, usuario, &puntos);
      while(leido==2){
        printf("%s: %i PTS\n", usuario, puntos);
        leido=fscanf(archivo_ranking, FORMATO_RANKING, usuario, &puntos);
      }
    }else{
      char usuario_aux[MAX_USUARIO];
      for (int jugador = 0; jugador < tope; jugador++){
        fscanf(archivo_ranking, FORMATO_RANKING, usuario, &puntos);
        if(strcmp(usuario, usuario_aux)==0){
          printf("[vacio]\n");
        }else{
          printf("%s: %i PTS\n", usuario, puntos);
          strcpy(usuario_aux, usuario);
        }
      }
    }
    fclose(archivo_ranking);
  }
}
/*
*Analisis: Según los comandos pasados por terminal determina como será el ranking, con su direccion
y la cantidad de jugadores a listar (si es un cantidad limitada)
*Pre: primer argumento==ARG_RANKING
*Post: LISTADO si tiene un tope para la lista, COMPLETO si debe mostrarse completo (tope_lista y direccion del ranking por parametro)
*/
int estado_ranking(char* argv[], char ranking[], int* tope_lista){
  char aux[MAX_ARCHIVO];
  char clave_config[MAX_ARCHIVO];
  char config[MAX_ARCHIVO];
  char clave_lista[MAX_ARCHIVO];
  char lista[MAX_ARCHIVO];
  if (argv[2]==NULL){
    obtener_direc_ranking(ARCHIVO_CONFIG_STANDARD, ranking);
    *(tope_lista) = CONFIG_VACIA;
    return RANKING_COMPLETO;
  }else{
    strcpy(aux,strtok(argv[2], SEPARADOR));
    if(strcmp(aux, "config") == 0){
      strcpy(config, strtok(NULL, SEPARADOR));
      obtener_direc_ranking(config, ranking);
      if (argv[3]==NULL){
        *(tope_lista) = CONFIG_VACIA;
        return RANKING_COMPLETO;
      }else{
        strcpy(clave_lista,strtok(argv[3], SEPARADOR));
        strcpy(lista,strtok(NULL, SEPARADOR));
        *(tope_lista) =atoi(lista);
        return RANKING_LISTADO;
      }
    }else if(strcmp(aux, "listar") == 0){
      strcpy(lista,strtok(NULL, SEPARADOR));
      *(tope_lista) = atoi(lista);
      if (argv[3] == NULL){
        obtener_direc_ranking(ARCHIVO_CONFIG_STANDARD, ranking);
      }else{
        strcpy(clave_config, strtok(argv[3], SEPARADOR));
        strcpy(config, strtok(NULL, SEPARADOR));
        obtener_direc_ranking(config, ranking);
      }
      return RANKING_LISTADO;
    }
  }
  return CONFIG_VACIA;
}
/*
*Analisis:Según los comandos que se pasen muestra diferentes rankings
*Pre: Modo de programa debe ser "ranking"
*Post: Datos del archivo del raking segun la configuracion y listado mostrado por pantalla
*/
void ranking(char* argv[]){
  char ranking[MAX_ARCHIVO];
  int tope_lista = CONFIG_VACIA;
  int modo_ranking=estado_ranking(argv, ranking, &tope_lista);
  if (modo_ranking == RANKING_COMPLETO){
    printf("RANKING de %s COMPLETO \n" , ranking);
  }else if (modo_ranking == RANKING_LISTADO){
    printf("RANKING de %s con %i jugadores \n", ranking, tope_lista);
  }
  mostra_ranking(ranking, tope_lista);
}
/*
*Analisis: Avisa si no puede abrir el archivo, sino lo lee y muestra por pantalla contenido
*Pre: El archivo es el que pasa el usuario por comandos y  el programa está en modo poneme_la_repe
*Post: Repeticion completa por pantalla
*/
void pasar_repeticion(char archivo[], float velocidad){
  FILE* partida=fopen(archivo,"r");
  if(!partida){
    printf("No se pudo abrir el archivo para pasar la repe.\n");
  }else{
    juego_t juego;
    fread(&juego, sizeof(juego_t),1, partida);
    while(!feof(partida)){
      printf("Repeticion a velocidad: %f\n", velocidad);
      mostrar_juego(juego);
      detener_el_tiempo(velocidad);
      system("clear");
      fread(&juego, sizeof(juego_t),1, partida);
    }
    fclose(partida);
  }
}
/*
*Analisis: Avisa si no se ingresó el archivo, y si es asi pasa la repeticion si existe ese archivo
*Pre: El primer argumento por comando debe ser "poneme_la_repe" y el segundo es pasado por el usuario
*Post: Repeticion o Advertencia de un error
*/
void poneme_la_repe(char* argv[]){
  if ((argv[2] == NULL)){
    printf("No se han ingresado los archivos correspondientes...\n");
  }else if (strcmp(strtok(argv[2], SEPARADOR),"grabacion")!=0){
    printf("Recordá que el comando es 'grabacion=', prueba nuevamente...\n");
  }else{
    char repeticion[MAX_ARCHIVO];
    strcpy(repeticion, strtok(NULL, SEPARADOR));
    float velocidad;
    if (argv[3]==NULL){
      velocidad=1;
      pasar_repeticion(repeticion, velocidad);
    }else if (strcmp(strtok(argv[3], SEPARADOR), "velocidad")==0){
      velocidad=(float) atof(strtok(NULL, SEPARADOR));
      pasar_repeticion(repeticion, velocidad);
    }else{
      printf("Estas pasando mal el último comando...\n");
    }
  }
}
/*
*Analisis: Muestra por pantalla el camino ha creado y en el nivel que lo hizo
*Pre: Haber terminado de crear un camino (aviso)
*Post: Informacion por pantalla
*/
void mostrar_camino_creado(int nivel, int camino){
	system("clear");
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n\n\n\n\n\n\n");
	printf("                        -------------------\n");
	printf("                CAMINO %i DEL NIVEL %i CONFIGURADO\n", camino, (nivel+1));
	printf("                        -------------------\n\n\n\n\n\n\n\n\n");
	printf("==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-==-== \n");
	detener_el_tiempo(2);
	system("clear");
}
/*
*Analisis: Escribe en un un archivo todas las coordenadas de un vector camino
*Pre: Tope propio a la cantidad de elementos y archivo previamente abierto y con las claves (n° de nivel y camino) ya escritas
*Post: Camino completo dentro del archivo
*/
void cargar_archivo_camino(FILE* archivo, coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
  for (int i = 0; i < tope_camino; i++) {
    fprintf(archivo, FORMATO_COORDENADA, camino[i].fil, camino[i].col);
  }
}
/*
*Analisis: Escribe en el archivo el número de nivel y de camino que se van escribir posteriormente
*Pre: Archivo previament abierto y nivel y camino que se corresponan al que se creó
*Post: Archivo con las claves escritas
*/
void titular_archivo_camino(FILE* archivo, int nivel, int camino){
  fprintf(archivo, FORMATO_CREAR_CAMINO_ESCRITURA, CLAVE_NIVEL, (nivel+1));
  fprintf(archivo, FORMATO_CREAR_CAMINO_ESCRITURA, CLAVE_CREAR_CAMINO, camino);
}
/*
*Analisis: Evalua si se salió del camino o volvió para atrás
*Pre: nueva_coord ya calculada a partir de la eleccion del usuario y de la coordenada actual,
tope_campo correspondiente al nivel,
 y que se pase la coordenada anterior a la actual (tope-2)
*Post: Verdadero si está dentro del campo y no volvio a la coordenada anterior
*/
bool cumple_condiciones(coordenada_t nueva_coord, coordenada_t coord_anterior, int tope_campo){
  if((nueva_coord.col==coord_anterior.col)&&(nueva_coord.fil==coord_anterior.fil)){
    return false;
  }else if((nueva_coord.col>=tope_campo)||(nueva_coord.fil>=tope_campo)){
    return false;
  }else if((nueva_coord.col<0)||(nueva_coord.fil<0)){
    return false;
  }else{
    return true;
  }
}
/*
*Analisis: Segun la direccion y la columna de la coord actual, se obtiene la nueva columna
*Pre: Pasa la columna de de la coordenada actual (tope-1) y la direccion despues de pedirla al usuario
*Post: Nueva columna
*/
int direccion_columna(char direccion,  int col_anterior){
  if(direccion==IZQ){
    return col_anterior-1;
  }else if(direccion==DER){
    return col_anterior+1;
  }else if(direccion==ARRIBA){
    return col_anterior;
  }else if(direccion==ABAJO){
    return col_anterior;
  }
  return -1;
}
/*
*Analisis: Segun la direccion y la fila de la coord actual, se obtiene la nueva fila
*Pre: Pasa la fila de de la coordenada actual (tope-1) y la direccion despues de pedirla al usuario
*Post: Nueva fila
*/
int direccion_fila(char direccion,  int fil_anterior){
  if(direccion==IZQ){
    return fil_anterior;
  }else if(direccion==DER){
    return fil_anterior;
  }else if(direccion==ARRIBA){
    return fil_anterior-1;
  }else if(direccion==ABAJO){
    return fil_anterior+1;
  }
  return -1;
}
/*
*Analisis: Chequea si la direccion pasada como letro corresponde a alguna de las constantes como direccion
*Pre: direccion pedida al usuario
*Post: Verdadero si es IZQ, DER, ABAJO o ARRIBA(constantes)
*/
bool cumple_direccion(char direccion){
  return((direccion==IZQ)||(direccion==DER)||(direccion==ABAJO)||(direccion==ARRIBA));
}
/*
*Analisis: Pide una direccion, controla que sea alguna de las constates que se asignaron en el programa
y pasa la nueva coordenada según esa direccion
*Pre: La coordenada anterior debe ser la ultima que tiene el vector de camino (tope-1)
*Post: Nueva coordenada para agregar al camino
*/
void pedir_direccion(coordenada_t coord_anterior, coordenada_t* nueva_coord){
  char direccion;
  printf("DIRECCION:");
  scanf(" %c", &direccion);
  while(!cumple_direccion(direccion)){
    printf("DIRECCION ERRONEA (Recordá: wasd!)\n");
    printf("DIRECCION:");
    scanf(" %c", &direccion);
  }
  nueva_coord->fil=direccion_fila(direccion, coord_anterior.fil);
  nueva_coord->col=direccion_columna(direccion, coord_anterior.col);
}
/*
*Analisis: Pide el nuevo tramo del camino a partir de una direccion que pone el usuario
mientras cumpla las condiciones (Sin volver para atras y sin salir del campo)
*Pre: Tope_campor correspondiente al nivel y vector camino pertenecientea un nivel_t
*Post: Nueva coordenada dentro del vector y el valor correspondiente del tope_camino
*/
void pedir_nuevo_tramo(coordenada_t camino[], int* tope_camino, int tope_campo){
  coordenada_t coord_aux;
  coordenada_t coord_anterior;
  coord_anterior.fil=camino[*tope_camino-1].fil;
  coord_anterior.col=camino[*tope_camino-1].col;
  pedir_direccion(coord_anterior, &coord_aux);
  while (((*tope_camino)>1)&&(!cumple_condiciones(coord_aux, camino[*tope_camino-2], tope_campo))){
    printf("VOLVISTE PARA ATRAS o SALISTE DEL MAPA!!\n");
    pedir_direccion(coord_anterior, &coord_aux);
  }
  camino[*tope_camino].fil=coord_aux.fil;
  camino[*tope_camino].col=coord_aux.col;
  (*tope_camino)=(*tope_camino + 1);
}
/*
*Analisis: Chequea si el camino está termminado según la última coordenada del camino,
y cual debe ser la col/fil de la torre segun  qué tipo de camino es
*Pre: ultima_coord correspondiente al ultimo valor del vector, modo de camino ya calculado y por ende el limite (según extension del campo)
*Post: Verdadero si el camino ya termino y debe ser torre la ultima coordenada
*/
bool camino_terminado(coordenada_t ultima_coord, int modo_camino, int limite){
  if(modo_camino==HORIZONTAL){
    return((ultima_coord.col) == limite);
  }else if(modo_camino==VERTICAL){
    return((ultima_coord.fil) == limite);
  }else{
    return SIN_DEFINIR;
  }
}
/*
*Analisis: Según donde se ubica la entrada y la extension del campo determina que tipo de camino es  (HORIZONTAL o VERTICAL)
*Pre: entrada ya pedida al usuario (no puede ser vertice ni perteneciente al campo) y tope_campo correspondiente al nivel
*Post: Tipo de camino (por constante) y límite del campo (donde se debe ubicar la torre)(contraria a la entrada)
*/
int modo_camino(coordenada_t entrada, int tope_campo, int* limite){
	if(entrada.col==0){
		*limite=(tope_campo-1);
		return HORIZONTAL;
	}else if (entrada.col==(tope_campo-1)){
		*limite=0;
		return HORIZONTAL;
	}else if (entrada.fil==0){
		*limite=(tope_campo-1);
		return VERTICAL;
	}else if (entrada.fil==(tope_campo-1)){
		*limite=0;
		return VERTICAL;
	}else{
		return SIN_DEFINIR;
	}
}
/*
*Analisis: Evalua si la fila columna es un margen del campo segun su tope
*Pre: tope propio de camnpo
*Post: verdadero si se encuentra en una fila o columna límite
*/
bool es_margen(int fila, int columna, int tope){
  if((fila==0)||(fila==(tope-1))||(columna==0)||(columna==(tope-1))){
    return true;
  }else{
    return false;
  }
}
/*
*Analisis: Evalua si la fila columna es vertice del campo segun su tope
*Pre:  tope propio de camnpo
*Post: verdadero si se encuentra en una fila y columna de los vértices
*/
bool es_vertice(int fila, int columna, int tope){
  if((fila==0)&&(columna==0)){
    return true;
  }else if((fila==0)&&(columna==(tope-1))){
    return true;
  }else if((fila==(tope-1))&&(columna==0)){
    return true;
  }else if((fila==(tope-1))&&(columna==(tope-1))){
    return true;
  }else{
    return false;
  }
}
/*
*Analisis: Pide por consala un coordenada
*Pre: -
*Post: coord con un valor de fil y col
*/
void pedir_coordenada(coordenada_t* coord){
  printf("FILA:");
  scanf("%i", &(coord->fil));
  printf("COLUMNA:");
  scanf("%i", &(coord->col));
}
/*
*Analisis: Asigna la primer coordenada del camino que estará en alguno de los margenes (sin estar en un vértice)
*Pre: camino que se va a crear y tope_campo propio del nivel del camino
*Post: coordenada de entrada que sea del márgen del campo y no un vértice del mismo
*/
void pedir_entrada(coordenada_t camino[], int* tope_camino, int tope_campo){
  coordenada_t coord_aux;
  printf("Asignar la ENTRADA: \n");
  pedir_coordenada(&coord_aux);
  while (es_vertice(coord_aux.fil, coord_aux.col, tope_campo)||(!es_margen(coord_aux.fil, coord_aux.col, tope_campo))){
    printf("HA PUESTO LA ENTRADA EN UN VERTICE, DENTRO DEL CAMPO o FUERA DE ÉL, INGRESE NUEVAMENTE: \n");
    pedir_coordenada(&coord_aux);
  }
  camino[*tope_camino].fil=coord_aux.fil;
  camino[*tope_camino].col=coord_aux.col;
  *(tope_camino)=1;
  printf("ENTRADA=(%i;%i)\n", camino[*tope_camino-1].fil, camino[*tope_camino-1].col);
}
/*
*Analisis: Muestra por pantalla un ayuda para saber las columnas del campo
*Pre: tope_campo del nivel donde se carga el camino
*Post: Informacion por pantalla
*/
void imprimir_margen(int tope_campo){
  for (int i = 0; i < tope_campo; i++) {
    if(i==0){
      printf("____0%i|", i);
    }else if (i<10){
      printf("0%i|", i);
    }else if(i==tope_campo-1){
      printf("%i|____\n", i);
    }else{
      printf("%i|", i);
    }
  }
}
/*
*Analisis: Asigna dentro del campo la entrada, la torre, y el trayecto del camino con constantes (letras)
*Pre: tope_camino que corresponda a la cantidad de coordenadas del camino
*Post: Campo con su camino marcado
*/
void asignar_camino(char campo[MAX_CAMPO][MAX_CAMPO], coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
  for (int i=0; i<tope_camino; i++){
    if (i == 0)
    campo[camino[i].fil][camino[i].col]= COMIENZO;
    else if(i == (tope_camino) - 1)
    campo[camino[i].fil][camino[i].col]= FINAL;
    else
    campo[camino[i].fil][camino[i].col]= CAMINITO;
  }
}
/*
*Analisis: Rellana el campo y egún el tipo de camino determina sus lugares prohibidos (para asignar la entrada)
o los lugares donde puede ir la torre (LIMITE)
*Pre: tope_campo corresponda al máximo de sus coordenadas, modo camino distinto a HORIZONTAL o VERTICAL si no está configurando los nuevos tramos
*Post: Campo inicializado con sus valores fuera del camino
*/
void inicializar_campo(char campo[MAX_CAMPO][MAX_CAMPO], int tope_campo, int modo_camino, int limite){
  for (int i=0; i<tope_campo; i++){
    for (int j = 0; j < tope_campo; j++) {
      if(modo_camino==HORIZONTAL){
        if(j==limite){
          campo[i][j]=LIMITE;
        }else{
          campo[i][j]=CAMPO;
        }
      }else if(modo_camino==VERTICAL){
        if(i==limite){
          campo[i][j]=LIMITE;
        }else{
          campo[i][j]=CAMPO;
        }
      }else{
        if (es_vertice(i, j, tope_campo)||(!es_margen(i, j, tope_campo))){
          campo[i][j]=PROHIBIDO;
        }else{
          campo[i][j]=CAMPO;
        }
      }
    }
  }
}
/*
*Analisis: Muestra el campo con el camino
*Pre: tope_campo corresponda al máximo de sus coordenadas
*Post: Campo con el camino por pantalla
*/
void mostrar_caminos(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino,  int tope_campo, int modo_camino, int limite){
  char campo[MAX_CAMPO][MAX_CAMPO];
  inicializar_campo(campo, tope_campo, modo_camino, limite);
  asignar_camino(campo, camino, tope_camino);
  imprimir_margen(tope_campo);
  for (int i=0; i < tope_campo; i++){
    if (i>=10)
    printf(" %i|", i);
    else
    printf(" 0%i|", i);
    for (int j=0; j < tope_campo; j++){
      if(campo[i][j]==PROHIBIDO){
        printf(COLOR_ROJO " %c " COLOR_RESET, campo[i][j]);
      }else if(campo[i][j]==LIMITE){
        printf(COLOR_VERDE " %c " COLOR_RESET, campo[i][j]);
      }else{
        printf(" %c ", campo[i][j]);
      }
    }
    if (i>=10)
    printf(" %i|", i);
    else
    printf(" 0%i|", i);
    printf("\n");
  }
  imprimir_margen(tope_campo);
}
/*
*Analisis: Informa al usuario las caracteristicas del camino que va a configurar
*Pre: Parametros correspondientes al camino por configurar
*Post: Informacion mostrada por pantalla
*/
void titular_el_campo(int nivel, int n_camino, int forma_camino){
		printf("NIVEL: %i         CAMINO: %i\n", (nivel+1), n_camino);
		if (forma_camino==HORIZONTAL){
			printf("%s\n", "HORIZONTAL");
		}else if (forma_camino==VERTICAL){
			printf("%s\n", "VERTICAL");
		}else{
      	printf("SIN DEFINIR\n");
    }
}
/*
*Analisis: Pide todos los datos del camino y los escribe en el archivo pasado por parametro
*Pre: tope_campo y n_camino correspondiente al nivel, archivo ya abierto y que sea el pasado por consola
*Post: Archivo cargado con un solo camino
*/
void pedir_camino(FILE* archivo, int nivel, int n_camino, int tope_campo){
		coordenada_t camino[MAX_LONGITUD_CAMINO];
		int tope_camino=0;
		int limite=SIN_DEFINIR;
		int forma_camino=SIN_DEFINIR;
		titular_el_campo(nivel, n_camino, forma_camino);
    mostrar_caminos(camino, tope_camino, tope_campo, forma_camino, limite);
    pedir_entrada(camino, &tope_camino, tope_campo);
		detener_el_tiempo(1.5);
		system("clear");
		forma_camino=modo_camino(camino[0], tope_campo, &limite);
    while (!camino_terminado((camino[tope_camino-1]), forma_camino, limite)){
			titular_el_campo(nivel, n_camino, forma_camino);
      mostrar_caminos(camino, tope_camino, tope_campo, forma_camino, limite);
      pedir_nuevo_tramo(camino, &tope_camino, tope_campo);
      system("clear");
    }
		titular_archivo_camino(archivo, nivel, n_camino);
    cargar_archivo_camino(archivo, camino, tope_camino);
}
/*
*Analisis: Segun el argumento pasado por el usuario, escribe (por la interaccion del usuario) toda la informacion de los caminos.
*Pre: Primer argumento pasado por consola "crear_caminos" (estado_programa==CREAR_CAMINOS)
*Post: Archivo de caminos pasado por consola escrito con todas las coordenadas de los caminos
*/
void crear_caminos(char* argv[]){
  if (argv[2] == NULL){
    printf("No se han ingresado los archivos correspondientes...\n");
  }else{
    FILE*archivo_camino=fopen(argv[2], "w");
    if(!archivo_camino){
      printf("No se pudo abrir el archivo_camino\n");
    }else{
      for (int nivel = NIVEL_1; nivel < MAX_NIVELES; nivel++) {
        system("clear");
        printf("Advertencia: Las ENTRADAS se ubican en los MÁRGENES y las TORRES en el lado OPUESTO a la entrada\n");
        printf("HERRAMIENTAS: 'wasd'(en minuscula) para mover el camino\n");
        if(nivel==NIVEL_1){
          pedir_camino(archivo_camino, nivel, CAMINO_1, TOPE_CAMPO_1);
          mostrar_camino_creado(nivel, CAMINO_1);
        }else if(nivel==NIVEL_2){
          pedir_camino(archivo_camino, nivel, CAMINO_2, TOPE_CAMPO_1);
          mostrar_camino_creado(nivel, CAMINO_2);
        }else if ((nivel==NIVEL_3)||(nivel==NIVEL_4)){
          pedir_camino(archivo_camino, nivel, CAMINO_1, TOPE_CAMPO_2);
          mostrar_camino_creado(nivel, CAMINO_1);
          pedir_camino(archivo_camino, nivel, CAMINO_2, TOPE_CAMPO_2);
          mostrar_camino_creado(nivel, CAMINO_2);
        }
      }
      fclose(archivo_camino);
    }
  }
}
/*
*Analisis: Pide y guardad la salud de las torres
*Pre: El archivo debe ser el mismo que pasa el usuario por crear_configuracion
*Post: Archivo con la resistencia de las torres escrita
*/
void asignar_torres_config(FILE* archivo){
  int torre_1;
  int torre_2;
  printf("%s\n", CLAVE_TORRES);
  fprintf(archivo, FORMATO_CLAVE_ESCRITURA , CLAVE_TORRES);
  printf("TORRE 1:");
  scanf("%i", &torre_1);
  printf("TORRE 2:");
  scanf("%i", &torre_2);
  fprintf(archivo, FORMATO_TORRES, torre_1, torre_2);
  system("clear");
}
/*
*Analisis: Pide y guardad la cantidad de defensores por nivel segun la clave
*Pre: El archivo debe ser el mismo que pasa el usuario por crear_configuracion
*Post: Archivo con uno de las canidades de defensores escritos
*/
void asignar_defesores_config(FILE* archivo, char clave[]){
  int cantidad[MAX_NIVELES];
  printf("%s\n", clave);
  fprintf(archivo, FORMATO_CLAVE_ESCRITURA, clave);
  for (int nivel = NIVEL_1; nivel < MAX_NIVELES; nivel++) {
    printf("Nivel %i:", nivel+1);
    scanf("%i", &cantidad[nivel]);
  }
  fprintf(archivo, FORMATO_INICIO, cantidad[NIVEL_1], cantidad[NIVEL_2], cantidad[NIVEL_3], cantidad[NIVEL_4]);
  system("clear");
}
/*
*Analisis: Pide y guardad la cantidad de defensores extra y sus costos a la torre segun la clave
*Pre: El archivo debe ser el mismo que pasa el usuario por crear_configuracion
*Post: Archivo con uno de los extra escritos
*/
void asignar_extra_config(FILE* archivo, char clave[]){
  int cant_extra;
  int costo_torre_1;
  int costo_torre_2;
  printf("%s\n", clave);
  fprintf(archivo, FORMATO_CLAVE_ESCRITURA , clave);
  printf("Cantidad de defensores :");
  scanf("%i", &cant_extra);
  printf("Costo TORRE 1:");
  scanf("%i", &costo_torre_1);
  printf("Costo TORRE 2:");
  scanf("%i", &costo_torre_2);
  fprintf(archivo, FORMATO_EXTRA, cant_extra, costo_torre_1, costo_torre_2);
  system("clear");
}
/*
*Analisis: Pide y guardad el fallo y el critico segun la clave
*Pre: El archivo debe ser el mismo que pasa el usuario por crear_configuracion
*Post: Archivo con uno de los animos escritos
*/
void asignar_animo_config(FILE* archivo, char clave[]){
  int critico;
  int fallo;
  printf("%s\n", clave);
  fprintf(archivo, FORMATO_CLAVE_ESCRITURA , clave);
  printf("Fallo:");
  scanf("%i", &fallo);
  printf("Crítico:");
  scanf("%i", &critico);
  fprintf(archivo, FORMATO_ANIMO, fallo, critico);
  system("clear");
}
/*
*Analisis: Pide y guardad la velocidad
*Pre: El archivo debe ser el mismo que pasa el usuario por crear_configuracion
*Post: Archivo con la velocidad escrita
*/
void asignar_velocidad_config(FILE* archivo){
  float velocidad;
  printf("%s\n", CLAVE_VELOCIDAD);
  fprintf(archivo, FORMATO_CLAVE_ESCRITURA , CLAVE_VELOCIDAD);
  printf("Velocidad (segundos):");
  scanf("%f", &velocidad);
  fprintf(archivo, FORMATO_VELOCIDAD, velocidad);
  system("clear");
}
/*
*Analisis: Pide y guardad la ruta del camino
*Pre: El archivo debe ser el mismo que pasa el usuario por crear_configuracion
*Post: Archivo con la ruta del camino escrita
*/
void asignar_caminos_config(FILE* archivo){
  char ruta_camino[MAX_DIRECCION];
  printf("%s\n", CLAVE_CAMINO);
  fprintf(archivo, FORMATO_CLAVE_ESCRITURA , CLAVE_CAMINO);
  printf("Ruta del camino personalizado (-1 si no tiene uno):");
  scanf(" %[^\n]", ruta_camino);
  fprintf(archivo, FORMATO_CAMINO, ruta_camino);
  system("clear");
}
/*
*Analisis: Avisa si no se puede abrir el archivo, sino interactua con el usuario para crear_configuracion
*Pre: El primer argumento por comando debe ser "crear_configuracion" y el segundo es pasado por el usuario
*Post: Archivo creado con informacion pedida o advertencia.
*/
void crear_configuracion(char* argv[]){
  if (argv[2] != NULL){
    FILE* archivo_config=fopen(argv[2], "w");
    if(!archivo_config){
      printf("No se pudo abrir la configuracion propia\n");
    }else{
      printf("Advertencia: Si no quiere configurar alguna de las opciones ingrese '-1'...\n");
      asignar_torres_config(archivo_config);
      asignar_defesores_config(archivo_config, CLAVE_G_INICIO);
      asignar_defesores_config(archivo_config, CLAVE_L_INICIO);
      asignar_extra_config(archivo_config, CLAVE_G_EXTRA);
      asignar_extra_config(archivo_config, CLAVE_L_EXTRA);
      asignar_animo_config(archivo_config, CLAVE_G_ANIMO);
      asignar_animo_config(archivo_config, CLAVE_L_ANIMO);
      asignar_velocidad_config(archivo_config);
      asignar_caminos_config(archivo_config);
    }
  }else{
    printf("No se han ingresado los archivos correspondientes...\n");
  }
}
/*FUNCIONES PÚBLICAS*/
void calcular_puntaje(juego_t juego, configuracion_t config, ranking_t* ranking){
  int torre_1=config.torres.resistencia_torre_1;
  int torre_2=config.torres.resistencia_torre_2;
  int enanos_extra=config.torres.enanos_extra;
  int elfos_extra=config.torres.elfos_extra;
  int enanos_inicio=(config.cantidad_enanos[NIVEL_1]+config.cantidad_enanos[NIVEL_2]+config.cantidad_enanos[NIVEL_3]+config.cantidad_enanos[NIVEL_4]);
  int elfos_inicio=((config.cantidad_elfos[NIVEL_1]+config.cantidad_elfos[NIVEL_2]+config.cantidad_elfos[NIVEL_3]+config.cantidad_elfos[NIVEL_4]));
  int denominador=(torre_1+torre_2+enanos_extra+elfos_extra+enanos_inicio+elfos_inicio);
  calcular_orcos_muertos(juego, &(ranking->orcos_muertos));
  ranking->puntos=(((ranking->orcos_muertos)*(MULTIPLICADOR))/(denominador));
}
void actualizar_ranking(juego_t juego, ranking_t ranking, char config[]){
  char direc_ranking[MAX_DIRECCION];
  obtener_direc_ranking(config, direc_ranking);
  agregar_en_ranking(direc_ranking, ranking);
}
void guardar_partida(juego_t juego, char grabacion[]){
  FILE* partida_guardada=fopen(grabacion, "a");
  if(!partida_guardada){
    printf("No se pudo abrir el archivo para grabar la partida.\n");
  }else{
    fwrite(&juego, sizeof(juego_t), 1, partida_guardada);
    fclose(partida_guardada);
  }
}
void configurar_camino_archivo(int nvl, nivel_t* nivel, configuracion_t configuracion){
  FILE* archivo_camino=fopen(configuracion.ruta_camino, "r");
  if(!archivo_camino){
    printf("No se pudo abrir el archivo_camino\n");
  }else{
  	if (nvl==NIVEL_1){
  		cargar_camino(archivo_camino, nvl, CAMINO_1, nivel);
  	}else if (nvl==NIVEL_2){
  		cargar_camino(archivo_camino, nvl, CAMINO_2, nivel);
  	}else if ((nvl==NIVEL_3)||(nvl==NIVEL_4)){
  		cargar_camino(archivo_camino, nvl, CAMINO_1, nivel);
  		cargar_camino(archivo_camino, nvl, CAMINO_2, nivel);
    }
  }
}
void cargar_confirguracion (configuracion_t* configuracion, int modo, char nombre_archivo[]){
    configuracion_t config_std;
    FILE*archivo_config_std=fopen("configuracion_standard.txt", "r");
    if(!archivo_config_std){
      printf("No se pudo abrir la configuracion\n");
    }else{
      leer_configuracion(archivo_config_std, &config_std);
      fclose(archivo_config_std);
    }
  if((modo == STANDARD_GRABANDO)||(modo == STANDARD_SIN_GRABAR)){
    *configuracion=config_std;
  }else if((modo == CUSTOM_GRABANDO)||(modo == CUSTOM_SIN_GRABAR)){
    FILE*archivo_config=fopen(nombre_archivo, "r");
    if(!archivo_config){
      printf("No se pudo abrir la configuracion propia\n");
    }else{
      leer_configuracion(archivo_config, configuracion);
      chequear_configuracion(configuracion, config_std);
      fclose(archivo_config);
    }
  }
}
int modo_juego(char* argv[], char config[], char grabacion[]){
  char arg_2[MAX_ARCHIVO];
  char arg_3[MAX_ARCHIVO];
  if(argv[2]!=NULL){
    strcpy(arg_2,strtok(argv[2], SEPARADOR));
    if(strcmp(arg_2,"config")==0){
      strcpy(config,strtok(NULL, SEPARADOR));
      if (argv[3]==NULL){
        strcpy(grabacion, "NO HAY GRABACION");
        return CUSTOM_SIN_GRABAR;
      }else{
        strcpy(arg_3,strtok(argv[3], SEPARADOR));
        strcpy(grabacion, strtok(NULL, SEPARADOR));
        return CUSTOM_GRABANDO;
      }
    }else if(strcmp(arg_2,"grabacion") == 0){
      strcpy(grabacion, strtok(NULL, SEPARADOR));
      if (argv[3]==NULL){
        strcpy(config, ARCHIVO_CONFIG_STANDARD);
        return STANDARD_GRABANDO;
      }else{
        strcpy(arg_3,strtok(argv[3], SEPARADOR));
        strcpy(config,strtok(NULL, SEPARADOR));
        return CUSTOM_GRABANDO;
      }
    }
  }
  strcpy(config,"configuracion_standard.txt");
  strcpy(grabacion, "NO HAY GRABACION");
  return STANDARD_SIN_GRABAR;
}
int estado_programa(char argumento[]){
  if(strcmp(argumento, ARG_JUGAR)==0){
    return JUGAR;
  }else if(strcmp(argumento, ARG_CREAR_CONFIGURACION)==0){
    return CREAR_CONFIGURACION;
  }else if(strcmp(argumento, ARG_CREAR_CAMINOS)==0){
    return CREAR_CAMINOS;
  }else if(strcmp(argumento, ARG_REPETICION)==0){
    return REPETICION;
  }else if(strcmp(argumento, ARG_RANKING)==0){
    return RANKING;
  }else if(strcmp(argumento, ARG_HELP)==0){
    return HELP;
  }else{
    return ERROR;
  }

}
void comandos(int programa, char* argv[]){
  if(programa == CREAR_CONFIGURACION){
    crear_configuracion(argv);
  }else if (programa == CREAR_CAMINOS){
    crear_caminos(argv);
  }else if (programa == REPETICION){
    poneme_la_repe(argv);
  }else if (programa == RANKING){
    ranking(argv);
  }else if (programa == HELP){
    mostrar_ayuda();
  }
}
