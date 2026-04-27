#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>

// Standard UI elements
void draw_ui_score(SDL_Renderer *ren, int score, int x, int y);
void draw_ui_level(SDL_Renderer *ren, int level, int x, int y);

// Full-screen overlays
void draw_start_screen(SDL_Renderer *ren);
void draw_game_over_screen(SDL_Renderer *ren, int score_val);
void draw_level_up_flash(SDL_Renderer *ren, int level);

// Low-level text engine (if needed by other files)
void draw_text(SDL_Renderer *ren, const char* txt, int x, int y, int sz);
void draw_char(SDL_Renderer *ren, char c, int x, int y, int sz);

#endif