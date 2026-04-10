#include <stdio.h>
#include <stdlib.h>
#include "../include/map.h"
#include "../include/constants.h"

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
    if (fscanf(file, "%d %d", &current_rows, &current_cols) != 2) {
        fclose(file);
        return false;
    }

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

void draw_map(SDL_Renderer* renderer) {
    if (!game_map) return;
    for (int r = 0; r < current_rows; r++) {
        for (int c = 0; c < current_cols; c++) {
            int x = c * TILE_SIZE;
            int y = r * TILE_SIZE;
            if (game_map[r][c] == 1) { // Wall
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_Rect wall = {x, y, TILE_SIZE, TILE_SIZE};
                SDL_RenderFillRect(renderer, &wall);
            } else if (game_map[r][c] == 2) { // Pellet
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_Rect pellet = {x + 14, y + 14, 4, 4};
                SDL_RenderFillRect(renderer, &pellet);
            }
        }
    }
}