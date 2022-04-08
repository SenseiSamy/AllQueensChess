#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct position
{   
    int x;
    int y;
} Position;


/*-- Fonction de sauvegardes --*/
void lire_chessboard(FILE *fichier, int chessboard[5][5]){
    /*Lit un fichier stockant le chessboard et rempli un tableau décrivant le plateau*/
    fichier = fopen("sauvegarde.txt", "r");
    if (fichier != NULL){
        for(int i=0;i < 4;i++){
            /* lit le fichier et mets les valeurs dans le tableau  */
            fscanf(fichier,"%d%d%d%d%d\n",&chessboard[i][0],&chessboard[i][1],&chessboard[i][2],&chessboard[i][3],&chessboard[i][4]);
        }
        fclose(fichier);
    }
}

void ecrire_chessboard(int chessboard[5][5], FILE *fichier){
    /*Sauvegarde un Array2D dans un fichier*/
    fichier = fopen("sauvegarde.txt", "w");
    if (fichier != NULL)
    {
        for (int i = 0; i < 5; i++)
        {
            fprintf(fichier, "%d%d%d%d%d\n", chessboard[i][0], chessboard[i][1], chessboard[i][2],chessboard[i][3],chessboard[i][4]);
        }
        fclose(fichier);
    }
}

/*-- Fonctions de jeu --*/
int sans_conflit(Position orig, Position fin, int chessboard[5][5]){
    /*Vérifie si un mouvement d'un reine est possible, renvoie 0 si le déplacement est possible, renvoie 1 sinon*/
    if (chessboard[fin.x][fin.y] == 0) /*Vérifie que la position d'arrivée est libre*/
    {   
        if (orig.x == fin.x || orig.y == fin.y){/*Vérifie les mouvements rectilignes*/
            printf("RECTILIGNE\n");
            if(orig.x == fin.x){
                printf("test X \n");
                for(int i = 0 ; i < (orig.x - fin.x) ; i++){
                    printf("test i\n");
                    int count=0;
                    if(chessboard[orig.x][i] == 0){
                        count += 1;
                        printf("count = %d\n",count);
                        printf("orig.x = %d i = %d\n",orig.x,i);
                        if(count == (orig.x - fin.x) ){
                            printf("test return 0\n");
                            return 0;
                        }
                    }
                }
            }
            if(orig.y == fin.y){
                printf("test Y \n");
                for(int i = 0 ; i < (orig.y - fin.y) ; i++){
                    int count=0;
                    if(chessboard[i][orig.y] == 0){
                        count += 1;
                        printf("count y = %d",count);
                        if(count == (orig.y - fin.y) ){
                            printf("test return 0\n");
                            return 0;
                        }
                    }
                }
            }
        }

        /*Vérifie les mouvements diagonaux*/
        if (abs(fin.x - orig.x) == abs(fin.y - orig.y)){
            int count=0;
            if( (orig.x - fin.x) < 0 && (orig.y- fin.y) < 0){ /* Verifier si : haut en bas - gauche a droite */
                printf("haut en bas - gauche a droite\n");
                printf("x = %d y = %d\n",orig.x,orig.y);
                for(int i= orig.x; i < abs(orig.x - fin.x) ; i++){
                    for(int y= orig.y; y < abs(orig.x - fin.x) ;y++){
                        if(chessboard[i][y] == 0){
                            count += 1;
                            printf("count = %d\n",count);
                            if(count == abs(orig.x - fin.x)){
                                return 0;
                            }
                        }
                    }
                }
            }
            count=0;
            if( (orig.x - fin.x) < 0 && (orig.y- fin.y) >= 0){ /* Verifier si : haut en bas - droite a gauche */
                printf("haut en bas - droite a gauche\n");
                for(int i= orig.x; i < abs(orig.x - fin.x) ; i++){
                    for(int y= orig.y; y > abs(orig.y - fin.y) ;y--){
                        if(chessboard[i][y] == 0){
                            count += 1;
                            printf("count = %d\n",count);
                            if(count == abs(orig.x - fin.x)){
                                return 0;
                            }
                        }
                    }
                }
            }
            count=0;
            if( (orig.x - fin.x) >= 0 && (orig.y- fin.y) < 0){ /* Verifier si : bas en haut - gauche a droite */
                printf("bas en haut - gauche a droite\n");
                for(int i= orig.x; i > (orig.x - fin.x) ; i--){
                    for(int y= orig.y; y < abs(orig.y - fin.y) ;y++){
                        if(chessboard[i][y] == 0){
                            count += 1;
                            printf("count = %d\n",count);
                            if(count == abs(orig.x - fin.x)){
                                return 0;
                            }
                        }
                    }
                }
            }
            count=0;
            if( (orig.x - fin.x) >= 0 && (orig.y - fin.y) >= 0){ /* Verifier si : bas en haut - droite a gauche */
                printf("bas en haut - droite a gauche\n");
                printf("x = %d y = %d\n",orig.x,orig.y);
                for(int i= orig.x; i > (orig.x - fin.x) ; i--){
                    for(int y= orig.y; y > abs(orig.y - fin.y) ;y--){
                        if(chessboard[i][y] == 0){
                            count += 1;
                            printf("count = %d\n",count);
                            if(count == abs(orig.x - fin.x)){
                                return 0;
                            }
                        }
                    }
                }
            }
        } 
    }
  return 1;
}

int winning(int chessboard[5][5]){
    int i,j,count_white=0,count_black=0;
    /*Vérifie si un num_joueur a gagné en vérifiant le plateau*/
    /*Comptage en ligne*/ 
    for(i=0 ; i < 4 ;i++){
        for(j=0;j < 4;j++){
            if(chessboard[i][j] == 1){
                count_white += 1;
                if(count_white == 4){
                    return 1;
                }
            }
            else{
                count_white=0;
            }
        }
    }
    for(i=0 ; i < 4 ;i++){
        for(j=0;j < 4;j++){
            if(chessboard[i][j] == 2){
                count_black += 1;
                if(count_black == 4){
                    return 2;
                }
            }
            else{
                count_black=0;
            }
        }
    }
    count_black=0;
    count_white=0;
    /*En colonne*/
    for(i=0 ; i < 4 ;i++){
        for(j=0;j < 4;j++){
            if(chessboard[j][i] == 1){
                count_white += 1;
                if(count_white == 4){
                    return 1;
                }
            }
            else{
                count_white=0;
            }
        }
    }
    for(i=0 ; i < 4 ;i++){
        for(j=0;j < 4;j++){
            if(chessboard[j][i] == 2){
                count_black += 1;
                if(count_black == 4){
                    return 2;
                }
            }
            else{
                count_black=0;
            }
        }
    }
    count_black=0;
    count_white=0;
    /*En diagonale*/
    for(i=0,j=0; i < 4 && j < 4 ;j++,i++){
        if(chessboard[i][j] == 1){
            count_white += 1;
            if(count_white == 4){
                return 1;
            }
        }
        else{
            count_white=0;
        }
    }
    for(i=0,j=0; i < 4 && j < 4 ;j++,i++){
        if(chessboard[i][j] == 2){
            count_black += 1;
            if(count_black == 4){
                return 2;
            }
        }
        else{
            count_black=0;
        }
    }
    count_black=0;
    count_white=0;
    /* deuxieme ligne haut - gauche a droite  */
    for(i=0,j=1; j <= 4 && i <= 3 ;j++,i++){
        if(chessboard[i][j] == 1){
            count_white += 1;
            if(count_white == 4){
                return 1;
            }
        }
        else{
            count_white=0;
        }
    }
    for(i=0,j=1; j <= 4 ;j++,i++){
        if(chessboard[i][j] == 2){
            count_black += 1;
            if(count_black == 4){
                return 2;
            }
        }
        else{
            count_black=0;
        }
    }
    count_black=0;
    count_white=0;
    /* troisieme ligne bas - gauche a droite  */
    for(i=1,j=0; i <= 4 ;j++,i++){
        if(chessboard[i][j] == 1){
            count_white += 1;
            if(count_white == 4){
                return 1;
            }
        }
        else{
            count_white=0;
        }
    }
    for(i=1,j=0; i <= 4 ;j++,i++){
        if(chessboard[i][j] == 2){
            count_black += 1;
            if(count_black == 4){
                return 2;
            }
        }
        else{
            count_black=0;
        }
    }
    count_black=0;
    count_white=0;
    /* droite a gauche - diagonale principale */
    for(i=0,j=4; j >= 0 ;j--,i++){
        if(chessboard[i][j] == 1){
            count_white += 1;
            if(count_white == 4){
                return 1;
            }
        }
        else{
            count_white=0;
        }
    }
    for(i=0,j=4; j >= 0 ;j--,i++){
        if(chessboard[i][j] == 2){
            count_black += 1;
            if(count_black == 4){
                return 2;
            }
        }
        else{
            count_black=0;
        }
    }
    count_black=0;
    count_white=0;
    /* droite a gauche - seconde diagonale */
    for(i=0,j=3; i <= 3 ;j--,i++){
        if(chessboard[i][j] == 1){
            count_white += 1;
            if(count_white == 4){
                return 1;
            }
        }
        else{
            count_white=0;
        }
    }
    for(i=0,j=3; i <= 3 ;j--,i++){
        if(chessboard[i][j] == 2){
            count_black += 1;
            if(count_black == 4){
                return 2;
            }
        }
        else{
            count_black=0;
        }
    }
    count_black=0;
    count_white=0;
    /* droite a gauche - troisième diagonale */
    for(i=1,j=4; i <= 4 ;j--,i++){
        if(chessboard[i][j] == 1){
            count_white += 1;
            if(count_white == 4){
                return 1;
            }
        }
        else{
            count_white=0;
        }
    }
    for(i=1,j=4; i <= 4 ;j--,i++){
        if(chessboard[i][j] == 2){
            count_black += 1;
            if(count_black == 4){
                return 2;
            }
        }
        else{
            count_black=0;
        }
    }
    count_black=0;
    count_white=0;
    return 0;
}

void afficher_chessboard(int chessboard[5][5]){
    /*Affiche le chessboard dans le terminal*/
    //printf("\e[1;1H\e[2J"); /*Clear le terminal*/
    printf("    A   B   C   D   E\n");
    printf("  ---------------------\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d |", i+1);
        for (int y = 0; y < 5; y++)
        {
            switch (chessboard[i][y])
            {
                case 1:
                    printf("\033[0;30m N \033[0m|");
                    break;
                case 2:
                    printf("\033[0;31m R \033[0m|");
                    break;
                default:
                    printf("   |");
                    break;
            }
        }
        printf("\n");
        printf("  ---------------------\n");
    }
}

Position *coord_to_pos(char coord[2]){
    /*Converti une coordonnée de la grille en structure position (ex: A3 -> pos.x = 0, pos.y = 2)*/
    Position *pos = malloc(sizeof(Position));
    switch (coord[0])
    {
        case 'A':
            pos->x = 0;
            break;
        case 'B':
            pos->x = 1;
            break;
        case 'C':
            pos->x = 2;
            break;
        case 'D':
            pos->x = 3;
            break;
        default:
            pos->x = 4;
            break;
    }
    switch (coord[1])
    {
        case '1':
            pos->y = 0;
            break;
        case '2':
            pos->y = 1;
            break;
        case '3':
            pos->y = 2;
            break;
        case '4':
            pos->y = 3;
            break;
        default:
            pos->y = 4;
            break;
    }
    return pos;
}

void deplacer_reine(int chessboard[5][5], int joueur){
    char coord_orig[2], coord_fin[2];
    int num_joueur = joueur;
    Position pos_orig, pos_fin;
    deplacer_pion:
    printf("Quel pion voulez vous déplacer (ex : A2) : ");
    scanf("%s", coord_orig);
    pos_orig = *coord_to_pos(coord_orig);
    printf("x = %d  y = %d\n", pos_orig.x, pos_orig.y);
    printf("value emplacement = %d  joueur = %d\n", chessboard[pos_orig.y][pos_orig.x], num_joueur);
    if(chessboard[pos_orig.y][pos_orig.x] != num_joueur)
    {
        afficher_chessboard(chessboard);
        printf("Veuillez indiquer une case avec un pion vous appartenant\n");
        goto deplacer_pion;
    }
    else{
      emplacement_pion:
      afficher_chessboard(chessboard);
      printf("Ou voulez vous le déplacer (ex : A2) : ");
      scanf("%s", coord_fin);
      pos_fin = *coord_to_pos(coord_fin);
      printf("x = %d  y = %d\n", pos_orig.x, pos_orig.y);
      printf("value emplacement = %d  joueur = %d\n", chessboard[pos_orig.y][pos_orig.x], num_joueur);
      if(sans_conflit(pos_orig, pos_fin, chessboard) != 0)
      {
          afficher_chessboard(chessboard);
          printf("Le déplacement est impossible, veuillez reessayer\n");
          goto emplacement_pion;
      }
      else{
          chessboard[pos_fin.y][pos_fin.x] = chessboard[pos_orig.y][pos_orig.x];
          chessboard[pos_orig.y][pos_orig.x] = 0;
      }
    }
}

void choix_utilisateur(int chessboard[5][5]){
    int choix;
    joueur1:
    printf("Que doit faire le joueur 1[Noir] ? | 1-Jouer | 2-Abandonner | 3-Sauvegarder\n");
    scanf("%d", &choix);
    if (choix != 1 && choix != 2 && choix != 3){
       afficher_chessboard(chessboard);
       printf("Veuillez entrer 1, 2 ou 3\n");
       goto joueur1;
    }
    else{
      if (choix == 1){
          afficher_chessboard(chessboard);
          deplacer_reine(chessboard, 1);
      }else if (choix == 2){
          printf("Le num_joueur 2 a gagné !");
          exit(1);
      }else{
          ecrire_chessboard(chessboard, NULL);
          exit(1);
      }
    }
    /*Tour du Joueur 2*/
    afficher_chessboard(chessboard);
    joueur2:
    printf("Que doit faire le joueur 2[Rouge] ? | 1-Jouer | 2-Abandonner | 3-Sauvegarder\n");
    scanf("%d", &choix);
    if(choix != 1 && choix != 2 && choix != 3){
       afficher_chessboard(chessboard);
       printf("Veuillez entrer 1, 2 ou 3\n");
       goto joueur2;
    }
    else{
      if (choix == 1){
          afficher_chessboard(chessboard);
          deplacer_reine(chessboard, 2);
      }else if (choix == 2){
          printf("Le num_joueur 1 a gagné !");
          exit(1);
      }else{
          ecrire_chessboard(chessboard, NULL);
          exit(1);
      }
    }
}

int main(void){
    int chessboard[5][5] = {{1,2,1,2,1}, 
                            {0,0,0,0,0}, 
                            {2,0,0,0,1}, 
                            {0,0,0,0,0}, 
                            {2,1,2,1,2}};
    int choix;
    printf("\033[H\033[2J\033[3J");
    do {
        printf("Que voulez vous faire :\n1 - Nouvelle partie\n2 - Reprendre une partie\n");
        scanf("%d", &choix);
    } while(choix != 1 && choix != 2);
    if (choix == 2)
        lire_chessboard(NULL, chessboard);
    while (winning(chessboard) == 0) /*Boucle principale du programme*/
    {
        afficher_chessboard(chessboard);
        choix_utilisateur(chessboard);
    }
    if (winning(chessboard) == 1){
        afficher_chessboard(chessboard);
        printf("Le num_joueur 1 a gagné !");
    } else{
        afficher_chessboard(chessboard);
        printf("Le num_joueur 2 a gagné !");
    }
    return 0;
}