#include <stdio.h>
#include <stdbool.h>
#include "dia_en_la_uni.h"

const char TRINEO = 'T';
const char NAVE_ESPACIAL = 'N';
const char CAMION = 'C';
const char ALFOMBRA = 'A';

const char BOLAS_DE_NIEVE = 'B';
const char PIUM_PIUM = 'P';
const char KUCHAU = 'K';
const char GENIO = 'G';

const int MIN_NUMERO_ENTERO = 0;
const float MIN_NUMERO_DECIMAL = 0.00f;

const int MAX_ENTERO = 23;
const float MAX_DECIMAL = 0.59f;

const int NOTA_MIN = 1;
const int NOTA_MAX = 10;

const int PUNTOS_TRINEO_NAVE = 10;
const int PUNTOS_CAMION_ALFOMBRA = 20;

const int PUNTOS_BOLAS_DE_NIEVE = 3;
const int PUNTOS_PIUM_PIUM = 6;
const int PUNTOS_KUCHAU = 9;
const int PUNTOS_GENIO = 12;

const int MULTIPLICADOR_1_3 = 1;
const int MULTIPLICADOR_4_6 = 2;
const int MULTIPLICADOR_7_8 = 3;
const int MULTIPLICADOR_9_10 = 4;

const int PRIMER_INTERVALO_MIN = 13;
const int PRIMER_INTERVALO_MAX = 41;

const float HORA_EXAMEN = 15.30f;

const char OLAF = 'O';
const char STITCH = 'S';
const char JASMIN = 'J';
const char RAYO = 'R';


bool es_transporte_invalido(char transporte){

	return (transporte != TRINEO && transporte != NAVE_ESPACIAL && transporte != CAMION && transporte != ALFOMBRA);
}

/*
 * Precondiciones: -
 * Postcondiciones: Pregunta por pantalla al usuario qué transporte elige y el valor que este ingresa es asignado a la variable transporte.
 *					Si el valor ingresado no es válido, se le vuelve a preguntar hasta que escriba uno que lo sea.
 */

void pregunta_transporte(char* transporte){

	printf("Estás saliendo de tu casa, y te enterás que hay paro de trenes. ¿Qué otro transporte elegís? Trineo (%c), nave espacial (%c), camión (%c), alfombra (%c).\n", TRINEO, NAVE_ESPACIAL, CAMION, ALFOMBRA);
	scanf(" %c", transporte);
	while(es_transporte_invalido(*transporte)){
		printf("Esa respuesta no es válida, por favor ingrese una de las siguientes opciones: Trineo (%c), nave espacial (%c), camión (%c), alfombra (%c).\n", TRINEO, NAVE_ESPACIAL, CAMION, ALFOMBRA);
		scanf(" %c", transporte);
	}
}

bool es_medio_invalido(char utilidad){

	return (utilidad != BOLAS_DE_NIEVE && utilidad != PIUM_PIUM && utilidad != KUCHAU && utilidad!= GENIO);
}

/*
 * Precondiciones: -
 * Postcondiciones: Pregunta por pantalla al usuario qué medio para deshacerse de la manifestación elige y el valor que este ingresa es asignado a la variable utilidad.
 *					Si el valor ingresado no es válido, se le vuelve a preguntar hasta que escriba uno que lo sea.
 */

void pregunta_manifestacion(char* utilidad){

	printf("En medio del camino te encontrás con una manifestación. ¿Qué medio utilizas para deshacerte de la manifestación? Bolas de nieve (%c), pium pium (%c), kuchau (%c), genio (%c).\n", BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU, GENIO);
	scanf(" %c", utilidad);
	while(es_medio_invalido(*utilidad)){
		printf("Esa respuesta no es válida, por favor ingrese una de las siguientes opciones: Bolas de nieve (%c), pium pium (%c), kuchau (%c), genio (%c).\n", BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU, GENIO);
		scanf(" %c", utilidad);
	}
}

/*
 * Precondiciones: - 
 * Postcondiciones: Le asigna la parte entera y la parte decimal de la hora a sus respectivas variables por referencia.
 */

void dividir_partes_hora(int* parte_entera, float* hora){

	(*parte_entera) = (int)(*hora);
	(*hora) = (*hora) - (float)(*parte_entera);
}

bool es_hora_invalida(int parte_entera, float hora){

	return (parte_entera > MAX_ENTERO || parte_entera < MIN_NUMERO_ENTERO || hora > MAX_DECIMAL || hora < MIN_NUMERO_DECIMAL);
}

/*
 * Precondiciones: - 
 * Postcondiciones: Pregunta por pantalla al usuario a qué hora llegó a la universidad y el valor que este ingresa es asignado a la variable hora.
 *					Si el valor ingresado no es válido, se le vuelve a preguntar hasta que escriba uno que lo sea.
 */

void pregunta_hora(float* hora){

	printf("Lograste superar la manifestación, ¿A qué hora conseguiste llegar a la universidad?\n");
	scanf("%f", hora);
	int parte_entera;
	dividir_partes_hora(&parte_entera, hora);
	while(es_hora_invalida(parte_entera, *hora)){
		printf("Esa respuesta no es válida, por favor ingrese un horario que si lo sea.\n");
		scanf("%f", hora);
		dividir_partes_hora(&parte_entera, hora);
	}
	(*hora) = (*hora) + (float)parte_entera;
}

bool es_nota_invalida(int nota){

	return (nota < NOTA_MIN || nota > NOTA_MAX);
}

/*
 * Precondiciones: -
 * Postcondiciones: Pregunta por pantalla al usuario qué nota se sacó y el valor que este ingresa es asignado a la variable nota.
 *					Si el valor ingresado no es válido, se le vuelve a preguntar hasta que escriba uno que lo sea.
 */

void pregunta_nota(int* nota){

	printf("Por fin llegó la nota del parcial! ¿Qué nota lograste sacarte?\n");
	scanf("%i", nota);
	while(es_nota_invalida(*nota)){
		printf("Esa respuesta no es válida, por favor ingrese un número del 1 al 10.\n");
		scanf("%i", nota);
	}
}

/*
 * Precondiciones: La variable transporte es TRINEO, NAVE_ESPACIAL, CAMION o ALFOMBRA.
 * Postcondiciones: Crea una variable de tipo int y dependiendo a qué constante es igual transporte se le asigna un número entero u otro; luego devuelve la variable.
 */

int puntaje_transporte(char transporte){

	int puntos_transporte;
	if(transporte == TRINEO || transporte == NAVE_ESPACIAL){
		puntos_transporte = PUNTOS_TRINEO_NAVE;
	}
	else{
		puntos_transporte = PUNTOS_CAMION_ALFOMBRA;
	}

	return puntos_transporte;
}

/*
 * Precondiciones: La variable utilidad es BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU o GENIO.
 * Postcondiciones: Crea una variable de tipo int y dependiendo a qué constante es igual utilidad se le asigna un número entero u otro; luego devuelve la variable.
 */

int puntaje_manifestacion(char utilidad){

	int puntos_manifestacion;
	if(utilidad	== BOLAS_DE_NIEVE){
		puntos_manifestacion = PUNTOS_BOLAS_DE_NIEVE;
	}
	else if(utilidad == PIUM_PIUM){
		puntos_manifestacion = PUNTOS_PIUM_PIUM;
	}
	else if(utilidad == KUCHAU){
		puntos_manifestacion = PUNTOS_KUCHAU;
	}
	else{
		puntos_manifestacion = PUNTOS_GENIO;
	}

	return puntos_manifestacion;
}

/*
 * Precondiciones: La variable nota es un número entero mayor o igual que NOTA_MIN y menor o igual que NOTA_MAX.
 * Postcondiciones: Crea una variable de tipo int y dependiendo en qué rango de números se encuentre nota se le asigna un número entero u otro; luego devuelve la variable.
 */

int multiplicador_nota(int nota){

	int multiplicador;
	if(nota >= NOTA_MIN && nota <= 3){
		multiplicador = MULTIPLICADOR_1_3;
	}
	else if(nota >= 4 && nota <= 6){
		multiplicador = MULTIPLICADOR_4_6;
	}
	else if(nota == 7 || nota == 8){
		multiplicador = MULTIPLICADOR_7_8;
	}else{
		multiplicador = MULTIPLICADOR_9_10;
	}

	return multiplicador;
}

/*
 * Precondiciones:	La variable transporte es TRINEO, NAVE_ESPACIAL, CAMION o ALFOMBRA.
 *					La variable utilidad es BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU o GENIO.
 *					La variable nota es un número entero mayor o igual que NOTA_MIN y menor o igual que NOTA_MAX.			
 * Postcondiciones: Realiza la cuenta para calcular el puntaje y el resultado se lo asigna a la variable puntaje_total por referencia.
 */

void calculo_puntaje(char transporte, char utilidad, int nota, int* puntaje_total){

	int puntos_transporte = puntaje_transporte(transporte);
	int puntos_manifestacion = puntaje_manifestacion(utilidad);
	int multiplicador = multiplicador_nota(nota);
	(*puntaje_total) = (puntos_transporte + (puntos_manifestacion * multiplicador));
}

/*
 * Precondiciones: -
 * Postcondiciones: Dependiendo el valor de las variables puntaje_total y hora se imprime un mensaje por pantalla u otro.
 */

void determinar_personaje(int puntaje_total, float hora, char* personaje){

	if(puntaje_total >= PRIMER_INTERVALO_MIN && puntaje_total <= PRIMER_INTERVALO_MAX){
		if(hora <= HORA_EXAMEN){
			printf("Con un puntaje de %i puntos se definió el personaje -Stitch-.\n", puntaje_total);
			(*personaje) = STITCH;
		}
		else{
			printf("Con un puntaje de %i puntos se definió el personaje -Olaf-.\n", puntaje_total);
			(*personaje) = OLAF;
		}
	}
	else{
		if(hora <= HORA_EXAMEN){
			printf("Con un puntaje de %i puntos se definió el personaje -Jasmín-.\n", puntaje_total);
			(*personaje) = JASMIN;
		}
		else{
			printf("Con un puntaje de %i puntos se definió el personaje -Rayo McQueen-.\n", puntaje_total);
			(*personaje) = RAYO;
		}
	}
}

void dia_en_la_uni(char* personaje){

	char transporte;
	char utilidad;
	float hora;
	int nota;
	int puntaje_total;

	pregunta_transporte(&transporte);
	pregunta_manifestacion(&utilidad);
	pregunta_hora(&hora);
	pregunta_nota(&nota);
	calculo_puntaje(transporte, utilidad, nota, &puntaje_total);
	determinar_personaje(puntaje_total, hora, personaje);
}