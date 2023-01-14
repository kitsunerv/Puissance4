/**
 * @file textualGame.h
 * @author Lucas CAGINICOLAU, Brandon CODAN
 * @brief contains the textual game structures and functions.
*/

#include "ai.h"


/**
 * @struct textual
 * 
 * @brief contains all the data required to make the graphical game run
*/
typedef struct{
    ai *ia;/**the game's ai(s) and their difficulty*/
    connect4 *board;/**the actual game board and all it's data*/
}textual;

/**
 * @brief initialize the textual game object
 * 
 * @param game the object we want initialized
 * @param ia the ia object for the game
 * @param board the game board
*/
void initTextual(textual *game,ai *ia,connect4 *board);

/**
 * @brief starts the game in the textual display style
 * 
 * @param game the game to start
*/
void textualGame(textual *game);

/**
 * @brief destroys the textual game object
 * 
 * @param game the object we want detroyed;
*/
void destroyText(textual *game);