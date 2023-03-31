#include "../lib/morpion.h"
#include <time.h>

int main(){
    
    srand(time(NULL));

    printf("============ ");
    printf("Affichage grille de valeurs sratégique des cases\n\n");

    int i,j;
    for(i=0;i<M;i++){
        for(j=0;j<M;j++){
            printf(" %f",strat_val(j,i));
        }
        printf("\n");
    }

    int grille[N][N];
    int morpion[M][M];
    int temp_morpion[M][M];
    int joueur=1;
    int vainqueur=0;

    printf("============ Début du test pour les fonctions d'évaluation\n");
    printf("Affichage grille et morpion à évaluer\n");
    init_grille(grille);
    grille[3][4]=1;
    grille[0][0]=2;
    grille[0][1]=2;
    grille[0][2]=1;
    grille[1][1]=1;
    afficher_grille(grille);
    
    init_morpion(morpion);
    afficher_morpion(morpion);

    printf("\n");

    //temp_morpion vaut le premier morpion du tableau

    int k,l;

    for(k=0;k<M;k++){
        for(l=0;l<M;l++){
            temp_morpion[k][l]=grille[k][l];
        }
    }

    printf("Affichage nombre de coups gagnants pour joueur 1 : %f\n\n", nb_coups_gagnants(1,temp_morpion));
    printf("Affichage nombre de coups gagnants pour joueur 2 : %f\n\n", nb_coups_gagnants(2,temp_morpion));

    printf("Affichage évaluation actuelle de la partie pour le joueur 1 : %f\n\n", eval_morpion(1,morpion,grille));
    printf("Affichage évaluation actuelle de la partie pour le joueur 2 : %f\n\n", eval_morpion(2,morpion,grille));


    int xdc=0; 
    int ydc=0;
    int x, y;
}
