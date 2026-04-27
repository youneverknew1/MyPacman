#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define PACMAN_SPEED 2.0f
typedef struct {
    float x, y;
    int dx, dy;
    int next_dx, next_dy;
} Player;

extern Player pacman;

bool check_wall(int x, int y); 
void move_player();
void draw_player(SDL_Renderer* renderer);

#endif