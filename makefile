
CC=gcc
FLAGS=-Wall -g

SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include

fich_menu_seul= menuscreen.o
fich_jeu_complet= gamescreen.o menuscreen.o morpion.o morpionfonction.o sauvegarde.o

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}

SRC=src/
HDIR=lib/
PROG=morpionfractal

all: game

game: ${fich_jeu_complet}
	${CC} ${FLAGS} ${fich_jeu_complet} -o ${PROG} ${LIBS} ${INCS}

menuscreen.o: ${SRC}menuscreen.c ${HDIR}screens.h
	${CC} -c ${FLAGS} ${SRC}menuscreen.c -o menuscreen.o ${LIBS} ${INCS}

gamescreen.o: ${SRC}gamescreen.c ${HDIR}screens.h
	${CC} -c ${FLAGS} ${SRC}gamescreen.c -o gamescreen.o ${LIBS} ${INCS}

morpion.o: ${SRC}morpion.c
	${CC} -c ${FLAGS} ${SRC}morpion.c -o morpion.o ${LIBS} ${INCS}

morpionfonction.o: ${SRC}morpionfonction.c ${HDIR}morpion.h
	${CC} -c ${FLAGS} ${SRC}morpionfonction.c -o morpionfonction.o ${LIBS} ${INCS}

sauvegarde.o: ${SRC}sauvegarde.c ${HDIR}sauvegarde.h
	${CC} -c ${FLAGS} ${SRC}sauvegarde.c -o sauvegarde.o ${LIBS} ${INCS}

clean:
	rm -f ${PROG}
	rm -f *.o

cleano:
	rm -f *.o
