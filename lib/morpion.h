#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 9
#define M 3
#define X 1 //Joueur X
#define O 2 //Joueur O

void init_grille(int grille[N][N]);
void init_morpion(int grille[M][M]);
void afficher_grille(int grille[N][N]);
void afficher_morpion(int grille[M][M]);
int morpiongagne(int grille[M][M]);
int coog_to_carr (int x, int y);
int debut_de_tour(int xdc, int ydc, int joueur, int morpion[M][M]);
void tour_du_joueur(int carre_jouable, int * joueur, int grille[N][N], int * xdc, int * ydc);
int check_carre(int grille[N][N], int morpion[M][M], int xdc, int ydc);
int predict_rect(int xdc, int ydc, int * x, int * y);
int valideCase (int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y);
int carre_plein(int grille[N][N], int x, int y);
int valideCase_var (int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y);