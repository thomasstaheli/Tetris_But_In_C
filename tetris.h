//
// Created by thoma on 05.07.2025.
//

#ifndef NAME_TETRIS_H
#define NAME_TETRIS_H

#include "board.h"
#include <stdbool.h>

typedef struct {
    Board board;
    bool  running;
} Tetris_game;

void spawn_new_shape(Shape shape_to_place, uint8_t shape_position, Shape_Coord *new_shape_coord);
void compute_pixels_shape(Shape shape_to_place, uint8_t shape_position, Shape_Coord *shape_coord);
void affect_shape_to_board(Shape shape_to_place, Shape_Coord shape_coord, Board *board);
void clear_shape_from_board(Shape_Coord shape_coord, Board *board);
int  shape_out_of_bound(Shape_Coord shape_coord, int x_increment, int y_increment);
int  can_shape_go_down(Shape_Coord shape_coord, Board board);


#endif //NAME_TETRIS_H
