#include <SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include "../include/map.h"
#include "../include/constants.h"


int game_map[map_rows][map_cols];

int score=0;
bool load_map(const char* filename) {
    FILE* file = fopen(filename, "r");
    for (int i = 0; i < map_rows; i++) {
        for (int j = 0; j < map_cols; j++) {
            if (fscanf(file, "%d", &game_map[i][j]) != 1) {
                fclose(file);
                return false;
            }
        }
    }
    fclose(file);
    return true;
}
void draw_map(SDL_Renderer* renderer) {
    for (int r = 0; r < map_rows; r++) {
        for (int c = 0; c < map_cols; c++) {
            int x = c * 32; 
            int y = r * 32;
            if (game_map[r][c] == 1) {

                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_Rect wall = {x, y, 32, 32};
                SDL_RenderFillRect(renderer, &wall);

            }else if (game_map[r][c] == 2) {

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_Rect pellet = {x + 14, y + 14, 4, 4}; //center (32/2-2)
                SDL_RenderFillRect(renderer, &pellet);
            }
        }
    }
}