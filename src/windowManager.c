/**
 * @file windowManager.c
 * @authors unknown, some of the function were modified (windowManager_assignTexture) and added (msleep, waitGetEvent, window_addImage,windowManager_assignBackground) by Lucas CAGINICOLAU and Brandon CODAN
 * @brief contains all the rendering/display related functions.
*/
#include <time.h>
#include "windowManager.h"

#include "SDL2/SDL_error.h"

static int counter = 0;

int windowManager_init(windowManager *window, char *title, unsigned width,
                       unsigned height) {
  if (!counter) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      fprintf(stderr, "Error SDL_Init: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
  }
  counter++;

  window->window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_SHOWN);

  if (!window->window) {
    fprintf(stderr, "Error SDL_CreateWindow: %s", SDL_GetError());
    return 0;
  }

  window->renderer =
      SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
  if (!window->renderer) {
    fprintf(stderr, "Error SDL_CreateRenderer: %s", SDL_GetError());
    SDL_DestroyWindow(window->window);
    return 0;
  }

  return 1;
}  // windowManager_init

void windowManager_destroy(windowManager *window) {
  SDL_DestroyRenderer(window->renderer);
  SDL_DestroyWindow(window->window);

  counter--;
  if (!counter) {
    SDL_Quit();
  }
}  // windowManager_destroy

void windowManager_assignTexture(windowManager *window, unsigned posxTexture,
                                 unsigned posyTexture, unsigned widthTexture,
                                 unsigned heightTexture, color *data,unsigned desiredwidth,unsigned desiredheight) {
  void *tmp;
  Uint32 *pixels;
  SDL_Texture *texture;
  SDL_PixelFormat *format;
  int i, j, pitch;

  texture = SDL_CreateTexture(window->renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_STREAMING, widthTexture,
                              heightTexture);

  if (!texture) {
    fprintf(stderr, "Error SDL_CreateTexture: %s", SDL_GetError());
    return;
  }

  format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
  if (!format) {
    fprintf(stderr, "Error SDL_AllocFormat: %s", SDL_GetError());
    SDL_DestroyTexture(texture);
    return;
  }

  SDL_LockTexture(texture, NULL, &tmp, &pitch);
  pixels = tmp;
  for (i = 0; i < heightTexture; i++) {
    for (j = 0; j < widthTexture; j++) {
    //fprintf(stderr,"aaaaah %d  %d\n",j,i);
    
      color c = data[i * widthTexture + j];
      pixels[i * widthTexture + j] = SDL_MapRGBA(format, c.r, c.g, c.b, c.a);
    }
  }
  SDL_Rect dstrect = { posxTexture, posyTexture, desiredwidth, desiredheight };
  SDL_UnlockTexture(texture);
  SDL_RenderCopy(window->renderer, texture, NULL, &dstrect);
  SDL_RenderPresent(window->renderer);

  SDL_FreeFormat(format);
  SDL_DestroyTexture(texture);
}  // windowManager_assignTexture

void waitGetEvent(int *x,int *y,int *end){
  SDL_Event event;
  while (SDL_WaitEvent(&event) >= 0) {
    switch (event.type) {
      case SDL_MOUSEBUTTONDOWN: {
        SDL_GetMouseState(x,y);
        return;
      } break;
      case SDL_QUIT:
        *x=0;
        *y=0;
        break;
    }
  }
}

void windowManager_waitUntilQuit(windowManager *window) {
  SDL_Event event;

  // Loop waiting for quitting
  while (SDL_WaitEvent(&event) >= 0) {
    switch (event.type) {
      case SDL_QUIT: {
        return;
      } break;
    }
  }
}  // windowManager_waitUntilQuit

int msleep(long msec)
{
    struct timespec ts;
    int res;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res);

    return res;
}

void window_addImage(windowManager *window,char *filepath,int posx,int posy,int width,int height){
  msleep(10);
  SDL_Surface *image = SDL_LoadBMP(filepath);
  if (!image) {
    fprintf(stderr, "Error SDL_LoadBMP: %s\n", SDL_GetError());
    return;
  }
  SDL_Texture * texture = SDL_CreateTextureFromSurface(window->renderer, image);
  if (!texture) {
    fprintf(stderr, "Error SDL_CreateTexture: %s\n", SDL_GetError());
    return;
  }
  SDL_Rect dstrect = { posx, posy, width, height };
  SDL_RenderCopy(window->renderer, texture, NULL, &dstrect);
  SDL_RenderPresent(window->renderer);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(image);
}

void windowManager_assignBackground(windowManager *window, unsigned posxTexture,
                                 unsigned posyTexture, unsigned widthTexture,
                                 unsigned heightTexture, color c) {
  void *tmp;
  Uint32 *pixels;
  SDL_Texture *texture;
  SDL_PixelFormat *format;
  int i, j, pitch;

  texture = SDL_CreateTexture(window->renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_STREAMING, widthTexture,
                              heightTexture);

  if (!texture) {
    fprintf(stderr, "Error SDL_CreateTexture: %s", SDL_GetError());
    return;
  }

  format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
  if (!format) {
    fprintf(stderr, "Error SDL_AllocFormat: %s", SDL_GetError());
    SDL_DestroyTexture(texture);
    return;
  }

  SDL_LockTexture(texture, NULL, &tmp, &pitch);
  pixels = tmp;
  for (i = 0; i < heightTexture; i++) {
    for (j = 0; j < widthTexture; j++) {
    //fprintf(stderr,"aaaaah %d  %d\n",j,i);
    
      pixels[i * widthTexture + j] = SDL_MapRGBA(format, c.r, c.g, c.b, c.a);
    }
  }
  SDL_UnlockTexture(texture);
  SDL_RenderCopy(window->renderer, texture, NULL, NULL);
  SDL_RenderPresent(window->renderer);

  SDL_FreeFormat(format);
  SDL_DestroyTexture(texture);
}  // windowManager_assignTexture

