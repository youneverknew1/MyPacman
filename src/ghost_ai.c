#include "../include/ghost_ai.h"
#include "../include/ghost_manager.h"
#include "../include/entity.h"
#include "../include/map.h"
#include "../include/constants.h"
#include <math.h>

void get_smart_direction(int idx, int tx, int ty, int *ox, int *oy) {
    int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    float best_dist = 1e9f; 
    int best_idx = -1;

    for (int i = 0; i < 4; i++) {
        int nx = (int)ghosts[idx].x + dir[i][0] * TILE_SIZE;
        int ny = (int)ghosts[idx].y + dir[i][1] * TILE_SIZE;

        if (check_wall(nx, ny)) continue;

        // Prevent 180-degree turns
        if (dir[i][0] == -ghosts[idx].dx && dir[i][1] == -ghosts[idx].dy) continue;

        float d = pow(tx - nx, 2) + pow(ty - ny, 2);

        if (d < best_dist) {
            best_dist = d;
            best_idx = i;
        }
    }

    if (best_idx != -1) {
        *ox = dir[best_idx][0];
        *oy = dir[best_idx][1];
    }
}