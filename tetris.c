//
// Created by thoma on 05.07.2025.
//
#include <stdint.h>
#include "display.h"
#include "tetris.h"
#include "shape.h"

void compute_pixels_shape(Shape shape_to_place, uint8_t shape_position, Shape_Coord *shape_coord) {

  for(int i = 1; i < PIXEL_PER_SHAPES; i++) {
    shape_coord->coord[i].x = shape_coord->coord[0].x
                              + shapes_coord[shape_to_place][shape_position].coord[i].x;
    shape_coord->coord[i].y = shape_coord->coord[0].y
                              + shapes_coord[shape_to_place][shape_position].coord[i].y;
  }

}

void spawn_new_shape(Shape shape_to_place, uint8_t shape_position, Shape_Coord *new_shape_coord) {
  // Set up the spawning place of the shape
  // Piece origin -> center to the board
  new_shape_coord->coord[0].x = BOARD_WIDTH / 2 - 1;
  new_shape_coord->coord[0].y = 0;
  // Generate the others shape's pixels depending on the origin
  compute_pixels_shape(shape_to_place, shape_position, new_shape_coord);

}

void affect_shape_to_board(Shape shape_type, Shape_Coord shape_coord, Board *board) {
  for(uint8_t i = 0; i < PIXEL_PER_SHAPES; ++i) {
    board->put((struct Board *) board, shape_coord.coord[i].x, shape_coord.coord[i].y, shape_type);
  }
}

int can_shape_go_down(Shape_Coord new_shape_coord, Board board) {
  return 1;
}

