
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