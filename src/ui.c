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

// --- INTERNAL HELPERS ---



// Unified Centering Logic for Overlays
void draw_centered_ui(SDL_Renderer *ren, const char* main_txt, const char* sub_txt, SDL_Color color) {
    // 1. Dim background
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 160);
    SDL_Rect r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(ren, &r);

    // 2. Draw Main Header (Centered)
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
    int main_sz = 6;
    int main_x = (SCREEN_WIDTH / 2) - (strlen(main_txt) * (main_sz * 2));
    draw_text(ren, main_txt, main_x, SCREEN_HEIGHT / 2 - 50, main_sz);

    // 3. Draw Subtext (Centered)
    if (sub_txt) {
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        int sub_sz = 3;
        int sub_x = (SCREEN_WIDTH / 2) - (strlen(sub_txt) * (sub_sz * 2));
        draw_text(ren, sub_txt, sub_x, SCREEN_HEIGHT / 2 + 30, sub_sz);
    }
}

// --- PUBLIC FUNCTIONS ---

void draw_start_screen(SDL_Renderer *ren) {
    draw_centered_ui(ren, "SHADID'S PACMAN", "SPACE TO START", (SDL_Color){255, 255, 0, 255});
}

void draw_game_over_screen(SDL_Renderer *ren, int score_val) {
    char buf[32];
    sprintf(buf, "SCORE %04d - R TO RETRY", score_val);
    draw_centered_ui(ren, "GAME OVER", buf, (SDL_Color){255, 0, 0, 255});
}

void draw_level_up_flash(SDL_Renderer *ren, int level) {
    char buf[16];
    sprintf(buf, "LEVEL %d", level);
    draw_centered_ui(ren, "LEVEL UP", buf, (SDL_Color){0, 255, 255, 255}); // Cyan flash
}

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

void draw_text(SDL_Renderer *ren, const char* txt, int x, int y, int sz) {
    for (int i = 0; txt[i] != '\0'; i++) {
        if (txt[i] != ' ') draw_char(ren, txt[i], x, y, sz);
        x += sz * 4; 
    }
}