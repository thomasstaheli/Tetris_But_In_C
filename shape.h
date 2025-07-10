//
// Created by thoma on 07.07.2025.
//

#ifndef NAME_SHAPE_H
#define NAME_SHAPE_H

#include <stdint.h>

#define PIXEL_PER_SHAPES 4
#define POSITION_PER_SHAPES 4
#define NUMBER_OF_SHAPES 7

typedef enum {
    EMPTY, SQUARE, RECTANGLE, S_SHAPE, Z_SHAPE, L_SHAPE, J_SHAPE, T_SHAPE, ERROR
} Shape;

// Coord X and Y are integer to avoid underflow with unsigned type.
// It makes condition test easier
typedef struct {
    int x, y;
} Coord;

// Each Shapes got 4 pixels
// Coord[0] = Shapes origin
typedef struct {
    Coord coord[PIXEL_PER_SHAPES];
} Shape_Coord;

// Hardcoding Shapes Positions
static const Shape_Coord shapes_coord[NUMBER_OF_SHAPES + 1][POSITION_PER_SHAPES] ={
        {{0,0}}, // EMPTY
          { // SQUARE
            {0, 0, 1, 0, 1, 1, 0, 1},
            {0, 0, 1, 0, 1, 1, 0, 1},
            {0, 0, 1, 0, 1, 1, 0, 1},
            {0, 0, 1, 0, 1, 1, 0, 1},
          }, // SQUARE
          { // RECTANGLE
            {0, 0, 1, 0, -1, 0, -2, 0},
            {0, 0, 0, -1, 0, 1, 0, 2},
            {0, 0, 1, 0, -1, 0, -2, 0},
            {0, 0, 0, -1, 0, 1, 0, 2}
          }, // RECTANGLE
          { // S_SHAPE
            {0, 0, 1, 0, 0, 1, -1, 1},
            {0, 0, -1, -1, -1, 0, 0, 1},
            {0, 0, 1, 0, 0, 1, -1, 1},
            {0, 0, -1, -1, -1, 0, 0, 1}
          }, // S_SHAPE
          { // Z_SHAPE
            {0, 0, -1, 0, 0, 1, 1, 1},
            {0, 0, 0, 1, 1, 0, 1, -1},
            {0, 0, -1, 0, 0, 1, 1, 1},
            {0, 0, 0, 1, 1, 0, 1, -1}
          }, // Z_SHAPE
          { // L_SHAPE
            {0, 0, -1, 0, -1, 1, 1, 0},
            {0, 0, 0, -1, -1, -1, 0, 1},
            {0, 0, -1, 0, 1, 0, 1, -1},
            {0, 0, 0, -1, 0, 1, 1, 1}
          }, // L_SHAPE
          { // J_SHAPE
            {0, 0, -1, 0, 1, 1, 1, 0},
            {0, 0, 0, -1, -1, 1, 0, 1},
            {0, 0, -1, 0, 1, 0, -1, -1},
            {0, 0, 0, -1, 0, 1, 1, -1}
          }, // J_SHAPE
          { // T_SHAPE
            {0, 0, -1, 0, 1, 0, 0, 1},
            {0, 0, -1, 0, 0, 1, 0, -1},
            {0, 0, -1, 0, 1, 0, 0, -1},
            {0, 0, 1, 0, 0, 1, 0, -1}
          } // T_SHAPE
};


#endif //NAME_SHAPE_H
