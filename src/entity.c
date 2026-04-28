#include "../include/entity.h"
#include "../include/map.h"
#include "../include/constants.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

Player pacman; 



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

        int col = ((int)pacman.x + 16) / TILE_SIZE;
        int row = ((int)pacman.y + 16) / TILE_SIZE;
        
        if (row >= 0 && row < current_rows && col >= 0 && col < current_cols) {
            if (game_map[row][col] == 2) {
                game_map[row][col] = 0;
                score += 10;
            }
        }
    }
}

void draw_player(SDL_Renderer *ren) {
    int x = (int)pacman.x;
    int y = (int)pacman.y;
    
    // Increment animation timer
    pacman.anim_timer++;
    if (pacman.anim_timer > 20) pacman.anim_timer = 0; // Reset every 20 frames

    // Draw the main body
    SDL_SetRenderDrawColor(ren, 255, 255, 0, 255); // Yellow
    SDL_Rect body = { x + 2, y + 2, TILE_SIZE - 4, TILE_SIZE - 4 };
    SDL_RenderFillRect(ren, &body);

    // MOUTH LOGIC: Only "cut out" the mouth if timer is in the first 10 frames
    if (pacman.anim_timer < 10 && (pacman.dx != 0 || pacman.dy != 0)) {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); // Black (Matches background)
        SDL_Rect mouth;
        
        int m_size = 12; // Size of the mouth opening
        
        if (pacman.dx > 0) { // Moving Right
            mouth = (SDL_Rect){ x + TILE_SIZE - m_size, y + TILE_SIZE/2 - 4, m_size, 8 };
        } else if (pacman.dx < 0) { // Moving Left
            mouth = (SDL_Rect){ x, y + TILE_SIZE/2 - 4, m_size, 8 };
        } else if (pacman.dy > 0) { // Moving Down
            mouth = (SDL_Rect){ x + TILE_SIZE/2 - 4, y + TILE_SIZE - m_size, 8, m_size };
        } else if (pacman.dy < 0) { // Moving Up
            mouth = (SDL_Rect){ x + TILE_SIZE/2 - 4, y, 8, m_size };
        }
        
        SDL_RenderFillRect(ren, &mouth);
    }
}
bool check_wall(int x, int y) {
    if (x < 0 || y < 0 || 
        (x + TILE_SIZE) > (current_cols * TILE_SIZE) || 
        (y + TILE_SIZE) > (current_rows * TILE_SIZE)) {
        return true; 
    }

    int left = x / TILE_SIZE;
    int right = (x + TILE_SIZE - 1) / TILE_SIZE;
    int top = y / TILE_SIZE;
    int bottom = (y + TILE_SIZE - 1) / TILE_SIZE;

    if (left < 0 || right >= current_cols || top < 0 || bottom >= current_rows) return true;
    if (!game_map) return true;

    return (game_map[top][left] == 1 || game_map[top][right] == 1 ||
            game_map[bottom][left] == 1 || game_map[bottom][right] == 1);
}