#include <SDL2/SDL.h>
#include<stdio.h>
#include<stdbool.h>
#include "../include/map.h"
#include "../include/constants.h"


int game_map[map_rows][map_cols];

bool load_map(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open %s\n", filename);
        return false;
    }

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
    for (int i = 0; i < map_rows; i++) {
        for (int j = 0; j < map_cols; j++) {
            SDL_Rect tile = {
                j * tile_size, // x position
                i * tile_size, // y position
                tile_size, 
                tile_size
            };

            if (game_map[i][j] == 1) {
                // Draw a Blue Wall
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_RenderFillRect(renderer, &tile);
            } else if (game_map[i][j] == 0) {
                // Draw a small Pellet (white dot)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_Rect pellet = {
                    (j * tile_size) + 14, 
                    (i * tile_size) + 14, 
                    4, 4
                };
                SDL_RenderFillRect(renderer, &pellet);
            }
        }
    }
}