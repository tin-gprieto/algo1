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
*Post: entero entre DIA_MINIMO y DIA_MAXIMO
*/ 
bool dia_valido(int dia){
	return ((dia >= DIA_MINIMO) && (dia <= DIA_MAXIMO));
}
/*
*Análisis: pregunta al usuario el número de dia y valida que sea entre DIA_MINIMO y DIA_MAXIMO(rango)
*Pre:-
*Post: entero que cumple rango
*/ 
void preguntar_dia(int* dia){
	printf("_Para saber la condición del viento, necesitamos que nos digas que dia (entre %i y %i) del mes es: ",DIA_MINIMO, DIA_MAXIMO);
	scanf("%d", &*dia);
	while(! dia_valido(*dia)){
		printf("La información ingresada no es valida, prueba nuevamente, es entre %i y %i: ", DIA_MINIMO, DIA_MAXIMO);
		scanf("%d",&*dia);
	}
}
/*
*Análisis: establece el valor del viento con constantes
*Pre: entero entre DIA_MINIMO a DIA_MAXIMO (rango)
*Post: viento definido por constante (VELOCIDAD_ALTA, VELOCIDAD_MEDIA, VELOCIDAD_BAJA)
*/ 
int calcular_viento(int dia, int* viento){
	if (dia<=DIA_VELOCIDAD_ALTA){
		return *viento=VELOCIDAD_ALTA;
	}
	else if (dia<=DIA_VELOCIDAD_MEDIA){
		return *viento=VELOCIDAD_MEDIA;
	}
	else if (dia<=DIA_VELOCIDAD_BAJA){
		return *viento=VELOCIDAD_BAJA;
	}
	return 0;		
}
/*
*Pre:-
*Post: letra MANIANA, TARDE, NOCHE('M', 'T' O 'N') 
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
	printf("_Tambien debemos conocer la humedad del aire, para aquello ingrese el momento del día, siendo '%c' la mañana, '%c' la tarde y '%c' la noche: ", MANIANA, TARDE, NOCHE);
	scanf(" %c", &*momento_del_dia);
	while (! momento_del_dia_valido(*momento_del_dia)){
		printf("La información ingresada no es valida, prueba nuevamente, deber ser '%c','%c' o '%c': ", MANIANA, TARDE, NOCHE);
		scanf(" %c", &*momento_del_dia);
	}
}
/*
*Análisis: a partir del valor del momento del dia asigna el valor de la humedad
*Pre: letra MANIANA, TARDE, NOCHE('M', 'T' O 'N')
*Post: humedad definida por constante (HUMEDAD_MANIANA, HUMEDAD_TARDE, HUMEDAD_NOCHE)
*/
int calcular_humedad(char momento_del_dia, int* humedad){
	if (momento_del_dia==MANIANA){
		return *humedad=HUMEDAD_MANIANA;
	}else if (momento_del_dia==TARDE){
		return *humedad=HUMEDAD_TARDE;
	}else if(momento_del_dia==NOCHE){
		return *humedad=HUMEDAD_NOCHE;
	}
	return 0;		
}
/*
*Pre:-
*Post: letra 'G', 'P', 'H' o 'E'
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
	printf("_¿Qué cenó la noche anterior? Las alternativas son '%c'(guiso), '%c'(pizza), '%c'(hamburguesa) y '%c'(ensalada):", GUISO, PIZZA, HAMBURGUESA, ENSALADA);
	scanf(" %c", &*cena);
	while (! cena_valida(*cena)){
		printf("La información ingresada no es valida, prueba nuevamente, debe ser '%c','%c','%c' o '%c': ", GUISO, PIZZA, HAMBURGUESA, ENSALADA);
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
*Análisis: pregunta al usuario cuantas horas durmió y valida que sean entre DORMIDO_MINIMO y DORMIDO_MAXIMO (rango)
*Pre:-
*Post: entero asignado a variable que cumple rango
*/
void preguntar_horas_dormidas(int* horas){
	printf("_Finalmente, no te olvides...¿Cuantas horas durmió? (número entre %i y %i): ", DORMIDO_MINIMO, DORMIDO_MAXIMO);
	scanf("%i", &*horas);
	while(! horas_dormidas_validas(*horas)){
		printf("La información ingresada no es valida, prueba nuevamente, es entre %i y %i: ", DORMIDO_MINIMO, DORMIDO_MAXIMO);
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
	printf("_¿Con que pie se despertó hoy? '%c'(derecho) o '%c'(izquierdo): ", DERECHO, IZQUIERDO);
	scanf(" %c", &*pie);
	while (! pie_valido(*pie)){
		printf("La información ingresada no es valida, prueba nuevamente, debe ser '%c' o '%c': ", DERECHO, IZQUIERDO);
		scanf(" %c", &*pie); 
	}
}
/*
*Análisis: contiene todas las preguntas sobre el ánimo(con procedimientos)
*Pre: constante que sea del valor indicado (LEGOLAS O GIMLI)
*Post: variables del ánimo definidas por constantes y que cumplan rango (pie D o I, cena G,P,H o E, horas 0 a 12)
*/
void preguntar_animo(const char heroe, char* cena, int* horas_dormidas, char* pie){
	if (heroe==LEGOLAS){
		printf("	Queremos conocer si nuestros héroes están lo suficientemente motivados para esta épica batalla.Te pediremos algunas cosas...\nPrimero para saber la confianza que tiene, debemos conocer el pie con el que se despertó; después la alimentación previa al combate, que es vital; y por último, las horas que durmió, un guerrero tiene que estar lúcido.\n 	Comencemos con Légolas:\n");
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
*Post: entero definido por constante (PUNTAJE_BAJO, PUNTAJE_MEDIO, PUNTAJE_ALTO, PUNTAJE_MUY_ALTO)
*/	
int puntuar_cena(char cena, int* puntos_cena){
	if (cena == GUISO){
		return *puntos_cena=PUNTAJE_BAJO;
	}else if (cena == PIZZA){
		return *puntos_cena=PUNTAJE_MEDIO;
	}else if (cena == HAMBURGUESA){
		return *puntos_cena=PUNTAJE_ALTO;
	}else if(cena == ENSALADA){
		return *puntos_cena=PUNTAJE_MUY_ALTO;
	}
	return 0;	
}
/*
*Análisis: asigna valor a la variable puntos_horas_dormidas según el valor de horas_dormidas
*Pre: entero que cumpla con rango(HORAS_MINIMO, HORAS_MAXIMO)
*Post: entero definido por constante (PUNTAJE_NULO, PUNTAJE_MEDIO, PUNTAJE_MUY_ALTO)
*/
int puntuar_horas_dormidas(int horas, int* puntos_horas_dormidas){
	if(horas < HORAS_MINIMO){
		return *puntos_horas_dormidas=PUNTAJE_NULO;
	}else if ((horas >= HORAS_MINIMO) && (horas <= HORAS_MAXIMO)){
		return *puntos_horas_dormidas=PUNTAJE_MEDIO;
	}else if (horas > HORAS_MAXIMO){
		return *puntos_horas_dormidas=PUNTAJE_MUY_ALTO;
	}
	return 0;		
}
/*
*Análisis: asigna valor a la variable puntos_pie según el valor de pie
*Pre: letra que cumpla con rango (DEREHO o IZQUIERDO)
*Post: entero definido por constante (PUNTAJE_MEDIO, PUNTAJE_NULO)
*/
int puntuar_pie(char pie, int* puntos_pie){
	if(pie == DERECHO){
		return *puntos_pie=PUNTAJE_MEDIO;
	}else if (pie == IZQUIERDO){
		return *puntos_pie=PUNTAJE_NULO;
	}
	return 0;	
}
/*
*Análisis: agrupa los procedimientos acordes a los puntos del ánimo 
*Pre: cada una de las variables debe cumplir con su respectivo rango
*Post: las variables de los puntos definidas por constantes (SIN_PUNTAJE, PRIMER_PUNTAJE, SEGUNDO_PUNTAJE, TERCER_PUNTAJE, CUARTO_PUNTAJE)
*/
void asignar_puntos_animo(char cena, int horas_dormidas, char pie, int* puntos_cena, int* puntos_horas_dormidas, int* puntos_pie){
	puntuar_pie(pie, &*puntos_pie);
	puntuar_cena(cena, &*puntos_cena);
	puntuar_horas_dormidas(horas_dormidas, &*puntos_horas_dormidas);
}
/*
*Análisis: opera con el valor de las variables de los puntos para definir la variable ánimo 
*Pre: variables que cumplan con los valores calculados (SIN_PUNTAJE, PRIMER_PUNTAJE, SEGUNDO_PUNTAJE, TERCER_PUNTAJE, CUARTO_PUNTAJE)
*Post: animo definido por letras (definidas en constantes)('M', 'R' o 'B')
*/
char sumar_puntos_animo(int puntos_cena, int puntos_horas_dormidas, int puntos_pie, char* animo){
	int resultado_numerico= puntos_cena+puntos_pie+puntos_horas_dormidas;
	if(resultado_numerico <= LIMITE_MALO){
		return *animo=MALO;
	}else if(resultado_numerico <= LIMITE_REGULAR){
		return *animo=REGULAR;
	}else if(resultado_numerico <= LIMITE_BUENO){
		return *animo=BUENO;
	}
	return 0;	
}
/*
*Análisis: imprime por pantalla el estado del viento según su valor
*Pre: valor de viento entre valores calulados (VELOCIDAD_ALTA, VELOCIDAD_MEDIA, VELOCIDAD_BAJA)
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
*Pre: valor de humedad entre valores calulados (HUMEDAD_MANIANA, HUMEDAD_TARDE, HUMEDAD_NOCHE)
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
*Pre: valor del ánimo entre valores calculados (BUENO, REGULAR o MALO)
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
*Pre: valor de ánimo entre valores calculados (BUENO, REGULAR o MALO)
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
/*
*Análisis: imprime por pantalla todos los resultados
*Pre: valor de viento, humedad, animo_legolas, animo_gimli entre valores calculados (VELOCIDAD_ALTA, VELOCIDAD_MEDIA, VELOCIDAD_BAJA/ HUMEDAD_MANIANA, HUMEDAD_TARDE, HUMEDAD_NOCHE/ BUENO, REGULAR o MALO)
*Post: resultado en la pantalla
*/
void decir_resultados(int viento, int humedad, char animo_legolas, char animo_gimli){
	decir_viento(viento);
	decir_humedad(humedad);
	decir_animo_legolas(animo_legolas);
	decir_animo_gimli(animo_gimli);
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
	preguntar_animo(LEGOLAS, &cena, &horas_dormidas,&pie);
	asignar_puntos_animo(cena, horas_dormidas, pie, &puntos_cena, &puntos_horas_dormidas, &puntos_pie);
	sumar_puntos_animo(puntos_cena, puntos_horas_dormidas, puntos_pie, &animo_legolas);
	preguntar_animo(GIMLI, &cena, &horas_dormidas, &pie);
	asignar_puntos_animo(cena, horas_dormidas, pie, &puntos_cena, &puntos_horas_dormidas, &puntos_pie);
	sumar_puntos_animo(puntos_cena, puntos_horas_dormidas, puntos_pie, &animo_gimli);
	decir_resultados(viento, humedad, animo_legolas, animo_gimli);
	printf("	Resumen: %i %i %c %c. \n", viento, humedad, animo_legolas, animo_gimli);

	return 0;
}