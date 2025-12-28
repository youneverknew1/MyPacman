#include "../include/ghost_ai.h"
#include "../include/map.h"      // This is the line that fixes your error
#include <math.h>
#include <stdbool.h>

void get_smart_direction(Ghost *ghost, Player *target, int *out_dx, int *out_dy) {
    int dirs[4][2] = {{0,-1}, {0,1}, {-1,0}, {1,0}}; // Up, Down, Left, Right
    float min_dist = 1e9f;
    int best_dir = -1;

    for (int i = 0; i < 4; i++) {
        int tx = (int)ghost->x + (dirs[i][0] * 32);
        int ty = (int)ghost->y + (dirs[i][1] * 32);

        // Now the compiler will know what check_wall is
        if (check_wall(tx, ty)) continue;
        
        // Prevent 180-degree turns
        if (dirs[i][0] == -ghost->dx && dirs[i][1] == -ghost->dy) continue;

        float dist = pow(target->x - tx, 2) + pow(target->y - ty, 2);
        if (dist < min_dist) {
            min_dist = dist;
            best_dir = i;
        }
    }

    if (best_dir != -1) {
        *out_dx = dirs[best_dir][0];
        *out_dy = dirs[best_dir][1];
    }
}