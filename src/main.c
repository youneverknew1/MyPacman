#include <SDL2/SDL.h>
#include "../include/constants.h"
#include "../include/map.h"
#include "../include/entity.h"
#include "../include/ghost_manager.h"
#include "../include/ui.h"

typedef enum { MENU, PLAY, OVER } State;
State state = MENU;

void reset() {
    load_map("assets/map.txt");
    setup_player();
    setup_all_ghosts();
    score = 0;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Pacman", 100, 100, screen_width, screen_height, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    
    reset();
    bool run = true;
    SDL_Event e;

    while (run) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) run = false;
            if (e.type == SDL_KEYDOWN) {
                if (state == MENU && e.key.keysym.sym == SDLK_SPACE) state = PLAY;
                if (state == OVER && e.key.keysym.sym == SDLK_r) { reset(); state = PLAY; }
                if (state == PLAY) {
                    if (e.key.keysym.sym == SDLK_UP) { pacman.next_dx = 0; pacman.next_dy = -1; }
                    if (e.key.keysym.sym == SDLK_DOWN) { pacman.next_dx = 0; pacman.next_dy = 1; }
                    if (e.key.keysym.sym == SDLK_LEFT) { pacman.next_dx = -1; pacman.next_dy = 0; }
                    if (e.key.keysym.sym == SDLK_RIGHT) { pacman.next_dx = 1; pacman.next_dy = 0; }
                }
            }
        }

        if (state == PLAY) {
            move_player();
            move_all_ghosts();
            if (check_pacman_collision()) state = OVER;
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        draw_map(ren);
        draw_player(ren);
        draw_all_ghosts(ren);
        draw_ui_score(ren, score, 10, 10);

        if (state == MENU) draw_start_screen(ren);
        if (state == OVER) draw_game_over_screen(ren, score);

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    SDL_Quit();
    return 0;
}