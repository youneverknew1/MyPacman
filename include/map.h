#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <stdbool.h>

bool check_wall(int x, int y);
bool load_map(const char* filename);

void draw_map(SDL_Renderer* renderer);

extern int game_map[20][19]; 

#endif