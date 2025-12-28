#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "../include/constants.h"
#include "../include/map.h"
#include "../include/entity.h"

int main(int argc, char *argv[])
{
    load_map("assets/map.txt");
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Sadid's Pacman", 100, 100, screen_width, screen_height, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    setup_player();
    bool running = true;
    SDL_Event event;

    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
                running = false;
            // movement
            if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    pacman.next_dx = 0;
                    pacman.next_dy = -1;
                    break;
                case SDLK_DOWN:
                    pacman.next_dx = 0;
                    pacman.next_dy = 1;
                    break;
                case SDLK_LEFT:
                    pacman.next_dx = -1;
                    pacman.next_dy = 0;
                    break;
                case SDLK_RIGHT:
                    pacman.next_dx = 1;
                    pacman.next_dy = 0;
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
                }
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