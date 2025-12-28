#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    float x, y;
    int dx, dy;
    int next_dx, next_dy;
} Player;

typedef struct {
    float x, y;
    int dx, dy;
    SDL_Color color;
} Ghost;

extern Player pacman;
extern int score;

void setup_player();
void move_player();
void draw_player(SDL_Renderer* renderer);

#endif