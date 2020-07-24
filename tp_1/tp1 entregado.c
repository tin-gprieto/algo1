#include <stdio.h>
#include <stdbool.h>

const int DIA_MINIMO=1;
const int DIA_MAXIMO=30;
const int DIA_VELOCIDAD_ALTA=10;
const int DIA_VELOCIDAD_MEDIA=20;
const int DIA_VELOCIDAD_BAJA=30;
const int VELOCIDAD_ALTA=75;
const int VELOCIDAD_MEDIA=50;
const int VELOCIDAD_BAJA=25;

const char MANIANA='M';
const char TARDE='T';
const char NOCHE='N';
const int HUMEDAD_MANIANA=75;
const int HUMEDAD_TARDE=25;
const int HUMEDAD_NOCHE=50;

const int DORMIDO_MAXIMO=12;
const int DORMIDO_MINIMO=0;
const int HORAS_MINIMO=5;
const int HORAS_MAXIMO=8;

const char DERECHO='D';
const char IZQUIERDO='I';
const char GUISO='G';
const char PIZZA='P';
const char HAMBURGUESA='H';
const char ENSALADA='E';

const int PUNTAJE_NULO=0;
const int PUNTAJE_BAJO=5;
const int PUNTAJE_MEDIO=10;
const int PUNTAJE_ALTO=15;
const int PUNTAJE_MUY_ALTO=20;

const char MALO='M';
const char REGULAR='R';
const char BUENO='B';
const int LIMITE_MALO=20;
const int LIMITE_REGULAR=35;
const int LIMITE_BUENO=50;

const char LEGOLAS='l';
const char GIMLI='g';

/*
*Pre:-
*Post: entero entre 0 y 30
*/ 
bool dia_valido(int dia){
	return ((dia >= DIA_MINIMO) && (dia <= DIA_MAXIMO));
}
/*
*Análisis: pregunta al usuario el número de dia y valida que sea entre 1 y 30(rango)
*Pre:-
*Post: entero que cumple rango
*/ 
void preguntar_dia(int* dia){
	printf("_Para saber la condición del viento, necesitamos que nos digas que dia (entre 1 y 30) del mes es: ");
	scanf("%d", &*dia);
	while(! dia_valido(*dia)){
		printf("La información ingresada no es valida, prueba nuevamente, es entre 1 y 30: ");
		scanf("%d",&*dia);
	}
}
/*
*Análisis: establece el valor del viento con constantes
*Pre: entero entre 1 a 30 (rango)
*Post: viento definido por constante (25, 50 o 75)
*/ 
void calcular_viento(int dia, int* viento){
	if (dia<=DIA_VELOCIDAD_ALTA){
		*viento=VELOCIDAD_ALTA;
	}
	else if (dia<=DIA_VELOCIDAD_MEDIA){
		*viento=VELOCIDAD_MEDIA;
	}
	else if (dia<=DIA_VELOCIDAD_BAJA){
		*viento=VELOCIDAD_BAJA;
	}	
}
/*
*Pre:-
*Post: letra 'M', 'T' O 'N'
*/ 
bool momento_del_dia_valido(char momento){
	return((momento == MANIANA) || (momento == TARDE) || (momento == NOCHE));
}
/*
*Análisis: pregunta al usuario la hora del dia y valida que se una letra válida ('M'/'T'/'N')(rango)
*Pre: -
*Post: letra asignda a una variable que cumple con el rango
*/
void preguntar_momento_del_dia(char* momento_del_dia){
	printf("_Tambien debemos conocer la humedad del aire, para aquello ingrese el momento del día, siendo 'M' la mañana, 'T' la tarde y 'N' la noche: ");
	scanf(" %c", &*momento_del_dia);
	while (! momento_del_dia_valido(*momento_del_dia)){
		printf("La información ingresada no es valida, prueba nuevamente, deber ser 'M','T' o 'N': ");
		scanf(" %c", &*momento_del_dia);
	}
}
/*
*Análisis: a partir del valor del momento del dia asigna el valor de la humedad
*Pre: letra 'M', 'T' o 'N'
*Post: humedad definida por constante (25, 50 o 75)
*/
void calcular_humedad(char momento_del_dia, int* humedad){
	if (momento_del_dia==MANIANA){
		*humedad=HUMEDAD_MANIANA;
	}else if (momento_del_dia==TARDE){
		*humedad=HUMEDAD_TARDE;
	}else if(momento_del_dia==NOCHE){
		*humedad=HUMEDAD_NOCHE;
	}	
}
/*
*Pre:-
*Post: letra 'G', 'P', 'H' O 'E'
*/ 
bool cena_valida(char cena){
	return((cena == GUISO) || (cena == PIZZA) || (cena == HAMBURGUESA) || (cena == ENSALADA)); 
}
/*
*Análisis: pregunta al usuario qué cenó y valida que sea una letra válida (G/H/P/E)(rango)
*Pre: -
*Post: asignada a una variable que cumple rango
*/
void preguntar_cena(char* cena){
	printf("_¿Qué cenó la noche anterior? Las alternativas son 'G'(guiso), 'P'(pizza), 'H'(hamburguesa) y 'E'(ensalada):");
	scanf(" %c", &*cena);
	while (! cena_valida(*cena)){
		printf("La información ingresada no es valida, prueba nuevamente, debe ser 'G','P','H' o 'E': ");
		scanf(" %c", &*cena);
	}
}
/*
*Pre:-
*Post: entero entre 0 y 12
*/ 
bool horas_dormidas_validas(int horas){
	return ((horas >= DORMIDO_MINIMO) && (horas <= DORMIDO_MAXIMO));
}
/*
*Análisis: pregunta al usuario cuantas horas durmió y valida que sean entre 0 y 12 (rango)
*Pre:-
*Post: entero asignado a variable que cumple rango
*/
void preguntar_horas_dormidas(int* horas){
	printf("_Finalmente, no te olvides...¿Cuantas horas durmió? (número entre 0 y 12): ");
	scanf("%i", &*horas);
	while(! horas_dormidas_validas(*horas)){
		printf("La información ingresada no es valida, prueba nuevamente, es entre 0 y 12: ");
		scanf("%i", &*horas);
		}
}
/*
*Pre:-
*Post: letra 'D' o 'I'
*/ 
bool pie_valido(char pie){
	return ((pie == DERECHO) || (pie == IZQUIERDO));
}
/*
*Análisis: pregunta al usuario el pie con el que se levantó y valida que sea 'D' o 'I'(rango)
*Pre:-
*Post: letra asignada a variable que cumple con rango
*/
void preguntar_pie(char* pie){	
	printf("_¿Con que pie se despertó hoy? 'D'(derecho) o 'I'(izquierdo): ");
	scanf(" %c", &*pie);
	while (! pie_valido(*pie)){
		printf("La información ingresada no es valida, prueba nuevamente, debe ser 'D' o 'I': ");
		scanf(" %c", &*pie);
	}
}
/*
*Análisis: contiene todas las preguntas sobre el ánimo(con procedimientos)
*Pre: constante que sea del valor indicado (LEGOLAS O GIMLI)
*Post: variables del ánimo definidas 
*/
void preguntar_animo(const char heroe, char* cena,int* horas_dormidas,char* pie){
	if (heroe==LEGOLAS){
		printf("	Queremos conocer si nuestros héroes están lo suficientemente motivados para esta épica batalla.Te pediremos algunas cosas...Primero para saber la confianza que tiene, debemos conocer el pie con el que se despertó; después la alimentación previa al combate, que es vital; y por último, las horas que durmió, un guerrero tiene que estar lúcido.\n 	Comencemos con Légolas:\n");
	}else if(heroe==GIMLI){
		printf("	Ahora necesitamos saber lo mismo sobre el valiente Gimli...\n");
	}	
	preguntar_pie(&*pie);
	preguntar_cena(&*cena);
	preguntar_horas_dormidas(&*horas_dormidas);
}
/*
*Análisis: asigna valor a la variable puntos_cena según el valor de cena
*Pre: letra que cumpla con rango(G/P/H/E)
*Post: entero definido por constante
*/	
void puntuar_cena(char cena, int* puntos_cena){
	if (cena == GUISO){
		*puntos_cena=PUNTAJE_BAJO;
	}else if (cena == PIZZA){
		*puntos_cena=PUNTAJE_MEDIO;
	}else if (cena == HAMBURGUESA){
		*puntos_cena=PUNTAJE_ALTO;
	}else if(cena == ENSALADA){
		*puntos_cena=PUNTAJE_MUY_ALTO;
	}
}
/*
*Análisis: asigna valor a la variable puntos_horas_dormidas según el valor de horas_dormidas
*Pre: entero que cumpla con rango(0 a 12)
*Post: entero definido por constante
*/
void puntuar_horas_dormidas(int horas, int* puntos_horas_dormidas){
	if(horas < HORAS_MINIMO){
		*puntos_horas_dormidas=PUNTAJE_NULO;
	}else if ((horas >= HORAS_MINIMO) && (horas <= HORAS_MAXIMO)){
		*puntos_horas_dormidas=PUNTAJE_MEDIO;
	}else if (horas > HORAS_MAXIMO){
		*puntos_horas_dormidas=PUNTAJE_MUY_ALTO;
	}	
}
/*
*Análisis: asigna valor a la variable puntos_pie según el valor de pie
*Pre: letra que cumpla con rango (D/I)
*Post: entero definido por constante
*/
void puntuar_pie(char pie, int* puntos_pie){
	if(pie == DERECHO){
		*puntos_pie=PUNTAJE_MEDIO;
	}else if (pie == IZQUIERDO){
		*puntos_pie=PUNTAJE_NULO;
	}
}
/*
*Análisis: agrupa los procedimientos acordes a los puntos del ánimo 
*Pre: cada una de las variables debe cumplir con su respectivo rango
*Post: las variables de los puntos definidas por constantes
*/
void asignar_puntos_animo(char cena,int horas_dormidas,char pie,int* puntos_cena,int* puntos_horas_dormidas,int* puntos_pie){
	puntuar_pie(pie, &*puntos_pie);
	puntuar_cena(cena,&*puntos_cena);
	puntuar_horas_dormidas(horas_dormidas, &*puntos_horas_dormidas);
}
/*
*Análisis: opera con el valor de las variables de los puntos para definir la variable ánimo 
*Pre: variables que cumplan con los valores esperados  (SIN_PUNTAJE,PRIMER_PUNTAJE,SEGUNDO_PUNTAJE,TERCER_PUNTAJE,CUARTO_PUNTAJE)
*Post: animo definido por letras (definidas en constantes)('M', 'R' o 'B')
*/
void sumar_puntos_animo(char* animo,int puntos_cena,int puntos_horas_dormidas,int puntos_pie){
	int resultado_numerico= puntos_cena+puntos_pie+puntos_horas_dormidas;
	if(resultado_numerico <= LIMITE_MALO){
		*animo=MALO;
	}else if(resultado_numerico <= LIMITE_REGULAR){
		*animo=REGULAR;
	}else if(resultado_numerico <= LIMITE_BUENO){
		*animo=BUENO;
	}
}
/*
*Análisis: imprime por pantalla el estado del viento según su valor
*Pre: valor de viento calculado
*Post: resultado en la pantalla
*/
void decir_viento(int viento){
	if(viento == VELOCIDAD_BAJA){
		printf("Una leve brisa baja de las montañas;");
	}else if(viento == VELOCIDAD_MEDIA){
		printf("El viento está movido, esperemos que no sea un problema;");
	}else if(viento == VELOCIDAD_ALTA){
		printf("Hay que tener cuidado con semejante ventisca, el labor de los arqueros se verá perjudicado;");
	}
}
/*
*Análisis: imprime por pantalla el estado de la humedad según su valor
*Pre: valor de humedad calculado
*Post: resultado en la pantalla
*/
void decir_humedad(int humedad){
	if(humedad == HUMEDAD_TARDE){
		printf("Poca humedad en el aire, los martillazos enanos serán contundentes.\n");
	}else if(humedad == HUMEDAD_NOCHE){
		printf("Ni poca ni mucha humedad, veremos qué ocurrirá...\n");
	}else if(humedad == HUMEDAD_MANIANA){
		printf("Sin lugar a dudas, tener las alcantarillas cerca no es buena idea, mucha humedad para el combate.\n");
	}
}
/*
*Análisis: imprime por pantalla el animo de Légolas
*Pre: valor del ánimo calculado
*Post: resultado en la pantalla
*/
void decir_animo_legolas(char animo_legolas){
	if(animo_legolas == BUENO){
		printf("El príncipe de los elfos siente que éste será su día, quiere sangre Uruk-Hai.\n");
	}else if(animo_legolas == REGULAR){
		printf("No se lo ve muy motivado a Légolas, sin embargo tensa su arco con pacienca.\n");
	}else if(animo_legolas == MALO){
		printf("La frialdad del elfo delata que se no encuentra en un buen momento.\n");
	}
}
/*
*Análisis: imprime por pantalla el animo de Gimli
*Pre: valor de ánimo calculado
*Post: resultado en la pantalla
*/
void decir_animo_gimli(char animo_gimli){
	if(animo_gimli == BUENO){
		printf("El frenesí de Gimli, hijo de Glóin,contagia a sus tropas, qué bueno verlo así!\n");
	}else if(animo_gimli == REGULAR){
		printf("Sin el fervor que lo caracteriza, Gimli se encuentra concetrado para el combate.\n");
	}else if(animo_gimli == MALO){
		printf("No es fácil que un enano del clan de Durin pase desapercibido cuando está de mal. \n");
	}
}
int main(){
	int dia=0; 
	int viento=0, humedad=0;
	int horas_dormidas=0;
	int puntos_cena=0,puntos_horas_dormidas=0,puntos_pie=0;

	char momento_del_dia;
	char cena;
	char pie;
	char animo_legolas, animo_gimli;

	printf("	La situación en el Abismo de Helm es preocupante, el constante asedio de las fuerzas de Saruman el Blanco tiene aterrado al pueblo de Rohan.\nPara ganar esta contienda necesitamos saber las condiciones del campo de batalla y el estado de nuestros comandantes para luchar...\n");
	preguntar_dia(&dia);
	calcular_viento(dia, &viento);
	preguntar_momento_del_dia(&momento_del_dia);
	calcular_humedad(momento_del_dia, &humedad);
	preguntar_animo(LEGOLAS, &cena,&horas_dormidas,&pie);
	asignar_puntos_animo(cena,horas_dormidas,pie,&puntos_cena,
						&puntos_horas_dormidas,&puntos_pie);
	sumar_puntos_animo(&animo_legolas,puntos_cena,
						puntos_horas_dormidas,puntos_pie);
	preguntar_animo(GIMLI,&cena,&horas_dormidas,&pie);
	asignar_puntos_animo(cena,horas_dormidas,pie,
						&puntos_cena,&puntos_horas_dormidas,&puntos_pie);
	sumar_puntos_animo(&animo_gimli,puntos_cena,
						puntos_horas_dormidas,puntos_pie);
	decir_viento(viento);
	decir_humedad(humedad);
	decir_animo_legolas(animo_legolas);
	decir_animo_gimli(animo_gimli);
	printf("	Resumen: %i %i %c %c. \n", viento, humedad, animo_legolas, animo_gimli);

	return 0;
}