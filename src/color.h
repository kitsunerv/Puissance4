/**
 * @file color.h
 * @authors unknown most likely, colors definition added by Lucas CAGINICOLAU and Brandon CODAN
 * @brief declares the color struct and all colors used throughout the graphiccal game.
*/
#pragma once

/**
 * @struct color
 * 
 * @brief this structure is how pixels colors are managed
*/
typedef struct {
  unsigned r : 8;/**the red value of the color*/
  unsigned g : 8;/**the green value of the color*/
  unsigned b : 8;/**the blue value of the color*/
  unsigned a : 8;/**the alpha value of the color*/
} color;

/**
 * @def COLOR_RED
 * @def COLOR_YELLOW
 * @def COLOR_BLACK
 * @def COLOR_BLUE
*/
#define COLOR_RED ((color){255, 0, 0, 255})
#define COLOR_YELLOW ((color){255, 255, 0, 255})
#define COLOR_BLACK ((color){0, 0, 0, 255})
#define COLOR_BLUE ((color){0, 0, 255, 255})