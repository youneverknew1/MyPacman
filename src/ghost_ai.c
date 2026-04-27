#include "../include/ghost_ai.h"
#include "../include/map.h"
#include "../include/constants.h"
#include "../include/entity.h"
#include "../include/ghost_manager.h"
#include <stdlib.h>
#include <math.h>

extern Ghost ghosts[GHOST_COUNT];
extern int active_ghosts;
void get_smart_direction(int ghost_idx, int target_x, int target_y, int* dx, int* dy) {
    int gx = (int)ghosts[ghost_idx].x / TILE_SIZE;
    int gy = (int)ghosts[ghost_idx].y / TILE_SIZE;
    int tx = target_x / TILE_SIZE;
    int ty = target_y / TILE_SIZE;

    // --- TARGETING PERSONALITIES ---
    if (ghost_idx >= 2) {
        // Flankers: Target 4 tiles ahead of Pacman
        tx += (pacman.dx * 4);
        ty += (pacman.dy * 4);
    }

    int dirs[4][2] = {{0,-1}, {0,1}, {-1,0}, {1,0}}; // Up, Down, Left, Right
    float distances[4] = {99999, 99999, 99999, 99999};
    int sorted_indices[4] = {0, 1, 2, 3};

    // 1. Calculate distances for all moves
    for (int i = 0; i < 4; i++) {
        int nx = gx + dirs[i][0];
        int ny = gy + dirs[i][1];

        if (nx < 0 || nx >= current_cols || ny < 0 || ny >= current_rows) continue;
        if (game_map[ny][nx] == 1) continue;
        if (dirs[i][0] == -ghosts[ghost_idx].dx && dirs[i][1] == -ghosts[ghost_idx].dy) continue;

        distances[i] = (float)((nx - tx) * (nx - tx) + (ny - ty) * (ny - ty));
    }

    // 2. Sort directions (Best to Worst)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (distances[sorted_indices[j]] > distances[sorted_indices[j+1]]) {
                int temp = sorted_indices[j];
                sorted_indices[j] = sorted_indices[j+1];
                sorted_indices[j+1] = temp;
            }
        }
    }

    // 3. IMPROVED ANTI-LINEUP (Applies to ALL ghosts now)
    for (int i = 0; i < 4; i++) {
        int choice = sorted_indices[i];
        if (distances[choice] > 90000) continue; 

        int next_tile_x = gx + dirs[choice][0];
        int next_tile_y = gy + dirs[choice][1];

        bool occupied = false;
        for (int j = 0; j < active_ghosts; j++) {
            if (ghost_idx == j) continue;
            
            int other_gx = (int)ghosts[j].x / TILE_SIZE;
            int other_gy = (int)ghosts[j].y / TILE_SIZE;

            // If another ghost is already in the tile we want to move to
            if (other_gx == next_tile_x && other_gy == next_tile_y) {
                occupied = true;
                break;
            }
        }

        // If the tile is free, take it.
        // If it's occupied, Ghost 0 and 1 will try the 2nd best path 
        // instead of just following the leader.
        if (!occupied) {
            *dx = dirs[choice][0];
            *dy = dirs[choice][1];
            return;
        }
    }

    // Fallback: If all paths are "occupied" by other ghosts, just take the best one anyway
    // (Otherwise they would get stuck)
    *dx = dirs[sorted_indices[0]][0];
    *dy = dirs[sorted_indices[0]][1];
}