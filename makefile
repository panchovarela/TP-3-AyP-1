JUEGO = juego
FLAGS = -std=c99 -Wall -Wconversion -Werror -lm

compile:
	gcc *.c utiles.o controlador.o -o ${JUEGO} ${FLAGS}

run:
	./${JUEGO}

compilegdb:
	gcc *.c utiles.o controlador.o -o ${JUEGO} ${FLAGS} -g

gdb:
	gdbtui ${JUEGO}

all: compile run