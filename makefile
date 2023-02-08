<<<<<<< HEAD
tictactoe : ./src/morpion.o ./src/morpionfonction.o ./src/sauvegarde.o ./lib/morpion.h ./lib/sauvegarde.h
	gcc ./src/morpion.o ./src/morpionfonction.o ./src/sauvegarde.o ./lib/morpion.h ./lib/sauvegarde.h -o tictactoe
	rm ./src/*.o
	
morpion.o : morpion.c
	cd src
	gcc morpion.c -c
	cd ..
	
morpionfonction.o : morpionfonction.c
	cd src
	gcc morpionfonction.c -c
	cd ..

sauvegarde.o : sauvegarde.c
	cd src
	gcc sauvegarde.c -c
	cd ..
=======

CC=gcc
FLAGS=-Wall -g
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
PROG=sdl_test
all: sdl_text
sdl_text: menuscreen.c
	${CC} -o ${PROG} menuscreen.c ${LIBS} ${INCS} ${FLAGS}
clean:
	rm -f ${PROG}
	rm -f *.o
>>>>>>> c96e7904ae2850f5fb1feb09290d19cb5db69d7e
