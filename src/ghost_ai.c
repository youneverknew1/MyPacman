#include "../include/ghost_ai.h"
#include "../include/map.h"
#include "../include/constants.h"
#include <math.h>

void get_smart_direction(Ghost *ghost, Player *target, int *out_dx, int *out_dy) {
    int dirs[4][2] = {{0,-1}, {0,1}, {-1,0}, {1,0}}; // Up, Down, Left, Right
    float min_dist = 9999999.0f;
    int best_dir = -1;

    for (int i = 0; i < 4; i++) {
        int test_dx = dirs[i][0];
        int test_dy = dirs[i][1];

        // 1. Don't check walls
        if (check_wall((int)ghost->x + (test_dx * 32), (int)ghost->y + (test_dy * 32))) {
            continue;
        }

        // 2. Prevent 180-degree turns (Ghosts shouldn't jitter back and forth)
        if (test_dx == -ghost->dx && test_dy == -ghost->dy) {
            continue;
        }

        // 3. Calculate distance to Pacman from the potential new tile
        float target_x = target->x;
        float target_y = target->y;
        float next_tile_x = ghost->x + (test_dx * 32);
        float next_tile_y = ghost->y + (test_dy * 32);

        // Squared distance is faster than sqrt()
        float dist = pow(target_x - next_tile_x, 2) + pow(target_y - next_tile_y, 2);

        if (dist < min_dist) {
            min_dist = dist;
            best_dir = i;
        }
    }

    // If a path is found, set the new direction
    if (best_dir != -1) {
        *out_dx = dirs[best_dir][0];
        *out_dy = dirs[best_dir][1];
    } else {
        // Dead end: Force a reversal
        *out_dx = -ghost->dx;
        *out_dy = -ghost->dy;
    }
}