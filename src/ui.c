#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/ui.h"
#include "../include/constants.h"

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
    {1,0,1,1,0,1,1,0,1,1,0,1,1,1,1}, {1,0,1,1,0,1,1,0,1,0,1,0,0,1,0}, // U, V
    {1,0,1,1,0,1,1,0,1,1,1,1,1,0,1}, {1,0,1,1,0,1,0,1,0,1,0,1,1,0,1}, // W, X
    {1,0,1,1,0,1,0,1,0,0,1,0,0,1,0}, {1,1,1,0,0,1,0,1,0,1,0,0,1,1,1}, // Y, Z
    {1,1,1,1,0,1,1,0,1,1,0,1,1,1,1}, {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0}, // 0, 1
    {1,1,1,0,0,1,1,1,1,1,0,0,1,1,1}, {1,1,1,0,0,1,1,1,1,0,0,1,1,1,1}, // 2, 3
    {1,0,1,1,0,1,1,1,1,0,0,1,0,0,1}, {1,1,1,1,0,0,1,1,1,0,0,1,1,1,1}, // 4, 5
    {1,1,1,1,0,0,1,1,1,1,0,1,1,1,1}, {1,1,1,0,0,1,0,1,0,0,1,0,0,1,0}, // 6, 7
    {1,1,1,1,0,1,1,1,1,1,0,1,1,1,1}, {1,1,1,1,0,1,1,1,1,0,0,1,1,1,1}  // 8, 9
};

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

void draw_overlay(SDL_Renderer *ren, SDL_Color col) {
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 180);
    SDL_Rect r = {0, 0, screen_width, screen_height};
    SDL_RenderFillRect(ren, &r);
    SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, 255);
}

void draw_start_screen(SDL_Renderer *ren) {
    draw_overlay(ren, (SDL_Color){255, 255, 0, 255});
    draw_text(ren, "PACMAN", screen_width/2 - 70, screen_height/2 - 40, 6);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    draw_text(ren, "SPACE TO START", screen_width/2 - 110, screen_height/2 + 40, 3);
}

void draw_game_over_screen(SDL_Renderer *ren, int score) {
    draw_overlay(ren, (SDL_Color){255, 0, 0, 255});
    draw_text(ren, "GAME OVER", screen_width/2 - 90, screen_height/2 - 60, 6);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    char buf[20];
    sprintf(buf, "SCORE %04d", score);
    draw_text(ren, buf, screen_width/2 - 80, screen_height/2, 4);
    draw_text(ren, "R TO RETRY", screen_width/2 - 70, screen_height/2 + 60, 3);
}

void draw_ui_score(SDL_Renderer *ren, int val, int x, int y) {
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    char buf[10];
    sprintf(buf, "%04d", val);
    draw_text(ren, buf, x, y, 4);
}