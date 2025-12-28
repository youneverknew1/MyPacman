#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// This "prototype" tells other files that check_wall exists
bool check_wall(int x, int y);

// Other map functions
bool load_map(const char* filename);
void draw_map(SDL_Renderer* renderer);

// Global map data
extern int game_map[20][19]; 

#endif