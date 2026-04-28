#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>

/**
 * HUD Elements (Score, Level, Lives)
 */
void draw_ui_score(SDL_Renderer *ren, int score, int x, int y);
void draw_ui_level(SDL_Renderer *ren, int level, int x, int y);
void draw_ui_lives(SDL_Renderer *ren, int lives, int x, int y);

/**
 * Full-Screen Overlays
 */
void draw_start_screen(SDL_Renderer *ren);
void draw_game_over_screen(SDL_Renderer *ren, int score_val);
void draw_level_up_flash(SDL_Renderer *ren, int level);

/**
 * Low-Level Text Engine
 */
void draw_text(SDL_Renderer *ren, const char* txt, int x, int y, int sz);
void draw_char(SDL_Renderer *ren, char c, int x, int y, int sz);

/**
 * Internal Helper (Optional to export, but useful if other files 
 * need to create custom overlays)
 */
void draw_centered_ui(SDL_Renderer *ren, const char* main_txt, const char* sub_txt, SDL_Color color);

#endif // UI_H