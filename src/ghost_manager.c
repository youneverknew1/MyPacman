#include "../include/ghost_manager.h"
#include "../include/ghost_ai.h"
#include "../include/map.h"
#include "../include/entity.h"
#include "../include/constants.h"
#include <stdlib.h>

Ghost ghosts[GHOST_COUNT];
extern int active_ghosts;

void setup_all_ghosts() {
    // 10 distinct colors for 10 ghosts
    SDL_Color colors[GHOST_COUNT] = {
        {255, 0, 0, 255},     // 1: Red
        {255, 182, 85, 255},  // 2: Orange
        {0, 255, 255, 255},   // 3: Cyan
        {255, 182, 255, 255}, // 4: Pink
        {50, 255, 50, 255},   // 5: Green
        {255, 255, 0, 255},   // 6: Yellow
        {150, 100, 255, 255}, // 7: Purple
        {255, 255, 255, 255}, // 8: White
        {100, 100, 100, 255}, // 9: Grey
        {0, 0, 255, 255}      // 10: Blue
    };

    for (int i = 0; i < GHOST_COUNT; i++) {
        ghosts[i].dx = 0;
        ghosts[i].dy = 0;
        ghosts[i].x = -100; // Parked off-screen
        ghosts[i].y = -100;
        ghosts[i].color = colors[i];
    }
}

void move_all_ghosts() {
    for (int i = 0; i < active_ghosts; i++) {
        if (ghosts[i].x < 0) continue;

        // 1. Grid-based turning logic
        if ((int)ghosts[i].x % TILE_SIZE == 0 && (int)ghosts[i].y % TILE_SIZE == 0) {
            int next_dx, next_dy;
            get_smart_direction(i, (int)pacman.x, (int)pacman.y, &next_dx, &next_dy);

            int target_col = ((int)ghosts[i].x / TILE_SIZE) + next_dx;
            int target_row = ((int)ghosts[i].y / TILE_SIZE) + next_dy;

            if (target_row >= 0 && target_row < current_rows && target_col >= 0 && target_col < current_cols) {
                if (game_map[target_row][target_col] != 1) {
                    ghosts[i].dx = next_dx;
                    ghosts[i].dy = next_dy;
                }
            }
        }
        
        // 2. Physical movement
        ghosts[i].x += ghosts[i].dx * GHOST_SPEED;
        ghosts[i].y += ghosts[i].dy * GHOST_SPEED;

        // 3. Gardener Logic (Fixed): Convert empty path (2) back to pellet (0)
        int center_x = ((int)ghosts[i].x + TILE_SIZE / 2) / TILE_SIZE;
        int center_y = ((int)ghosts[i].y + TILE_SIZE / 2) / TILE_SIZE;

        if (center_y >= 0 && center_y < current_rows && center_x >= 0 && center_x < current_cols) {
            if (game_map[center_y][center_x] == 0) {
                game_map[center_y][center_x] = 2; 
            }
        }
    }
}

void draw_all_ghosts(SDL_Renderer* ren) {
    for (int i = 0; i < active_ghosts; i++) {
        if (ghosts[i].x < 0) continue;

        int x = (int)ghosts[i].x;
        int y = (int)ghosts[i].y;

        // Draw Ghost Body (Square for now, but with color)
        SDL_Rect body = {x + 2, y + 2, TILE_SIZE - 4, TILE_SIZE - 4};
        SDL_SetRenderDrawColor(ren, ghosts[i].color.r, ghosts[i].color.g, ghosts[i].color.b, 255);
        SDL_RenderFillRect(ren, &body);

        // Draw Eyes (The "Face")
        // Eyes look in the direction the ghost is moving
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // White for eyes
        
        int eye_offset_x = ghosts[i].dx * 4;
        int eye_offset_y = ghosts[i].dy * 4;

        // Left Eye
        SDL_Rect eyeL = {x + 6 + eye_offset_x, y + 8 + eye_offset_y, 6, 8};
        // Right Eye
        SDL_Rect eyeR = {x + 18 + eye_offset_x, y + 8 + eye_offset_y, 6, 8};
        
        SDL_RenderFillRect(ren, &eyeL);
        SDL_RenderFillRect(ren, &eyeR);

        // Pupils (Black dots inside eyes)
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_Rect pupilL = {x + 8 + eye_offset_x + ghosts[i].dx*2, y + 10 + eye_offset_y + ghosts[i].dy*2, 2, 3};
        SDL_Rect pupilR = {x + 20 + eye_offset_x + ghosts[i].dx*2, y + 10 + eye_offset_y + ghosts[i].dy*2, 2, 3};
        SDL_RenderFillRect(ren, &pupilL);
        SDL_RenderFillRect(ren, &pupilR);
    }
}

bool check_pacman_collision() {
    for (int i = 0; i < active_ghosts; i++) {
        if (ghosts[i].x < 0) continue;
        
        // Using a slightly tighter hitbox (18 pixels) for fairness
        if (abs((int)pacman.x - (int)ghosts[i].x) < 18 && 
            abs((int)pacman.y - (int)ghosts[i].y) < 18) {
            return true;
        }
    }
    return false;
}