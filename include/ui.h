#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>

// Standard HUD elements
void draw_ui_score(SDL_Renderer *ren, int s, int x, int y);
void draw_ui_level(SDL_Renderer *ren, int l, int x, int y);
void draw_ui_lives(SDL_Renderer *ren, int l, int x, int y);

// Full screen overlays (Flashes)
void draw_start_screen(SDL_Renderer *ren);
void draw_game_over_screen(SDL_Renderer *ren, int s);
void draw_level_up_flash(SDL_Renderer *ren, int l);
void draw_life_flash(SDL_Renderer *ren); // The new Gold flash

// Helper functions for drawing text and shapes
void draw_text(SDL_Renderer *ren, const char* txt, int x, int y, int sz);
void draw_char(SDL_Renderer *ren, char c, int x, int y, int sz);
void draw_heart(SDL_Renderer *ren, int x, int y, int sz);
void draw_centered_ui(SDL_Renderer *ren, const char* main_txt, const char* sub_txt, SDL_Color color);

#endif