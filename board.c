/**
 * @file    board.h
 * @author  Thomas Stäheli
 * @date    06 July 2025
 * @brief   Structure with function pointer to use a 2D Table (Board)
 */

#include "board.h"
#include <stdio.h>

void init_board_features(Board *board) {
  // Set up the function pointer
  board->init = (void (*)(struct Board *, Shape)) init;
  board->show = (void (*)(struct Board *)) show;
  board->put  = (int (*)(struct Board *, uint8_t, uint8_t, Shape)) put;
  board->get  = (Shape (*)(struct Board *, uint8_t, uint8_t)) get;
}

int is_out_of_bound(int col, int line) {
  // x = [0, BOARD_WIDTH[ AND y = [-inf, BOARD_HEIGHT[
  // Out of Bound ? Yes, return 1 else return 0
  return !(col >= 0 && col < BOARD_WIDTH) || line >= BOARD_HEIGHT;
}

void init(Board *board, Shape value) {
  for(uint8_t line = 0; line < BOARD_HEIGHT; line++) {
    for(uint8_t col = 0; col < BOARD_WIDTH; col++) {
      // cast to (struct Board *) to avoid warnings
      board->put((struct Board *) board, col, line, value);
    }
  }
}

// Use for debug purposes
void show(Board *board) {
  for(uint8_t line = 0; line < BOARD_HEIGHT; line++) {
    for(uint8_t col = 0; col < BOARD_WIDTH; col++) {
      // cast to (struct Board *) to avoid warnings
      printf("%d ", (int) board->get((struct Board *) board, col, line));
    }
    printf("\n");
  }
  printf("\n");
}

Shape get(Board *board, uint8_t col, uint8_t line) {
  // x = selected case in the line x (column), y = selected line
  if(is_out_of_bound(col, line)) {
    return -1;
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

