
CC=gcc
FLAGS=-Wall -g

SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include

fich_jeu_complet= screen_jeu.o screen_menu.o screen_option.o screens.o morpion.o morpionfonction.o sauvegarde.o ia.o eval_ia.o screen_rdj.o

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}

SRC=src/
HDIR=lib/
PROG=morpionfractal
TEST=tests/



all: game

game: ${fich_jeu_complet}
	${CC} ${FLAGS} ${fich_jeu_complet} -o ${PROG} ${LIBS} ${INCS}

screens.o: ${SRC}screens.c ${HDIR}screens.h
	${CC} -c ${FLAGS} ${SRC}screens.c -o screens.o ${LIBS} ${INCS}

screen_jeu.o: ${SRC}screen_jeu.c ${HDIR}screens.h
	${CC} -c ${FLAGS} ${SRC}screen_jeu.c -o screen_jeu.o ${LIBS} ${INCS}

screen_menu.o: ${SRC}screen_menu.c ${HDIR}screens.h
	${CC} -c ${FLAGS} ${SRC}screen_menu.c -o screen_menu.o ${LIBS} ${INCS}

screen_option.o: ${SRC}screen_option.c ${HDIR}screens.h
	${CC} -c ${FLAGS} ${SRC}screen_option.c -o screen_option.o ${LIBS} ${INCS}
	
morpion.o: ${SRC}morpion.c
	${CC} -c ${FLAGS} ${SRC}morpion.c -o morpion.o ${LIBS} ${INCS}

morpionfonction.o: ${SRC}morpionfonction.c ${HDIR}morpion.h
	${CC} -c ${FLAGS} ${SRC}morpionfonction.c -o morpionfonction.o ${LIBS} ${INCS}

sauvegarde.o: ${SRC}sauvegarde.c ${HDIR}sauvegarde.h
	${CC} -c ${FLAGS} ${SRC}sauvegarde.c -o sauvegarde.o ${LIBS} ${INCS}

ia.o: ${SRC}ia.c ${HDIR}morpion.h
	${CC} -c ${FLAGS} ${SRC}ia.c -o ia.o ${LIBS} ${INCS}

eval_ia.o: ${SRC}eval_ia.c ${HDIR}morpion.h
	${CC} -c ${FLAGS} ${SRC}eval_ia.c -o eval_ia.o ${LIBS} ${INCS}

screen_rdj.o: ${SRC}screen_rdj.c ${HDIR}screens.h
	${CC} -c ${FLAGS} ${SRC}screen_rdj.c -o screen_rdj.o ${LIBS} ${INCS}


test : test_morpionfonction test_sauvegarde test_ia test_eval_ia

test_morpionfonction : ${TEST}test_morpionfonction.o morpionfonction.o
	${CC} ${FLAGS} ${TEST}test_morpionfonction.o morpionfonction.o -o test_morpionfonction
	
test_morpionfonction.o : ${TEST}test_morpionfonction.c
	${CC} -c ${FLAGS} ${TEST}test_morpionfonction.c -o test_morpionfonction.o

test_sauvegarde : ${TEST}test_sauvegarde.o sauvegarde.o morpionfonction.o
	${CC} ${FLAGS} ${TEST}test_sauvegarde.o sauvegarde.o morpionfonction.o -o test_sauvegarde
	
test_sauvegarde.o : ${TEST}test_sauvegarde.c
	${CC} -c ${FLAGS} ${TEST}test_sauvegarde.c -o test_sauvegarde.o

test_ia : ${TEST}test_ia.o ia.o morpionfonction.o
	${CC} ${FLAGS} ${TEST}test_ia.o ia.o morpionfonction.o -o test_ia
	
test_ia.o : ${TEST}test_ia.c
	${CC} -c ${FLAGS} ${TEST}test_ia.c -o test_ia.o

test_eval_ia : ${TEST}test_eval_ia.o ia.o morpionfonction.o
	${CC} ${FLAGS} ${TEST}test_eval_ia.o eval_ia.o ia.o morpionfonction.o -o test_eval_ia
	
test_eval_ia.o : ${TEST}test_eval_ia.c
	${CC} -c ${FLAGS} ${TEST}test_eval_ia.c -o test_eval_ia.o

clean:
	rm -f ${PROG}
	rm -f *.o
	rm -f ./tests/*.o



cleano:
	rm -f *.o
	rm -f ./tests/*.o
