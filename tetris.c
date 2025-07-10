/**
 * @file    tetris.c
 * @author  Thomas Stäheli
 * @date    06 July 2025
 * @brief   File that contain tetris logic
 */

#include <stdint.h>
#include "tetris.h"
#include "shape.h"

// Compute the others pixel of the Shape depending on the Shape's origin and position
void compute_pixels_shape(Shape shape_to_place, uint8_t shape_position, Shape_Coord *shape_coord) {
  // Start from the second pixel, because i = 0 is the shape's origin
  for(int i = 1; i < PIXEL_PER_SHAPES; ++i) {
    shape_coord->coord[i].x = shape_coord->coord[0].x
                              + shapes_coord[shape_to_place][shape_position].coord[i].x;
    shape_coord->coord[i].y = shape_coord->coord[0].y
                              + shapes_coord[shape_to_place][shape_position].coord[i].y;
  }

}

// Set up the spawning place of the shape
void spawn_new_shape(Shape shape_to_place, uint8_t shape_position, Shape_Coord *new_shape_coord) {
  // Piece origin -> center to the board
  new_shape_coord->coord[0].x = BOARD_WIDTH / 2 - 1;
  new_shape_coord->coord[0].y = 0;
  // Generate the others shape's pixels depending on the origin
  compute_pixels_shape(shape_to_place, shape_position, new_shape_coord);

}

// Add the current shape to the board
void affect_shape_to_board(Shape shape_type, Shape_Coord shape_coord, Board *board) {
  for(uint8_t i = 0; i < PIXEL_PER_SHAPES; ++i) {
    board->put((struct Board *) board, shape_coord.coord[i].x, shape_coord.coord[i].y, shape_type);
  }
}

// Same function as affect_shape_to_board, but it looks easier to read the code
void clear_shape_from_board(Shape_Coord shape_coord, Board *board) {
  for(uint8_t i = 0; i < PIXEL_PER_SHAPES; ++i) {
    board->put((struct Board *) board, shape_coord.coord[i].x, shape_coord.coord[i].y, EMPTY);
  }
}

// Get all the colliding pixels from the shape on the Y axe
uint8_t get_colliding_pixels(Shape_Coord shape_coord, Shape_Coord *colliding_pixels) {
  // Get the deeper pixel (deeper on Y axe) for each X axe.
  uint8_t nb_colliding = 0;
  uint8_t already_in;
  // For all the Pixels
  for(uint8_t i = 0; i < PIXEL_PER_SHAPES; ++i) {
    already_in = 0;
    // We check in the already pixel colliding, if the X coordinate already exist
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
    // Add a pixel in the colliding table, if a pixel in this X coordinate do not exist
    if(!already_in) {
      colliding_pixels->coord[nb_colliding] = shape_coord.coord[i];
      ++nb_colliding;
    }
  }

  return nb_colliding;
}

// Check if the shape is blocked by another piece
int can_shape_go_down(Shape_Coord shape_coord, Board board) {
  // Check if the shapes can go down one more time
  int coord_x;
  int coord_y;
  // Will contain all the colliding pixels
  Shape_Coord colliding_pixels;
  uint8_t nb_colliding = get_colliding_pixels(shape_coord, &colliding_pixels);
  // For each pixel, check if one block the shape to go down
  for(uint8_t i = 0; i < nb_colliding; ++i) {
    coord_x = colliding_pixels.coord[i].x;
    coord_y = colliding_pixels.coord[i].y;
    // Check if the shape reach the bottom of the board or if there's a shape under it.
    if(coord_y >= BOARD_HEIGHT - 1 || board.get((struct Board *) &board, coord_x, coord_y + 1)) {
      return 0;
    }
  }

  return 1;
}

// Check for each pixel of the shape, if a pixel is out of bound.
int is_shape_out_of_bound(Shape_Coord *shape_coord, int x_increment, int y_increment) {
  // For each pixel, check if it will be out of bound
  for(uint8_t i = 0; i < PIXEL_PER_SHAPES; ++i) {
    shape_coord->coord[i].x += x_increment;
    shape_coord->coord[i].y += y_increment;
    // Test for each pixel
    if(is_out_of_bound(shape_coord->coord[i].x, shape_coord->coord[i].y)) {
      return 1;
    }
  }

  return 0;
}

// Move the shape's origin until each pixel is in bound
void update_shapes_until_in_bound(Shape shape_to_place, uint8_t shape_position, Shape_Coord *shape_coord) {
  // While shape is not in bound
  int incr_decr = 0;

  while(is_shape_out_of_bound(shape_coord, incr_decr, 0)) {
    if(shape_coord->coord[0].x < BOARD_WIDTH / 2) {
      // Shape is colliding with left side
      incr_decr = 1;
    } else {
      // Shape is colliding with right side
      incr_decr = -1;
    }
  }
}

// This function do not really erase a line, but each lines go down by one unit on the Y axe
// start_line contain the line to erase
void erase_full_line(Board *board, uint8_t erase_line_idx) {
  // From the start index, copy and paste the above line
  for(uint8_t line = erase_line_idx; line > 0; --line) {
    for(uint8_t col = 0; col < BOARD_WIDTH; ++col) {
      // Take the value above
      Shape tmp = board->get((struct Board *) board, col, line - 1);
      // Paste the above value
      board->put((struct Board *) board, col, line, tmp);
    }
  }
  // The line on the top will be EMPTY
  for(uint8_t col = 0; col < BOARD_WIDTH; ++col) {
    board->put((struct Board *) board, col, 0, EMPTY);
  }
}

// Check if a line has no EMPTY pixel
void check_for_full_lines(Board *board) {
  // For all pixel in the board
  for(uint8_t line = 0; line < BOARD_HEIGHT; ++line) {
    for(uint8_t col = 0; col < BOARD_WIDTH; ++col) {
      // Check EMPTY pixel
      if(board->get((struct Board *) board, col, line) == EMPTY) {
        break;
      } // If it is the last pixel which is empty
      else if(col == BOARD_WIDTH - 1) {
        // Update the board
        erase_full_line(board, line);
      }
    }
  }
}

