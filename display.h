//
// Created by thoma on 05.07.2025.
//

#ifndef NAME_DISPLAY_H
#define NAME_DISPLAY_H

#include <SDL.h>
#include "tetris.h"
#include "board.h" // TO assign Color to Shapes


typedef struct {
    uint8_t r, g, b, a;
} Color;

static const Color RED    = {255, 0, 0, 255};
static const Color YELLOW = {255, 255, 0, 255};
static const Color ORANGE = {255, 128, 0, 255};
static const Color BLUE   = {0, 0, 255, 255};
static const Color CYAN   = {43, 255, 255, 255};
static const Color PURPLE = {127, 0, 255, 255};
static const Color GREEN  = {0, 128, 0, 255};
static const Color BLACK  = {0, 0, 0, 255};
static const Color WHITE  = {255, 255, 255, 255};

// Associate Color to Shapes (BLACK for EMPTY, YELLOW for SQUARE, ...)
static const Color shapes_color[8] = {BLACK, YELLOW, CYAN, GREEN,
                                      RED, ORANGE, BLUE, PURPLE};

typedef struct {
    SDL_Window    *window;
    SDL_Renderer  *renderer;
    Tetris_game   *game;
} SDL_display;

void init_display(SDL_display *display);
void remove_display(SDL_display *display);
void clear_display(SDL_display *display);
void draw_grid_game(SDL_display *display);
void draw_board_game(SDL_display *display);

void play_tetris(SDL_display *display);

#endif //NAME_DISPLAY_H
