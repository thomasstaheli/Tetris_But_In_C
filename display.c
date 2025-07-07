//
// Created by thoma on 05.07.2025.
//
#include "display.h"
#include <stdio.h>
#include "settings.h"

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

void clear_display(SDL_display *display) {

  // Background color as black
  SDL_SetRenderDrawColor(display->renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
  SDL_RenderClear(display->renderer);

}

void draw_grid_game(SDL_display *display) {

  // Compute the menu bar place depending on the display size
  uint16_t menu_line_pos = DISPLAY_WIDTH - MENU_BAR_SIZE;
  // Compute the spacing between all the columns
  uint8_t spacing_width = menu_line_pos / BOARD_WIDTH;
  // Compute the spacing between all the lines
  uint8_t spacing_height = DISPLAY_HEIGHT / BOARD_HEIGHT;

  // Set Color for all the Lines
  SDL_SetRenderDrawColor(display->renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);

  // Horizontal lines
  for(uint8_t line = 1; line < BOARD_HEIGHT; line++) {
    SDL_RenderDrawLine(display->renderer, 0, spacing_height * line,
                       menu_line_pos, spacing_height * line);
  }

  // Verticals lines
  for(uint8_t line = 1; line <= BOARD_WIDTH; line++) {
    SDL_RenderDrawLine(display->renderer, spacing_width * line, 0,
                       spacing_width * line, DISPLAY_HEIGHT);
  }

}

void draw_board_game(SDL_display *display) {

  // Compute the menu bar place depending on the display size
  uint16_t menu_line_pos = DISPLAY_WIDTH - MENU_BAR_SIZE;
  // Compute the spacing between all the columns
  uint8_t scare_width = menu_line_pos / BOARD_WIDTH;
  // Compute the spacing between all the lines
  uint8_t scare_height = DISPLAY_HEIGHT / BOARD_HEIGHT;
  // Prepare rectangle to fill the board
  SDL_Rect rect = {.w = scare_width, .h = scare_height}; // x, y, width, height
  Color color;

  for(uint8_t line = 0; line < BOARD_HEIGHT; line++) {
    rect.y = scare_height * line;
    for(uint8_t col = 0; col < BOARD_WIDTH; col++) {
      rect.x = scare_width * col;
      color = shapes_color[display->game->board.get((struct Board *) &display->game->board, line, col)];
      SDL_SetRenderDrawColor(display->renderer, color.r, color.g, color.b, color.a);
      SDL_RenderFillRect(display->renderer, &rect);
    }
  }

}

void play_tetris(SDL_display *display) {

  // Set up the function pointer
  display->game->board.init_board = (void (*)(struct Board *, Shape)) init_board;
  display->game->board.display_board = (void (*)(struct Board *)) display_board;
  display->game->board.put = (int (*)(struct Board *, uint8_t, uint8_t, Shape)) put;
  display->game->board.get = (Shape (*)(struct Board *, uint8_t, uint8_t)) get;
  // Init the game board
  display->game->running = true;
  display->game->board.init_board((struct Board *) &display->game->board, EMPTY);
  // TODO : USING ONLY FOR DEBUG ONLY
  display->game->board.display_board((struct Board *) &display->game->board);

  Shape shape_to_place;

  // animation loop
  while (display->game->running) {
    SDL_Event event;

    // Events management
    while (SDL_PollEvent(&event)) {
      switch (event.type) {

        case SDL_QUIT:
          // handling of close button
          display->game->running = false;
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

    clear_display(display);
    draw_board_game(display);
    draw_grid_game(display);

    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(display->renderer);

    // calculates to 60 fps
    SDL_Delay(1000 / 60);
  }

}
