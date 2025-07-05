//
// Created by thoma on 05.07.2025.
//

#ifndef NAME_DISPLAY_H
#define NAME_DISPLAY_H

#include <SDL.h>

#define DISPLAY_WIDTH   1000
#define DISPLAY_HEIGHT  1000

typedef struct {
    SDL_Window    *window;
    SDL_Renderer  *renderer;
} SDL_display;

void init_display(SDL_display *display);
void remove_display(SDL_display *display);

#endif //NAME_DISPLAY_H
