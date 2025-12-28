#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    float x, y;       
    int dx, dy; 
    int next_dx, next_dy; 
} Player;

extern Player pacman;

void setup_player();
void move_player();
void draw_player(SDL_Renderer* renderer);

#endif