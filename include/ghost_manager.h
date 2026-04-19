#ifndef GHOST_MANAGER_H
#define GHOST_MANAGER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define GHOST_COUNT 2
#define GHOST_SPEED 1

typedef struct {
    float x, y;
    int dx, dy;
    SDL_Color color;
} Ghost;

extern Ghost ghosts[GHOST_COUNT];

void setup_all_ghosts();
void move_all_ghosts();
void draw_all_ghosts(SDL_Renderer* renderer);
bool check_pacman_collision();

#endif