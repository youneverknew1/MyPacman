#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/ui.h"
#include "../include/constants.h"

// 3x5 Pixel Font Data
static const int font[36][15] = {
    {1,1,1,1,0,1,1,1,1,1,0,1,1,0,1}, {1,1,0,1,0,1,1,1,0,1,0,1,1,1,0}, // A, B
    {1,1,1,1,0,0,1,0,0,1,0,0,1,1,1}, {1,1,0,1,0,1,1,0,1,1,0,1,1,1,0}, // C, D
    {1,1,1,1,0,0,1,1,1,1,0,0,1,1,1}, {1,1,1,1,0,0,1,1,0,1,0,0,1,0,0}, // E, F
    {1,1,1,1,0,0,1,0,1,1,0,1,1,1,1}, {1,0,1,1,0,1,1,1,1,1,0,1,1,0,1}, // G, H
    {1,1,1,0,1,0,0,1,0,0,1,0,1,1,1}, {0,0,1,0,0,1,0,0,1,1,0,1,1,1,1}, // I, J
    {1,0,1,1,0,1,1,1,0,1,0,1,1,0,1}, {1,0,0,1,0,0,1,0,0,1,0,0,1,1,1}, // K, L
    {1,0,1,1,1,1,1,0,1,1,0,1,1,0,1}, {1,1,1,1,0,1,1,0,1,1,0,1,1,0,1}, // M, N
    {1,1,1,1,0,1,1,0,1,1,0,1,1,1,1}, {1,1,1,1,0,1,1,1,1,1,0,0,1,0,0}, // O, P
    {1,1,1,1,0,1,1,1,1,0,1,1,0,0,1}, {1,1,1,1,0,1,1,1,0,1,0,1,1,0,1}, // Q, R
    {1,1,1,1,0,0,1,1,1,0,0,1,1,1,1}, {1,1,1,0,1,0,0,1,0,0,1,0,0,1,0}, // S, T
    {1,0,1,1,0,1,1,1,1,1,0,1,1,1,1}, {1,0,1,1,0,1,1,0,1,0,1,0,0,1,0}, // U, V
    {1,0,1,1,0,1,1,0,1,1,1,1,1,0,1}, {1,0,1,1,0,1,0,1,0,1,0,1,1,0,1}, // W, X
    {1,0,1,1,0,1,0,1,0,0,1,0,0,1,0}, {1,1,1,0,0,1,0,1,0,1,0,0,1,1,1}, // Y, Z
    {1,1,1,1,0,1,1,0,1,1,0,1,1,1,1}, {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0}, // 0, 1
    {1,1,1,0,0,1,1,1,1,1,0,0,1,1,1}, {1,1,1,0,0,1,1,1,1,0,0,1,1,1,1}, // 2, 3
    {1,0,1,1,0,1,1,1,1,0,0,1,0,0,1}, {1,1,1,1,0,0,1,1,1,0,0,1,1,1,1}, // 4, 5
    {1,1,1,1,0,0,1,1,1,1,0,1,1,1,1}, {1,1,1,0,0,1,0,1,0,0,1,0,0,1,0}, // 6, 7
    {1,1,1,1,0,1,1,1,1,1,0,1,1,1,1}, {1,1,1,1,0,1,1,1,1,0,0,1,1,1,1}  // 8, 9
};

// Basic Character Drawing
void draw_char(SDL_Renderer *ren, char c, int x, int y, int sz) {
    int idx = -1;
    if (c >= 'A' && c <= 'Z') idx = c - 'A';
    else if (c >= 'a' && c <= 'z') idx = c - 'a';
    else if (c >= '0' && c <= '9') idx = c - '0' + 26;
    if (idx == -1) return;

    for (int i = 0; i < 15; i++) {
        if (font[idx][i]) {
            SDL_Rect r = { x + (i % 3) * sz, y + (i / 3) * sz, sz, sz };
            SDL_RenderFillRect(ren, &r);
        }
    }
}

// Basic Text Drawing
void draw_text(SDL_Renderer *ren, const char* txt, int x, int y, int sz) {
    for (int i = 0; txt[i] != '\0'; i++) {
        if (txt[i] != ' ') draw_char(ren, txt[i], x, y, sz);
        x += sz * 4; 
    }
}

// Unified Centering Logic for Overlays
void draw_centered_ui(SDL_Renderer *ren, const char* main_txt, const char* sub_txt, SDL_Color color) {
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 160);
    SDL_Rect r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(ren, &r);

    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
    int main_sz = 6;
    int main_x = (SCREEN_WIDTH / 2) - (strlen(main_txt) * (main_sz * 2));
    draw_text(ren, main_txt, main_x, SCREEN_HEIGHT / 2 - 50, main_sz);

    if (sub_txt) {
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        int sub_sz = 3;
        int sub_x = (SCREEN_WIDTH / 2) - (strlen(sub_txt) * (sub_sz * 2));
        draw_text(ren, sub_txt, sub_x, SCREEN_HEIGHT / 2 + 30, sub_sz);
    }
}

// Public Screens
void draw_start_screen(SDL_Renderer *ren) {
    draw_centered_ui(ren, "SHADIDs PACMAN", "SPACE TO START", (SDL_Color){255, 255, 0, 255});
}

void draw_game_over_screen(SDL_Renderer *ren, int score_val) {
    char buf[32];
    sprintf(buf, "SCORE %04d - R TO RETRY", score_val);
    draw_centered_ui(ren, "GAME OVER", buf, (SDL_Color){255, 0, 0, 255});
}

void draw_level_up_flash(SDL_Renderer *ren, int level) {
    char buf[16];
    sprintf(buf, "LEVEL %d", level);
    draw_centered_ui(ren, "LEVEL UP", buf, (SDL_Color){0, 255, 255, 255});
}

// HUD Elements
// Inside src/ui.c

void draw_ui_score(SDL_Renderer *ren, int score, int x, int y) {
    char buf[16]; sprintf(buf, "SCORE %04d", score);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    draw_text(ren, buf, x, y, 2);
}

void draw_ui_level(SDL_Renderer *ren, int level, int x, int y) {
    char buf[16]; sprintf(buf, "LEVEL %d", level);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    draw_text(ren, buf, x, y, 2);
}

void draw_heart(SDL_Renderer *ren, int x, int y, int sz) {
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255); // Red hearts!

    // A heart made of 5 rectangles (3x3 grid style)
    // Left "hump"
    SDL_Rect left_top = { x, y, sz, sz };
    // Right "hump"
    SDL_Rect right_top = { x + sz * 2, y, sz, sz };
    // Middle row
    SDL_Rect mid = { x, y + sz, sz * 3, sz };
    // Bottom point
    SDL_Rect bottom = { x + sz, y + sz * 2, sz, sz };

    SDL_RenderFillRect(ren, &left_top);
    SDL_RenderFillRect(ren, &right_top);
    SDL_RenderFillRect(ren, &mid);
    SDL_RenderFillRect(ren, &bottom);
}

void draw_ui_lives(SDL_Renderer *ren, int lives_count, int x, int y) {
    // First, draw the label "LIVES"
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    draw_text(ren, "LIVES", x, y, 2);

    // Then, draw heart shapes next to it
    int heart_x_start = x + 100; // Start hearts after the word "LIVES"
    for (int i = 0; i < lives_count; i++) {
        draw_heart(ren, heart_x_start + (i * 30), y - 2, 6);
    }
}