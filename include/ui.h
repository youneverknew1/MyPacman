#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>

void draw_digit(SDL_Renderer *renderer, int digit, int x, int y, int size);
void draw_letter(SDL_Renderer *renderer, char c, int x, int y, int size);
void draw_text(SDL_Renderer *renderer, const char* text, int x, int y, int size);

void draw_ui_score(SDL_Renderer *renderer, int val, int x, int y);
void draw_start_screen(SDL_Renderer *renderer);
void draw_game_over_screen(SDL_Renderer *renderer, int final_score);

#endif