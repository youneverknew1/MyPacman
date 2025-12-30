#include "../include/ghost_manager.h"
#include "../include/ghost_ai.h"
#include "../include/map.h"
#include <stdlib.h>
#include "../include/constants.h"

Ghost ghosts[GHOST_COUNT];

void setup_all_ghosts() {
    int pos[GHOST_COUNT][2]={
        {1,1}, 
        {17,18}
    };
    SDL_Color colors[GHOST_COUNT] = {
        {255, 0, 0, 255},   //red
        {255, 182, 85, 255} //orange
    };

    for (int i = 0; i < GHOST_COUNT; i++) {
        ghosts[i].x = (float)pos[i][0] * 32;
        ghosts[i].y = (float)pos[i][1] * 32;
        ghosts[i].dx = 0;
        ghosts[i].dy = 0;
        ghosts[i].color = colors[i];
    }
}

void move_all_ghosts() {
    for (int i = 0; i < GHOST_COUNT; i++) {
        if ((int)ghosts[i].x % 32 == 0 && (int)ghosts[i].y % 32 == 0) {
            get_smart_direction(i, &ghosts[i].dx, &ghosts[i].dy);
        }
        ghosts[i].x += ghosts[i].dx*2;
        ghosts[i].y += ghosts[i].dy*2;

        int current_column = ((int)ghosts[i].x + 16) / 32;
        int current_row = ((int)ghosts[i].y + 16) / 32;

        if (current_row >= 0 && current_row < map_rows &&
             current_column >= 0 && current_column < map_cols) {
            if (game_map[current_row][current_column] == 0) {
                game_map[current_row][current_column] = 2;
            }
        }
    }
}

void draw_all_ghosts(SDL_Renderer* renderer){
    for (int i = 0; i < GHOST_COUNT; i++) {
        SDL_Rect r = {(int)ghosts[i].x, (int)ghosts[i].y, 32, 32};
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