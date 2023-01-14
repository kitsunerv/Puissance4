/**
 * @file ai.h
 * @authors Lucas CAGINICOLAU, Brandon CODAN
 * @brief contains the declaration of the ai struct and main ai function as the other function should'nt be called outside of it.
*/
#pragma once
#include "connect4.h"

/**
 * @struct ai
 * 
 * @brief struct containing tha ais data (nb and difficulty of each)
 *  
*/
typedef struct{
    int nb;/** the number of ais (1 for ai1, 2 for ai2, and 3 for both of them) */
    int ai1;/** difficulty of ai1 */
    int ai2;/** difficulty of ai2 */
}ai;

/**
 * @brief this is big brain time 
 * 
 * @param board the board as it currently is
 * @param diff the ai difficlty
 * 
 * @return the column the ai plays
*/
int ai_player(connect4 *board,int diff);
