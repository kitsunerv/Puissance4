/**
 * @file textualGame.c
 * @author Lucas CAGINICOLAU, Brandon CODAN
 * @brief contains the textual game structures and functions.
*/
#include <stdio.h>

#include "textualGame.h"


/**
 *@brief displays the board for the textual style
*/
void affGrille(int board[][7]){//affichage de la grille de jeu en mode terminal
    int i,j;
    printf("/-------------\\\n|1|2|3|4|5|6|7|\n");
    for ( i = 0; i < 6; i++)
    {
        printf("|");
        for ( j = 0; j < 7; j++)
        {
            switch(board[i][j]){
                case 1:
                    printf("O");
                    break;
                case 2:
                    printf("@");
                    break;
                default:
                    printf(" ");
            }
            printf("|");
        }
        printf("\n");
    }
    printf("\\-------------/\n");
    
}

/**
 * @brief takes a human player inputs and executes them
*/
void pInputs(connect4 *board){//cette fonction gere les entrées du jouer humain en mode terminal
    printf("joueur %d : ",board->player+1);
    int pos;
    scanf("%d",&pos);
    while(pos<1||pos>7){//verification que le nombre soit valide
        printf("nombre invalide doit etre entre 1 et 7: ");
        scanf("%d",&pos);
    }
    pos--;
    played(board,pos);
}

/**
 * @brief change the difficulty of the ai passed in parameter
 * 
 * @param ai the ai we want to select the difficulty of
 * @param nb no real importance used for display purpose only
 * 
 * @return set the value of the ai parameters to the chosen difficulty
*/
void aInit(int *ai,int nb){
    int choice;
    printf("choisissez le niveaux de l'ai%d:\n1: facile\n2: normale\n3: difficile\n",nb);
    scanf("%d",&choice);
    while (choice<1&&choice>3){
        printf("choix invalide choisissez entre 1 et 3");
        scanf("%d",&choice);
    }
    *ai=choice;
}

/**
 * @brief the selection of the gamemode and calls the selection of the ai(s) difficulty
 * 
 * @param ai1 difficulty of ai1
 * @param ai2 difficulty of ai2
 * 
 * @return put the variables in parameter to their difficulty
*/
void Ginit(int *ai1,int *ai2){
    int choice;
    printf("choisissez le mode de jeu:\n1: JcJ\n2: JcO (Joueur commence)\n3: OcJ (Ordinateur commence)\n4: OcO\n");
    scanf("%d",&choice);
    while (choice<1&&choice>4){
        printf("choix invalide choisissez entre 1 et 4");
        scanf("%d",&choice);
    }
    switch (choice)
    {
    case 1:
        *ai1=0;
        *ai2=0;
        break;
    case 2:
        
        *ai1=0;
        aInit(ai2,2);
        break;
    case 3:
        aInit(ai1,1);
        *ai2=0;
        break;
    case 4:
        aInit(ai1,1);
        aInit(ai2,2);
        break;
    default:
        break;
    }

}



void initTextual(textual *game,ai *ia,connect4 *board){
    game->board=board;
    game->ia=ia;
}

void textualGame(textual *game){
    int i=0;
    Ginit(&(game->ia->ai1),&(game->ia->ai2));
    reset(game->board);
    int p=0;
    int won =0;
    int end=0;
    while(!won&&!end&&i<42){//game loop
        affGrille(game->board->data);//on affiche la grille
        if(game->ia->ai1>0&&!p){//si tour de joueur 1 et joueur 1 est un ia alors on demande a ia1 ce qu'elle joue
            played(game->board,ai_player(game->board,game->ia->ai1));
        }else if(game->ia->ai2>0&&p){//si tour de joueur 2 et joueur 2 est un ia alors on demande a ia2 ce qu'elle joue
            played(game->board,ai_player(game->board,game->ia->ai2));
        }
        else{//sinon on demande au joueur
            pInputs(game->board);
        }
        won=vertical(game->board->data)||horizontal(game->board->data)||slash(game->board->data)||backslash(game->board->data);//est ce que quelqu'un a gané
        p=!p;//on change le joueur pour le prochain tour
        i++;
    }
    affGrille(game->board->data);//on affiche la grille une derniere fois
    if(i==42&&!won){
        printf("égalité !");
    }
    if(!end){
    printf("Joueur %d a gagné!\n",(!p)+1);
    }
}


void destroyText(textual *game){
    destroy(game->board);
}