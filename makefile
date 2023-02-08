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
