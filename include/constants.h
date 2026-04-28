#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// Tile and Game Settings
#define TILE_SIZE 32
#define GHOST_COUNT 10
#define GHOST_SPEED 2.0f

// Map Dimensions (Defined in map.c, shared here)
extern int current_rows;
extern int current_cols;

// Dynamic Screen Scaling
#define SCREEN_WIDTH (current_cols * TILE_SIZE)
#define SCREEN_HEIGHT (current_rows * TILE_SIZE)

// Global Game State
typedef enum { 
    STATE_MENU, 
    STATE_PLAY, 
    STATE_OVER 
} GameState;

extern GameState state;
extern int score;
extern int lives;         // Added to track Pacman's health
extern int current_level; // Added for the Level Up logic

#endif // CONSTANTS_H