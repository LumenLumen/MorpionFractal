#include "../lib/morpion.h"

int main(){

    int grille[N][N];
    int morpion[M][M];
    int joueur=1;
    int vainqueur=0;

    printf("============ Début du test pour les fonctions IA\n");
    printf("Affichage grille et morpion avant coup IA\n");
    init_grille(grille);
    grille[3][4]=1;
    grille[0][0]=2;
    grille[0][1]=2;
    grille[0][2]=1;
    grille[1][1]=1;
    afficher_grille(grille);
    
    init_morpion(morpion);
    afficher_morpion(morpion);


    int xdc=0; 
    int ydc=0;
    int x, y;

    printf("xdc=%i ydc=%i\n",xdc,ydc);
    ia_random(&joueur,grille,morpion,&xdc,&ydc,&x,&y);
    check_carre(grille,morpion,x,y);
    printf("x=%i y=%i\n\n",x,y);


    printf("Affichage grille et morpion après coup IA\n");
    afficher_grille(grille);
    afficher_morpion(morpion);

    printf("début partie avec deux IA random\n");
    init_grille(grille);
    init_morpion(morpion);
    xdc=0; 
    ydc=0;
    int i = 0;
    while(vainqueur==0 && i<75){
        ia_random(&joueur,grille,morpion,&xdc,&ydc,&x,&y);
        check_carre(grille,morpion,x,y);
        vainqueur=morpiongagne(morpion);
        i++;
    }
    printf("Affichage grille après fin de la partie\n");
    afficher_grille(grille);
    afficher_morpion(morpion);
    printf("Vainqueur=%i nb coups=%i\n",vainqueur,i);
}
