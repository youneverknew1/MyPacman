#include "../include/ghost_ai.h"
#include "../include/ghost_manager.h"
#include "../include/map.h"

void get_smart_direction(int idx, int *ox, int *oy) {
    int direction[4][2] = {{0,-1}, {0,1}, {-1,0}, {1,0}};
    float min_dist = 1e9f;
    int bestIdx = -1;

    for (int j = 0; j < 4; j++) {
        int testX = (int)ghosts[idx].x + direction[j][0] * 32;
        int testY = (int)ghosts[idx].y + direction[j][1] * 32;

        if (check_wall(testX, testY)) continue;
        if (direction[j][0] == -ghosts[idx].dx && direction[j][1] == -ghosts[idx].dy) continue;

        float diffX = pacman.x - testX;
        float diffY = pacman.y - testY;
        float dist = (diffX * diffX) + (diffY * diffY);

        if (dist < min_dist) {
            min_dist = dist;
            bestIdx = j;
        }
    }

    if (bestIdx != -1) {
        *ox = direction[bestIdx][0];
        *oy = direction[bestIdx][1];
    }
}