#include "../include/ghost_manager.h"
#include "../include/ghost_ai.h"
#include "../include/map.h"
#include "../include/entity.h"
#include "../include/constants.h"
#include <stdlib.h>

Ghost ghosts[GHOST_COUNT];
extern int active_ghosts;

void setup_all_ghosts() {
    // Defined a set of 10 distinct colors for the 10 levels
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
        ghosts[i].x = -100; // Initialize off-screen
        ghosts[i].y = -100;
        ghosts[i].color = colors[i];
    }
}

// void move_all_ghosts() {
//     for (int i = 0; i < active_ghosts; i++) {
//         // Only allow a turn if the ghost is perfectly centered on a tile
//         if ((int)ghosts[i].x % TILE_SIZE == 0 && (int)ghosts[i].y % TILE_SIZE == 0) {
//             int next_dx, next_dy;
//             get_smart_direction(i, (int)pacman.x, (int)pacman.y, &next_dx, &next_dy);

//             int target_col = ((int)ghosts[i].x / TILE_SIZE) + next_dx;
//             int target_row = ((int)ghosts[i].y / TILE_SIZE) + next_dy;

//             // Boundary check to prevent crashing on map edges
//             if (target_row >= 0 && target_row < current_rows && target_col >= 0 && target_col < current_cols) {
//                 if (game_map[target_row][target_col] != 1) {
//                     ghosts[i].dx = next_dx;
//                     ghosts[i].dy = next_dy;
//                 }
//             }
//         }
        
//         ghosts[i].x += ghosts[i].dx * GHOST_SPEED;
//         ghosts[i].y += ghosts[i].dy * GHOST_SPEED;
//     }
// }
void move_all_ghosts() {
    for (int i = 0; i < active_ghosts; i++) {
        // Skip ghosts that are parked off-screen
        if (ghosts[i].x < 0) continue;

        // 1. Direction logic: Only change direction at tile intersections
        if ((int)ghosts[i].x % TILE_SIZE == 0 && (int)ghosts[i].y % TILE_SIZE == 0) {
            int next_dx, next_dy;
            get_smart_direction(i, (int)pacman.x, (int)pacman.y, &next_dx, &next_dy);

            int target_col = ((int)ghosts[i].x / TILE_SIZE) + next_dx;
            int target_row = ((int)ghosts[i].y / TILE_SIZE) + next_dy;

            // Boundary check
            if (target_row >= 0 && target_row < current_rows && target_col >= 0 && target_col < current_cols) {
                if (game_map[target_row][target_col] != 1) {
                    ghosts[i].dx = next_dx;
                    ghosts[i].dy = next_dy;
                }
            }
        }
        
        // 2. Move the ghost
        ghosts[i].x += ghosts[i].dx * GHOST_SPEED;
        ghosts[i].y += ghosts[i].dy * GHOST_SPEED;

        // 3. --- GHOSTS LEAVE PELLETS ---
        // Calculate the tile coordinates based on the ghost's center
        int center_x = ((int)ghosts[i].x + TILE_SIZE / 2) / TILE_SIZE;
        int center_y = ((int)ghosts[i].y + TILE_SIZE / 2) / TILE_SIZE;

        // Verify we are within map bounds
        if (center_y >= 0 && center_y < current_rows && center_x >= 0 && center_x < current_cols) {
            // If the ghost is over an empty path (2), convert it back to a pellet (0)
            if (game_map[center_y][center_x] == 0) {
                game_map[center_y][center_x] = 2;
            }
        }
    }
}
void draw_all_ghosts(SDL_Renderer* renderer) {
    for (int i = 0; i < active_ghosts; i++) {
        // Safety check: don't draw if they are still "parked" off-screen
        if (ghosts[i].x < 0 || ghosts[i].y < 0) continue;

        SDL_Rect r = {(int)ghosts[i].x, (int)ghosts[i].y, TILE_SIZE, TILE_SIZE};
        SDL_SetRenderDrawColor(renderer, ghosts[i].color.r, ghosts[i].color.g, ghosts[i].color.b, 255);
        SDL_RenderFillRect(renderer, &r);
    }
}

bool check_pacman_collision() {
    for (int i = 0; i < active_ghosts; i++) {
        if (abs((int)pacman.x - (int)ghosts[i].x) < 20 && 
            abs((int)pacman.y - (int)ghosts[i].y) < 20){
            return true;
        }
    }
    return false;
}