#ifndef entity_h
#define entity_h
#include<SDL2/SDL.h>
#include "constants.h"

typedef struct{
    float x;
    float y;
    int dx;
    int dy;
} Player;

extern Player pacman;
void setup_player();
void move_player();
void draw_player(SDL_Renderer* renderer);
#endif