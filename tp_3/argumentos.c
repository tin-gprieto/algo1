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
#define FORMATO_CLAVE "%[^=]"
#define FORMATO_TORRES "%i;%i\n"
#define FORMATO_INICIO "%i;%i;%i;%i\n"
#define FORMATO_EXTRA "%i;%i;%i\n"
#define FORMATO_ANIMO "%i;%i\n"
#define FORMATO_VELOCIDAD "%f\n"
#define FORMATO_CAMINO "%s\n"

#define NIVEL_1 0
#define NIVEL_2 1
#define NIVEL_3 2
#define NIVEL_4 3
#define TORRE_1 0
#define TORRE_2 1

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
const char SEPARADOR[MAX_SEPARADOR]= "=";

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
void configurar_caminos(configuracion_t configuracion, coordenada_t camino[], int* tope_camino, int tope_campo){
}
void chequear_entero(int* entero, int standard){
  if(*entero==-1){
    *entero=standard;
  }
}
/*
void chequear_configuracion(configuracion_t* configuracion, configuracion_t standard){
  chequear_entero(&(configuracion.torres.resistencia_torre_1), standard.torres.resistencia_torre_1);
  chequear_entero(&(configuracion.torres.resistencia_torre_2), standard.torres.resistencia_torre_2);
  for(int i=0; i<TOPE_NIVELES; i++){
    chequear_entero(&(configuracion.cantidad_enanos[i]), standard.cantidad_enanos[i]);
  }
  for(int i=0; i<TOPE_NIVELES; i++){
    chequear_entero(&(configuracion.cantidad_elfos[i]), standard.cantidad_elfos[i]);
  }
}
*/
void leer_configuracion(FILE* archivo, configuracion_t* config){

}
void cargar_confirguracion (configuracion_t* configuracion, int modo, char nombre_archivo[]){
    configuracion_t config;
    FILE*archivo=fopen("configuracion_standard.txt", "r");
    if(!archivo){
      printf("No se pudo abrir la configuracion\n");
      fclose(archivo);
    }else{
      char clave[MAX_CLAVE];
      int leido=fscanf(archivo,FORMATO_CLAVE, clave);
      while(leido==1){
        if (strcmp(clave,"RESISTENCIA_TORRES")==0){
          fscanf(archivo,FORMATO_TORRES, &(config.torres.resistencia_torre_1), &(config.torres.resistencia_torre_2));
        }else if (strcmp(clave, "ENANOS_INICIO")==0){
          fscanf(archivo,FORMATO_INICIO, &(config.cantidad_enanos[NIVEL_1]), &(config.cantidad_enanos[NIVEL_2]), &(config.cantidad_enanos[NIVEL_3]), &(config.cantidad_enanos[NIVEL_4]));
        }else if (strcmp(clave, "ELFOS_INICIO")==0){
          fscanf(archivo,FORMATO_INICIO, &(config.cantidad_elfos[NIVEL_1]), &(config.cantidad_elfos[NIVEL_2]), &(config.cantidad_elfos[NIVEL_3]), &(config.cantidad_elfos[NIVEL_4]));
        }else if (strcmp(clave, "ENANOS_EXTRA")==0){
          fscanf(archivo,FORMATO_EXTRA, &(config.torres.enanos_extra), &(config.costo_G_extra[TORRE_1]), &(config.costo_G_extra[TORRE_2]));
        }else if (strcmp(clave, "ELFOS_EXTRA")==0){
          fscanf(archivo,FORMATO_EXTRA, &(config.torres.elfos_extra), &(config.costo_L_extra[TORRE_1]), &(config.costo_L_extra[TORRE_2]));
        }else if (strcmp(clave, "ENANOS_ANIMO")==0){
          fscanf(archivo,FORMATO_ANIMO, &(config.fallo_gimli), &(config.critico_gimli));
        }else if (strcmp(clave, "ELFOS_ANIMO")==0){
          fscanf(archivo,FORMATO_ANIMO, &(config.fallo_legolas), &(config.critico_legolas));
        }else if (strcmp(clave, "VELOCIDAD")==0){
          fscanf(archivo,FORMATO_VELOCIDAD, &(config.velocidad));
        }else if (strcmp(clave, "CAMINOS")==0){
          fscanf(archivo,FORMATO_CAMINO, config.ruta_camino);
        }
        memset(clave,'\0',MAX_CLAVE);
        leido=fscanf(archivo,FORMATO_CLAVE, clave);
      }
      fclose(archivo);
    }
  if((modo == STANDARD_GRABANDO)||(modo == STANDARD_SIN_GRABAR)){
    *configuracion=config;
  }
  /*else if((modo == CUSTOM_GRABANDO)||(modo == CUSTOM_SIN_GRABAR)){
    FILE*archivo_config_std=fopen("configuracion_standard.txt", "r")
    if(!archivo_config_std){
      printf("No se pudo abrir la configuracion\n");
      fclose(archivo_arch_config);
    }else{
      leer_configuracion(archivo_config_std, configuracion);
      chequear_configuracion(configuracion, config_std);
    }
      fclose(archivo_config_std);
    }
  }
*/
}
void poner_repeticion(char arg[]){
}
void actualizar_ranking(juego_t juego){
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
/*
*
*
*
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
*
*
*
*/
void crear_configuracion(char* argv[]){
  if (argv[2] != NULL){
    printf("Se crea configuracion en %s \n", argv[2]);
  }else{
    printf("No se han ingresado los archivos correspondientes...\n");
  }
}
/*
*
*
*
*/
void crear_caminos(char* argv[]){
  if (argv[2] != NULL){
    printf("Se crean caminos en %s \n", argv[2]);
  }else{
    printf("No se han ingresado los archivos correspondientes...\n");
  }
}
/*
*
*
*
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
*
*
*
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
int modo_juego(int tope_arg, char* argv[], char config[], char grabacion[]){
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
