#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/map.h"
#include "../include/constants.h"
#include <SDL2/SDL.h>

int **game_map = NULL;
int current_rows = 0;
int current_cols = 0;
int score = 0;
bool is_power_active = false;
int power_timer = 0;

bool load_map(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return false;

    if (game_map != NULL)
    {
        for (int i = 0; i < current_rows; i++)
            free(game_map[i]);
        free(game_map);
    }

    fscanf(file, "%d %d", &current_rows, &current_cols);
    game_map = (int **)malloc(current_rows * sizeof(int *));
    for (int i = 0; i < current_rows; i++)
    {
        game_map[i] = (int *)malloc(current_cols * sizeof(int));
        for (int j = 0; j < current_cols; j++)
        {
            fscanf(file, "%d", &game_map[i][j]);
        }
    }
    fclose(file);
    return true;
}

void spawn_power_pellet()
{
    if (!game_map)
        return;
    srand(time(NULL));
    bool placed = false;
    int attempts = 0;
    while (!placed && attempts < 100)
    {
        int r = rand() % current_rows;
        int c = rand() % current_cols;
        if (game_map[r][c] == 0)
        {                       // Only on empty path
            game_map[r][c] = 5; // 5 = Power Pellet
            placed = true;
        }
        attempts++;
    }
}

void draw_map(SDL_Renderer *ren)
{
    for (int r = 0; r < current_rows; r++)
    {
        for (int c = 0; c < current_cols; c++)
        {
            SDL_Rect rect = {c * TILE_SIZE, r * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if (game_map[r][c] == 1)
            {
                SDL_SetRenderDrawColor(ren, 0, 0, 255, 255); // Blue Walls
                SDL_RenderFillRect(ren, &rect);
            }
            else if (game_map[r][c] == 2)
            {
                SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // Pellets
                SDL_Rect dot = {c * TILE_SIZE + 14, r * TILE_SIZE + 14, 4, 4};
                SDL_RenderFillRect(ren, &dot);
            }
            else if (game_map[r][c] == 5)
            {
                // Flashy Power Pellet
                SDL_SetRenderDrawColor(ren, 255, 100, 255, 255);
                SDL_Rect power = {c * TILE_SIZE + 8, r * TILE_SIZE + 8, 16, 16};
                SDL_RenderFillRect(ren, &power);
            }
        }
    }
}