#include <stdio.h>
#include "display.h"
#include "tetris.h"

int main(int argc, char *argv[]) {

  // Avoid warnings
  (void)argc;
  (void)argv;

  SDL_display *display = (SDL_display*) malloc(sizeof(SDL_display));
  if(!display) {
    printf("Cannot allocate for SDL_Display struct.\n");
    return 0;
  }

  Tetris_game *game = (Tetris_game*) malloc(sizeof(Tetris_game));
  if(!game) {
    printf("Cannot allocate for Tetris_game struct.\n");
    goto err_game_malloc;
  }

  printf("Starting game ...\n");

  init_display(display);

  // ...

  remove_display(display);

  free(game);

err_game_malloc:
  free(display);

  return 0;
}
