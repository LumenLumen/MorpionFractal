#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"
/**
\file morpionfonction.c
\brief programme ...
\author Groupe morpion fractal
\version 1
\date 9 février 2023
*/
/**
\fn void init_grille(int grille[N][N])
\brief fonction qui initialise la grille .
*/
void init_grille(int grille[N][N]){
    int i, j;
    for (i=0 ; i<N ; i++)
        for(j=0 ; j<N ; j++)
            grille[i][j]=0 ;
}
/**
\fn void init_morpion(int grille[M][M])
\brief fonction qui initialise le morpion.
*/
void init_morpion(int grille[M][M]){
    int i, j;
    for (i=0 ; i<M ; i++)
        for(j=0 ; j<M ; j++)
            grille[i][j]=0 ;
}
/**
\fn void afficher_grille(int grille[N][N])
\brief Fonction qui affiche la  grille.
*/
void afficher_grille(int grille[N][N]){
    int i, j;
    for (i=0 ; i<N ; i++){
        for(j=0 ; j<N ; j++){
            /*
            switch (grille[i][j]){
                case 0 : printf("0 ") ; break ;
                case O : printf("o ") ; break ;
                case X : printf("x ") ; break ;
            }*/
            printf("%i ", grille[i][j]);

            if ((j%3 == 2) && (j != 8)) printf ("| ");
        }

        printf("\n");

        if ((i%3 == 2) && (i != 8)) printf("----------------------\n");
    }
}
/**
\fn void afficher_morpion(int grille[M][M])
\brief Fonction qui affiche le morpion.
*/
void afficher_morpion(int grille[M][M]){
    int i, j;
    for (i=0 ; i<M ; i++){
        for(j=0 ; j<M ; j++)
            printf("%d ", grille[i][j]) ;
        printf("\n");
    }
}
/**
\fn int morpiongagne(int grille[M][M]
\brief Fonction qui vérifie s'il y a un gagnant dans une grille 3*3 et qui prend en paramètre la grille.

*/
/*Vérifie s'il y a un gagnant dans une grille 3*3.
Prend en paramètre la grille, retourne la valeur du vainqueur sinon 0.*/
int morpiongagne(int grille[M][M]){
    int i, centre ;

    //Vérification des colonnes.
    for (i=0 ; i<M ; i++){
        if ((grille[i][0] == grille[i][1]) && (grille[i][1] == grille[i][2]) &&(grille[i][1] != 0)){
            return grille[i][0];
        }
    }

    //Verification des lignes.
    for (i=0 ; i<M ; i++){
        if ((grille[0][i] == grille[1][i]) && (grille[1][i] == grille[2][i]) && (grille[1][i] != 0)){
            return grille[0][i];
        }
    }

    //Si la case centrale est prise, on vérifie les diagonales.
    centre = grille[1][1];
    if (centre){
        if ((grille[0][0] == centre) && (centre == grille[2][2]))
            return centre ;
        if ((grille[0][2] == centre) && (centre == grille[2][0]))
            return centre ;
    }

    return 0;
}
/**
\fn int coog_to_carr (int x, int y)
\brief Fonction qui prends en paramètre des coordonnées [0;8][0;8]. On suppose les coordonnés corrects.
\return le carré (0-8) dans lequel elles se trouvent.
*/
/*Prends en paramètre des coordonnées [0;8][0;8]. On suppose les coordonnés corrects.
Retourne le carré (0-8) dans lequel elles se trouvent.*/
int coog_to_carr (int x, int y){
    if (x < 0) return -1;
    if (x <= 2){
        if (y <= 2) return 0 ;
        if (y <= 5) return 1 ;
        if (y <= 8) return 2 ;
    }
    if (x <= 5){
        if (y <= 2) return 3 ;
        if (y <= 5) return 4 ;
        if (y <= 8) return 5 ;
    }
    if (x <= 8){
        if (y <= 2) return 6 ;
        if (y <= 5) return 7 ;
        if (y <= 8) return 8 ;
    }
    return -1 ;
}
/**
\fn int check_carre(int grille[N][N], int morpion[M][M], int xdc, int ydc)
\brief Fonction qui vérifie que si un carré a été rempli grâce au dernier coup, on rempli le morpion 3*3 si nécessaire. Prends en paramètre la grille, le morpion, et les derniers coordonnées joués.
*/
int check_carre(int grille[N][N], int morpion[M][M], int xdc, int ydc){
    int carre[M][M] ; //On recopie le contenu du carré où le dernier coup a été joué dans carre
    //int num_carre = coog_to_carr(xdc, ydc);
    int i,j ;

    ///On se place sur la première case du carré où le dernier coup a été joué.
    while (xdc%3 != 0) xdc--;
    while (ydc%3 != 0) ydc--;

    for (i = 0; i<M ; i++){
        for (j = 0; j<M ; j++){
            carre[i][j]=grille[xdc+i][ydc+j];
        }
    }

    //printf("Carre de la fonction \n");
    
    i = morpiongagne(carre);
    if(i){ ///On place dans i la valeur du vainqueur s'il existe, sinon i = 0 et la condition ne se lance pas.
        morpion[xdc/3][ydc/3] = i ;
    }
    /** 
    \return la valeur de i 
    */
    return i;
}
    /**
    \fn int predict_rect(int xdc, int ydc, int * x, int * y)
    \brief Prends en paramètres le dernier coup joué, retourne le carré dans lequel devra jouer le joueur au prochain coup
    \return 0
    */
/*Prends en paramètres le dernier coup joué, retourne le carré dans lequel devra jouer le joueur au prochain coup*/
int predict_rect(int xdc, int ydc, int * x, int * y){
    if (xdc == -1){ //Premier coup
        *x = 1 ;
        *y = 1 ;
    }
    else {
        *x = xdc%M ;
        *y = ydc%M ;
    }

    return 0;
}

/**
\fn  int valideCase (int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y)
\brief Prends en paramètre le joueur dont c'est le tour, la grille 9*9, le morpion 3*3, les coordonnées de la dernière case jouée, et les coordonnées de la case jouée

*/

/*Prends en paramètre le joueur dont c'est le tour, la grille 9*9, le morpion 3*3, les coordonnées de la dernière case jouée, et les coordonnées de la case jouée
Retourne -1 si le coup n'est pas valide, 0 sinon.*/
int valideCase (int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y){

    int carre = -1 ;

    if (*xdc == -1){ //C'est le premier tour.
        carre =  4 ;
    }
    ///Si le joueur est renvoyé sur une case déjà gagnée par un joueur.
    else if ( morpion[(*xdc)%M][(*ydc)%M] != 0 ){
        carre = 9;
    }
    else {
        carre = (*xdc)%M * 3 + (*ydc)%M ;
    }

    //printf("Contenu de la case visée : %i en x=%i et y=%i avec carre=%i et morpion=%i ",grille[x][y],x,y,carre,morpion[x/M][y/M]);
    if((coog_to_carr(x,y) != carre) && (carre != 9)){
        return 3 ;
    }
    else if (grille[x][y] != 0){
        return 4;
    }
    else if (carre == 9 && morpion[x/M][y/M] != 0){
        return 5;
    }
    else {
        *xdc = x ;
        *ydc = y ;///Les coordonnées sont valides et deviennent le nouveau dernier coup joué.
        grille[x][y] = *joueur ; ///On ajoute la valeur du joueur à la grille à l'endroit joué.
        ///Si le joueur du coup est X, alors on passe au tour de O, sinon c'est le tour de X.
        if (*joueur == X) *joueur = O ;
        else *joueur = X ;
        return 0 ; 
    }
    /**
    \return -1 si le coup n'est pas valide, 0 sinon
    */
    return -1 ;
}
/**
\fn int carre_plein(int grille[N][N], int x, int y)
\brief Prend en paramètre une matrice 3*3.
\return VRAI si le carré est plein, FAUX s'il reste de la place.
*/
/*Prend en paramètre une matrice 3*3, retourne VRAI si le carré est plein, FAUX s'il reste de la place.*/
int carre_plein(int grille[N][N], int x, int y){
    int cpt = 0 ;

    //On se place sur la première case du carré.
    while (x%3 != 0) x--;
    while (y%3 != 0) y--;

    for (int i = 0 ; i < M ; i ++){
        for(int j = 0 ; j < M ; j++){
            if (grille[x+i][y+j] != 0) cpt++ ;
        }
    }

    if (cpt == 9) return 1 ;
    else return 0 ;
}


/**
\fn int valideCase_var (int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y)
\brief Prends en paramètre le joueur dont c'est le tour, la grille 9*9, le morpion 3*3, les coordonnées de la dernière case jouée, et les coordonnées de la case jouée
*/
/*Prends en paramètre le joueur dont c'est le tour, la grille 9*9, le morpion 3*3, les coordonnées de la dernière case jouée, et les coordonnées de la case jouée
Retourne -1 si le coup n'est pas valide, 0 sinon.*/
int valideCase_var (int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y){

    int carre = -1 ;
    int xx, yy ;
    predict_rect(*xdc, *ydc, &xx, &yy);

    if (*xdc == -1){ //C'est le premier tour.
        carre =  4 ;
    }
    else if (carre_plein(grille,xx*M, yy*M)){
        carre = 9;
    }
    else { //Sinon
        carre = (*xdc)%M * 3 + (*ydc)%M ;
    }

    if((coog_to_carr(x,y) != carre) && (carre != 9)){/// Si le coup joué n'est pas dans le bon carré
        return 3 ;
    }
    else if (grille[x][y] != 0){ ///Si la case n'est pas déjà prise
        return 4;
    }
    else if (carre_plein(grille, x, y)){ ///Si la case où veut jouer le joueur est pleine.
        return 5 ;
    }
    else {
        *xdc = x ;
        *ydc = y ;///Les coordonnées sont valides et deviennent le nouveau dernier coup joué.
        grille[x][y] = *joueur ; ///On ajoute la valeur du joueur à la grille à l'endroit joué.
        ///Si le joueur du coup est X, alors on passe au tour de O, sinon c'est le tour de X.
        if (*joueur == X) *joueur = O ;
        else *joueur = X ;
        return 0 ; 
    }
    /**
    \return -1 si le coup n'est pas valide, 0 sinon.
    */

    return -1 ;
}