#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define N 9
#define M 3
#define X 1 //Joueur X
#define O 2 //Joueur O

typedef struct option_s {
    int autosave ;
} option_t ;

void save (char * name, int grille[N][N], int joueur, int, int);
void load (char * name, int grille[N][N], int * joueur, int*, int*);
void option (option_t *);