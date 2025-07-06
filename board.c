//
// Created by thoma on 06.07.2025.
//
#include "board.h"
#include <stdio.h>

int isOutOfBound(uint8_t x, uint8_t y) {
  // x = [0, BOARD_WIDTH[ AND y = [0, BOARD_HEIGHT[
  // OutOfBound ? Yes, return -1 else return 0
  return x < 0 || x >= BOARD_HEIGHT || y < 0 || y >= BOARD_WIDTH ? -1 : 0;
}

void init_board(Board *board, Shape value) {
  for(uint8_t line = 0; line < BOARD_HEIGHT; line++) {
    for(uint8_t col = 0; col < BOARD_WIDTH; col++) {
      // cast to (struct Board *) to avoid warnings
      board->put((struct Board *) board, line, col, value);
    }
  }

  // TODO : REMOVE -> TO TEST COLOR
  int line = BOARD_HEIGHT - 1;
  board->put((struct Board *) board, line, 0, SQUARE);
  board->put((struct Board *) board, line, 1, RECTANGLE);
  board->put((struct Board *) board, line, 2, S_SHAPE);
  board->put((struct Board *) board, line, 3, Z_SHAPE);
  board->put((struct Board *) board, line, 4, T_SHAPE);
  board->put((struct Board *) board, line, 5, J_SHAPE);
  board->put((struct Board *) board, line, 6, L_SHAPE);
}

void display_board(Board *board) {
  Shape tmp;
  for(uint8_t line = 0; line < BOARD_HEIGHT; line++) {
    for(uint8_t col = 0; col < BOARD_WIDTH; col++) {
      // cast to (struct Board *) to avoid warnings
      tmp = board->get((struct Board *) board, line, col);
      printf("%d ", (int) tmp);
    }
    printf("\n");
  }
}

Shape get(Board *board, uint8_t x, uint8_t y) {
  // x = selected line, y = selected case in the line x (column)
  if(isOutOfBound(x, y)) {
    return ERROR;
  }

  return board->array[x][y];
}

int put(Board *board, uint8_t x, uint8_t y, Shape value) {
  // Error detection
  if(isOutOfBound(x, y)) {
    return -1;
  }
  // No error detected
  board->array[x][y] = value;
  return 0;
}

