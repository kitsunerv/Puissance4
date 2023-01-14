/**
 * @file connect4.c
 * @authors Lucas CAGINICOLAU, Brandon CODAN
 * @brief all the game related functions.
*/

#include "connect4.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void update(connect4 *board,int x,int y){
    int col,line;
    int divx= board->width/7;
    int divy= board->height/6;
    int cx=(divx*x)+(divx/2);
    int cy=(divy*y)+(divy/2);
    int dx,dy;
    int infx=divx*x;
    int infy=divy*y;
    int supx=infx+divx;
    int supy=infy+divy;
    int rad=board->radius*board->radius;
    for ( line = infy; line < supy && line < board->height; line++)
    {
        for (col = infx; col < supx && col < board->width; col++)
        {
            dx=(col-cx)*(col-cx);
            dy=(line-cy)*(line-cy);
            if(dx+dy<=rad){
                if(board->data[y][x]==board->red+1){
                    board->pixels[col+(board->width*line)]=COLOR_RED;
                }else if(board->data[y][x]==0){
                    board->pixels[col+(board->width*line)]=COLOR_BLACK;
                }else{
                    board->pixels[col+(board->width*line)]=COLOR_YELLOW;
                }
            }
        }
   }
    
}

void draw(connect4 *board){
    int i,j;
    for (i = 0; i < board->height;i++){
        for ( j = 0; j < board->width; j++){
            board->pixels[(i*board->width)+j]=COLOR_BLUE;
        }
    }
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
        {
            update(board,j,i);
        }
    }
}

void init(connect4 *board ,int height ,int width){
    board->red=0;
    board->player=0;
    board->tie=0;
    board->height=height;
    board->width=width;
    int i,j;
    for (i = 0; i < 7; i++)
    {
        board->colstate[i]=0;
    }
    for ( i = 0; i < 6; i++)
    {
        for ( j = 0; j < 7; j++)
        {
            board->data[i][j]=0;
        }
        
    }
    int divx=width/7;
    int divy=height/6;
    if(divx>divy){
        board->radius=((float)(divy)*0.9)/2;
    }else{
        board->radius=((float)(divx)*0.9)/2;
    }
    board->pixels=(color *)malloc(width * height * sizeof(color));;
    if(!board){
        printf("probleme alloc 5\n");
    }
    draw(board);
}

void played(connect4 *board, int col){
    int line=5-board->colstate[col];
    if(line>=0){
        board->colstate[col]++;
        board->data[line][col]=board->player+1;
        board->player=!board->player;
        update(board,col,line);
    }
}

void destroy(connect4 *board){
    free(board->pixels);
}

int backslash(int data[6][7]){
    int i,j;
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            if(data[i][j]!=0&&data[i][j]==data[i+1][j+1]&&
                data[i+1][j+1]==data[i+2][j+2]&&
                    data[i+2][j+2]==data[i+3][j+3]){
                return 1;
            }
        }
    }
    return 0;
}

int slash(int data[6][7]){
    int i,j;
    for ( i = 0; i < 3; i++)
    {
        for ( j = 3; j < 7; j++)
        {
            if(data[i][j]!=0&&data[i][j]==data[i+1][j-1]&&
                data[i+1][j-1]==data[i+2][j-2]&&
                    data[i+2][j-2]==data[i+3][j-3]){
                return 1;
            }
        }
    }
    return 0;
}

int vertical(int data[6][7]){
    int i,j;
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 7; j++)
        {
            if(data[i][j]!=0&&data[i][j]==data[i+1][j]&&
                data[i+1][j]==data[i+2][j]&&
                    data[i+2][j]==data[i+3][j]){
                return 1;
            }
        }
    }
    return 0;
}

int horizontal(int data[6][7]){
    int i,j;
    for ( i = 0; i < 6; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            if(data[i][j]!=0&&data[i][j]==data[i][j+1]&&
                data[i][j+1]==data[i][j+2]&&
                    data[i][j+2]==data[i][j+3]){
                return 1;
            }
        }
    }
    return 0;
}

void reset(connect4 *board){
    int line,col;
    for ( col = 0; col < 7; col++)
    {
        for ( line = 0; line < 6; line++)
        {
            board->data[line][col]=0;
            update(board,col,line);
        }
        board->colstate[col]=0;
    }
    board->player=0;
    board->tie=0;
}