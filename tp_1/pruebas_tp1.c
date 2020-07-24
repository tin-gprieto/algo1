#include <stdio.h>
#include <stdbool.h>

const char GUISO='G';
const char PIZZA='P';
const char HAMBURGUESA='H';
const char ENSALADA='E';

	bool cena_valida(char cena){
	return((cena==GUISO)||(cena==PIZZA)||(cena==HAMBURGUESA)||(cena==ENSALADA)); 
}
void preguntar_cena(char* cena){
	printf("¿Qué cenó la noche anterior? Las alternativas son 'G'(guiso), 'P'(pizza), 'H'(hamburguesa) y 'E'(ensalada):");
	scanf("%c", &*cena);
		while (! cena_valida(*cena)){
		printf("La información ingresada no es valida, prueba nuevamente: ");
		scanf("%c", &*cena);
	}
}
int main(){
	char cena;
		preguntar_cena(&cena);
	return 0;
}