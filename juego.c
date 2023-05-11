#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "papeleo.h"
#include "dia_en_la_uni.h"
#include "controlador.h"

int main(){

	juego_t juego;
	char personaje;

	srand((unsigned)time(NULL));
	dia_en_la_uni(&personaje);
	system("clear");
	inicializar_controlador();
	inicializar_juego(&juego, personaje);
	printf("\n\n¡¡¡NO ORDENASTE TU PAPELEO ANOCHE!!!\n\n\n");
	imprimir_terreno(juego);
	while(estado_juego(juego) == 0){
		realizar_jugada(&juego);
		system("clear");
		printf("\n\n¡¡¡NO ORDENASTE TU PAPELEO ANOCHE!!!\n\n\n");
		imprimir_terreno(juego);
	}
	system("clear");
	terminar_controlador();
	printf("\n");
	if(estado_juego(juego) == 1){
		printf(" \
   ####     ##     ##   ##    ##      #####   ######   #######    ##\n \
  ##  ##   ####    ###  ##   ####    ##   ##  # ## #    ##   #   ####\n \
 ##       ##  ##   #### ##  ##  ##   #          ##      ## #     ####\n \
 ##       ##  ##   ## ####  ##  ##    #####     ##      ####      ##\n \
 ##  ###  ######   ##  ###  ######        ##    ##      ## #      ##\n \
  ##  ##  ##  ##   ##   ##  ##  ##   ##   ##    ##      ##   #\n \
   #####  ##  ##   ##   ##  ##  ##    #####    ####    #######    ##\n\n");
	}
	else{
		printf(" \
   ####     ##     ##   ##  #######            #####   ##   ##  #######  ######\n \
  ##  ##   ####    ### ###   ##   #           ##   ##  ##   ##   ##   #   ##  ##\n \
 ##       ##  ##   #######   ## #             ##   ##   ## ##    ## #     ##  ##\n \
 ##       ##  ##   #######   ####             ##   ##   ## ##    ####     #####\n \
 ##  ###  ######   ## # ##   ## #             ##   ##    ###     ## #     ## ##\n \
  ##  ##  ##  ##   ##   ##   ##   #           ##   ##    ###     ##   #   ##  ##\n \
   #####  ##  ##   ##   ##  #######            #####      #     #######  #### ##\n\n");
	}

	return 0;
}