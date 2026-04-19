#include "../include/entity.h"
#include "../include/map.h"
#include "../include/constants.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

Player pacman; 

bool check_wall(int x, int y) {
    if (x < 0 || y < 0 || 
        (x + TILE_SIZE) > (current_cols * TILE_SIZE) || 
        (y + TILE_SIZE) > (current_rows * TILE_SIZE)) {
        return true; 
    }

    // GRID COORDINATE MATH
    int left = x / TILE_SIZE;
    int right = (x + TILE_SIZE - 1) / TILE_SIZE;
    int top = y / TILE_SIZE;
    int bottom = (y + TILE_SIZE - 1) / TILE_SIZE;

    if (left < 0 || right >= current_cols || top < 0 || bottom >= current_rows) return true;
    if (!game_map) return true;

    return (game_map[top][left] == 1 || game_map[top][right] == 1 ||
            game_map[bottom][left] == 1 || game_map[bottom][right] == 1);
}

void move_player() {
    for (int i = 0; i < PACMAN_SPEED; i++) {
        if ((int)pacman.x % TILE_SIZE == 0 && (int)pacman.y % TILE_SIZE == 0) {
            if (!check_wall((int)pacman.x + pacman.next_dx, (int)pacman.y + pacman.next_dy)) {
                pacman.dx = pacman.next_dx;
                pacman.dy = pacman.next_dy;
            }
        }
        if (!check_wall((int)pacman.x + pacman.dx, (int)pacman.y + pacman.dy)) {
            pacman.x += pacman.dx;
            pacman.y += pacman.dy;
        }

        // Pellet eat
        int centerX = (int)pacman.x + TILE_SIZE / 2;
        int centerY = (int)pacman.y + TILE_SIZE / 2;
        int col = centerX / TILE_SIZE;
        int row = centerY / TILE_SIZE;
        
        if (row >= 0 && row < current_rows && col >= 0 && col < current_cols) {
            if (game_map[row][col] == 2) {
                game_map[row][col] = 0;
                score += 10;
            }
        }
    }
}

void draw_player(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_Rect r = {(int)pacman.x, (int)pacman.y, TILE_SIZE, TILE_SIZE};
    SDL_RenderFillRect(renderer, &r);
}