//
// Created by thoma on 06.07.2025.
//

#ifndef NAME_BOARD_H
#define NAME_BOARD_H

#include "settings.h"
#include <stdint.h>

typedef enum {
    EMPTY, SQUARE, RECTANGLE, S_SHAPE, Z_SHAPE, L_SHAPE, J_SHAPE, T_SHAPE
} Shape;

typedef struct {
  // For each height we have one line of BOARD_WIDTH
  Shape array[BOARD_HEIGHT][BOARD_WIDTH];
  // Functions pointers
  void  (*init_board)(struct Board *board, Shape value);
  void  (*display)(struct Board *);
  Shape (*get)(struct Board *, uint8_t x, uint8_t y);
  int   (*put)(struct Board *, uint8_t x, uint8_t y, Shape value);
} Board;

void  init_board(Board *board, Shape value);
void  display(Board *board);
Shape get(Board *board, uint8_t x, uint8_t y);
int   put(Board *board, uint8_t x, uint8_t y, Shape value);

#endif //NAME_BOARD_H
