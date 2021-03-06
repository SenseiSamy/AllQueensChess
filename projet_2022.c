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
void lire_chessboard(FILE* fichier, int *chessboard) {
    /*Lit un fichier stockant le chessboard et rempli un tableau décrivant le plateau*/
    fichier = fopen("sauvegarde.txt", "r");
    if (fichier != NULL) {
        for (int i = 0; i < 5; i++) {
            /* lit le fichier et mets les valeurs dans le tableau  */
            fscanf(fichier, "%d %d %d %d %d\n", (chessboard + (i*5) ), (chessboard + (i * 5)+1 ), (chessboard + (i * 5)+2), (chessboard + (i * 5)+3), (chessboard + (i * 5)+4));
        }
        fclose(fichier);
    }
}

void ecrire_chessboard(int chessboard[5][5], FILE* fichier) {
    /*Sauvegarde un Array2D dans un fichier*/
    fichier = fopen("sauvegarde.txt", "w");
    if (fichier != NULL)
    {
        for (int i = 0; i < 5; i++)
        {
            fprintf(fichier, "%d %d %d %d %d\n", chessboard[i][0], chessboard[i][1], chessboard[i][2], chessboard[i][3], chessboard[i][4]);
        }
        fclose(fichier);
    }
}

/*-- Fonctions de jeu --*/
int sans_conflit(Position orig, Position fin, int chessboard[5][5]) {
    /*Vérifie si un mouvement d'un reine est possible, renvoie 0 si le déplacement est possible, renvoie 1 sinon*/
    if (chessboard[fin.y][fin.x] == 0) /*Vérifie que la position d'arrivée est libre*/
    {   
        int x = orig.x, y = orig.y;
        if (fin.y == orig.y){ /*vérifie si le mouvement est horizontal*/
            while ((x != fin.x-1) && (x != fin.x+1)){ /*si oui, vérifie qu'il n'y a pas de reine genant le mouvement*/
                if (x < fin.x)
                    x++;
                else
                    x--;
                if (chessboard[y][x] != 0)
                    return 1; /*retourne 1 si le mouvement est gené*/
            } return 0; /*retourne 0 si aucune reine ne gene*/
        } else if (fin.x == orig.x){ /*vérifie si le mouvement est vertical*/
            while ((y != fin.y-1) && (y != fin.y+1)){ /*si oui, vérifie qu'il n'y a pas de reine genant le mouvement*/
                if (y < fin.y)
                    y++;
                else
                    y--;
                if (chessboard[y][x] != 0)
                    return 1; /*retourne 1 si le mouvement est gené*/ 
            } return 0; /*retourne 0 si aucune reine ne gene*/
        } else if (abs(orig.x - fin.x) == abs(orig.y - fin.y)){ /*vérifie si le mouvement est vertical*/
            if (x < fin.x)
                x++;
            else
                x--;
            if (y < fin.y)
                y++;
            else
                y--;
            while ((x != fin.x) && (y != fin.y)){ /*si oui, vérifie qu'il n'y a pas de reine genant le mouvement*/
                 if (chessboard[y][x] != 0){
                    return 1; /*retourne 1 si le mouvement est gené*/ 
                }
                if (x < fin.x)
                    x++;
                else
                    x--;
                if (y < fin.y)
                    y++;
                else
                    y--;
            } return 0; /*retourne 0 si aucune reine ne gene*/
        } else
            return 1; /*retourne 1 si le mouvement n'est ni horizontal, vertical ou diagonal*/
    }
    return 1; /*retourne 1 si la case d'arrivée n'est pas vide*/
}

int winning(int chessboard[5][5]) {
    int i, j, count_white = 0, count_black = 0;
    /*Vérifie si un num_joueur a gagné en vérifiant le plateau*/
    /*En diagonale*/
    for (i = 0, j = 0; i < 4 && j < 4; j++, i++) {
        if (chessboard[i][j] == 1) {
            count_white += 1;
            if (count_white == 4) {
                return 1;
            }
        }
        else {
            count_white = 0;
        }
    }
    for (i = 0, j = 0; i < 4 && j < 4; j++, i++) {
        if (chessboard[i][j] == 2) {
            count_black += 1;
            if (count_black == 4) {
                return 2;
            }
        }
        else {
            count_black = 0;
        }
    }
    count_black = 0;
    count_white = 0;
    /* deuxieme ligne haut - gauche a droite  */
    for (i = 0, j = 1; j <= 4 && i <= 3; j++, i++) {
        if (chessboard[i][j] == 1) {
            count_white += 1;
            if (count_white == 4) {
                return 1;
            }
        }
        else {
            count_white = 0;
        }
    }
    for (i = 0, j = 1; j <= 4; j++, i++) {
        if (chessboard[i][j] == 2) {
            count_black += 1;
            if (count_black == 4) {
                return 2;
            }
        }
        else {
            count_black = 0;
        }
    }
    count_black = 0;
    count_white = 0;
    /* troisieme ligne bas - gauche a droite  */
    for (i = 1, j = 0; i <= 4; j++, i++) {
        if (chessboard[i][j] == 1) {
            count_white += 1;
            if (count_white == 4) {
                return 1;
            }
        }
        else {
            count_white = 0;
        }
    }
    for (i = 1, j = 0; i <= 4; j++, i++) {
        if (chessboard[i][j] == 2) {
            count_black += 1;
            if (count_black == 4) {
                return 2;
            }
        }
        else {
            count_black = 0;
        }
    }
    count_black = 0;
    count_white = 0;
    /* droite a gauche - diagonale principale */
    for (i = 0, j = 4; j >= 0; j--, i++) {
        if (chessboard[i][j] == 1) {
            count_white += 1;
            if (count_white == 4) {
                return 1;
            }
        }
        else {
            count_white = 0;
        }
    }
    for (i = 0, j = 4; j >= 0; j--, i++) {
        if (chessboard[i][j] == 2) {
            count_black += 1;
            if (count_black == 4) {
                return 2;
            }
        }
        else {
            count_black = 0;
        }
    }
    count_black = 0;
    count_white = 0;
    /* droite a gauche - seconde diagonale */
    for (i = 0, j = 3; i <= 3; j--, i++) {
        if (chessboard[i][j] == 1) {
            count_white += 1;
            if (count_white == 4) {
                return 1;
            }
        }
        else {
            count_white = 0;
        }
    }
    for (i = 0, j = 3; i <= 3; j--, i++) {
        if (chessboard[i][j] == 2) {
            count_black += 1;
            if (count_black == 4) {
                return 2;
            }
        }
        else {
            count_black = 0;
        }
    }
    count_black = 0;
    count_white = 0;
    /* droite a gauche - troisième diagonale */
    for (i = 1, j = 4; i <= 4; j--, i++) {
        if (chessboard[i][j] == 1) {
            count_white += 1;
            if (count_white == 4) {
                return 1;
            }
        }
        else {
            count_white = 0;
        }
    }
    for (i = 1, j = 4; i <= 4; j--, i++) {
        if (chessboard[i][j] == 2) {
            count_black += 1;
            if (count_black == 4) {
                return 2;
            }
        }
        else {
            count_black = 0;
        }
    }
    /* Verif horizontale */
    for (j = 0; j < 5 ; j++) {
        for (i = 0; i < 5 ;i++) {
            if (chessboard[j][i] == 2) {
                count_black += 1;
                if (count_black == 4) {
                    return 2;
                }
            }
            else {
                count_black = 0;
            }
        }
    }
    for (j = 0; j < 5; j++) {
        for (i = 0; i < 5; i++) {
            if (chessboard[j][i] == 2) {
                count_white += 1;
                if (count_white == 4) {
                    return 2;
                }
            }
            else {
                count_white = 0;
            }
        }
    }
    count_black = 0;
    count_white = 0;
    /* Verif verticale */
    for (j = 0; j < 5; j++) {
        for (i = 0; i < 5; i++) {
            if (chessboard[i][j] == 2) {
                count_black += 1;
                if (count_black == 4) {
                    return 2;
                }
            }
            else {
                count_black = 0;
            }
        }
    }
    for (j = 0; j < 5; j++) {
        for (i = 0; i < 5; i++) {
            if (chessboard[i][j] == 2) {
                count_white += 1;
                if (count_white == 4) {
                    return 2;
                }
            }
            else {
                count_white = 0;
            }
        }
    }
    return 0;
}

void afficher_chessboard(int chessboard[5][5]) {
    /*Affiche le chessboard dans le terminal*/
    printf("\033[1;1H\033[2J"); /*Clear le terminal*/
    printf("    A   B   C   D   E\n");
    printf("  ---------------------\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d |", i + 1);
        for (int y = 0; y < 5; y++)
        {
            switch (chessboard[i][y])
            {
            case 1:
                printf("\033[0;34m N \033[0m|");
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

Position* coord_to_pos(char coord[2]) {
    /*Converti une coordonnée de la grille en structure position (ex: A3 -> pos.x = 0, pos.y = 2)*/
    Position* pos = malloc(sizeof(char));
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
    free(pos); 
}

void deplacer_reine(int chessboard[5][5], int joueur) {
    char coord_orig[3], coord_fin[3];
    int num_joueur = joueur;
    Position pos_orig, pos_fin;
deplacer_pion:
    printf("Quel pion voulez vous déplacer (ex : A2) : ");
    scanf("%s", coord_orig);
    pos_orig = *coord_to_pos(coord_orig);
    printf("x = %d  y = %d\n", pos_orig.x, pos_orig.y);
    printf("value emplacement = %d  joueur = %d\n", chessboard[pos_orig.y][pos_orig.x], num_joueur);
    if (chessboard[pos_orig.y][pos_orig.x] != num_joueur)
    {
        afficher_chessboard(chessboard);
        printf("Veuillez indiquer une case avec un pion vous appartenant\n");
        goto deplacer_pion;
    }
    else {
    emplacement_pion:
        afficher_chessboard(chessboard);
        printf("Ou voulez vous le déplacer (ex : A2) : ");
        scanf("%s", coord_fin);
        pos_fin = *coord_to_pos(coord_fin);
        printf("x = %d  y = %d\n", pos_fin.x, pos_fin.y);
        printf("value emplacement = %d  joueur = %d\n", chessboard[pos_fin.y][pos_fin.x], num_joueur);
        printf("sans conflit = %d\n", sans_conflit(pos_orig, pos_fin, chessboard));
        if (sans_conflit(pos_orig, pos_fin, chessboard) != 0)
        {
            afficher_chessboard(chessboard);
            printf("Le déplacement est impossible, veuillez reessayer\n");
            goto emplacement_pion;
        }
        else {
            chessboard[pos_fin.y][pos_fin.x] = chessboard[pos_orig.y][pos_orig.x];
            chessboard[pos_orig.y][pos_orig.x] = 0;
        }
    }
}

void choix_utilisateur(int chessboard[5][5]) {
    int choix;
joueur1:
    printf("Que doit faire le joueur 1 [Noir] ? | 1-Jouer | 2-Abandonner | 3-Sauvegarder\n");
    scanf("%d", &choix);
    if (choix != 1 && choix != 2 && choix != 3) {
        afficher_chessboard(chessboard);
        printf("Veuillez entrer 1, 2 ou 3\n");
        goto joueur1;
    }
    else {
        if (choix == 1) {
            afficher_chessboard(chessboard);
            deplacer_reine(chessboard, 1);
        }
        else if (choix == 2) {
            printf("Le joueur 2 a gagné !");
            exit(1);
        }
        else {
            ecrire_chessboard(chessboard, NULL);
            exit(1);
        }
    }
    /*Tour du Joueur 2*/
    afficher_chessboard(chessboard);
joueur2:
    printf("Que doit faire le joueur 2 [Rouge] ? | 1-Jouer | 2-Abandonner\n");
    scanf("%d", &choix);
    if (choix != 1 && choix != 2) {
        afficher_chessboard(chessboard);
        printf("Veuillez entrer 1, 2 ou 3\n");
        goto joueur2;
    }
    else {
        if (choix == 1) {
            afficher_chessboard(chessboard);
            deplacer_reine(chessboard, 2);
        }
        else {
            printf("Le joueur 1 a gagné !");
            exit(1);
        }
    }
}

int main(void) {
    int chessboard[5][5] = { {1,2,1,2,1},
                            {0,0,0,0,0},
                            {2,0,0,0,1},
                            {0,0,0,0,0},
                            {2,1,2,1,2} };
    int choix;
    //printf("\033[1;1H\033[2J");
    do {
        printf("Que voulez vous faire :\n1 - Nouvelle partie\n2 - Reprendre une partie\n");
        scanf("%d", &choix);
    } while (choix != 1 && choix != 2);
    if (choix == 2)
        lire_chessboard(NULL, chessboard);
    while (winning(chessboard) == 0) /*Boucle principale du programme*/
    {
        afficher_chessboard(chessboard);
        choix_utilisateur(chessboard);
    }
    if (winning(chessboard) == 1) {
        afficher_chessboard(chessboard);
        printf("Le num_joueur 1 a gagné !");
    }
    else {
        afficher_chessboard(chessboard);
        printf("Le num_joueur 2 a gagné !");
    }
    return 0;
}