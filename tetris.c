//
// Created by thoma on 05.07.2025.
//
#include "display.h"
#include "tetris.h"
#include <stdbool.h>

void play_tetris(Tetris_game *game, SDL_display *display) {

  bool close = false;

  // animation loop
  while (!close) {
    SDL_Event event;

    // Events management
    while (SDL_PollEvent(&event)) {
      switch (event.type) {

        case SDL_QUIT:
          // handling of close button
          close = 1;
          break;

        case SDL_KEYDOWN:
          // keyboard API for key pressed
          switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
              // ...
              break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
              // ...
              break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
              // ...
              break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
              // ...
              break;
            default:
              break;
          }
      }
    }

    // clears the screen
    SDL_RenderClear(display->renderer);
    // SDL_RenderCopy(display->renderer, tex, NULL, &dest);

    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(display->renderer);

    // calculates to 60 fps
    SDL_Delay(1000 / 60);
  }

}