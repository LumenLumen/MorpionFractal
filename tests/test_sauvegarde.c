#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"

int main(){

    int grille[N][N];
    int morpion[M][M];

    printf("============ Début du test pour les fonctions save & load\n");
    init_grille(grille);
    grille[3][4]=1;
    grille[0][0]=2;
    grille[0][1]=2;
    grille[0][2]=2;
    printf("Grille avant sauvegarde :\n");
    afficher_grille(grille);
    init_morpion(morpion);
    morpion[0][0]=2;
    printf("Morpion avant sauvegarde :\n");
    afficher_morpion(morpion);
    printf("Sauvegarde avec joueur=1 et (x,y) dernier coup=(3,4)\n\n");
    save("test_save1.txt",grille,morpion,1,3,4);
    FILE * slot = fopen("test_save1.txt","r");
    char savedata[92];
    fscanf(slot,"%s\n",savedata);
    printf("Données de sauvegarde 1 = %s\n",savedata);
    printf("Grille après sauvegarde (ne doit pas être modifiée) :\n");
    afficher_grille(grille);
    printf("Morpion après sauvegarde (ne doit pas être modifié) :\n");
    afficher_morpion(morpion);
    fclose(slot);

    printf("\n===== Test chargement\n\n");
    init_grille(grille);
    init_morpion(morpion);printf("Grille avant chargement :\n");
    afficher_grille(grille);
    printf("Morpion avant chargement :\n");
    afficher_morpion(morpion);
    int joueur,xdc,ydc;
    printf("Initialistion variables de jeu, joueur = %i et coordonnées dernier coup = (%i, %i)\n",joueur,xdc,ydc);
    printf("Chargement avec fichier test_save2.txt\n");
    slot = fopen("test_save2.txt","r");
    fscanf(slot,"%s\n",savedata);
    printf("Données de sauvegarde 2 = %s\n",savedata);
    load("test_save2.txt",grille,morpion,&joueur,&xdc,&ydc);
    printf("Nouvelles variables de jeu, joueur = %i et coordonnées dernier coup = (%i, %i)\n",joueur,xdc,ydc);
    printf("Grille après chargement :\n");
    afficher_grille(grille);
    printf("Morpion après chargement :\n");
    afficher_morpion(morpion);
    fclose(slot);


    return 0;
}
