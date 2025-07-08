//
// Created by thoma on 05.07.2025.
//
#include <stdint.h>
#include "display.h"
#include "tetris.h"
#include "shape.h"

void compute_pixels_shape(Shape shape_to_place, uint8_t shape_position, Shape_Coord *shape_coord) {

  for(int i = 1; i < PIXEL_PER_SHAPES; ++i) {
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

void clear_shape_from_board(Shape_Coord shape_coord, Board *board) {
  for(uint8_t i = 0; i < PIXEL_PER_SHAPES; ++i) {
    board->put((struct Board *) board, shape_coord.coord[i].x, shape_coord.coord[i].y, EMPTY);
  }
}

uint8_t get_colliding_pixels(Shape_Coord shape_coord, Shape_Coord *colliding_pixels) {
  // Get the deeper pixel (deeper on Y axe) for each X axe.
  uint8_t nb_colliding = 0;
  uint8_t already_in;
  // Takes only
  for(uint8_t i = 0; i < PIXEL_PER_SHAPES; ++i) {
    already_in = 0;
    for(uint8_t j = 0; j < nb_colliding; ++j) {
      if(shape_coord.coord[i].x == colliding_pixels->coord[j].x &&
         shape_coord.coord[i].y <= colliding_pixels->coord[j].y) {
        // A deeper pixel already exist in this X axe
        already_in = 1;
      } else if(shape_coord.coord[i].x == colliding_pixels->coord[j].x &&
                shape_coord.coord[i].y > colliding_pixels->coord[j].y) {
        // Find a pixel deeper then the previous one
        already_in = 1;
        colliding_pixels->coord[j] = shape_coord.coord[i];
      }
    }

    if(!already_in) {
      colliding_pixels->coord[nb_colliding] = shape_coord.coord[i];
      ++nb_colliding;
    }
  }

  return nb_colliding;
}

int can_shape_go_down(Shape_Coord shape_coord, Board board) {
  int coord_x;
  int coord_y;
  Shape_Coord colliding_pixels;
  uint8_t nb_colliding = get_colliding_pixels(shape_coord, &colliding_pixels);
  // For each pixel, check
  for(uint8_t i = 0; i < nb_colliding; ++i) {
    coord_x = colliding_pixels.coord[i].x;
    coord_y = colliding_pixels.coord[i].y;

    if(coord_y >= BOARD_HEIGHT - 1 || board.get((struct Board *) &board, coord_x, coord_y + 1)) {
      return 0;
    }
  }

  return 1;
}

int shape_out_of_bound(Shape_Coord shape_coord, int x_increment, int y_increment) {
  // For each pixel, check if it will be out of bound
  for(uint8_t i = 0; i < PIXEL_PER_SHAPES; ++i) {
    shape_coord.coord[i].x += x_increment;
    shape_coord.coord[i].y += y_increment;

    if(is_out_of_bound(shape_coord.coord[i].x, shape_coord.coord[i].y)) {
      return 1;
    }
  }

  return 0;
}




