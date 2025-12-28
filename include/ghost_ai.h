#ifndef GHOST_AI_H
#define GHOST_AI_H

#include "entity.h"

// Returns the best direction (0: Up, 1: Down, 2: Left, 3: Right)
void get_smart_direction(Ghost *ghost, Player *target, int *out_dx, int *out_dy);

#endif