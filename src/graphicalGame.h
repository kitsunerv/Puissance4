/**
 * @file graphicalGame.h
 * @author Lucas CAGINICOLAU, Brandon CODAN
 * @brief declares the graphical game structures and functions.
*/

#include "windowManager.h"
#include "ai.h"

/**
 * @enum Gstates
 * 
 * @brief this enum contains a definition for all states of the graphical game
*/
enum Gstates {MENU,  GAME, GAMEOVER, AISCREEN, GAMEMODE, END, SETTING};

/**
 * @struct graphical
 * 
 * @brief contains all the data required to make the graphical game run
*/
typedef struct{
    windowManager *window;/**the renderer*/
    enum Gstates status;/**the game's current status*/
    ai *ia;/**the game's ai(s) and their difficulty*/
    connect4 *board;/**the actual game board and all it's data*/
    int red;/**which player places red tokens*/
    int width;/**width of the display*/
    int height;/**height of the display*/
    int bwidth;/**width of the buttons*/
    int bheight;/**height of the buttons*/
    int twidth;/**width of the titles*/
    int theight;/**height of the titles*/
}graphical;

/**
 * @brief initialize the textual game object
 * 
 * @param game the object we want initialized
 * @param window the renderer of the graphical window
 * @param ia the ia object for the game
 * @param board the game board
 * @param height the height of the game window
 * @param width the width of the game window
*/
void initGraphical(graphical *game,windowManager *window,ai *ia,connect4 *board,int height,int width);

/**
 * @brief starts the game in the graphical display style
 * 
 * @param game the game to start
*/
void graphicalGame(graphical *game);

/**
 * @brief destroys the graphical game object
 * 
 * @param game the object we want detroyed;
*/
void destroyGraph(graphical *game);