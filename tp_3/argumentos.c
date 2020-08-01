#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "defendiendo_torres.h"

#define MAX_SEPARADOR 2
#define MAX_ARCHIVO 20

const int JUGAR=0;
const int CREAR_CONFIGURACION=1;
const int CREAR_CAMINOS=2;
const int REPETICION=3;
const int RANKING=4;
const int ERROR=-1;
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
void crear_caminos(configuracion_t configuracion){
}
void crear_confirguracion (configuracion_t configuracion, int argc, char* arg[]){
}
void cargar_confirguracion (configuracion_t* configuracion, char arg[]){
}
void poner_repeticion(char arg[]){
}
void actualizar_ranking(juego_t juego){
}
void guardar_partida(juego_t juego, int tope_arg, char* arg[]){
}
void comandos(int programa, char* argv[]){
  if(programa == CREAR_CONFIGURACION){
    if (argv[2] != NULL){
      printf("Se crea configuracion en %s \n", argv[2]);
    }else{
      printf("No se han ingresado los archivos correspondientes...\n");
    }
  }else if (programa == CREAR_CAMINOS){
    if (argv[2] != NULL){
      printf("Se crean caminos en %s \n", argv[2]);
    }else{
      printf("No se han ingresado los archivos correspondientes...\n");
    }
  }else if (programa == REPETICION){
    if ((argv[2] == NULL)){
      printf("No se han ingresado los archivos correspondientes...\n");
    }else if (strcmp(strtok(argv[2], SEPARADOR),"grabacion")!=0){
      printf("Recuerda que el comando es 'grabacion=', prueba nuevamente...\n");
    }else{
      printf("tu archivo es %s\n", strtok(NULL, SEPARADOR));
    }
  }else if (programa == RANKING){
    if (argv[2]==NULL){
      printf("RANKING COMPLETO\n");
      return 0;
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
          return 0;
        }else{
          strcpy(arg_3,strtok(argv[3], SEPARADOR));
          strcpy(arg_3_valor,strtok(NULL, SEPARADOR));
          int tope_lista=atoi(arg_3_valor);
          printf("RANKING de %s con %i jugadores \n", arg_2_valor, tope_lista);
          return 0;
        }
      }else if(strcmp(arg_2,"listar") == 0){
        int tope_lista=atoi(arg_2_valor);
        if (argv[3]==NULL){
          printf("RANKING de config_standard con %i jugadores \n", tope_lista);
          return 0;
        }else{
          strcpy(arg_3,strtok(argv[3], SEPARADOR));
          strcpy(arg_3_valor,strtok(NULL, SEPARADOR));
          printf("RANKING de %s con  %i jugadores \n", arg_3_valor, tope_lista);
          return 0;
        }
      }
    }
  }
}
