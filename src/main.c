#include <SDL2/SDL.h>
#include "../include/constants.h"
#include "../include/map.h"
#include "../include/entity.h"
#include "../include/ghost_manager.h"
#include "../include/ui.h"
#include <stdbool.h>

GameState state = STATE_MENU;
SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;

void spawn_entities() {
    int g_idx = 0;
    for (int r = 0; r < current_rows; r++) {
        for (int c = 0; c < current_cols; c++) {
            if (game_map[r][c] == 3) {
                pacman.x = (float)c * TILE_SIZE;
                pacman.y = (float)r * TILE_SIZE;
                game_map[r][c] = 0; 
            } else if (game_map[r][c] == 4 && g_idx < GHOST_COUNT) {
                ghosts[g_idx].x = (float)c * TILE_SIZE;
                ghosts[g_idx].y = (float)r * TILE_SIZE;
                game_map[r][c] = 0;
                g_idx++;
            }
        }
    }
}

void reset() {
    if (load_map("assets/map.txt")) {
        int w = current_cols * TILE_SIZE;
        int h = current_rows * TILE_SIZE;
        SDL_SetWindowSize(win, w, h);
        
        SDL_RenderSetLogicalSize(ren, w, h); 
        
        setup_all_ghosts();
        spawn_entities();
        pacman.dx = pacman.dy = pacman.next_dx = pacman.next_dy = 0;
        score = 0;
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    reset();
    
    bool run = true;
    SDL_Event event;

    while (run) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) run = false;
            if (event.type == SDL_KEYDOWN) {
                if (state == STATE_MENU && event.key.keysym.sym == SDLK_SPACE) state = STATE_PLAY;
                if (state == STATE_OVER && event.key.keysym.sym == SDLK_r) { reset(); state = STATE_PLAY; }
                
                if (state == STATE_PLAY) {
                    if (event.key.keysym.sym == SDLK_UP)    { pacman.next_dx = 0;  pacman.next_dy = -1; }
                    if (event.key.keysym.sym == SDLK_DOWN)  { pacman.next_dx = 0;  pacman.next_dy = 1;  }
                    if (event.key.keysym.sym == SDLK_LEFT)  { pacman.next_dx = -1; pacman.next_dy = 0;  }
                    if (event.key.keysym.sym == SDLK_RIGHT) { pacman.next_dx = 1;  pacman.next_dy = 0;  }
                }
            }
        }

        if (state == STATE_PLAY) {
            move_player();
            move_all_ghosts();
            if (check_pacman_collision()) state = STATE_OVER;
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        draw_map(ren);
        draw_player(ren);
        draw_all_ghosts(ren);
        draw_ui_score(ren, score, 20, 10);

        if (state == STATE_MENU) draw_start_screen(ren);
        if (state == STATE_OVER) draw_game_over_screen(ren, score);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}