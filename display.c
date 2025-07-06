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

void draw_grid_game(SDL_display *display) {

  // Background color as black
  SDL_SetRenderDrawColor(display->renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
  SDL_RenderClear(display->renderer);

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

