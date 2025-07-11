/**
 * @file    display.c
 * @author  Thomas Stäheli
 * @date    06 July 2025
 * @brief   File that contain the game display (using SDL2)
 */

#include <stdlib.h>
#include <time.h>
#include "display.h"
#include "settings.h"

// Init the display using SDL2 library
void init_display(SDL_display *display) {

  SDL_Init(SDL_INIT_VIDEO);
  // Create the window
  display->window = SDL_CreateWindow(
          "Tetris in C",
          SDL_WINDOWPOS_CENTERED,
          SDL_WINDOWPOS_CENTERED,
          DISPLAY_WIDTH, DISPLAY_HEIGHT,
          SDL_WINDOW_SHOWN
  );
  // Create the renderer
  display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);

  Color background_color = {0, 0, 0, 255};
  // Set up the background
  SDL_SetRenderDrawColor(display->renderer, background_color.r, background_color.g, background_color.b, background_color.a);
  SDL_RenderClear(display->renderer);
  SDL_RenderPresent(display->renderer);
}

// Call this method before exiting the main program
void remove_display(SDL_display *display) {
  // Destroy / Free dynamic structures
  SDL_DestroyRenderer(display->renderer);
  SDL_DestroyWindow(display->window);
  SDL_Quit();
}

void clear_display(SDL_display *display) {
  // Background color as black
  SDL_SetRenderDrawColor(display->renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
  SDL_RenderClear(display->renderer);
}

// Draw the grid (white lines)
void draw_grid_game(SDL_display *display) {

  // Compute the menu bar place depending on the display size
  uint16_t menu_line_pos = DISPLAY_WIDTH - MENU_BAR_SIZE;
  // Compute the spacing between all the columns
  uint8_t spacing_width = menu_line_pos / BOARD_WIDTH;
  // Compute the spacing between all the lines
  uint8_t spacing_height = DISPLAY_HEIGHT / BOARD_HEIGHT;

  // Set Color for all the Lines
  SDL_SetRenderDrawColor(display->renderer, WHITE.r, WHITE.g, WHITE.b, WHITE.a);

  // Horizontal lines
  for(uint8_t line = 1; line < BOARD_HEIGHT; line++) {
    SDL_RenderDrawLine(display->renderer, 0, spacing_height * line,
                       menu_line_pos, spacing_height * line);
  }

  // Verticals lines
  for(uint8_t line = 1; line <= BOARD_WIDTH; line++) {
    SDL_RenderDrawLine(display->renderer, spacing_width * line, 0,
                       spacing_width * line, DISPLAY_HEIGHT);
  }

}

// Draw each pixel from the board
void draw_board_game(SDL_display *display) {

  // Compute the menu bar place depending on the display size
  uint16_t menu_line_pos = DISPLAY_WIDTH - MENU_BAR_SIZE;
  // Compute the spacing between all the columns
  uint8_t scare_width = menu_line_pos / BOARD_WIDTH;
  // Compute the spacing between all the lines
  uint8_t scare_height = DISPLAY_HEIGHT / BOARD_HEIGHT;
  // Prepare rectangle to fill the board
  SDL_Rect rect = {.w = scare_width, .h = scare_height}; // x, y, width, height
  Color color;

  for(uint8_t line = 0; line < BOARD_HEIGHT; line++) {
    rect.y = scare_height * line;
    for(uint8_t col = 0; col < BOARD_WIDTH; col++) {
      rect.x = scare_width * col;
      color = shapes_color[display->game->board.get((struct Board *) &display->game->board, col, line)];
      SDL_SetRenderDrawColor(display->renderer, color.r, color.g, color.b, color.a);
      SDL_RenderFillRect(display->renderer, &rect);
    }
  }

}

// Main function of the program, if you call it, it will start the game
void play_tetris(SDL_display *display) {

  init_board_features(&display->game->board);
  // Init the game board
  display->game->running = true;
  display->game->board.init((struct Board *) &display->game->board, EMPTY);

  // Count down before going down
  // TODO : PUT THIS VARIABLE IN THE GAME STRUCTURE
  uint16_t count_down = 0;
  uint16_t count_down_limit = DEFAULT_COUNT_DOWN_LIMIT;
  // Default position of the shape
  // TODO : PUT THIS VARIABLE IN THE GAME STRUCTURE
  uint8_t shape_position = 0;
  // Set up random (fixed time)
  srand(time(NULL));
  // TODO : PUT THIS VARIABLE IN THE GAME STRUCTURE
  // Select a shape between 1 and 7 (0 = EMPTY)
  Shape shape_to_place = rand() % NUMBER_OF_SHAPES + 1;
  Shape_Coord new_shape_coord;
  Shape_Coord old_shape_coord;
  Shape_Coord tmp_shape_coord;
  // Generate a new random shape and compute the pixel from the origin
  spawn_new_shape(shape_to_place, shape_position, &new_shape_coord);
  // Set up the old shape (useful to clear)
  old_shape_coord = new_shape_coord;
  // Put the shape in the game board
  affect_shape_to_board(shape_to_place, new_shape_coord, &display->game->board);

  // Main loop
  while (display->game->running) {
    SDL_Event event;

    // Events management
    while (SDL_PollEvent(&event)) {
      switch (event.type) {

        case SDL_QUIT:
          // handling of close button
          display->game->running = false;
          break;

        case SDL_KEYDOWN:
          // keyboard API for key pressed
          switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
              shape_position = (shape_position + 1) % POSITION_PER_SHAPES;
              // pre-computing the shape to know if this position is out of bound
              compute_pixels_shape(shape_to_place, shape_position, &new_shape_coord);
              // Check if shapes is out of bound after changing position
              update_shapes_until_in_bound(shape_to_place, shape_position, &new_shape_coord);
              break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
              /* TODO : THERE IS A CHANCE THAT THE USER PRESS DOWN KEY AND THE COUNTDOWN APPEND AT THE SAME TIME,
                        IT WILL GO THROW A SHAPE OR THE BOARD !
              */
              tmp_shape_coord = new_shape_coord;
              if(!is_shape_out_of_bound(&tmp_shape_coord, 0, 1))  {
                new_shape_coord = tmp_shape_coord;
              }
              break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
              // TODO : CHECK FOR OTHERS SHAPES, for now I can go throw shapes (colliding pixels)
              tmp_shape_coord = new_shape_coord;
              if(!is_shape_out_of_bound(&tmp_shape_coord, -1, 0)) {
                new_shape_coord = tmp_shape_coord;
              }
              break;

            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
              // TODO : CHECK FOR OTHERS SHAPES, for now I can go throw shapes (colliding pixels)
              tmp_shape_coord = new_shape_coord;
              if(!is_shape_out_of_bound(&tmp_shape_coord, 1, 0)) {
                new_shape_coord = tmp_shape_coord;
              }
              break;
            default:
              break;
          }
      }
    }
    // Check if the shape collides with another shape or reach the end on the board
    if(!can_shape_go_down(old_shape_coord, display->game->board)) {
      // Generate a new shape
      shape_to_place = rand() % NUMBER_OF_SHAPES + 1;
      shape_position = 0;
      spawn_new_shape(shape_to_place, shape_position, &new_shape_coord);
      // Erase lines that are full of shape's pixels
      check_for_full_lines(&display->game->board);
    } else {
      // Clear the old shape
      clear_shape_from_board(old_shape_coord, &display->game->board);
      if(count_down != 0 && count_down % count_down_limit == 0) {
        count_down = 0;
        // Automatically going down after countdown
        new_shape_coord.coord[0].y += 1;
      } else {
        count_down += 1;
      }
      // Compute the pixel from the new shape's origin
      compute_pixels_shape(shape_to_place, shape_position, &new_shape_coord);
    }
    // Put the shape in the board before drawing it
    old_shape_coord = new_shape_coord;
    affect_shape_to_board(shape_to_place, new_shape_coord, &display->game->board);

    // Clear and draw the game
    clear_display(display);
    draw_board_game(display);
    draw_grid_game(display);

    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(display->renderer);

    // calculates to 60 fps
    // 1 s = 60 imgs / 16.6667 ms
    SDL_Delay(1000 / FPS);
  }

}