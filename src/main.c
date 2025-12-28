#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/constants.h"
#include "../include/map.h"
#include "../include/entity.h"
#include "../include/ui.h"

typedef enum {
    STATE_START_MENU,
    STATE_PLAYING,
    STATE_GAME_OVER
} GameState;

void reset_game() {
    load_map("assets/map.txt");
    setup_player();
    setup_ghost();
    score = 0;
}

int main(int argc, char *argv[])
{
    if (!load_map("assets/map.txt")) return 1;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Sadid's Pacman", 100, 100, screen_width, screen_height, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    setup_player();
    setup_ghost();

    bool running = true;
    GameState current_state = STATE_START_MENU;
    SDL_Event event;

    while (running) {
        // --- 1. INPUT ---
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) running = false;

                if (current_state == STATE_START_MENU) {
                    if (event.key.keysym.sym == SDLK_SPACE) current_state = STATE_PLAYING;
                } 
                else if (current_state == STATE_GAME_OVER) {
                    if (event.key.keysym.sym == SDLK_r) {
                        reset_game();
                        current_state = STATE_PLAYING;
                    }
                } 
                else if (current_state == STATE_PLAYING) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:    pacman.next_dx = 0;  pacman.next_dy = -1; break;
                        case SDLK_DOWN:  pacman.next_dx = 0;  pacman.next_dy = 1;  break;
                        case SDLK_LEFT:  pacman.next_dx = -1; pacman.next_dy = 0;  break;
                        case SDLK_RIGHT: pacman.next_dx = 1;  pacman.next_dy = 0;  break;
                    }
                }
            }
        }

        // --- 2. LOGIC ---
        if (current_state == STATE_PLAYING) {
            move_player();
            move_ghost();
            if (abs((int)pacman.x - (int)blinky.x) < 22 && abs((int)pacman.y - (int)blinky.y) < 22) {
                current_state = STATE_GAME_OVER;
            }
        }

        // --- 3. RENDERING ---
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        draw_map(renderer);
        draw_player(renderer);
        draw_ghost(renderer);
        draw_ui_score(renderer, score, 20, 10);

        if (current_state == STATE_START_MENU) draw_start_screen(renderer);
        else if (current_state == STATE_GAME_OVER) draw_game_over_screen(renderer, score);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}