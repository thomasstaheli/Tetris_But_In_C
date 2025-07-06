//
// Created by thoma on 06.07.2025.
//
#include "board.h"

int isOutOfBound(uint8_t x, uint8_t y) {
  // x = [0, BOARD_WIDTH[ AND y = [0, BOARD_HEIGHT[
  // OutOfBound ? Yes, return -1 else return 0
  return x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT ? -1 : 0;
}

void init_board(Board *board, Shape value) {
  for(uint8_t line = 0; line < BOARD_HEIGHT; line++) {
    for(uint8_t col = 0; col < BOARD_WIDTH; col++) {
      // cast to (struct Board *) to avoid warnings
      board->put((struct Board *) board, line, col, value);
    }
  }
}

void display(Board *board) {
  for(uint8_t line = 0; line < BOARD_HEIGHT; line++) {
    for(uint8_t col = 0; col < BOARD_WIDTH; col++) {
      // cast to (struct Board *) to avoid warnings
      board->get((struct Board *) board, line, col);
    }
  }
}

Shape get(Board *board, uint8_t x, uint8_t y) {
  // x = selected line, y = selected case in the line x (column)
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

