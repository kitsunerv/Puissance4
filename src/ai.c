/**
 * @file ai.c
 * @authors Lucas CAGINICOLAU, Brandon CODAN
 * @brief all the ai functions.
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "ai.h"
#include "connect4.h"


/**
 * @brief checks if the player in the parameters can win
 * 
 * @param p the player we want to check
 * @param board the board as it is currently
 * 
 * @return 1 if the player can win else 0
*/
int winnable(int p,int board[][7]){// regarde si le joueur passé en parametre a la possibilité de gagner
    int line,col;
    for ( col = 0; col < 7; col++){
        if(board[0][col]!=0){
            continue;
        }
        line=0;
        while (line<5&&board[line+1][col]==0){
            line++;
        }
        board[line][col]=(p)+1;
        if(slash(board)||backslash(board)||vertical(board)||horizontal(board)){
            return col;//si oui on retourne la colonne concernée
        }else{
            board[line][col]=0;
        }
    }
    return -1;//sinon on retourne -1 vu que 0 est une valeur accepté 
}

/**
 * @brief test which collumns to avoid  since playing them would lead to the other player's win
 * 
 * @param p the current player
 * @param tempboard the board used to test various things 
 * @param forbidden the the list of forbidden collumns
 * @param nb the number of entries in the list of forbidden collumns
 * 
 * @return the list of forbidden columns and how many they are
*/
void block(int p,int tempboard[][7],int *forbidden,int *nb){
    int line,col;
    for ( col = 0; col < 7; col++){
        if(tempboard[0][col]!=0){
            continue;
        }
        line=0;
        while (line<5&&tempboard[line+1][col]==0){
            line++;
        }
        if(line>0){
            tempboard[line-1][col]=(!p)+1;
            
            if(slash(tempboard)||backslash(tempboard)||vertical(tempboard)||horizontal(tempboard)){
                (*nb)++;
                forbidden[(*nb)-1]=col;                
            }
            tempboard[line-1][col]=0;
        }
    }
}


/**
 * @brief counts how many possibility to win the player passed in parameters has to win
 * 
 * @param board the board we want to test
 * @param p the player we want to test
*/
int count(int board[][7],int p){
    int line,col,res=0;
    for ( col = 0; col < 7; col++){
        if(board[0][col]!=0){
            continue;
        }
        line=0;
        while (line<5&&board[line+1][col]==0){
            line++;
        }
        board[line][col]=p+1;
        if(slash(board)||backslash(board)||vertical(board)||horizontal(board)){
            res++;
        }
        board[line][col]=0;
    }
    return res;
}


/**
 * @brief checks if there is a column in which if the other player played it would lead to him having two ways to win
 * 
 * @param p the player we want to check
 * @param board the board as it currently is
 * @param forbidden the list of forbiden columns
 * @param nb the number of forbidden columns
 * 
 * @return the column to block or -1 if none since 0 is accepted
*/
int forkblock(int p,int board[][7],int forbidden[], int *nb){
    int line,col;
    for ( col = 0; col < 7; col++){
        if(board[0][col]!=0){
            continue;
        }
        line=0;
        while (line<5&&board[line+1][col]==0){
            line++;
        }
        board[line][col]=p+1;
        int t=count(board,p);
        board[line][col]=0;
        if(t>1){
            return col;//si oui on retourne la colonne concernée
        }else{
            if(line>0){
                board[line-1][col]=(p)+1;
                if(count(board,p)>1){
                    (*nb)++;
                    forbidden[(*nb)-1]=col;
                }
                board[line-1][col]=0;
            }
        }
    }
    return -1;//sinon on retourne -1 vu que 0 est une valeur accepté 
}

int ai_player(connect4 *board,int diff){
    if(board->data[5][3]==0)return 3;
    int tempboard[6][7];
    int nbforbidden=0;
    int t,i,j;
    int line,col;
    for ( line = 0; line < 6; line++){//copie la grille d'origine pour etre sur de pas faire de la merde avec
        for ( col = 0; col < 7; col++){
            tempboard[line][col]=board->data[line][col];
        }
        
    }
    t=winnable(board->player,tempboard);//regarde si l'ia a la possibilité de gagner
    if(t!=-1){//si oui on gagne
        return t;
    }
    t=winnable(!board->player,tempboard);//regarde si dans l'etat actuel l'adversaire a la possibilité de gagner
    if(t!=-1){//si oui on le bloque
        return t;
    }
    int forbidden[7];
    
    if(diff>1){//si l'ia est en mode normal elle regarde si il y a des colonnes a eviter car placer un pion dans ces collones donnerai la possibilité de gagner a l'adversaire
        block(board->player,tempboard,forbidden,&nbforbidden);
    }
    if(diff>2){//si l'ia est en mode difficile elle regarde si en l'etat actuel l'adversaire a la possibilité de creer un scenario ou peut importe l'action de l'ia au prochain tour l'adversaire gagnera (aussi appelé fouchette)
        t=forkblock(!board->player,tempboard,forbidden,&nbforbidden);
        if(t!=-1){//Si oui on le bloque
            return t;
        }
    }

    int dispo[7];
    int nbdispo=0;
    int t2;
    for( i=0 ; i<7 ; i++ ){//on regardes quelle colonnes qui sont sans risque et pas pleine
        t2=0;
        for( j=0 ; j<nbforbidden ; j++){
            if(i==forbidden[j]) t2=1;
        }
        if(!t2&&board->data[0][i]==0){
            nbdispo++;
            dispo[nbdispo-1]=i;
        }
    }
    int r;
    if(nbdispo>0){
            t=rand();
            r= t% nbdispo;
            t=dispo[r];
    }else{
            r=rand() % nbforbidden;
            t=forbidden[r];
    }
    return (t);
}