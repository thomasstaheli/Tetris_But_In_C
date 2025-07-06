//
// Created by thoma on 05.07.2025.
//
#include "display.h"
#include "stdio.h"
#include "settings.h"

typedef struct {
    uint8_t r, g, b, a;
} Color;

void init_display(SDL_display *display) {

  SDL_Init(SDL_INIT_VIDEO);

  display->window = SDL_CreateWindow(
          "Tetris in C",
          SDL_WINDOWPOS_CENTERED,
          SDL_WINDOWPOS_CENTERED,
          DISPLAY_WIDTH, DISPLAY_HEIGHT,
          SDL_WINDOW_SHOWN
  );

  display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);

  Color backgroundColor = {0, 0, 0, 255};

  SDL_SetRenderDrawColor(display->renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
  SDL_RenderClear(display->renderer);
  SDL_RenderPresent(display->renderer);

}

void remove_display(SDL_display *display) {

  SDL_DestroyRenderer(display->renderer);
  SDL_DestroyWindow(display->window);
  SDL_Quit();

}

