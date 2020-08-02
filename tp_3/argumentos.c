#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "defendiendo_torres.h"
#include "utiles.h"

#define MAX_SEPARADOR 2
#define MAX_ARCHIVO 50
#define MAX_CLAVE 50
#define MAX_DIRECCION 50
#define MAX_LONGITUD_CAMINO 200

#define FORMATO_CLAVE "%[^=]"
#define FORMATO_CLAVE_ESCRITURA "%s"
#define FORMATO_TORRES "=%i;%i\n"
#define FORMATO_INICIO "=%i;%i;%i;%i\n"
#define FORMATO_EXTRA "=%i;%i;%i\n"
#define FORMATO_ANIMO "=%i;%i\n"
#define FORMATO_VELOCIDAD "=%f\n"
#define FORMATO_CAMINO "=%s\n"
#define FORMATO_CREAR_CAMINO "=%i\n"
#define FORMATO_NIVEL "=%i\n"
#define FORMATO_COORDENADA "%i;%i\n"
#define FORMATO_RANKING "%s;%i\n"

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

#define NIVEL_1 0
#define NIVEL_2 1
#define NIVEL_3 2
#define NIVEL_4 3
#define TORRE_1 0
#define TORRE_2 1
#define TOPE_CAMPO_1 15
#define TOPE_CAMPO_2 20

const int JUGAR=0;
const int CREAR_CONFIGURACION=1;
const int CREAR_CAMINOS=2;
const int REPETICION=3;
const int RANKING=4;
const int ERROR=-1;
const int STANDARD_SIN_GRABAR=0;
const int STANDARD_GRABANDO=1;
const int CUSTOM_SIN_GRABAR=2;
const int CUSTOM_GRABANDO=3;
const int TOPE_NIVELES=4;
const int CONFIG_VACIA=-1;
const int CAMINO_1=1;
const int CAMINO_2=2;
const char SEPARADOR[MAX_SEPARADOR]= "=";
const char IZQ= 'a';
const char DER= 'd';
const char ARRIBA= 'w';
const char ABAJO= 's';

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
    configuracion->velocidad=standard.velocidad;
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
        (config->es_aleatoreo)=false;
      }else{
        (config->es_aleatoreo)=true;
      }
    }
    memset(clave,'\0',MAX_CLAVE);
    leido=fscanf(archivo,FORMATO_CLAVE, clave);
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
}/*
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
      fclose(archivo_config);
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
/*
*NO TERMINADA
*Analisis: Lee el archivo de caminos y lo pasa al nivel que corresponde
*/
void cargar_camino(FILE* archivo, int nvl, int camino, nivel_t* nivel){
}
/*
*NO TERMINADA
*Analisis: Pide el valor de la fila de la entrada. columna fija
*/
void pedir_entrada(coordenada_t* entrada){
  entrada->col=0;
  printf("Asignar fila de la ENTRADA: \n");
  scanf("%i", &(entrada->fil) );
  printf("ENTRADA=(%i;%i)\n", entrada->fil, entrada->col );

}
/*
*NO TERMINADA
*Analisis: Pide una coordenad nueva a partir de la anterior.
*/
void pedir_coorndenada(coordenada_t camino[], int* tope_camino){
    char direccion;
    coordenada_t coord_aux;
    direccion = getchar();
    if(direccion==IZQ){
      coord_aux.fil=camino[*tope_camino-1].fil;
      coord_aux.col=camino[*tope_camino-1].col-1;
    }else if(direccion==DER){
      coord_aux.fil=camino[*tope_camino-1].fil;
      coord_aux.col=camino[*tope_camino-1].col+1;
    }else if(direccion==ARRIBA){
      coord_aux.fil=camino[*tope_camino-1].fil-1;
      coord_aux.col=camino[*tope_camino-1].col;
    }else if(direccion==ABAJO){
      coord_aux.fil=camino[*tope_camino-1].fil+1;
      coord_aux.col=camino[*tope_camino-1].col;
    }
    if ((*tope_camino=!1)&&(coord_aux.fil==camino[*tope_camino-2].fil)&&(coord_aux.col==camino[*tope_camino-2].col)){
      while((coord_aux.fil==camino[*tope_camino-2].fil)&&(coord_aux.col==camino[*tope_camino-2].col)){
        printf("VOLVISTE PARA ATRAS!!\n");
        direccion = getchar();
        if(direccion==IZQ){
          coord_aux.fil=camino[*tope_camino-1].fil;
          coord_aux.col=camino[*tope_camino-1].col-1;
        }else if(direccion==DER){
          coord_aux.fil=camino[*tope_camino-1].fil;
          coord_aux.col=camino[*tope_camino-1].col+1;
        }else if(direccion==ARRIBA){
          coord_aux.fil=camino[*tope_camino-1].fil-1;
          coord_aux.col=camino[*tope_camino-1].col;
        }else if(direccion==ABAJO){
          coord_aux.fil=camino[*tope_camino-1].fil+1;
          coord_aux.col=camino[*tope_camino-1].col;
        }
      }
    }else{
      camino[*tope_camino]=coord_aux;
      *tope_camino++;
    }
}
/*
*NO TERMINADA
*Analisis: Escribe un camino completo al archivo
*/
void asignar_camino(FILE* archivo, int nivel, int camino, juego_t* juego,  int tope_campo){
  fprintf(archivo, FORMATO_CLAVE_ESCRITURA, CLAVE_NIVEL);
  fprintf(archivo, FORMATO_NIVEL, nivel);
  fprintf(archivo, FORMATO_CLAVE_ESCRITURA, CLAVE_CREAR_CAMINO);
  fprintf(archivo, FORMATO_NIVEL, camino);
  if(camino==CAMINO_1){
    juego->nivel.tope_camino_1=1;
    pedir_entrada(&juego->nivel.camino_1[0]);
    while ((juego->nivel.camino_1[juego->nivel.tope_camino_1].col)=!(juego->nivel.tope_camino_1)){
      mostrar_juego(*juego);
      pedir_coorndenada(juego->nivel.camino_1, &juego->nivel.tope_camino_1);
      system("clear");
    }
    for (int i = 0; i < juego->nivel.tope_camino_1; i++) {
      fprintf(archivo, FORMATO_COORDENADA, juego->nivel.camino_1[i].fil, juego->nivel.camino_1[i].col);
    }
  }else if (camino==CAMINO_2) {
    juego->nivel.tope_camino_2=1;
    pedir_entrada(&juego->nivel.camino_2[0]);
    while ((juego->nivel.camino_2[juego->nivel.tope_camino_2].col)=!(juego->nivel.tope_camino_2)){
      mostrar_juego(*juego);
      pedir_coorndenada(juego->nivel.camino_2, &juego->nivel.tope_camino_2);
      system("clear");
    }
    for (int i = 0; i < juego->nivel.tope_camino_2; i++) {
      fprintf(archivo, FORMATO_COORDENADA, juego->nivel.camino_2[i].fil, juego->nivel.camino_2[i].col);
    }
  }
}
/*
*NO TERMINADA
*Analisis: Segun el argumento pasado por el usuario, escribe toda la informacion de los caminos.
*/
void crear_caminos(char* argv[]){
  if (argv[2] == NULL){
    printf("No se han ingresado los archivos correspondientes...\n");
  }else{
    FILE*archivo_camino=fopen(argv[2], "w");
    if(!archivo_camino){
      printf("No se pudo abrir el archivo_camino\n");
      fclose(archivo_camino);
    }else{
      printf("Advertencia: Las ENTRADAS de los caminos se ubican en la COLUMNA 0 y las TORRES se ubicaran en la ÚLTIMA COLUMNA\n");
      printf("HERRAMIENTAS: 'wasd'(en minuscula) para mover el camino\n");
      for (int nivel = NIVEL_1; nivel < MAX_NIVELES; nivel++) {
        juego_t juego_aux;
        juego_aux.nivel_actual=nivel;
        if(nivel==NIVEL_1){
          pedir_camino(archivo_camino, juego_aux, TOPE_CAMPO_1);
        }
      }
    }
  }
}
/*
*Analisis: Avisa si no puede abrir el archivo, sino lo lee y muestra por pantalla contenido
*Pre: EL archivo es el que pasa el usuario por comandos y  el programa está en modo poneme_la_repe
*Post: Repeticion completa por pantalla
*/
void pasar_repeticion(char archivo[], float velocidad){
  FILE* partida=fopen(archivo,"r");
  if(!partida){
    printf("No se pudo abrir el archivo para pasar la repe.\n");
    fclose(partida);
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
    printf("Recuerda que el comando es 'grabacion=', prueba nuevamente...\n");
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
*NO TERMINADA
*Analisis: Imprime por pantalla los datos del archivo de ranking
*/
void poner_ranking(char* argv[]){
  if (argv[2]==NULL){
    printf("RANKING COMPLETO\n");
  }else{
    char arg_2[MAX_ARCHIVO];
    char arg_2_valor[MAX_ARCHIVO];
    char arg_3[MAX_ARCHIVO];
    char arg_3_valor[MAX_ARCHIVO];
    strcpy(arg_2,strtok(argv[2], SEPARADOR));
    strcpy(arg_2_valor,strtok(NULL, SEPARADOR));
    if(strcmp(arg_2,"config")==0){
      if (argv[3]==NULL){
        printf("RANKING de %s COMPLETO \n" , arg_2_valor);
      }else{
        strcpy(arg_3,strtok(argv[3], SEPARADOR));
        strcpy(arg_3_valor,strtok(NULL, SEPARADOR));
        int tope_lista=atoi(arg_3_valor);
        printf("RANKING de %s con %i jugadores \n", arg_2_valor, tope_lista);
      }
    }else if(strcmp(arg_2,"listar") == 0){
      int tope_lista=atoi(arg_2_valor);
      if (argv[3]==NULL){
        printf("RANKING de config_standard con %i jugadores \n", tope_lista);
      }else{
        strcpy(arg_3,strtok(argv[3], SEPARADOR));
        strcpy(arg_3_valor,strtok(NULL, SEPARADOR));
        printf("RANKING de %s con  %i jugadores \n", arg_3_valor, tope_lista);
      }
    }
  }
}
void actualizar_ranking(juego_t juego){
}
void configurar_camino_archivo(int nvl, nivel_t* nivel, configuracion_t configuracion){
  FILE* archivo_camino=fopen(configuracion.ruta_camino, "r");
  if(!archivo_camino){
    printf("No se pudo abrir el archivo_camino\n");
    fclose(archivo_camino);
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
bool estan_los_archivos(int programa, char argumento[]){
  if (programa==CREAR_CONFIGURACION){
    if (argumento == NULL)
      return false;
    else
      return true;
  }else if (programa==CREAR_CAMINOS){
    if (argumento == NULL)
      return false;
    else
      return true;
  }else if(programa==REPETICION){
    if (argumento == NULL){
      return false;
    }else
      return true;
  }else{
    return false;
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
        strcpy(config,"configuracion_standard.txt");
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
  if(strcmp(argumento,"jugar")==0){
    return JUGAR;
  }else if(strcmp(argumento,"crear_configuracion")==0){
    return CREAR_CONFIGURACION;
  }else if(strcmp(argumento,"crear_caminos")==0){
    return CREAR_CAMINOS;
  }else if(strcmp(argumento,"poneme_la_repe")==0){
    return REPETICION;
  }else if(strcmp(argumento,"ranking")==0){
    return RANKING;
  }else{
    return ERROR;
  }

}
void guardar_partida(juego_t juego, char grabacion[]){
  FILE* partida_guardada=fopen(grabacion, "a");
  if(!partida_guardada){
    printf("No se pudo abrir el archivo para grabar la partida.\n");
    fclose(partida_guardada);
  }else{
    fwrite(&juego, sizeof(juego_t), 1, partida_guardada);
    fclose(partida_guardada);
  }
}
void cargar_confirguracion (configuracion_t* configuracion, int modo, char nombre_archivo[]){
    configuracion_t config_std;
    FILE*archivo_config_std=fopen("configuracion_standard.txt", "r");
    if(!archivo_config_std){
      printf("No se pudo abrir la configuracion\n");
      fclose(archivo_config_std);
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
      fclose(archivo_config);
    }else{
      leer_configuracion(archivo_config, configuracion);
      chequear_configuracion(configuracion, config_std);
      fclose(archivo_config);
    }
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
    poner_ranking(argv);
  }
}
