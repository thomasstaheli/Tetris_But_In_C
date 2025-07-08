//
// Created by thoma on 06.07.2025.
//

#ifndef NAME_BOARD_H
#define NAME_BOARD_H

#include "settings.h"
#include "shape.h"
#include <stdint.h>

typedef struct {
  // For each height we have one line of BOARD_WIDTH
  Shape array[BOARD_HEIGHT][BOARD_WIDTH];
  // Functions pointers
  void  (*init_board)(struct Board *board, Shape value);
  void  (*display_board)(struct Board *);
  Shape (*get)(struct Board *, uint8_t col, uint8_t line);
  int   (*put)(struct Board *, uint8_t col, uint8_t line, Shape value);
} Board;

void  init_board(Board *board, Shape value);
void  display_board(Board *board);
Shape get(Board *board, uint8_t col, uint8_t line);
int   put(Board *board, uint8_t col, uint8_t line, Shape value);
int   is_out_of_bound(uint8_t col, uint8_t line);

#endif //NAME_BOARD_H
