#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <windows.h>
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
            /* enregistre le tabledau dans le fichier "sauvegarde.txt"  */
            fprintf(fichier, "%d %d %d %d %d\n", chessboard[i][0], chessboard[i][1], chessboard[i][2], chessboard[i][3], chessboard[i][4]);
        }
        fclose(fichier);
    }
}

/*-- Fonctions de jeu --*/
int sans_conflit(Position orig, Position fin, int chessboard[5][5]) {
    int i, y, count;
    /*Vérifie si un mouvement d'un reine est possible, renvoie 0 si le déplacement est possible, renvoie 1 sinon*/
    if (chessboard[fin.y][fin.x] == 0) /*Vérifie que la position d'arrivée est libre*/
    {
        count = 0;
        if (orig.x == fin.x || orig.y == fin.y) {/*Vérifie les mouvements rectilignes*/
            if (orig.x == fin.x) { /* Vertical */
                if ((orig.y - fin.y) < 0) { /* Vertical haut en bas */
                    for (i = orig.y; i <= fin.y; i++) {
                        if (chessboard[i][orig.x] == 0) {
                            count += 1;
                            if (count == abs(orig.y - fin.y)) {
                                return 0;
                            }
                        }
                    }
                }
                else if ((orig.y - fin.y) >= 0) { /* Vertical bas en haut */
                    for (i = fin.y; i <= orig.y; i++) {
                        if (chessboard[i][orig.x] == 0) {
                            count += 1;
                            if (count == abs(orig.y - fin.y)) {
                                return 0;
                            }
                        }
                    }
                }
            }
            else if (orig.y == fin.y) {
                count = 0;
                if ((orig.x - fin.x) < 0) { /* Horizontal gauche a droite */
                    for (i = orig.x; i <= fin.x; i++) {
                        if (chessboard[orig.y][i] == 0) {
                            count += 1;
                            if (count == abs(orig.x - fin.x)) {
                                return 0;
                            }
                        }
                    }
                }
                else if ((orig.x - fin.x) >= 0) { /* Horizontal droite a gauche */
                    for (i = fin.x; i <= orig.x; i++) {
                        if (chessboard[orig.y][i] == 0) {
                            count += 1;
                            if (count == abs(orig.x - fin.x)) {
                                return 0;
                            }
                        }
                    }
                }
            }
        }
        /*Vérifie les mouvements diagonaux*/
        else if (abs(orig.x - fin.x) == abs(orig.y - fin.y)) {
            count = 0;
            if ((fin.x - orig.x) > 0 && (fin.y - orig.y) > 0) { /* Haut en Bas - Gauche a Droite */
                for (y = orig.y, i = orig.x; y <= fin.y; y++, i++) {
                    if (chessboard[y][i] == 0) {
                        count += 1;
                        if (count == abs(fin.x - orig.x)) {
                            return 0;
                        }
                    }
                }
            }
            else if ((fin.x - orig.x) < 0 && (fin.y - orig.y) > 0) { /* Haut en Bas - Droite a Gauche */
                count = 0;
                for (i = orig.x, y = orig.y; i > fin.x; i--, y++) {
                    if (chessboard[y][i] == 0) {
                        count += 1;
                        if (count == abs(fin.x - orig.x)) {
                            return 0;
                        }
                    }
                }
            }
            else if ((fin.x - orig.x) > 0 && (fin.y - orig.y) < 0) { /* Bas en Haut - Gauche a Droite */
                count = 0;
                for (i = orig.x, y = orig.y; i <= fin.x; i++, y--) {
                    if (chessboard[y][i] == 0) {
                        count += 1;
                        if (count == abs(fin.x - orig.x)) {
                            return 0;
                        }
                    }
                }
            }
            else if ((fin.x - orig.x) < 0 && (fin.y - orig.y) < 0) { /* Haut en Bas - Droite a Gauche */
                count = 0;
                for (i = fin.x, y = fin.y; i > orig.x; i--, y--) {
                    if (chessboard[y][i] == 0) {
                        count += 1;
                        if (count == abs(fin.x - orig.x)) {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int winning(int chessboard[5][5]) {
    int i, j, count_white = 0, count_black = 0;
    /*Vérifie si un joueur a gagné en vérifiant le plateau*/
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
    for (j = 0; j < 5; j++) {
        for (i = 0; i < 5; i++) {
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
    printf("     A   B   C   D   E\n");
    printf("   ---------------------\n");
    for (int i = 0; i < 5; i++)
    {
        printf(" %d |", i + 1);
        for (int y = 0; y < 5; y++)
        {
            switch (chessboard[i][y])
            {
            case 1:
                printf("\033[47m\033[7;34m N \033[0m|");
                break;
            case 2:
                printf("\033[47m\033[7;31m R \033[0m|");
                break;
            default:
                printf("\033[47m   \033[0m|");
                break;
            }
        }
        printf("\n");
        printf("   ---------------------\033[0m\n");
    }
}

Position* coord_to_pos(char coord[2]) {
    /*Converti une coordonnée de la grille en structure position (ex: A3 -> pos.x = 0, pos.y = 2)*/
    Position* pos = malloc(sizeof(char));
    switch (coord[0]) /* regarde le premier charactère */
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
    switch (coord[1]) /* regarde le second charactère pour convertire*/
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
    if (joueur == 2) {
        printf("\033[0;31m[Rouge]\033[0mQuel pion voulez vous deplacer (ex : A2) : ");
    }
    else {
        printf("\033[0;34m[Noir]\033[0mQuel pion voulez vous deplacer (ex : A2) : ");
    }
    scanf("%s", coord_orig);
    pos_orig = *coord_to_pos(coord_orig);
    if (chessboard[pos_orig.y][pos_orig.x] != num_joueur)
    {
        afficher_chessboard(chessboard);
        printf("\033[0;41m\033[1;36m /!\\ Veuillez indiquer une case avec un pion vous appartenant /!\\ \033[0m\n");
        goto deplacer_pion;
    }
    else {
    emplacement_pion:
        afficher_chessboard(chessboard);
        if (joueur == 2) {
            printf("\033[0;31m[Rouge]\033[0mOu voulez vous le deplacer (ex : A2) : \033[0m");
        }
        else {
            printf("\033[0;34m[Noir]\033[0mOu voulez vous le deplacer (ex : A2) : \033[0m");
        }
        scanf("%s", coord_fin);
        pos_fin = *coord_to_pos(coord_fin);
        if (sans_conflit(pos_orig, pos_fin, chessboard) != 0)
        {
            afficher_chessboard(chessboard);
            printf("\033[0;41m\033[1;37m Le deplacement est impossible, veuillez reessayer \033[0m\n");
            Sleep(3000);
            goto emplacement_pion;
        }
        else {
            chessboard[pos_fin.y][pos_fin.x] = chessboard[pos_orig.y][pos_orig.x];
            chessboard[pos_orig.y][pos_orig.x] = 0;
        }
    }
}

void choix_utilisateur(int chessboard[5][5]) {
    /*Demande à l'utilisateur sont choix*/
    int choix;
joueur1:
    printf("\033[0;34m[Noir]\033[0mQue doit faire le joueur 1 ? | 1-Jouer | 2-Abandonner | 3-Sauvegarder \033[0m\n");
    scanf("%d", &choix);
    if (choix != 1 && choix != 2 && choix != 3) {
        afficher_chessboard(chessboard);
        printf("\033[0;41m\033[1;37m Veuillez entrer 1, 2 ou 3 \033[0m\n");
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
    printf("\033[0;31m[Rouge]\033[0mQue doit faire le joueur 2 ? | 1-Jouer | 2-Abandonner\033[0m\n");
    scanf("%d", &choix);
    if (choix != 1 && choix != 2) {
        afficher_chessboard(chessboard);
        printf("\033[0;41m\033[1;37m Veuillez entrer 1, 2 ou 3 \033[0m\n");
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
    int chessboard[5][5] = {{1,2,1,2,1},
                            {0,0,0,0,0},
                            {2,0,0,0,1},
                            {0,0,0,0,0},
                            {2,1,2,1,2} };
    int choix=0;
    do { /* Premier choix au début du lancement du prog */
        printf("\033[4;37mQue voulez vous faire :\033[0m\n 1 - Nouvelle partie\n 2 - Reprendre une partie\n");
        scanf("%d", &choix);
    } while (choix != 1 && choix != 2);
    if (choix == 2)
        lire_chessboard(NULL, &chessboard[0][0]);
    while (winning(chessboard) == 0) /*Boucle principale du programme*/
    {
        afficher_chessboard(chessboard);
        choix_utilisateur(chessboard);
    }
    if (winning(chessboard) == 1) { /* Vérification qui a gagné */
        afficher_chessboard(chessboard);
        printf("\033[1;37mLe Joueur Noir a gagné !");
    }
    else {
        afficher_chessboard(chessboard);
        printf("\033[1;37mLe Joueur Rouge a gagné !");
    }
    return 0;
}