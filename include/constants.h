#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define TILE_SIZE 32

extern int current_rows;
extern int current_cols;

#define SCREEN_WIDTH (current_cols * TILE_SIZE)
#define SCREEN_HEIGHT (current_rows * TILE_SIZE)

typedef enum { STATE_MENU, STATE_PLAY, STATE_OVER } GameState;
extern GameState state;
extern int score;

#endif