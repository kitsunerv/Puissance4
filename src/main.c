/**
 * @file main.c
 * @author Lucas CAGINICOLAU, Brandon CODAN
 * @brief the main game functions.
*/


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SDL2/SDL.h"

#include "SDL2/SDL_error.h"
#include "connect4.h"
#include "windowManager.h"
#include "ai.h"
#include "graphicalGame.h"
#include "textualGame.h"

/**
 * @def WIDTH
 * @brief the width of the window
*/
#define WIDTH 1722
/**
 * @def HEIGHT
 * @brief the height of the window
*/
#define HEIGHT 962


/**
 * @brief the main game loop
*/
int main() {
  srand(time(NULL));
  connect4 board;
  int choice;
  ai ia={0,0,0};
  printf("choisissez le style de jeu:\n1: textuel\n2: graphique\n");
  scanf("%d",&choice);
  while (choice!=1&&choice!=2){
    printf("choix invalid choisissez entre 1 et2\n");
    scanf("%d",&choice);
  }
  if(choice==2){
    init(&board,HEIGHT,WIDTH);
    windowManager window;
    windowManager_init(&window, "Puissance 4", WIDTH, HEIGHT);
    graphical game;
    initGraphical(&game,&window,&ia,&board,HEIGHT,WIDTH);
    graphicalGame(&game);
    destroyGraph(&game);

  }else{
    init(&board,0,0);
    textual game;
    initTextual(&game,&ia,&board);
    textualGame(&game);
    destroyText(&game);
  }
  return 0;
}