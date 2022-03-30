#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct position
{   
    int x;
    int y;
} Position;


/*-- Fonction de sauvegardes --*/
int *lire_chessboard(FILE *fichier, int chessboard[5][5]){
    /*Lit un fichier stockant le chessboard et renvoie un Array2D décrivant les valeurs des cellules de la grille*/
}

void ecrire_chessboard(int chessboard[5][5], FILE *fichier){
    /*Sauvegarde un Array2D dans un fichier*/
    fichier = fopen("sauvegarde.txt", "w");
    if (fichier != NULL)
    {
        for (int i = 0; i < 5; i++)
        {
            fprintf(fichier, "%d,%d,%d,%d,%d\n", chessboard[i][0], chessboard[i][1], chessboard[i][2],chessboard[i][3],chessboard[i][4]);
        }
        fclose(fichier);
    }
}

/*-- Fonctions de jeu --*/
int sans_conflit(Position orig, Position fin, int chessboard[5][5]){
    /*Vérifie si un mouvement d'un reine est possible, renvoie 0 si le déplacement est possible, renvoie 1 sinon*/
    if (chessboard[fin.y][fin.x] == 0) /*Vérifie que la position d'arrivée est libre*/
    {
        if (orig.x == fin.x || orig.y == fin.y) /*Vérifie les mouvements rectilignes*/
            return 0;
        if (abs(fin.x - orig.x) == abs(fin.y - orig.y)) /*Vérifie les mouvements diagonaux*/
            return 0;
    }
    return 1;
}

int winning(int chessboard[5][5]){
    /*Vérifie si un joueur a gagné en vérifiant le plateau*/
}

void afficher_chessboard(int chessboard[5][5]){
    /*Affiche le chessboard dans le terminal*/
    printf("\e[1;1H\e[2J"); /*Clear le terminal*/
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
                    printf(" N |");
                    break;
                case 2:
                    printf(" R |");
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

int main(void){
    FILE *fichier = NULL;
    int chessboard[5][5] = {{1,2,1,2,1}, {0,0,0,0,0}, {2,0,0,0,1}, {0,0,0,0,0}, {2,1,2,1,2}};
    return 0;
}