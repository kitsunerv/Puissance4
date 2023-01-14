/**
 * @file connect4.h
 * @authors Lucas CAGINICOLAU, Brandon CODAN
 * @brief declares the connect4 struct and the game related functions.
*/
#pragma once

#include "color.h"

/**
 * @struct connect4
 * 
 * @brief this struct contains all the data for the game (the game grid, number of tokens in each column,width and height of the graphical,the radius of the tokens,current player, which plaer plays red tokens, a check if the board is tied and the whole grid of pixels to be rendered for the graphical window)
 * 
*/
typedef struct{
    int data[6][7];/**the matrix containnig the states of each cells of the board*/
    int colstate[7];/**the list contining the number of tokens in each columns*/
    unsigned width;/**the width of the board in pixels*/
    unsigned height;/**the height of the board in pixels*/
    int radius;/**the radius of the tokens in pixels*/
    int player;/**the current player (0 = player1, 1 = player2)*/
    int red;/**which player plays the red tokens (0 = player1, 1 = player2)*/
    int tie;/**value to checks if the game is tied*/
    color *pixels;/**the matrix of pixels that make the board displays as it is*/
}connect4;

/**
 * @brief initilaze the connect4 object with the specified width and height for the graphical window
 * 
 * @param board the object we want to initialize
 * @param width the width of the graphical wiondow
 * @param height the height of the graphical wiondow
*/
void init(connect4 *board, int width, int height);

/**
 * @brief execute a move
 * 
 * @param board the game
 * @param col the column played
 * 
 * 
*/
void played(connect4 *board, int col);

/**
 * @brief draws the background of the bord then call the function update which draws the pieces or empty slots
 * 
 * @param board the game we want to draw
*/
void draw(connect4 *board);

/**
 * @brief draws the slot passed int parameters with the x and y coordinate
 * 
 * @param board the object we want to update
 * @param x the x coordinate of the slot we want updated
 * @param y the y coordinate of the slot we want updated
 * 
*/
void update(connect4 *board,int x,int y);

/**
 * @brief destroys the object passed in parameter
 * 
 * @param board the object we want destroyed
*/
void destroy(connect4 *board);

/**
 * @brief checks if someone won in a horizontal motif
 * 
 * @param board the game board that we want to test
 * 
 * @return 1 if someone won with a horizontal motif else 0
*/
int horizontal(int board[6][7]);

/**
 * @brief checks if someone won in a vertical motif
 * 
 * @param board the game board that we want to test
 * 
 * @return 1 if someone won with a vertical motif else 0
*/
int vertical(int board[6][7]);

/**
 * @brief checks if someone won in a diagonal motif in the same orentation as a slah (/)
 * 
 * @param board the game board that we want to test
 * 
 * @return 1 if someone won with a slash diagonal else 0
*/
int slash(int board[6][7]);

/**
 * @brief checks if someone won in a diagonal motif in the same orentation as a backslah (\)
 * 
 * @param board the game board that we want to test
 * 
 * @return 1 if someone won with a backslash diagonal else 0
*/
int backslash(int board[6][7]);

/**
 * @brief resets the data of the board in parameter
 * 
 * @param board the board we want reset
*/
void reset(connect4 *board);
