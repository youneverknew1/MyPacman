#include "../include/ghost_manager.h"
#include "../include/ghost_ai.h"
#include "../include/map.h"
#include "../include/entity.h"
#include "../include/constants.h"
#include <stdlib.h>

Ghost ghosts[GHOST_COUNT];

void setup_all_ghosts() {
    SDL_Color colors[GHOST_COUNT] = {
        {255, 0, 0, 255},   // Red 
        {255, 182, 85, 255},// Orange
        {255, 0,255,255},
        {0,255,0,255}
    };

    for (int i = 0; i < GHOST_COUNT; i++) {
        ghosts[i].dx = 0;
        ghosts[i].dy = 0;
        ghosts[i].color = colors[i];
    }
}

void move_all_ghosts() {
    for (int i = 0; i < GHOST_COUNT; i++) {
        // Only allow a turn if the ghost is perfectly centered on a tile
        if ((int)ghosts[i].x % TILE_SIZE == 0 && (int)ghosts[i].y % TILE_SIZE == 0) {
            int next_dx, next_dy;
            get_smart_direction(i, (int)pacman.x, (int)pacman.y, &next_dx, &next_dy);

            // Look ahead: where would the ghost be?
            int target_col = ((int)ghosts[i].x / TILE_SIZE) + next_dx;
            int target_row = ((int)ghosts[i].y / TILE_SIZE) + next_dy;

            // Only change direction if the path is clear (not a wall '1')
            if (game_map[target_row][target_col] != 1) {
                ghosts[i].dx = next_dx;
                ghosts[i].dy = next_dy;
            }
        }
        
        ghosts[i].x += ghosts[i].dx * GHOST_SPEED;
        ghosts[i].y += ghosts[i].dy * GHOST_SPEED;
    }
}

void draw_all_ghosts(SDL_Renderer* renderer){
    for (int i = 0; i < GHOST_COUNT; i++) {
        SDL_Rect r = {(int)ghosts[i].x, (int)ghosts[i].y, TILE_SIZE, TILE_SIZE};
        SDL_SetRenderDrawColor(renderer, ghosts[i].color.r, ghosts[i].color.g, ghosts[i].color.b, 255);
        SDL_RenderFillRect(renderer, &r);
    }
}

bool check_pacman_collision() {
    for (int i = 0; i < GHOST_COUNT; i++) {
        if (abs((int)pacman.x - (int)ghosts[i].x) < 20 && 
            abs((int)pacman.y - (int)ghosts[i].y) < 20){
            return true;
        }
    }
    return false;
}