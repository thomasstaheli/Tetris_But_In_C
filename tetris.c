//
// Created by thoma on 05.07.2025.
//
#include "display.h"
#include "tetris.h"

void play_tetris(Tetris_game *game, SDL_display *display) {

  game->board.init_board = (void (*)(struct Board *, Shape)) init_board;
  game->board.display_board = (void (*)(struct Board *)) display_board;
  game->board.put = (int (*)(struct Board *, uint8_t, uint8_t, Shape)) put;
  game->board.get = (Shape (*)(struct Board *, uint8_t, uint8_t)) get;

  game->running = true;
  game->board.init_board((struct Board *) &game->board, EMPTY);
  // TODO : USING ONLY FOR DEBUG
  game->board.display_board((struct Board *) &game->board);

  // animation loop
  while (game->running) {
    SDL_Event event;

    // Events management
    while (SDL_PollEvent(&event)) {
      switch (event.type) {

        case SDL_QUIT:
          // handling of close button
          game->running = false;
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

    draw_grid_game(display);

    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(display->renderer);

    // calculates to 60 fps
    SDL_Delay(1000 / 60);
  }

}