#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/ui.h"
#include "../include/constants.h"

// 3x5 bitmasks for A-Z
static const int char_masks[26][15] = {
    {1,1,1, 1,0,1, 1,1,1, 1,0,1, 1,0,1}, // A
    {1,1,0, 1,0,1, 1,1,0, 1,0,1, 1,1,0}, // B
    {1,1,1, 1,0,0, 1,0,0, 1,0,0, 1,1,1}, // C
    {1,1,0, 1,0,1, 1,0,1, 1,0,1, 1,1,0}, // D
    {1,1,1, 1,0,0, 1,1,1, 1,0,0, 1,1,1}, // E
    {1,1,1, 1,0,0, 1,1,0, 1,0,0, 1,0,0}, // F
    {1,1,1, 1,0,0, 1,0,1, 1,0,1, 1,1,1}, // G
    {1,0,1, 1,0,1, 1,1,1, 1,0,1, 1,0,1}, // H
    {1,1,1, 0,1,0, 0,1,0, 0,1,0, 1,1,1}, // I
    {0,0,1, 0,0,1, 0,0,1, 1,0,1, 1,1,1}, // J
    {1,0,1, 1,0,1, 1,1,0, 1,0,1, 1,0,1}, // K
    {1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,1,1}, // L
    {1,0,1, 1,1,1, 1,0,1, 1,0,1, 1,0,1}, // M
    {1,1,1, 1,0,1, 1,0,1, 1,0,1, 1,0,1}, // N
    {1,1,1, 1,0,1, 1,0,1, 1,0,1, 1,1,1}, // O
    {1,1,1, 1,0,1, 1,1,1, 1,0,0, 1,0,0}, // P
    {1,1,1, 1,0,1, 1,1,1, 0,1,1, 0,0,1}, // Q
    {1,1,1, 1,0,1, 1,1,0, 1,0,1, 1,0,1}, // R
    {1,1,1, 1,0,0, 1,1,1, 0,0,1, 1,1,1}, // S
    {1,1,1, 0,1,0, 0,1,0, 0,1,0, 0,1,0}, // T
    {1,0,1, 1,0,1, 1,0,1, 1,0,1, 1,1,1}, // U
    {1,0,1, 1,0,1, 1,0,1, 0,1,0, 0,1,0}, // V
    {1,0,1, 1,0,1, 1,0,1, 1,1,1, 1,0,1}, // W
    {1,0,1, 1,0,1, 0,1,0, 1,0,1, 1,0,1}, // X
    {1,0,1, 1,0,1, 0,1,0, 0,1,0, 0,1,0}, // Y
    {1,1,1, 0,0,1, 0,1,0, 1,0,0, 1,1,1}  // Z
};

// 3x5 bitmasks for 0-9
static const int digit_masks[10][15] = {
    {1,1,1, 1,0,1, 1,0,1, 1,0,1, 1,1,1}, // 0
    {0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0}, // 1
    {1,1,1, 0,0,1, 1,1,1, 1,0,0, 1,1,1}, // 2
    {1,1,1, 0,0,1, 1,1,1, 0,0,1, 1,1,1}, // 3
    {1,0,1, 1,0,1, 1,1,1, 0,0,1, 0,0,1}, // 4
    {1,1,1, 1,0,0, 1,1,1, 0,0,1, 1,1,1}, // 5
    {1,1,1, 1,0,0, 1,1,1, 1,0,1, 1,1,1}, // 6
    {1,1,1, 0,0,1, 0,1,0, 0,1,0, 0,1,0}, // 7
    {1,1,1, 1,0,1, 1,1,1, 1,0,1, 1,1,1}, // 8
    {1,1,1, 1,0,1, 1,1,1, 0,0,1, 1,1,1}  // 9
};

void draw_letter(SDL_Renderer *renderer, char c, int x, int y, int size) {
    c = toupper(c);
    if (c < 'A' || c > 'Z') return;
    int index = c - 'A';
    for (int i = 0; i < 15; i++) {
        if (char_masks[index][i]) {
            SDL_Rect block = { x + (i % 3) * size, y + (i / 3) * size, size, size };
            SDL_RenderFillRect(renderer, &block);
        }
    }
}

void draw_digit(SDL_Renderer *renderer, int digit, int x, int y, int size) {
    if (digit < 0 || digit > 9) return;
    for (int i = 0; i < 15; i++) {
        if (digit_masks[digit][i]) {
            SDL_Rect block = { x + (i % 3) * size, y + (i / 3) * size, size, size };
            SDL_RenderFillRect(renderer, &block);
        }
    }
}

void draw_text(SDL_Renderer *renderer, const char* text, int x, int y, int size) {
    int spacing = size * 4; 
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ') { x += spacing; continue; }
        if (isdigit((unsigned char)text[i])) {
            draw_digit(renderer, text[i] - '0', x, y, size);
        } else {
            draw_letter(renderer, text[i], x, y, size);
        }
        x += spacing;
    }
}

void draw_start_screen(SDL_Renderer *renderer) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    SDL_Rect bg = {0, 0, screen_width, screen_height};
    SDL_RenderFillRect(renderer, &bg);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
    draw_text(renderer, "PACMAN", screen_width/2 - 80, screen_height/2 - 40, 6);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    draw_text(renderer, "SPACE TO START", screen_width/2 - 110, screen_height/2 + 40, 3);
}

void draw_game_over_screen(SDL_Renderer *renderer, int final_score) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_Rect bg = {0, 0, screen_width, screen_height};
    SDL_RenderFillRect(renderer, &bg);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
    draw_text(renderer, "GAME OVER", screen_width/2 - 90, screen_height/2 - 60, 6);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    char score_buf[20];
    sprintf(score_buf, "SCORE %04d", final_score);
    draw_text(renderer, score_buf, screen_width/2 - 80, screen_height/2, 4);
    draw_text(renderer, "R TO RETRY", screen_width/2 - 70, screen_height/2 + 60, 3);
}

void draw_ui_score(SDL_Renderer *renderer, int val, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    char buf[10];
    sprintf(buf, "%04d", val);
    draw_text(renderer, buf, x, y, 4);
}