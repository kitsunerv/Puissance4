/**
 * @file windowManager.h
 * @authors unknown, some of the function were modified (windowManager_assignTexture) and added (msleep, waitGetEvent, window_addImage,windowManager_assignBackground) by Lucas CAGINICOLAU and Brandon CODAN
 * @brief declares the windowManager struct and all the rendering/display related functions.
*/
#pragma once

#include "SDL2/SDL.h"
#include "color.h"

/**
 * @struct windowManager
 * @brief the structure responsible for rendering the graphical display
*/
typedef struct {
  SDL_Window *window;/**the display window*/
  SDL_Renderer *renderer;/**the renderer of the display window*/

  unsigned width;/**width of the display*/
  unsigned height;/**height of the display*/

} windowManager;

/**
 * @brief Construct the window regarding the given parameters.
 *
 * @param window is the window we created.
 * @param title is the window title
 * @param width is the window width
 * @param height is the window height
 * @return 0 if a problem occurs, >0 otherwise.
 */
int windowManager_init(windowManager *window, char *title, unsigned width,
                       unsigned height);

/**
 * @brief Free the memory allocated for the window.
 *
 * @param window is the window we destroy.
 */
void windowManager_destroy(windowManager *window);

/**
 * @brief Change the texture of a particular part of the renderer.
 *
 * @param window is window where the change is applied.
 * @param posxTexture is the position regarding the x-axis.
 * @param posyTexture is the position regarding the y-axis.
 * @param widthTexture is the width of the texture.
 * @param heightTexture is the height of the texture.
 * @param texture is the texture itself (it is a raw matrix).
 * @param desiredwidth is the width of the rectangle we change.
 * @param desiredheight is the height of the rectangle we change.
 */
void windowManager_assignTexture(windowManager *window, unsigned posxTexture,
                                 unsigned posyTexture, unsigned widthTexture,
                                 unsigned heightTexture, color *texture,unsigned desiredwidth,unsigned desiredheight);

/**
 * @brief Wait the the event of quitting the window.
 *
 * @param window is the window we are waiting for the event.
 */
void windowManager_waitUntilQuit(windowManager *window);

/**
 * @brief waits for a mouse click and return it's position if
 * 
 * @param x this parameter serves to get the X coordinate of the mouse when it gets pressed
 * @param y this parameter serves to get the Y coordinate of the mouse when it gets pressed
 * @param end serves to signal if the close button of the window was pressed
*/
void waitGetEvent(int *x,int *y,int *end);

/**
 * @brief displays an image on a particular part of the renderer.
 *
 * @param window is window where the change is applied.
 * @param filepath is the path of the disere image
 * @param posx is the position regarding the x-axis.
 * @param posy is the position regarding the y-axis.
 * @param width is the width of the image we want.
 * @param height is the height of the image we want.
 */
void window_addImage(windowManager *window,char *filepath,int posx,int posy,int width,int height);

/**
 * @brief create a uniform image on the renderer of the specified color
 *
 * @param window is window where the change is applied.
 * @param posxTexture is the position regarding the x-axis.
 * @param posyTexture is the position regarding the y-axis.
 * @param widthTexture is the width of the rectangle we change.
 * @param heightTexture is the height of the rectangle we change.
 * @param color is the color wanted.
 */
void windowManager_assignBackground(windowManager *window, unsigned posxTexture,
                                 unsigned posyTexture, unsigned widthTexture,
                                 unsigned heightTexture, color color);

/**
 * @brief make the calling thread wait the specified amount of milisecond
 * 
 * @param msec the time we want to make the calling thread wait
*/
int msleep(long msec);
