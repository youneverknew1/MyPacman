#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/constants.h"
#include "../include/map.h"
#include "../include/entity.h"

int main(int argc, char* argv[]) {
    load_map("assets/map.txt");
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window=SDL_CreateWindow("Sadid's Pacman",100,100,screen_width,screen_height,0);
    SDL_Renderer* renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    setup_player();
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;

            //movement
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP)    { pacman.dx = 0;  pacman.dy = -1; }
                if (event.key.keysym.sym == SDLK_DOWN)  { pacman.dx = 0;  pacman.dy = 1;  }
                if (event.key.keysym.sym == SDLK_LEFT)  { pacman.dx = -1; pacman.dy = 0;  }
                if (event.key.keysym.sym == SDLK_RIGHT) { pacman.dx = 1;  pacman.dy = 0;  }
            }
        }
        move_player();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        draw_map(renderer);
        draw_player(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}