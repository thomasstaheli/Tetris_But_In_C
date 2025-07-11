/**
 * @file    board.h
 * @author  Thomas Stäheli
 * @date    06 July 2025
 * @brief   Structure with function pointer to use a 2D Table (Board)
 */

#ifndef NAME_BOARD_H
#define NAME_BOARD_H

#include "settings.h"
#include "shape.h"
#include <stdint.h>

typedef struct {
  // For each height we have one line of BOARD_WIDTH
  Shape array[BOARD_HEIGHT][BOARD_WIDTH];
  // Functions pointers
  void  (*init)(struct Board *board, Shape value);
  void  (*show)(struct Board *);
  Shape (*get)(struct Board *, uint8_t col, uint8_t line);
  int   (*put)(struct Board *, uint8_t col, uint8_t line, Shape value);
} Board;

void  init_board_features(Board *board);
void  init(Board *board, Shape value);
void  show(Board *board);
Shape get(Board *board, uint8_t col, uint8_t line);
int   put(Board *board, uint8_t col, uint8_t line, Shape value);
int   is_out_of_bound(int col, int line);

#endif //NAME_BOARD_H
