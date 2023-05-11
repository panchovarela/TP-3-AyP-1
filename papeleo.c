#include <stdio.h>
#include <stdlib.h>
#include "papeleo.h"

#define FUEGOS_EMOJI "\U0001f525"
#define MEDIAS_EMOJI "\U0001f9e6"
#define BOTELLAS_EMOJI "\U0001f6e2\uFE0F"
#define INTERRUPTOR_EMOJI "\U0001f579\uFE0F"
#define PARED_EMOJI "\U0001f9f1"
#define MIKE_EMOJI "\U0001f47e"

const char FUEGOS = 'F';
const char MEDIAS = 'M';
const char BOTELLAS_DE_GRITOS = 'G';
const char INTERRUPTORES_AHUYENTA_RANDALL = 'I';
const char PARED = 'X';
const char MIKE = 'W';

static const char OLAF = 'O';
static const char JASMIN = 'J';
static const char RAYO = 'R';
static const char STITCH = 'S';

const char MOVIMIENTO_DERECHA = 'D';
const char MOVIMIENTO_IZQUIERDA = 'A';
const char ROTAR_HORARIO = 'E';
const char ROTAR_ANTIHORARIO = 'Q';
const char MARTILLO = 'Z';
const char EXTINTOR = 'C';
const char ROMPER_PARED_ARRIBA = 'W';
const char ROMPER_PARED_ABAJO = 'S';
const char ROMPER_PARED_DERECHA = 'D';
const char ROMPER_PARED_IZQUIERDA = 'A';
const char APAGAR_FUEGO_ARRIBA = 'W';
const char APAGAR_FUEGO_DERECHA = 'D';
const char APAGAR_FUEGO_IZQUIERDA = 'A';

const int PRIMER_NIVEL = 1;
const int SEGUNDO_NIVEL = 2;
const int TERCER_NIVEL = 3;
const int CANTIDAD_NIVELES = 3;

const int PRIMERA_FILA = 0;
const int PRIMERA_COLUMNA = 0;

const int LADO_TERRENO_PRIMER_NIVEL = 22;
const int PAPELEOS_PRIMER_NIVEL = 2;
const int MOVIMIENTOS_PRIMER_NIVEL = 40;
const int FUEGOS_PRIMER_NIVEL = 10;
const int MEDIAS_PRIMER_NIVEL = 5;
const int BOTELLAS_PRIMER_NIVEL = 4;
const int INTERRUPTORES_PRIMER_NIVEL = 1;
const int MARTILLOS_PRIMER_NIVEL = 4;
const int EXTINTORES_PRIMER_NIVEL = 4;

const int LADO_TERRENO_SEGUNDO_NIVEL = 17;
const int PAPELEOS_SEGUNDO_NIVEL = 3;
const int MOVIMIENTOS_SEGUNDO_NIVEL = 30;
const int FUEGOS_SEGUNDO_NIVEL = 5;
const int MEDIAS_SEGUNDO_NIVEL = 4;
const int BOTELLAS_SEGUNDO_NIVEL = 3;
const int INTERRUPTORES_SEGUNDO_NIVEL = 1;
const int MARTILLOS_SEGUNDO_NIVEL = 5;
const int EXTINTORES_SEGUNDO_NIVEL = 2;

const int LADO_TERRENO_TERCER_NIVEL = 12;
const int PAPELEOS_TERCER_NIVEL = 4;
const int MOVIMIENTOS_TERCER_NIVEL = 20;
const int FUEGOS_TERCER_NIVEL = 3;
const int MEDIAS_TERCER_NIVEL = 3;
const int BOTELLAS_TERCER_NIVEL = 2;
const int INTERRUPTORES_TERCER_NIVEL = 0;
const int MARTILLOS_TERCER_NIVEL = 6;
const int EXTINTORES_TERCER_NIVEL = 2;

const int FUEGOS_EXTINGUIDOS_OLAF_PRIMER_NIVEL = 2;
const int FUEGOS_EXTINGUIDOS_OLAF_SEGUNDO_NIVEL = 1;
const int PAPELEO_QUEMADO_STITCH = 1;
const int OBSEQUIO_JASMIN = 1;
const int OBSEQUIO_RAYO = 10;
const int RANDALL_PRIMER_NIVEL = 7;
const int RANDALL_SEGUNDO_NIVEL = 5;
const int RANDALL_TERCER_NIVEL = 3;
const int MOVIMIENTOS_PARED_PRIMER_NIVEL = 40;
const int MOVIMIENTOS_PARED_SEGUNDO_NIVEL = 30;
const int MOVIMIENTOS_PARED_TERCER_NIVEL = 20;

const int GANADO = 1;
const int PERDIDO = -1;
const int EN_CURSO = 0;

const int MOVIMIENTOS_SOBRANTES_FUEGO = 0;
const int MOVIMIENTOS_PERDIDOS_MEDIA = 10;
const int MOVIMIENTOS_GANADOS_BOTELLA = 7;

const int CERO = 0;
const char SI = 'y';

/*
 * Precondiciones: -
 * Postcondiciones: Rellena la matriz terreno ingresando un espacio en cada una de las celdas hasta el tope.
 */
void generar_terreno(char terreno[LADO_TERRENO_PRIMER_NIVEL][LADO_TERRENO_PRIMER_NIVEL], int tope){
	for(int i = 0; i < tope; i++){
		for(int j = 0; j < tope; j++){
			terreno[i][j] = ' ';
		}
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Carga la matriz terreno con las paredes correspondientes del nivel actual.
 */
void cargar_paredes_terreno(nivel_t nivel, char terreno[LADO_TERRENO_PRIMER_NIVEL][LADO_TERRENO_PRIMER_NIVEL]){
	for(int i = 0; i < nivel.tope_paredes; i++){
		terreno[nivel.paredes[i].fil][nivel.paredes[i].col] = PARED;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Carga la matriz terreno con los obstáculos correspondientes del nivel actual.
 */
void cargar_obstaculos_terreno(nivel_t nivel, char terreno[LADO_TERRENO_PRIMER_NIVEL][LADO_TERRENO_PRIMER_NIVEL]){
	for(int i = 0; i < nivel.tope_obstaculos; i++){
		terreno[nivel.obstaculos[i].posicion.fil][nivel.obstaculos[i].posicion.col] = nivel.obstaculos[i].tipo;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Carga la matriz terreno con las herramientas correspondientes del nivel actual.
 */
void cargar_herramientas_terreno(nivel_t nivel, char terreno[LADO_TERRENO_PRIMER_NIVEL][LADO_TERRENO_PRIMER_NIVEL]){
	for(int i = 0; i < nivel.tope_herramientas; i++){
		terreno[nivel.herramientas[i].posicion.fil][nivel.herramientas[i].posicion.col] = nivel.herramientas[i].tipo;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Carga la matriz terreno con los papeleos correspondientes del nivel actual.
 */
void cargar_papeleos_terreno(nivel_t nivel, char terreno[LADO_TERRENO_PRIMER_NIVEL][LADO_TERRENO_PRIMER_NIVEL]){
	for(int i = 0; i < nivel.tope_papeleos; i++){
		if(!nivel.papeleos[i].recolectado){
			terreno[nivel.papeleos[i].posicion.fil][nivel.papeleos[i].posicion.col] = (char)(nivel.papeleos[i].id_papeleo + '0');
		}
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Carga la matriz terreno con los elementos correspondientes del nivel actual.
 */
void cargar_terreno(nivel_t nivel, char terreno[LADO_TERRENO_PRIMER_NIVEL][LADO_TERRENO_PRIMER_NIVEL]){
	cargar_paredes_terreno(nivel, terreno);
	cargar_obstaculos_terreno(nivel, terreno);
	cargar_herramientas_terreno(nivel, terreno);
	cargar_papeleos_terreno(nivel, terreno);
}

/*
 * Precondiciones: -
 * Postcondiciones: Traduce el elemento del terreno a su correspondiente emoji.
 */
void imprimir_emoji(char terreno[LADO_TERRENO_PRIMER_NIVEL][LADO_TERRENO_PRIMER_NIVEL], int fila, int columna){
	if(terreno[fila][columna] == PARED){
		printf("%s", PARED_EMOJI);
	}
	else if(terreno[fila][columna] == FUEGOS){
		printf("%s", FUEGOS_EMOJI);
	}
	else if(terreno[fila][columna] == MEDIAS){
		printf("%s", MEDIAS_EMOJI);
	}
	else if(terreno[fila][columna] == BOTELLAS_DE_GRITOS){
		printf("%s", BOTELLAS_EMOJI);
	}
	else if(terreno[fila][columna] == INTERRUPTORES_AHUYENTA_RANDALL){
		printf("%s", INTERRUPTOR_EMOJI);
	}
	else if(terreno[fila][columna] == MIKE){
		printf("%s", MIKE_EMOJI);
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Carga la matriz terreno con todas las estructuras válidas del nivel y la imprime por pantalla.
 */
void mostrar_terreno(nivel_t nivel, char terreno[LADO_TERRENO_PRIMER_NIVEL][LADO_TERRENO_PRIMER_NIVEL], int tope, coordenada_t posicion_jugador){
	generar_terreno(terreno, tope);
	cargar_terreno(nivel, terreno);
	terreno[posicion_jugador.fil][posicion_jugador.col] = MIKE;
	for(int i = 0; i < tope; i++){
		for(int j = 0; j < tope; j++){
			if(terreno[i][j] == FUEGOS || terreno[i][j] == MEDIAS || terreno[i][j] == BOTELLAS_DE_GRITOS || terreno[i][j] == INTERRUPTORES_AHUYENTA_RANDALL || terreno[i][j] == PARED || terreno[i][j] == MIKE){
				imprimir_emoji(terreno, i, j);
			}
			else{
				printf(" %c", terreno[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

void imprimir_terreno(juego_t juego){
	printf("Movimientos restantes: %i | Movimientos realizados: %i\n", juego.jugador.movimientos, juego.jugador.movimientos_realizados);
	printf("Martillos: %i | Extintores: %i\n\n", juego.jugador.martillos, juego.jugador.extintores);
	char terreno[LADO_TERRENO_PRIMER_NIVEL][LADO_TERRENO_PRIMER_NIVEL];
	if(juego.nivel_actual == PRIMER_NIVEL){
		mostrar_terreno(juego.niveles[PRIMER_NIVEL - 1], terreno, LADO_TERRENO_PRIMER_NIVEL, juego.jugador.posicion);
	}
	else if(juego.nivel_actual == SEGUNDO_NIVEL){
		mostrar_terreno(juego.niveles[SEGUNDO_NIVEL - 1], terreno, LADO_TERRENO_SEGUNDO_NIVEL, juego.jugador.posicion);
	}
	else{
		mostrar_terreno(juego.niveles[TERCER_NIVEL - 1], terreno, LADO_TERRENO_PRIMER_NIVEL, juego.jugador.posicion);
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Asigna a la variable posición una fila aleatoria que se encuentre entre 1 y (filas -1) y una columna aleatoria que se encuentre
 * entre 1 y (columnas - 1).
 */
void generar_posicion(coordenada_t* posicion, int lado_terreno){
	posicion->fil = rand() % (lado_terreno - 2) + 1;
	posicion->col = rand() % (lado_terreno - 2) + 1;
}

/*
 * Precondiciones: -
 * Postcondiciones: Inicializa los topes de los distintos vectores de elementos en CERO.
 */
void inicializar_topes(int* tope_paredes, int* tope_obstaculos, int* tope_herramientas, int* tope_papeleos){
	(*tope_paredes) = CERO;
	(*tope_obstaculos) = CERO;
	(*tope_herramientas) = CERO;
	(*tope_papeleos) = CERO;
}

/*
 * Precondiciones: -
 * Postcondiciones: Verificará que la posición recibida no esté ocupada por algún otro elemento del nivel cargado hasta el momento. En ese caso devolverá true,
 * caso contrario false.
 */
bool es_coordenada_valida(nivel_t* nivel, coordenada_t posicion, char proced_randall, int pos_papeleo){
	bool valida = true;
	if(posicion.fil == nivel->pos_inicial_jugador.fil && posicion.col == nivel->pos_inicial_jugador.col){
		valida = false;
	}
	int i = 0;
	while(i < nivel->tope_paredes && valida == true){
		if(posicion.fil == nivel->paredes[i].fil && posicion.col == nivel->paredes[i].col){
			valida = false;
		}
		i++;
	}
	i = 0;
	while(i < nivel->tope_obstaculos && valida == true){
		if(posicion.fil == nivel->obstaculos[i].posicion.fil && posicion.col == nivel->obstaculos[i].posicion.col){
			valida = false;
		}
		i++;
	}
	i = 0;
	while(i < nivel->tope_herramientas && valida == true){
		if(posicion.fil == nivel->herramientas[i].posicion.fil && posicion.col == nivel->herramientas[i].posicion.col){
			valida = false;
		}
		i++;
	}
	i = 0;
	while(i < nivel->tope_papeleos && valida == true){
		if(posicion.fil == nivel->papeleos[i].posicion.fil && posicion.col == nivel->papeleos[i].posicion.col){
			if(proced_randall == SI){
				if(i != pos_papeleo){
					valida = false;
				}
			}
			else{
				valida = false;
			}
		}
		i++;
	}
	return valida;
}

/*
 * Precondiciones: -
 * Postcondiciones: Verificará que la posición recibida sea adyacente a una pared del nivel.
 */
bool es_coordenada_fuego_valida(coordenada_t paredes[MAX_PAREDES], int tope_paredes, coordenada_t posicion){
	int i = 0;
	bool posicion_valida = false;
	while(i < tope_paredes && posicion_valida == false){
		if(abs(posicion.fil - paredes[i].fil) + abs(posicion.col - paredes[i].col) == 1){
			posicion_valida = true;
		}
		i++;
	}
	return posicion_valida;
}

/*
 * Precondiciones: -
 * Postcondiciones: Inicializará un obstáculo de tipo MEDIAS en el vector de obstáculos y se le asigna una posición aleatoria.
 * 					Si la posición que le es asignada ya está ocupada por otro elemento cargado hasta el momento, se le asigna otra hasta encontrar una que no lo esté.
 */
void inicializar_media(nivel_t* nivel, int i, int lado_terreno){
	generar_posicion(&nivel->obstaculos[i].posicion, lado_terreno);
	while(!es_coordenada_valida(nivel, nivel->obstaculos[i].posicion, 'n', 0)){
		generar_posicion(&nivel->obstaculos[i].posicion, lado_terreno);
	}
	nivel->obstaculos[i].tipo = MEDIAS;
	nivel->tope_obstaculos ++;
}

/*
 * Precondiciones: -
 * Postcondiciones: Inicializará un obstáculo de tipo FUEGOS en el vector de obstáculos y se le asigna una posición aleatoria.
 * 					Si la posición que le es asignada ya está ocupada por otro elemento cargado hasta el momento o no es adyacente a una pared,
 *					se le asigna otra hasta encontrar una que cumpla ambas condiciones.
 */
void inicializar_fuego(nivel_t* nivel, int i, int lado_terreno){
	generar_posicion(&nivel->obstaculos[i].posicion, lado_terreno);
	while(!es_coordenada_valida(nivel, nivel->obstaculos[i].posicion, 'n', 0) ||
		!es_coordenada_fuego_valida(nivel->paredes, nivel->tope_paredes, nivel->obstaculos[i].posicion)){
		generar_posicion(&nivel->obstaculos[i].posicion, lado_terreno);
	}
	nivel->obstaculos[i].tipo = FUEGOS;
	nivel->tope_obstaculos ++;
}

/*
 * Precondiciones: Recibirá el primer nivel del juego y el personaje obtenido de dia_en_la_uni, el cual será OLAF, JASMÍN, RAYO o STITCH.
 * Postcondiciones: Cargará los obstáculos del primer nivel.
 */
void cargar_obstaculos_primer_nivel(nivel_t* primer_nivel, char personaje_tp1){
	for(int i = 0; i < MEDIAS_PRIMER_NIVEL; i++){
		inicializar_media(primer_nivel, i, LADO_TERRENO_PRIMER_NIVEL);
	}
	if(personaje_tp1 == OLAF){
		for(int i = MEDIAS_PRIMER_NIVEL; i < (MEDIAS_PRIMER_NIVEL + FUEGOS_PRIMER_NIVEL - FUEGOS_EXTINGUIDOS_OLAF_PRIMER_NIVEL); i++){
			inicializar_fuego(primer_nivel, i, LADO_TERRENO_PRIMER_NIVEL);
		}
	}
	else{
		for(int i = MEDIAS_PRIMER_NIVEL; i < (MEDIAS_PRIMER_NIVEL + FUEGOS_PRIMER_NIVEL); i++){
			inicializar_fuego(primer_nivel, i, LADO_TERRENO_PRIMER_NIVEL);
		}
	}
}

/*
 * Precondiciones: Recibirá el segundo nivel del juego y el personaje obtenido de dia_en_la_uni, el cual será OLAF, JASMÍN, RAYO o STITCH.
 * Postcondiciones: Cargará los obstáculos del segundo nivel.
 */
void cargar_obstaculos_segundo_nivel(nivel_t* segundo_nivel, char personaje_tp1){
	for(int i = 0; i < MEDIAS_SEGUNDO_NIVEL; i++){
		inicializar_media(segundo_nivel, i, LADO_TERRENO_SEGUNDO_NIVEL);
	}
	if(personaje_tp1 == OLAF){
		for(int i = MEDIAS_SEGUNDO_NIVEL; i < (MEDIAS_SEGUNDO_NIVEL + FUEGOS_SEGUNDO_NIVEL - FUEGOS_EXTINGUIDOS_OLAF_SEGUNDO_NIVEL); i++){
			inicializar_fuego(segundo_nivel, i, LADO_TERRENO_SEGUNDO_NIVEL);
		}
	}
	else{
		for(int i = MEDIAS_SEGUNDO_NIVEL; i < (MEDIAS_SEGUNDO_NIVEL + FUEGOS_SEGUNDO_NIVEL); i++){
			inicializar_fuego(segundo_nivel, i, LADO_TERRENO_SEGUNDO_NIVEL);
		}
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Cargará los obstáculos del tercer nivel.
 */
void cargar_obstaculos_tercer_nivel(nivel_t* tercer_nivel){
	for(int i = 0; i < MEDIAS_TERCER_NIVEL; i++){
		inicializar_media(tercer_nivel, i, LADO_TERRENO_TERCER_NIVEL);
	}
	for(int i = MEDIAS_TERCER_NIVEL; i < (MEDIAS_TERCER_NIVEL + FUEGOS_TERCER_NIVEL); i++){
		inicializar_fuego(tercer_nivel, i, LADO_TERRENO_TERCER_NIVEL);
	}
}

/*
 * Precondiciones: Recibirá un nivel del juego, el número del nivel, un entero del 1 al 3, y el personaje obtenido de dia_en_la_uni, el cual será OLAF, JASMÍN, RAYO o STITCH.
 * Postcondiciones: Cargará los obstáculos del nivel correspondiente.
 */
void obtener_obstaculos(nivel_t* nivel, int numero_nivel, char personaje_tp1){
	if(numero_nivel == PRIMER_NIVEL){
		cargar_obstaculos_primer_nivel(nivel, personaje_tp1);
	}
	else if(numero_nivel == SEGUNDO_NIVEL){
		cargar_obstaculos_segundo_nivel(nivel, personaje_tp1);
	}
	else{
		cargar_obstaculos_tercer_nivel(nivel);
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Inicializará una herramienta en el vector de herramientas y se le asigna una posición aleatoria.
 * 					Si la posición que le es asignada ya está ocupada por otro elemento cargado hasta el momento, se le asigna otra hasta encontrar una que no lo esté.
 */
void cargar_herramienta(nivel_t* nivel, int i, int lado_terreno, char tipo){
	generar_posicion(&nivel->herramientas[i].posicion, lado_terreno);
	while(!es_coordenada_valida(nivel, nivel->herramientas[i].posicion, 'n', 0)){
		generar_posicion(&nivel->herramientas[i].posicion, lado_terreno);
	}
	nivel->herramientas[i].tipo = tipo;
	nivel->tope_herramientas ++;
}

/*
 * Precondiciones: -
 * Postcondiciones: Cargará las herramientas del primer nivel.
 */
void cargar_herramientas_primer_nivel(nivel_t* primer_nivel){
	for(int i = 0; i < BOTELLAS_PRIMER_NIVEL; i++){
		cargar_herramienta(primer_nivel, i, LADO_TERRENO_PRIMER_NIVEL, BOTELLAS_DE_GRITOS);
	}
	for(int i = BOTELLAS_PRIMER_NIVEL; i < (BOTELLAS_PRIMER_NIVEL + INTERRUPTORES_PRIMER_NIVEL); i++){
		cargar_herramienta(primer_nivel, i, LADO_TERRENO_PRIMER_NIVEL, INTERRUPTORES_AHUYENTA_RANDALL);
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Cargará las herramientas del segundo nivel.
 */
void cargar_herramientas_segundo_nivel(nivel_t* segundo_nivel){
	for(int i = 0; i < BOTELLAS_SEGUNDO_NIVEL; i++){
		cargar_herramienta(segundo_nivel, i, LADO_TERRENO_SEGUNDO_NIVEL, BOTELLAS_DE_GRITOS);
	}
	for(int i = BOTELLAS_SEGUNDO_NIVEL; i < (BOTELLAS_SEGUNDO_NIVEL + INTERRUPTORES_SEGUNDO_NIVEL); i++){
		cargar_herramienta(segundo_nivel, i, LADO_TERRENO_SEGUNDO_NIVEL, INTERRUPTORES_AHUYENTA_RANDALL);
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Cargará las herramientas del tercer nivel.
 */
void cargar_herramientas_tercer_nivel(nivel_t* tercer_nivel){
	for(int i = 0; i < BOTELLAS_TERCER_NIVEL; i++){
		cargar_herramienta(tercer_nivel, i, LADO_TERRENO_TERCER_NIVEL, BOTELLAS_DE_GRITOS);
	}
	for(int i = BOTELLAS_TERCER_NIVEL; i < (BOTELLAS_TERCER_NIVEL + INTERRUPTORES_TERCER_NIVEL); i++){
		cargar_herramienta(tercer_nivel, i, LADO_TERRENO_TERCER_NIVEL, INTERRUPTORES_AHUYENTA_RANDALL);
	}
}

/*
 * Precondiciones: Recibirá un nivel del juego y el número del nivel, el cual será un entero del 1 al 3.
 * Postcondiciones: Cargará las herramientas del nivel correspondiente.
 */
void obtener_herramientas(nivel_t* nivel, int numero_nivel){
	if(numero_nivel == PRIMER_NIVEL){
		cargar_herramientas_primer_nivel(nivel);
	}
	else if(numero_nivel == SEGUNDO_NIVEL){
		cargar_herramientas_segundo_nivel(nivel);
	}
	else{
		cargar_herramientas_tercer_nivel(nivel);
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Cargará un papeleo del nivel correspondiente, inicianizándolo en el vector de papeleos y asignándole una posición aleatoria.
 *					Si la posición que le es asignada ya está ocupada por otro elemento cargado hasta el momento, se le asigna otra hasta encontrar una que no lo esté.
 */
void cargar_papeleos(nivel_t* nivel, int i, int lado_terreno){
	generar_posicion(&nivel->papeleos[i].posicion, lado_terreno);
	while(!es_coordenada_valida(nivel, nivel->papeleos[i].posicion, 'n', 0)){
		generar_posicion(&nivel->papeleos[i].posicion, lado_terreno);
	}
	nivel->papeleos[i].id_papeleo = i + 1;
	nivel->papeleos[i].recolectado = false;
	nivel->tope_papeleos ++;
}


/*
 * Precondiciones: Recibirá un nivel del juego, el número del nivel, un entero del 1 al 3, y el personaje obtenido de dia_en_la_uni, el cual será OLAF, JASMÍN, RAYO o STITCH.
 * Postcondiciones: Cargará los papeleos del nivel correspondiente.
 */
void obtener_papeleos(nivel_t* nivel, int numero_nivel, char personaje_tp1){
	if(numero_nivel == PRIMER_NIVEL){
		for(int i = 0; i < PAPELEOS_PRIMER_NIVEL; i++){
			cargar_papeleos(nivel, i, LADO_TERRENO_PRIMER_NIVEL);
		}
	}
	else if(numero_nivel == SEGUNDO_NIVEL){
		for(int i = 0; i < PAPELEOS_SEGUNDO_NIVEL; i++){
			cargar_papeleos(nivel, i, LADO_TERRENO_SEGUNDO_NIVEL);
		}
	}
	else{
		if(personaje_tp1 == STITCH){
			for(int i = 0; i < PAPELEOS_TERCER_NIVEL - PAPELEO_QUEMADO_STITCH; i++){
				cargar_papeleos(nivel, i, LADO_TERRENO_TERCER_NIVEL);
			}
		}
		else{
			for(int i = 0; i < PAPELEOS_TERCER_NIVEL; i++){
				cargar_papeleos(nivel, i, LADO_TERRENO_TERCER_NIVEL);
			}
		}
	}
}

void inicializar_nivel(nivel_t* nivel, int numero_nivel, char personaje_tp1){
	inicializar_topes(&nivel->tope_paredes, &nivel->tope_obstaculos, &nivel->tope_herramientas, &nivel->tope_papeleos);
	obtener_paredes(numero_nivel, nivel->paredes, &nivel->tope_paredes, &nivel->pos_inicial_jugador);
	obtener_obstaculos(nivel, numero_nivel, personaje_tp1);
	obtener_herramientas(nivel, numero_nivel);
	obtener_papeleos(nivel, numero_nivel, personaje_tp1);
}

/*
 * Precondiciones: Recibirá el jugador y el personaje obtenido de dia_en_la_uni, el cual será OLAF, JASMÍN, RAYO o STITCH.
 * Postcondiciones: Inicializará el personaje del primer nivel cargando todos los datos del mismo.
 * 					Si el personaje es RAYO, se le sumará OBSEQUIO_RAYO a los movimientos del jugador.
 * 					Si el personaje es JASMIN, se le sumará OBSEQUIO_JASMIN a los martillos del jugador.
 */
void inicializar_personaje_primer_nivel(jugador_t* jugador, char personaje_tp1){
	if(personaje_tp1 == RAYO){
		jugador->movimientos = MOVIMIENTOS_PRIMER_NIVEL + OBSEQUIO_RAYO;
	}
	else{
		jugador->movimientos = MOVIMIENTOS_PRIMER_NIVEL;
	}
	if(personaje_tp1 == JASMIN){
		jugador->martillos = MARTILLOS_PRIMER_NIVEL + OBSEQUIO_JASMIN;
	}
	else{
		jugador->martillos = MARTILLOS_PRIMER_NIVEL;
	}
	jugador->extintores = EXTINTORES_PRIMER_NIVEL;
	jugador->ahuyenta_randall = false;
}

/*
 * Precondiciones: Recibirá el jugador y el personaje obtenido de dia_en_la_uni, el cual será OLAF, JASMÍN, RAYO o STITCH.
 * Postcondiciones: Inicializará el personaje del segundo nivel cargando todos los datos del mismo.
 * 					Si el personaje es JASMIN, se le sumará OBSEQUIO_JASMIN a los martillos del jugador.
 */
void inicializar_personaje_segundo_nivel(jugador_t* jugador, char personaje_tp1){
	jugador->movimientos += MOVIMIENTOS_SEGUNDO_NIVEL;
	if(personaje_tp1 == JASMIN){
		jugador->martillos = MARTILLOS_SEGUNDO_NIVEL + OBSEQUIO_JASMIN;
	}
	else{
		jugador->martillos = MARTILLOS_SEGUNDO_NIVEL;
	}
	jugador->extintores = EXTINTORES_SEGUNDO_NIVEL;
	jugador->ahuyenta_randall = false;
}

/*
 * Precondiciones: Recibirá el jugador y el personaje obtenido de dia_en_la_uni, el cual será OLAF, JASMÍN, RAYO o STITCH.
 * Postcondiciones: Inicializará el personaje del segundo nivel cargando todos los datos del mismo.
 * 					Si el personaje es JASMIN, se le sumará OBSEQUIO_JASMIN a los martillos del jugador.
 */
void inicializar_personaje_tercer_nivel(jugador_t* jugador, char personaje_tp1){
	jugador->movimientos += MOVIMIENTOS_TERCER_NIVEL;
	if(personaje_tp1 == JASMIN){
		jugador->martillos = MARTILLOS_TERCER_NIVEL + OBSEQUIO_JASMIN;
	}
	else{
		jugador->martillos = MARTILLOS_TERCER_NIVEL;
	}
	jugador->extintores = EXTINTORES_TERCER_NIVEL;
	jugador->ahuyenta_randall = false;
}

/*
 * Precondiciones: Recibirá el jugador, el nivel actual, un número entero del 1 al 3, y el personaje obtenido de dia_en_la_uni, el cual será OLAF, JASMÍN, RAYO o STITCH.
 * Postcondiciones: Inicializará el personaje correspondiente al nivel actual con todos los datos del mismo.
 */
void inicializar_personaje(jugador_t* jugador, int nivel_actual, char personaje_tp1, coordenada_t pos_inicial_jugador){
	jugador->posicion.fil = pos_inicial_jugador.fil;
	jugador->posicion.col = pos_inicial_jugador.col;
	jugador->movimientos_realizados = 0;
	if(nivel_actual == PRIMER_NIVEL){
		inicializar_personaje_primer_nivel(jugador, personaje_tp1);
	}
	else if(nivel_actual == SEGUNDO_NIVEL){
		inicializar_personaje_segundo_nivel(jugador, personaje_tp1);
	}
	else{
		inicializar_personaje_tercer_nivel(jugador, personaje_tp1);
	}
}

void inicializar_juego(juego_t* juego, char personaje_tp1){
	juego->personaje_tp1 = personaje_tp1;
	juego->nivel_actual = PRIMER_NIVEL;
	for(int i = 0; i < CANTIDAD_NIVELES; i++){
		inicializar_nivel(&juego->niveles[i], i + 1, personaje_tp1);
	}
	inicializar_personaje(&juego->jugador, PRIMER_NIVEL, personaje_tp1, juego->niveles[juego->nivel_actual].pos_inicial_jugador);
}

int estado_nivel(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
	int i = 0;
	bool completado = true;
	while(i < tope_papeleos && completado){
		if(!papeleos[i].recolectado){
			completado = false;
		}
		i++;
	}
	if(completado){
		return GANADO;
	}
	else{
		return EN_CURSO;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Determinará si todos los niveles están gananado y devuelve true si lo están o false en caso contrario.
 */
bool estan_niveles_ganados(nivel_t niveles[MAX_NIVELES]){
	int i = 0;
	bool ganados = true;
	while(i < CANTIDAD_NIVELES && ganados){
		if(estado_nivel(niveles[i].papeleos, niveles[i].tope_papeleos) == EN_CURSO){
			ganados = false;
		}
		i++;
	}
	return ganados;
}

int estado_juego(juego_t juego){
	if(estan_niveles_ganados(juego.niveles)){
		return GANADO;
	}
	if(juego.jugador.movimientos <= 0){
		return PERDIDO;
	}
	else{
		return EN_CURSO;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Si la variable jugada no es válida, se le volverá a pedir una jugada al usuario hasta que ingrese una que sí lo sea.
 */
void verificar_jugada(char* jugada){
	while((*jugada) != MOVIMIENTO_DERECHA && (*jugada) != MOVIMIENTO_IZQUIERDA && (*jugada) != ROTAR_HORARIO && (*jugada) != ROTAR_ANTIHORARIO && (*jugada) != MARTILLO && (*jugada) != EXTINTOR){
		printf("Esa jugada no es válida, por favor ingresar una que sí lo sea.\n");
		scanf(" %c", jugada);
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Le pedirá al usuario que ingrese una jugada y la devolverá.
 */
char pedir_jugada(juego_t* juego){
	printf("Ingrese: %c para rotar en sentido horario\n", ROTAR_HORARIO);
	printf("         %c para rotar en sentido antihorario\n", ROTAR_ANTIHORARIO);
	printf("         %c para moverse hacia la derecha\n", MOVIMIENTO_DERECHA);
	printf("         %c para moverse hacia la izquierda\n", MOVIMIENTO_IZQUIERDA);
	printf("         %c para utilizar un martillo\n", MARTILLO);
	printf("         %c para utilizar un extintor\n\n", EXTINTOR);
	char jugada;
	scanf(" %c", &jugada);
	verificar_jugada(&jugada);
	return jugada;
}

/*
 * Precondiciones: La variable nivel debe ser PRIMER_NIVEL, SEGUNDO_NIVEL o TERCER_NIVEL.
 * Postcondiciones: Devolverá el terreno correspondiente al nivel.
 */
int lado(int nivel){
	if(nivel == PRIMER_NIVEL){
		return LADO_TERRENO_PRIMER_NIVEL;
	}
	else if(nivel == SEGUNDO_NIVEL){
		return LADO_TERRENO_SEGUNDO_NIVEL;
	}
	else{
		return LADO_TERRENO_TERCER_NIVEL;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Determinará si el movimiento es válido. Si lo es devolverá true y si no false.
 */
bool es_movimiento_valido(nivel_t* nivel, coordenada_t posicion, char direccion){
	if(direccion == MOVIMIENTO_DERECHA){
		posicion.col++;
	}
	else{
		posicion.col--;
	}
	int i = 0;
	bool movimiento_valido = true;
	while(movimiento_valido && i < nivel->tope_paredes){
		if(nivel->paredes[i].fil == posicion.fil && nivel->paredes[i].col == posicion.col){
			movimiento_valido = false;
		}
		i++;
	}
	return movimiento_valido;
}

/*
 * Precondiciones: -
 * Postcondiciones: Si el jugador se tope con un fuego, sus movimientos serán MOVIMIENTOS_SOBRANTES_FUEGO.
 *					Si se topa con una media, se le restará MOVIMIENTOS_PERDIDOS_MEDIA a sus movimientos.
 */
void topar_obstaculo(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos, coordenada_t posicion, int* movimientos){
	int i = 0;
	bool topado = false;
	while(!topado && i < tope_obstaculos){
		if(obstaculos[i].posicion.fil == posicion.fil && obstaculos[i].posicion.col == posicion.col){
			topado = true;
			if(obstaculos[i].tipo == FUEGOS){
				(*movimientos) = MOVIMIENTOS_SOBRANTES_FUEGO;
			}
			else{
				(*movimientos) -= MOVIMIENTOS_PERDIDOS_MEDIA;
			}
		}
		i++;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Si el jugador se topa con un interruptor ahuyenta Randall, si ahuyenta_randall es false pasará a ser true y si es true pasará a ser false.
 *					Si el jugador se topa con una botella de gritos, se le sumará MOVIMIENTOS_GANADOS_BOTELLA a sus movimientos.
 */
void topar_herramienta(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, coordenada_t posicion, bool* ahuyenta_randall, int* movimientos){
	int i = 0;
	bool topado = false;
	while(!topado && i < tope_herramientas){
		if(herramientas[i].posicion.fil == posicion.fil && herramientas[i].posicion.col == posicion.col){
			topado = true;
			if(herramientas[i].tipo == INTERRUPTORES_AHUYENTA_RANDALL){
				if((*ahuyenta_randall) == false){
					(*ahuyenta_randall) = true;
				}
				else{
					(*ahuyenta_randall) = false;
				}
			}
			else{
				(*movimientos) += MOVIMIENTOS_GANADOS_BOTELLA;
			}
		}
		i++;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones:	Si el jugador se topa con un papaleo, si el papeleo con el id anterior ya fue recolectado, el campo recolectado del papeleo topado será true.
 */
void recolectar_papeleo(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos, int posicion){
	if(posicion == 0){
		papeleos[posicion].recolectado = true;
	}
	else{
		if(papeleos[posicion - 1].recolectado == true){
			papeleos[posicion].recolectado = true;
		}
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Si el jugador se topa con un papaleo, si el papeleo con el id anterior ya fue recolectado, el campo recolectado del papeleo topado será true.
 */
void topar_papeleo(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos, coordenada_t posicion){
	int i = 0;
	bool topado = false;
	while(!topado && i < tope_papeleos){
		if(papeleos[i].posicion.fil == posicion.fil && papeleos[i].posicion.col == posicion.col){
			topado = true;
			recolectar_papeleo(papeleos, tope_papeleos, i);
		}
		i++;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: En caso de que el jugador se tope con un elemento del juego, se ejecutará la acción correspondiente.
 */
void realizar_movimiento(nivel_t* nivel, jugador_t* jugador){
	jugador->movimientos--;
	jugador->movimientos_realizados++;
	topar_obstaculo(nivel->obstaculos, nivel->tope_obstaculos, jugador->posicion, &jugador->movimientos);
	topar_herramienta(nivel->herramientas, nivel->tope_herramientas, jugador->posicion, &jugador->ahuyenta_randall, &jugador->movimientos);
	topar_papeleo(nivel->papeleos, nivel->tope_papeleos, jugador->posicion);
}

/*
 * Precondiciones: La variable direccion debe ser MOVIMIENTO_DERECHA o MOVIMIENTO_IZQUIERDA.
 * Postcondiciones: Dependiendo el sentido de la dirección, el personaje se moverá para la derecha o para la izquierda si no hay una pared que se interponga.
 */
void movimiento(nivel_t* nivel, jugador_t* jugador, char direccion){
	if(direccion == MOVIMIENTO_DERECHA){
		if(es_movimiento_valido(nivel, jugador->posicion, MOVIMIENTO_DERECHA)){
			jugador->posicion.col++;
			realizar_movimiento(nivel, jugador);
		}
	}
	else{
		if(es_movimiento_valido(nivel, jugador->posicion, MOVIMIENTO_IZQUIERDA)){
			jugador->posicion.col--;
			realizar_movimiento(nivel, jugador);
		}
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Rotará la coordenada en el sentido indicado.
 */
void rotar_coordenada(coordenada_t* posicion, int lado_terreno, char sentido){
	coordenada_t coordenada;
	coordenada.fil = posicion->fil;
	coordenada.col = posicion->col;
	if(sentido == ROTAR_HORARIO){
		posicion->fil = coordenada.col;
		posicion->col = abs(coordenada.fil - lado_terreno + 1);
	}
	else{
		posicion->fil = abs(coordenada.col - lado_terreno + 1);
		posicion->col = coordenada.fil;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Rotará las paredes del nivel.
 */
void rotar_paredes(coordenada_t paredes[MAX_PAREDES], int tope_paredes, int lado_terreno, char sentido){
	for(int i = 0; i < tope_paredes; i++){
		rotar_coordenada(&paredes[i], lado_terreno, sentido);
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Rotará los obstáculos del nivel.
 */
void rotar_obstaculos(objeto_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos, int lado_terreno, char sentido){
	for(int i = 0; i < tope_obstaculos; i++){
		rotar_coordenada(&obstaculos[i].posicion, lado_terreno, sentido);
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Rotará las herramientas del nivel.
 */
void rotar_herramientas(objeto_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, int lado_terreno, char sentido){
	for(int i = 0; i < tope_herramientas; i++){
		rotar_coordenada(&herramientas[i].posicion, lado_terreno, sentido);
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Rotará los papeleos del nivel.
 */
void rotar_papeleos(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos, int lado_terreno, char sentido){
	for(int i = 0; i < tope_papeleos; i++){
		rotar_coordenada(&papeleos[i].posicion, lado_terreno, sentido);
	}
}

/*
 * Precondiciones: La variable lado_terreno debe ser LADO_TERRENO_PRIMER_NIVEL, LADO_TERRENO_SEGUNDO_NIVEL o LADO_TERRENO_TERCER_NIVEL.
 *					La variable sentido debe ser ROTAR_HORARIO o ROTAR_ANTIHORARIO.
 * Postcondiciones: Rotará todos los elementos del nivel, incluyendo al jugador.
 */
void rotar(juego_t* juego, int lado_terreno, char sentido){
	rotar_paredes(juego->niveles[juego->nivel_actual - 1].paredes, juego->niveles[juego->nivel_actual - 1].tope_paredes, lado_terreno, sentido);
	rotar_obstaculos(juego->niveles[juego->nivel_actual - 1].obstaculos, juego->niveles[juego->nivel_actual - 1].tope_obstaculos, lado_terreno, sentido);
	rotar_herramientas(juego->niveles[juego->nivel_actual - 1].herramientas, juego->niveles[juego->nivel_actual - 1].tope_herramientas, lado_terreno, sentido);
	rotar_papeleos(juego->niveles[juego->nivel_actual - 1].papeleos, juego->niveles[juego->nivel_actual - 1].tope_papeleos, lado_terreno, sentido);
	rotar_coordenada(&juego->jugador.posicion, lado_terreno, sentido);
	juego->jugador.movimientos_realizados++;
	juego->jugador.movimientos--;
}

/*
 * Precondiciones: La variable elemento debe ser PARED o FUEGOS.
 * Postcondiciones: Si la dirección es inválida se le informará al usuario por pantalla.
 */
void verificar_direccion(char* direccion, char elemento){
	if(elemento == PARED){
		while((*direccion) != ROMPER_PARED_ARRIBA && (*direccion) != ROMPER_PARED_ABAJO && (*direccion) != ROMPER_PARED_DERECHA && (*direccion) != ROMPER_PARED_IZQUIERDA){
			printf("Esa jugada no es válida, por favor ingresar una que sí lo sea.\n");
			scanf(" %c", direccion);
		}
	}
	else{
		while((*direccion) != APAGAR_FUEGO_IZQUIERDA && (*direccion) != APAGAR_FUEGO_DERECHA && (*direccion) != APAGAR_FUEGO_ARRIBA){
			printf("Esa jugada no es válida, por favor ingresar una que sí lo sea.\n");
			scanf(" %c", direccion);
		}
	}
}

/*
 * Precondiciones: La variable lado_terreno debe ser LADO_TERRENO_PRIMER_NIVEL, LADO_TERRENO_SEGUNDO_NIVEL o LADO_TERRENO_TERCER_NIVEL.
 * Postcondiciones: Si la pared corresponde al borde del terreno devolverá true o false en caso contrario.
 */
bool pertenece_al_borde(coordenada_t pared, int lado_terreno){
	return ((pared.fil == PRIMERA_FILA || pared.fil == lado_terreno - 1) || (pared.col == PRIMERA_COLUMNA || pared.col == lado_terreno - 1));
}

/*
 * Precondiciones: -
 * Postcondiciones: Eliminará físicamente una pared del vector de paredes.
 */
void eliminar_pared(coordenada_t paredes[MAX_PAREDES], int* tope_paredes, int posicion){
	paredes[posicion].fil = paredes[(*tope_paredes) - 1].fil;
	paredes[posicion].col = paredes[(*tope_paredes) - 1].col;
	(*tope_paredes)--;
}

/*
 * Precondiciones: La variable lado_terreno debe ser LADO_TERRENO_PRIMER_NIVEL, LADO_TERRENO_SEGUNDO_NIVEL o LADO_TERRENO_TERCER_NIVEL.
 * Postcondiciones: Si la pared a romper no pertenece al borde del terreno será eliminada.
 */
void romper_pared(coordenada_t paredes[MAX_PAREDES], int* tope_paredes, int* martillos, int fila_pared, int columna_pared, int lado_terreno){
	int i = 0;
	bool pared_encontrada = false;
	while(i < (*tope_paredes) && !pared_encontrada){
		if(paredes[i].fil == fila_pared && paredes[i].col == columna_pared){
			pared_encontrada = true;
			if(!pertenece_al_borde(paredes[i], lado_terreno)){
				eliminar_pared(paredes, tope_paredes, i);
				(*martillos)--;
			}
			else{
				printf("No es posible romper esa pared.");
			}
		}
		i++;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Le pedirá al usuario que ingrese la dirección en la que desea romper la pared.
 */
 void preguntar_direccion_martillo(char* direccion){
 	printf("Romperás una pared!\nElije: %c para romper la pared a tu derecha\n", ROMPER_PARED_DERECHA);
	printf("       %c para romper la pared a tu izquierda\n", ROMPER_PARED_IZQUIERDA);
	printf("       %c para romper la pared de arriba\n", ROMPER_PARED_ARRIBA);
	printf("       %c para romper la pared de abajo\n\n", ROMPER_PARED_ABAJO);
	scanf(" %c", direccion);
 }

/*
 * Precondiciones: La variable lado_terreno debe ser LADO_TERRENO_PRIMER_NIVEL, LADO_TERRENO_SEGUNDO_NIVEL o LADO_TERRENO_TERCER_NIVEL.
 * Postcondiciones: Se utilizará un martillo para romper una pared que se encuentre arriba, abajo, a la derecha o a la izquierda del personaje.
 */
void utilizar_martillo(int* martillos, coordenada_t posicion, coordenada_t paredes[MAX_PAREDES], int* tope_paredes, int lado_terreno){
	if((*martillos) > 0){
		char direccion;
		preguntar_direccion_martillo(&direccion);
		verificar_direccion(&direccion, PARED);
		if(direccion == ROMPER_PARED_ARRIBA){
			romper_pared(paredes, tope_paredes, martillos, (posicion.fil - 1), posicion.col, lado_terreno);
		}
		else if(direccion == ROMPER_PARED_ABAJO){
			romper_pared(paredes, tope_paredes, martillos, (posicion.fil + 1), posicion.col, lado_terreno);
		}
		else if(direccion == ROMPER_PARED_DERECHA){
			romper_pared(paredes, tope_paredes, martillos, posicion.fil, (posicion.col + 1), lado_terreno);
		}
		else{
			romper_pared(paredes, tope_paredes, martillos, posicion.fil, (posicion.col - 1), lado_terreno);
		}
	}
	else{
		printf("Te has quedado sin martillos!");
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Eliminará físicamente un fuego del vector de obstáculos.
 */
void eliminar_fuego(objeto_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos, int posicion){
	obstaculos[posicion].tipo = obstaculos[(*tope_obstaculos) - 1].tipo;
	obstaculos[posicion].posicion.fil = obstaculos[(*tope_obstaculos) - 1].posicion.fil;
	obstaculos[posicion].posicion.col = obstaculos[(*tope_obstaculos) - 1].posicion.col;
	(*tope_obstaculos)--;
}

/*
 * Precondiciones: -
 * Postcondiciones: Apagará un fuego del nivel.
 */
void apagar_fuego(objeto_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos, int fila_fuego, int columna_fuego, int* extintores){
	int i = 0;
	bool fuego_encontrado = false;
	while(!fuego_encontrado && i < (*tope_obstaculos)){
		if(obstaculos[i].posicion.fil == fila_fuego && obstaculos[i].posicion.col == columna_fuego){
			fuego_encontrado = true;
			eliminar_fuego(obstaculos, tope_obstaculos, i);
			(*extintores)--;
		}
		i++;
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Le pedirá al usuario la dirección en la que desea apagar el fuego.
 */
void preguntar_direccion_extintor(char* direccion){
	printf("Apagarás un fuego!\nElije: %c para apagar un fuego que tengas a tu derecha\n", APAGAR_FUEGO_DERECHA);
	printf("       %c para apagar un fuego que tengas a tu izquierda\n", APAGAR_FUEGO_IZQUIERDA);
	printf("       %c para apagar un fuego que tengas arriba tuyo\n\n", APAGAR_FUEGO_ARRIBA);
	scanf(" %c", direccion);
}

/*
 * Precondiciones: -
 * Postcondiciones: Se utilizará un extintor para apagar un fuego que se encuentre arriba, a la derecha o a la izquierda del personaje.
 */
void utilizar_extintor(int* extintores, coordenada_t posicion, objeto_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos){
	if((*extintores) > 0){
		char direccion;
		preguntar_direccion_extintor(&direccion);
		verificar_direccion(&direccion, FUEGOS);
		if(direccion == APAGAR_FUEGO_ARRIBA){
			apagar_fuego(obstaculos, tope_obstaculos, (posicion.fil - 1), posicion.col, extintores);
		}
		else if(direccion == APAGAR_FUEGO_DERECHA){
			apagar_fuego(obstaculos, tope_obstaculos, posicion.fil, (posicion.col + 1), extintores);
		}
		else{
			apagar_fuego(obstaculos, tope_obstaculos, posicion.fil, (posicion.col - 1), extintores);
		}
	}
	else{
		printf("Te has quedado sin extintores!");
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Devolverá true si en la coordenada que está abajo de la del personaje hay una pared o false en caso contrario.
 */
bool hay_pared_abajo(coordenada_t paredes[MAX_PAREDES], int tope_paredes, int fila_pared, int columna_pared){
	int i = 0;
	bool pared_debajo = false;
	while(!pared_debajo && i < tope_paredes){
		if(paredes[i].fil == fila_pared && paredes[i].col == columna_pared){
			pared_debajo = true;
		}
		i++;
	}
	return pared_debajo;
}

/*
 * Precondiciones: -
 * Postcondiciones: Mientras que no haya una pared en la coordenada que está abajo de la del personaje, este caerá.
 */
void aplicar_gravedad(jugador_t* jugador, nivel_t* nivel){
	while(!hay_pared_abajo(nivel->paredes, nivel->tope_paredes, (jugador->posicion.fil + 1), jugador->posicion.col)){
		jugador->posicion.fil++;
		topar_obstaculo(nivel->obstaculos, nivel->tope_obstaculos, jugador->posicion, &jugador->movimientos);
		topar_herramienta(nivel->herramientas, nivel->tope_herramientas, jugador->posicion, &jugador->ahuyenta_randall, &jugador->movimientos);
		topar_papeleo(nivel->papeleos, nivel->tope_papeleos, jugador->posicion);
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Devolverá una posición random del vector de papeleos.
 */
int papeleo_random(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
	int posicion_random = rand() % tope_papeleos;
	while(papeleos[posicion_random].recolectado){
		posicion_random = rand() % tope_papeleos;
	}
	return posicion_random;
}

/*
 * Precondiciones: -
 * Postcondiciones: Si la variable ahuyenta_randall es false, un papaleo random (no recolectado) se teletransportará a una posición aleatoria si la variable movimientos_realizados
 *					es divisible por R, siendo R un valor distinto cada nivel.
 */
void randall(nivel_t niveles[MAX_NIVELES], bool ahuyenta_randall, int nivel_actual, int movimientos_realizados){
	if(!ahuyenta_randall){
		int posicion_random;
		if(nivel_actual == PRIMER_NIVEL){
			if(movimientos_realizados % RANDALL_PRIMER_NIVEL == 0){
				posicion_random = papeleo_random(niveles[PRIMER_NIVEL - 1].papeleos, niveles[PRIMER_NIVEL - 1].tope_papeleos);
				generar_posicion(&niveles[PRIMER_NIVEL - 1].papeleos[posicion_random].posicion, LADO_TERRENO_PRIMER_NIVEL);
				while(!es_coordenada_valida(&niveles[PRIMER_NIVEL - 1], niveles[PRIMER_NIVEL - 1].papeleos[posicion_random].posicion, SI, posicion_random)){
					generar_posicion(&niveles[PRIMER_NIVEL - 1].papeleos[posicion_random].posicion, LADO_TERRENO_PRIMER_NIVEL);
				}
			}
		}
		else if(nivel_actual == SEGUNDO_NIVEL){
			if(movimientos_realizados % RANDALL_SEGUNDO_NIVEL == 0){
				posicion_random = papeleo_random(niveles[SEGUNDO_NIVEL - 1].papeleos, niveles[SEGUNDO_NIVEL - 1].tope_papeleos);
				generar_posicion(&niveles[SEGUNDO_NIVEL - 1].papeleos[posicion_random].posicion, LADO_TERRENO_SEGUNDO_NIVEL);
				while(!es_coordenada_valida(&niveles[SEGUNDO_NIVEL - 1], niveles[SEGUNDO_NIVEL - 1].papeleos[posicion_random].posicion, SI, posicion_random)){
					generar_posicion(&niveles[SEGUNDO_NIVEL - 1].papeleos[posicion_random].posicion, LADO_TERRENO_SEGUNDO_NIVEL);
				}
			}
		}
		else{
			if(movimientos_realizados % RANDALL_TERCER_NIVEL == 0){
				posicion_random = papeleo_random(niveles[TERCER_NIVEL - 1].papeleos, niveles[TERCER_NIVEL - 1].tope_papeleos);
				generar_posicion(&niveles[TERCER_NIVEL - 1].papeleos[posicion_random].posicion, LADO_TERRENO_TERCER_NIVEL);
				while(!es_coordenada_valida(&niveles[TERCER_NIVEL - 1], niveles[TERCER_NIVEL - 1].papeleos[posicion_random].posicion, SI, posicion_random)){
					generar_posicion(&niveles[TERCER_NIVEL - 1].papeleos[posicion_random].posicion, LADO_TERRENO_TERCER_NIVEL);
				}
			}
		}
	}
}

/*
 * Precondiciones: -
 * Postcondiciones: Durante los primeros X movimientos del jugador en el respectivo nivel, aparecerá una nueva pared en una posición aleatoria, válida y libre.
 */
void pared_random(nivel_t niveles[MAX_NIVELES], int nivel_actual, int movimientos_realizados){
	if(nivel_actual == PRIMER_NIVEL){
		if(movimientos_realizados < MOVIMIENTOS_PARED_PRIMER_NIVEL){
			generar_posicion(&niveles[PRIMER_NIVEL - 1].paredes[niveles[PRIMER_NIVEL - 1].tope_paredes], LADO_TERRENO_PRIMER_NIVEL);
			while(!es_coordenada_valida(&niveles[PRIMER_NIVEL - 1], niveles[PRIMER_NIVEL - 1].paredes[niveles[PRIMER_NIVEL - 1].tope_paredes],'n', 0)){
				generar_posicion(&niveles[PRIMER_NIVEL - 1].paredes[niveles[PRIMER_NIVEL - 1].tope_paredes], LADO_TERRENO_PRIMER_NIVEL);
			}
			niveles[PRIMER_NIVEL - 1].tope_paredes++;
		}
	}
	else if(nivel_actual == SEGUNDO_NIVEL){
		if(movimientos_realizados < MOVIMIENTOS_PARED_SEGUNDO_NIVEL){
			generar_posicion(&niveles[SEGUNDO_NIVEL - 1].paredes[niveles[SEGUNDO_NIVEL - 1].tope_paredes], LADO_TERRENO_SEGUNDO_NIVEL);
			while(!es_coordenada_valida(&niveles[SEGUNDO_NIVEL - 1], niveles[SEGUNDO_NIVEL - 1].paredes[niveles[SEGUNDO_NIVEL - 1].tope_paredes], 'n', 0)){
				generar_posicion(&niveles[SEGUNDO_NIVEL - 1].paredes[niveles[SEGUNDO_NIVEL - 1].tope_paredes], LADO_TERRENO_SEGUNDO_NIVEL);
			}
			niveles[SEGUNDO_NIVEL - 1].tope_paredes++;
		}
	}
	else{
		if(movimientos_realizados < MOVIMIENTOS_PARED_TERCER_NIVEL){
			generar_posicion(&niveles[TERCER_NIVEL - 1].paredes[niveles[TERCER_NIVEL - 1].tope_paredes], LADO_TERRENO_TERCER_NIVEL);
			while(!es_coordenada_valida(&niveles[TERCER_NIVEL - 1], niveles[TERCER_NIVEL - 1].paredes[niveles[TERCER_NIVEL - 1].tope_paredes], 'n', 0)){
				generar_posicion(&niveles[TERCER_NIVEL - 1].paredes[niveles[TERCER_NIVEL - 1].tope_paredes], LADO_TERRENO_TERCER_NIVEL);
			}
			niveles[TERCER_NIVEL - 1].tope_paredes++;
		}
	}
}

void realizar_jugada(juego_t* juego){
	char jugada = pedir_jugada(juego);
	int lado_terreno = lado(juego->nivel_actual);
	coordenada_t posicion; posicion.fil = juego->jugador.posicion.fil; posicion.col = juego->jugador.posicion.col;
	if(jugada == MOVIMIENTO_DERECHA){
		movimiento(&juego->niveles[juego->nivel_actual - 1], &juego->jugador, MOVIMIENTO_DERECHA);
		if(juego->jugador.posicion.fil !=  posicion.fil || juego->jugador.posicion.col != posicion.col){
			pared_random(juego->niveles, juego->nivel_actual, juego->jugador.movimientos_realizados);
		}
	}
	else if(jugada == MOVIMIENTO_IZQUIERDA){
		movimiento(&juego->niveles[juego->nivel_actual - 1], &juego->jugador, MOVIMIENTO_IZQUIERDA);
		if(juego->jugador.posicion.fil !=  posicion.fil || juego->jugador.posicion.col != posicion.col){
			pared_random(juego->niveles, juego->nivel_actual, juego->jugador.movimientos_realizados);
		}
	}
	else if(jugada == ROTAR_HORARIO){
		rotar(juego, lado_terreno, ROTAR_HORARIO);
		pared_random(juego->niveles, juego->nivel_actual, juego->jugador.movimientos_realizados);
	}
	else if(jugada == ROTAR_ANTIHORARIO){
		rotar(juego, lado_terreno, ROTAR_ANTIHORARIO);
		pared_random(juego->niveles, juego->nivel_actual, juego->jugador.movimientos_realizados);
	}
	else if(jugada == MARTILLO){
		utilizar_martillo(&juego->jugador.martillos, juego->jugador.posicion, juego->niveles[juego->nivel_actual - 1].paredes, &juego->niveles[juego->nivel_actual - 1].tope_paredes, lado_terreno);
	}
	else{
		utilizar_extintor(&juego->jugador.extintores, juego->jugador.posicion, juego->niveles[juego->nivel_actual - 1].obstaculos, &juego->niveles[juego->nivel_actual - 1].tope_obstaculos);
	}
	aplicar_gravedad(&juego->jugador, &juego->niveles[juego->nivel_actual - 1]);
	randall(juego->niveles, juego->jugador.ahuyenta_randall, juego->nivel_actual, juego->jugador.movimientos_realizados);
	if(estado_nivel(juego->niveles[juego->nivel_actual - 1].papeleos, juego->niveles[juego->nivel_actual - 1].tope_papeleos) == 1){
		juego->nivel_actual++;
		if(juego->nivel_actual <= CANTIDAD_NIVELES){
			inicializar_personaje(&juego->jugador, juego->nivel_actual, juego->personaje_tp1, juego->niveles[juego->nivel_actual - 1].pos_inicial_jugador);
		}
	}
}