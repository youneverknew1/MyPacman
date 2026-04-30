#include <stdio.h>
#include <string.h>
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
    {1,0,1,1,0,1,1,1,1,1,0,1,1,1,1}, {1,0,1,1,0,1,1,0,1,0,1,0,0,1,0}, // U, V
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

void draw_heart(SDL_Renderer *ren, int x, int y, int sz) {
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_Rect rects[4] = {
        {x, y, sz, sz}, {x + sz*2, y, sz, sz}, // Top bumps
        {x, y + sz, sz*3, sz},                // Middle
        {x + sz, y + sz*2, sz, sz}             // Bottom point
    };
    for(int i=0; i<4; i++) SDL_RenderFillRect(ren, &rects[i]);
}

void draw_ui_score(SDL_Renderer *ren, int s, int x, int y) {
    char buf[16]; sprintf(buf, "SCORE %04d", s);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    draw_text(ren, buf, x, y, 2);
}

void draw_ui_level(SDL_Renderer *ren, int l, int x, int y) {
    char buf[16]; sprintf(buf, "LEVEL %d", l);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    draw_text(ren, buf, x, y, 2);
}

void draw_ui_lives(SDL_Renderer *ren, int l, int x, int y) {
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    draw_text(ren, "LIVES", x, y, 2);
    for (int i = 0; i < l; i++) {
        draw_heart(ren, x + 85 + (i * 28), y, 5);
    }
}

void draw_centered_ui(SDL_Renderer *ren, const char* main_txt, const char* sub_txt, SDL_Color color) {
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 180);
    SDL_Rect r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(ren, &r);
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, 255);
    draw_text(ren, main_txt, (SCREEN_WIDTH/2) - (strlen(main_txt)*12), SCREEN_HEIGHT/2 - 40, 6);
    if (sub_txt) {
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        draw_text(ren, sub_txt, (SCREEN_WIDTH/2) - (strlen(sub_txt)*6), SCREEN_HEIGHT/2 + 40, 3);
    }
}

void draw_start_screen(SDL_Renderer *ren) { draw_centered_ui(ren, "SHADIDS PACMAN", "SPACE TO START", (SDL_Color){255, 255, 0, 255}); }
void draw_game_over_screen(SDL_Renderer *ren, int s) { char buf[32]; sprintf(buf, "SCORE %04d - R TO RETRY", s); draw_centered_ui(ren, "GAME OVER", buf, (SDL_Color){255, 0, 0, 255}); }
void draw_level_up_flash(SDL_Renderer *ren, int l) {
    char level_buf[32]; 
    sprintf(level_buf, "LEVEL %d", l);
    
    draw_centered_ui(ren, "LEVEL UP", level_buf, (SDL_Color){0, 255, 255, 255}); 
    
    // Speed Message
    SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
    draw_text(ren, "+0.2 SPEED INCREASE", (SCREEN_WIDTH/2) - 160, (SCREEN_HEIGHT/2) + 60, 2);

}
void draw_life_flash(SDL_Renderer *ren) {
    // 1. Same orientation/logic as Level Flash: Darken the background
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 180); // Slightly darker for impact
    SDL_Rect full_screen = {0, 0, current_cols * TILE_SIZE, current_rows * TILE_SIZE};
    SDL_RenderFillRect(ren, &full_screen);

    // 2. Big Gold Main Text (Size 6 for that "BIG FLASH" feel)
    SDL_SetRenderDrawColor(ren, 255, 215, 0, 255); // Gold/Yellow
    const char* main_txt = "LIFE ATTAINED";
    // Centering logic: (Total Width / 2) - (Length * (CharWidth * Size) / 2)
    int main_x = (current_cols * TILE_SIZE / 2) - (strlen(main_txt) * 12);
    int main_y = (current_rows * TILE_SIZE / 2) - 40;
    draw_text(ren, main_txt, main_x, main_y, 6);

    // 3. Smaller White Sub-Text (Same orientation as your Level X text)
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // White
    const char* sub_txt = "EXTRA HEART ADDED";
    int sub_x = (current_cols * TILE_SIZE / 2) - (strlen(sub_txt) * 6);
    int sub_y = main_y + 80; // Positioned below the main text
    draw_text(ren, sub_txt, sub_x, sub_y, 3);
}// Ensure this closing brace is here!