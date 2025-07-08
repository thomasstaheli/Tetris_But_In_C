//
// Created by thoma on 06.07.2025.
//
#include "board.h"
#include <stdio.h>

int is_out_of_bound(uint8_t col, uint8_t line) {
  // x = [0, BOARD_WIDTH[ AND y = [0, BOARD_HEIGHT[
  // Out of Bound ? Yes, return 1 else return 0
  return !(col >= 0 && col < BOARD_WIDTH) || !(line >= 0 || line < BOARD_HEIGHT);
}

void init_board(Board *board, Shape value) {
  for(uint8_t line = 0; line < BOARD_HEIGHT; line++) {
    for(uint8_t col = 0; col < BOARD_WIDTH; col++) {
      // cast to (struct Board *) to avoid warnings
      board->put((struct Board *) board, col, line, value);
    }
  }
}

// Use for debug purposes
void display_board(Board *board) {
  Shape tmp;
  for(uint8_t line = 0; line < BOARD_HEIGHT; line++) {
    for(uint8_t col = 0; col < BOARD_WIDTH; col++) {
      // cast to (struct Board *) to avoid warnings
      tmp = board->get((struct Board *) board, col, line);
      printf("%d ", (int) tmp);
    }
    printf("\n");
  }
  printf("\n");
}

Shape get(Board *board, uint8_t col, uint8_t line) {
  // x = selected case in the line x (column), y = selected line
  if(is_out_of_bound(col, line)) {
    return ERROR;
  }

  return board->array[line][col];
}

int put(Board *board, uint8_t col, uint8_t line, Shape value) {
  // Error detection
  if(is_out_of_bound(col, line)) {
    return -1;
  }
  // No error detected
  board->array[line][col] = value;
  return 0;
}

