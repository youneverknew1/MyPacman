#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <stdbool.h>

extern int** game_map; 

bool load_map(const char* filename);
void draw_map(SDL_Renderer* renderer);

#endif