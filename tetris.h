//
// Created by thoma on 05.07.2025.
//

#ifndef NAME_TETRIS_H
#define NAME_TETRIS_H

#include "board.h"
#include <stdbool.h>

typedef struct {
    Board board;
    bool  running;
} Tetris_game;

#endif //NAME_TETRIS_H
