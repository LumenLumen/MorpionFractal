#include "../lib/morpion.h"
#include "../lib/sauvegarde.h"

void init_grille(int grille[N][N]){
    int i, j;
    for (i=0 ; i<N ; i++)
        for(j=0 ; j<N ; j++)
            grille[i][j]=0 ;
}

void init_morpion(int grille[M][M]){
    int i, j;
    for (i=0 ; i<M ; i++)
        for(j=0 ; j<M ; j++)
            grille[i][j]=0 ;
}

void afficher_grille(int grille[N][N]){
    int i, j;
    for (i=0 ; i<N ; i++){
        for(j=0 ; j<N ; j++){
            
            switch (grille[i][j]){
                case 0 : printf("0 ") ; break ;
                case O : printf("o ") ; break ;
                case X : printf("x ") ; break ;
            }

            if ((j%3 == 2) && (j != 8)) printf ("| ");
        }

        printf("\n");

        if ((i%3 == 2) && (i != 8)) printf("----------------------\n");
    }
}

void afficher_morpion(int grille[M][M]){
    int i, j;
    for (i=0 ; i<M ; i++){
        for(j=0 ; j<M ; j++)
            printf("%d ", grille[i][j]) ;
        printf("\n");
    }
}

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

/*Effectue les affichages du début de tour et vérifie où le joueur peut jouer. 
Prend en paramètre le joueur et les coordonnées du dernier coup joué, ainsi que le morpion.
Retourne le numéro de la case (0-8) où le joueur peut jouer, 9 si partout.*/
int debut_de_tour(int xdc, int ydc, int joueur, int morpion[M][M]){

    //A qui est le tour.
    if (joueur == X)
        printf("C'est au tour de X.\n");
    else
        printf("C'est au tour de O.\n");
    

    if (xdc == -1){ //C'est le premier tour.
        printf("Vous devez jouer dans le carré central.\n");
        return 4 ;
    }
    //Si le joueur est renvoyé sur une case déjà gagnée par un joueur.
    else if ( morpion[(xdc)%M][(ydc)%M] != 0 ){
        printf("Vous pouvez jouer sur n'importe quelle case libre.\n");
        return 9;
    }
    else {
        printf("Vous devez jouer dans le carré ligne %d, colonne %d.\n", (xdc)%M +1, (ydc)%M +1);
        return (xdc)%M * 3 + (ydc)%M ;
    }

    return -1;
}

/*Demande le coup au joueur, vérifie qu'il est valide.
Prend en paramètre le carré jouable, le joueur dont c'est le tour, la grille, l'adresse du dernier coup joué*/
void tour_du_joueur(int carre_jouable, int * joueur, int grille[N][N], int * xdc, int * ydc){
    int x, y ;

    printf("Sur quelle ligne souhaitez-vous jouer (1-9) ? ");
    scanf("%d", &x);
    printf("Sur quelle colonne souhaitez-vous jouer (1-9) ?");
    scanf("%d", &y);
    x--;
    y--;

    if ((x<0 || x>8) && (y<0 || y>8)){
        printf("Coordonnées non valides.\n");
        tour_du_joueur(carre_jouable,joueur,grille,xdc,ydc);
    }
    else if((coog_to_carr(x,y) != carre_jouable) && (carre_jouable != 9)){
        printf("Carré non valide.\n");
        tour_du_joueur(carre_jouable,joueur,grille,xdc,ydc);
    }
    else if (grille[x][y] != 0){
        printf("La case est déjà occupée.\n") ;
        tour_du_joueur(carre_jouable,joueur,grille,xdc,ydc);
    }
    else {
        *xdc = x ;
        *ydc = y ;//Les coordonnées sont valides et deviennent le nouveau dernier coup joué.
        grille[x][y] = *joueur ; //On ajoute la valeur du joueur à la grille à l'endroit joué.
        //Si le joueur du coup est X, alors on passe au tour de O, sinon c'est le tour de X.
        if (*joueur == X) *joueur = O ;
        else *joueur = X ;
    }
}

/*Vérifie que si un carré a été rempli grâce au dernier coup, rempli le morpion 3*3 si nécessaire.
Prends en paramètre la grille, le morpion, et les derniers coordonnées joués.*/
void check_carre(int grille[N][N], int morpion[M][M], int xdc, int ydc){
    int carre[M][M] ; //On recopie le contenu du carré où le dernier coup a été joué dans carre
    //int num_carre = coog_to_carr(xdc, ydc);
    int i,j ;

    //On se place sur la première case du carré où le dernier coup a été joué.
    while (xdc%3 != 0) xdc--;
    while (ydc%3 != 0) ydc--;

    for (i = 0; i<M ; i++){
        for (j = 0; j<M ; j++){
            carre[i][j]=grille[xdc+i][ydc+j];
        }
    }
    
    if(i == morpiongagne(carre)){ //On place dans i la valeur du vainqueur s'il existe, sinon i = 0 et la condition ne se lance pas.
        morpion[xdc/3][ydc/3] = i ;
    }    
}


/*Lance la partie de morpion. 
Prends en paramètre VRAI si une partie sauvegardée doit ếtre chargée, FAUX sinon.
Prends en paramètre les options de jeu.*/
void morpion (int reload, option_t opt){
    int grille[N][N];
    int morpion[M][M];

    int joueur = 1 ;
    int * xdc = malloc(sizeof(int)); //Ligne du dernier coup ;
    int * ydc = malloc(sizeof(int)); //Colonne du dernier coup ;
    int carre = -1;
    int vainqueur = 0 ;

    (* xdc) = -1 ;

    if (reload)
        load("save.txt", grille, &joueur, xdc, ydc);
    else {
        init_grille(grille);
        init_morpion(morpion);
    }

    while (! vainqueur){ //Tant qu'il n'y a pas de vainqueur.

        system("clear");
        afficher_grille(grille);

        carre = debut_de_tour(*xdc,*ydc,joueur,morpion);
        tour_du_joueur(carre, &joueur, grille, xdc, ydc);

        check_carre(grille, morpion, *xdc, *ydc);
        vainqueur = morpiongagne(morpion);

        if (opt.autosave) save("save.txt", grille, joueur, *xdc, *ydc);
    }

    system("clear");
    afficher_grille(grille);

    free(xdc);
    free(ydc);

    if (vainqueur == X){
        printf("Le vainqueur est X !");
        sleep(3);
        system("clear");
    }
    else {
        printf("Le vainqueur est O !");
        sleep(3);
        system("clear");
    }
}