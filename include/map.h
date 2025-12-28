#ifndef map_h
#define map_h

#include"constants.h"
#include<stdbool.h>
#include<SDL2/SDL.h>

extern int game_map[map_rows][map_cols];

bool load_map(const char* filename);

void draw_map(SDL_Renderer* renderer);

extern int score;
#endif