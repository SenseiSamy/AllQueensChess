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
}

int winning(int chessboard[5][5]){
    /*Vérifie si un joueur a gagné en vérifiant le plateau*/
}

int main(void){
    FILE *fichier = NULL;
    int chessboard[5][5] = {{1,2,1,2,1}, {0,0,0,0,0}, {2,0,0,0,1}, {0,0,0,0,0}, {2,1,2,1,2}};
    ecrire_chessboard(chessboard, fichier);
    return 0;
}