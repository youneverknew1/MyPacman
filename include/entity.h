#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "constants.h"

typedef struct {
    float x, y;       
    int dx, dy; 
    int next_dx, next_dy; 
} Player;

typedef struct{
    float x,y;
    int dx,dy;
    SDL_Color color;
} Ghost;

extern Player pacman;
extern Ghost blinky;

void setup_player();
void move_player();
void draw_player(SDL_Renderer* renderer);

void setup_ghost();
void move_ghost();
void draw_ghost(SDL_Renderer* renderer);

bool check_wall(int x,int y);

#endif