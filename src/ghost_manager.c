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
        {255, 182, 85, 255} // Orange
        // {255, 0,255,255},
    };

    for (int i = 0; i < GHOST_COUNT; i++) {
        ghosts[i].dx = 0;
        ghosts[i].dy = 0;
        ghosts[i].color = colors[i];
    }
}

void move_all_ghosts() {
    for (int i = 0; i < GHOST_COUNT; i++) {
        if ((int)ghosts[i].x % TILE_SIZE == 0 && (int)ghosts[i].y % TILE_SIZE == 0) {
            
            // All ghosts target Pacman's exact position
            int tx = (int)pacman.x;
            int ty = (int)pacman.y;

            get_smart_direction(i, tx, ty, &ghosts[i].dx, &ghosts[i].dy);
        }

        ghosts[i].x += ghosts[i].dx * GHOST_SPEED;
        ghosts[i].y += ghosts[i].dy * GHOST_SPEED;

        // Trail of pellets logic
        int current_column = ((int)ghosts[i].x + 16) / TILE_SIZE;
        int current_row = ((int)ghosts[i].y + 16) / TILE_SIZE;

        if (current_row >= 0 && current_row < current_rows &&
            current_column >= 0 && current_column < current_cols) {
            if (game_map[current_row][current_column] == 0) {
                game_map[current_row][current_column] = 2; 
            }
        }
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