#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"
/**
    \file morpionfonction.c
    \brief contient toutes les fonctions utiles à une partie de morpion
    \author Groupe morpion fractal
    \version 1
    \date 9 février 2023
*/

/**
    \fn void init_grille(int grille[N][N])
    \brief fonction qui initialise la grille avec des 0.
    \param matrice 9*9
*/
void init_grille(int grille[N][N]){
    int i, j;
    for (i=0 ; i<N ; i++)
        for(j=0 ; j<N ; j++)
            grille[i][j]=0 ;
}

/**
    \fn void init_morpion(int grille[M][M])
    \brief fonction qui initialise le morpion avec des 0.
    \param grille matrice 3*3
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
    \param grille matrice 9*9
*/
void afficher_grille(int grille[N][N]){
    int i, j;
    for (i=0 ; i<N ; i++){
        for(j=0 ; j<N ; j++){
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
    \param grille matrice 3*3
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
    \brief Fonction qui vérifie s'il y a un gagnant dans une grille 3*3
    \param grille matrice 3*3
    \return -1 si match nul, 0 pas de vainqueur, 1 X gagne, 2 O gagne.
*/
int morpiongagne(int grille[M][M]){
    int i, j, cpt = 0, centre ;

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

    for (i = 0 ; i < M ; i ++){
        for(j = 0 ; j < M ; j++){
            if (grille[i][j] != 0) cpt++ ;
        }
    }
    if (cpt == 9){//Le carré est plein
        return -1;
    }

    return 0;
}

/**
    \fn int coog_to_carr (int x, int y)
    \brief Donne le sous-morpion dans lequel se trouve un coup.
    \param x abscisse du coup à vérifier
    \param y ordonné du coup à vérifier
    \return le carré (0-8) dans lequel elles se trouvent selon le tableau suivant : ((0,1,2),(3,4,5),(6,7,8)).
*/
int coog_to_carr (int x, int y){
    if (x < 0 || y < 0) return -1;
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
    \brief Fonction qui vérifie que si un carré a été rempli grâce au dernier coup, on rempli le morpion 3*3 si nécessaire.
    \param grille matrice 9*9
    \param morpion matrice 3*3
    \param xdc abscisse dernier coup joué
    \param ydc ordonné dernier coup joué
*/
int check_carre(int grille[N][N], int morpion[M][M], int xdc, int ydc){
    int carre[M][M] ; //On recopie le contenu du carré où le dernier coup a été joué dans carre
    int i,j ;

    ///On se place sur la première case du carré où le dernier coup a été joué.
    while (xdc%3 != 0) xdc--;
    while (ydc%3 != 0) ydc--;

    for (i = 0; i<M ; i++){
        for (j = 0; j<M ; j++){
            carre[i][j]=grille[xdc+i][ydc+j];
        }
    }
    
    i = morpiongagne(carre);
    if(i && morpion[xdc/3][ydc/3] == 0 ){ //On place dans i la valeur du vainqueur s'il existe, sinon i = 0 et la condition ne se lance pas.
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
    \brief Vérifie si le coup est valide. S'il est valide, remplace xdc, ydc par le coup vérifie, ajoute le coup dans la grille et passe au joueur suivant
    \param joueur pointeur vers le joueur dont c'est le tour
    \param grille matrice 9*9
    \param morpion matrice 3*3
    \param xdc pointeur vers abscisse dernier coup joué
    \param ydc pointeur vers ordonnée dernier coup joué
    \param x abscisse coup à vérifier
    \param y ordonnée coup à vérifier
    \return 0 si le coup est okay, 3 si carré non valide, 4 si case déjà prise, 5 si carré déjà complété, -1 si erreur
*/
int valideCase (int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y){

    int carre = -1 ;

    if (*xdc == -1){ //C'est le premier tour.
        carre =  4 ;
    }
    ///Si le joueur est renvoyé sur une case déjà gagnée par un joueur.
    else if ( morpion[(*xdc)%M][(*ydc)%M] != 0 || carre_plein(grille, *xdc, *ydc)){
        carre = 9;
    }
    else {
        carre = (*xdc)%M * 3 + (*ydc)%M ;
    }

    if((coog_to_carr(x,y) != carre) && (carre != 9)){ //Carré non valide
        return 3 ;
    }
    else if (grille[x][y] != 0){ //Case prise
        return 4;
    }
    else if (carre == 9 && morpion[x/M][y/M] != 0){ //Carré complet
        return 5;
    }
    else { //Coup okay
        *xdc = x ;
        *ydc = y ;///Les coordonnées sont valides et deviennent le nouveau dernier coup joué.
        grille[x][y] = *joueur ; ///On ajoute la valeur du joueur à la grille à l'endroit joué.
        ///Si le joueur du coup est X, alors on passe au tour de O, sinon c'est le tour de X.
        if (*joueur == X) *joueur = O ;
        else *joueur = X ;
        return 0 ; 
    }
    return -1 ;
}

/**
    \fn int carre_plein(int grille[N][N], int x, int y)
    \brief Vérifie si un sous-morpion est plein.
    \param grille matrice 9*9
    \param i ordonné d'un coup dans le sous-morpion à vérifier
    \param j abscisse d'un coup dans le sous-morpion à vérifier
    \return VRAI si le carré est plein, FAUX s'il reste de la place.
*/
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
    \fn  int valideCase_var (int * joueur, int grille[N][N], int morpion[M][M], int * xdc, int * ydc, int x, int y)
    \brief Vérifie si le coup est valide en suivant les règles de la variante. S'il est valide, remplace xdc, ydc par le coup vérifie, ajoute le coup dans la grille et passe au joueur suivant
    \param joueur pointeur vers le joueur dont c'est le tour
    \param grille matrice 9*9
    \param morpion matrice 3*3
    \param xdc pointeur vers abscisse dernier coup joué
    \param ydc pointeur vers ordonnée dernier coup joué
    \param x abscisse coup à vérifier
    \param y ordonnée coup à vérifier
    \return 0 si le coup est okay, 3 si carré non valide, 4 si case déjà prise, 5 si carré déjà complété, -1 si erreur
*/
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

    return -1 ;
}