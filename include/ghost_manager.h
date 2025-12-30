#ifndef GHOST_MANAGER_H
#define GHOST_MANAGER_H

#include <SDL2/SDL.h>
#include "entity.h"

#define GHOST_COUNT 2

extern Ghost ghosts[GHOST_COUNT];

void setup_all_ghosts();
void move_all_ghosts();
void draw_all_ghosts(SDL_Renderer* renderer);
bool check_pacman_collision();

#endif