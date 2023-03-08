#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"

int main(){

    int grille[N][N];
    int morpion[M][M];

    printf("============ Début du test pour les fonctions init_grille & init_morpion\n");
    printf("Grille avant init :\n");
    afficher_grille(grille);
    init_grille(grille);
    printf("Grille après init :\n");
    afficher_grille(grille);
    printf("\nMorpion avant init :\n");
    afficher_morpion(morpion);
    init_morpion(morpion);
    printf("Morpion après init :\n");
    afficher_morpion(morpion);

    return 0;
}