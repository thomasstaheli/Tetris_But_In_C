//
// Created by thoma on 05.07.2025.
//

#ifndef NAME_DISPLAY_H
#define NAME_DISPLAY_H

#include <SDL.h>

typedef struct {
    uint8_t r, g, b, a;
} Color;

static const Color RED    = {255, 0, 0, 255};
static const Color BLACK  = {0, 0, 0, 255};
static const Color WHITE  = {255, 255, 255, 255};

typedef struct {
    SDL_Window    *window;
    SDL_Renderer  *renderer;
} SDL_display;

void init_display(SDL_display *display);
void remove_display(SDL_display *display);
void draw_grid_game(SDL_display *display);

#endif //NAME_DISPLAY_H
