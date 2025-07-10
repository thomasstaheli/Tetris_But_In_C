/**
 * @file    tetris.h
 * @author  Thomas Stäheli
 * @date    06 July 2025
 * @brief   File that contain tetris logic
 */

#ifndef NAME_TETRIS_H
#define NAME_TETRIS_H

#include "board.h"
#include <stdbool.h>

// Game structure
typedef struct {
    Board board;      // 2D Table
    bool  running;    // True = game running / False = User stop the game
    uint32_t score;   // User score
} Tetris_game;

void spawn_new_shape(Shape shape_to_place, uint8_t shape_position, Shape_Coord *new_shape_coord);
void compute_pixels_shape(Shape shape_to_place, uint8_t shape_position, Shape_Coord *shape_coord);
void affect_shape_to_board(Shape shape_to_place, Shape_Coord shape_coord, Board *board);
void clear_shape_from_board(Shape_Coord shape_coord, Board *board);
int  is_shape_out_of_bound(Shape_Coord *shape_coord, int x_increment, int y_increment);
int  can_shape_go_down(Shape_Coord shape_coord, Board board);
void update_shapes_until_in_bound(Shape shape_to_place, uint8_t shape_position, Shape_Coord *shape_coord);
void check_for_full_lines(Board *board);

/* TODO : What's missing ?
 * - Lose condition
 * - KEY RIGHT / LEFT -> colliding with other shapes -> should block
 * - KEY UP -> Changing position should block too if another shape blocks
 * - Let a bit of time before blocking the shapes, so the user can move a bit his shape to do special moves
 */

#endif //NAME_TETRIS_H
