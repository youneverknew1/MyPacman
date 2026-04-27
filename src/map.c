#include "../include/map.h"
#include "../include/constants.h"
#include <stdio.h>
#include <stdlib.h>

int** game_map = NULL;
int current_rows = 0;
int current_cols = 0;
int score = 0;

bool load_map(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return false;

    if (game_map != NULL) {
        for (int i = 0; i < current_rows; i++) free(game_map[i]);
        free(game_map);
    }
    
    fscanf(file, "%d %d", &current_rows, &current_cols);
    game_map = (int**)malloc(current_rows * sizeof(int*));
    for (int i = 0; i < current_rows; i++) {
        game_map[i] = (int*)malloc(current_cols * sizeof(int));
        for (int j = 0; j < current_cols; j++) {
            fscanf(file, "%d", &game_map[i][j]);
        }
    }
    fclose(file);
    return true;
}

void draw_map(SDL_Renderer* ren) {
    for (int r = 0; r < current_rows; r++) {
        for (int c = 0; c < current_cols; c++) {
            SDL_Rect rect = {c * TILE_SIZE, r * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if (game_map[r][c] == 1) {
                SDL_SetRenderDrawColor(ren, 0, 0, 255, 255); // Blue Walls
                SDL_RenderFillRect(ren, &rect);
            } else if (game_map[r][c] == 2) {
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // Pellets
                // Math to keep pellet centered in the 24x24 tile
                SDL_Rect dot = {c * TILE_SIZE + 10, r * TILE_SIZE + 10, 4, 4};
                SDL_RenderFillRect(ren, &dot);
            }
        }
    }
}