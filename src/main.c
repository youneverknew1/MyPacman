#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "../include/constants.h"
#include "../include/map.h"
#include "../include/entity.h"
#include "../include/ghost_manager.h"
#include "../include/ui.h"

int current_level = 1;
int active_ghosts = 2;
int level_flash_timer = 0;
int lives = 3; // Initialized lives

GameState state = STATE_MENU;
SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;

// Moves Pacman and active ghosts back to their starting spots from the map
void spawn_entities()
{
    int g_idx = 0;
    for (int r = 0; r < current_rows; r++)
    {
        for (int c = 0; c < current_cols; c++)
        {
            if (game_map[r][c] == 3)
            {
                pacman.x = (float)c * TILE_SIZE;
                pacman.y = (float)r * TILE_SIZE;
            }
            else if (game_map[r][c] == 4)
            {
                if (g_idx < active_ghosts)
                {
                    ghosts[g_idx].x = (float)c * TILE_SIZE;
                    ghosts[g_idx].y = (float)r * TILE_SIZE;
                    ghosts[g_idx].dx = 0; // Stop movement on spawn
                    ghosts[g_idx].dy = 0;
                    g_idx++;
                }
            }
        }
    }
}

void add_new_ghost()
{
    if (active_ghosts >= GHOST_COUNT)
        return;

    int found_spawns = 0;
    for (int r = 0; r < current_rows; r++)
    {
        for (int c = 0; c < current_cols; c++)
        {
            if (game_map[r][c] == 4)
            {
                if (found_spawns == active_ghosts)
                {
                    ghosts[active_ghosts].x = (float)c * TILE_SIZE;
                    ghosts[active_ghosts].y = (float)r * TILE_SIZE;
                    ghosts[active_ghosts].dx = 0;
                    ghosts[active_ghosts].dy = 0;
                    active_ghosts++;
                    return;
                }
                found_spawns++;
            }
        }
    }
}

void level_up()
{
    current_level++;
    add_new_ghost();
    level_flash_timer = 90;
}

// Full Reset (Score and Level wiped)
void reset()
{
    if (load_map("assets/map.txt"))
    {
        int w = current_cols * TILE_SIZE;
        int h = current_rows * TILE_SIZE;
        SDL_SetWindowSize(win, w, h);
        SDL_RenderSetLogicalSize(ren, w, h);

        score = 0;
        current_level = 1;
        active_ghosts = 2;
        lives = 3; // Reset lives back to 3
        level_flash_timer = 0;

        setup_all_ghosts();
        spawn_entities();
        pacman.dx = pacman.dy = pacman.next_dx = pacman.next_dy = 0;
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);

    // Initial window size will be corrected by reset()
    win = SDL_CreateWindow("SHADIDs PACMAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    reset();

    bool run = true;
    SDL_Event event;
    while (run)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                run = false;
            if (event.type == SDL_KEYDOWN)
            {
                if (state == STATE_MENU && event.key.keysym.sym == SDLK_SPACE)
                    state = STATE_PLAY;
                if (state == STATE_OVER && event.key.keysym.sym == SDLK_r)
                {
                    reset();
                    state = STATE_PLAY;
                }

                if (state == STATE_PLAY)
                {
                    if (event.key.keysym.sym == SDLK_UP)
                    {
                        pacman.next_dx = 0;
                        pacman.next_dy = -1;
                    }
                    if (event.key.keysym.sym == SDLK_DOWN)
                    {
                        pacman.next_dx = 0;
                        pacman.next_dy = 1;
                    }
                    if (event.key.keysym.sym == SDLK_LEFT)
                    {
                        pacman.next_dx = -1;
                        pacman.next_dy = 0;
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT)
                    {
                        pacman.next_dx = 1;
                        pacman.next_dy = 0;
                    }
                }
            }
        }

        if (state == STATE_PLAY)
        {
            move_player();
            move_all_ghosts();

            // Check for level up
            if (score >= current_level * 500)
                level_up();

            // LIVES LOGIC
            if (check_pacman_collision())
            {
                lives--;
                if (lives <= 0)
                {
                    state = STATE_OVER;
                }
                else
                {
                    // Soft Reset: Keep score and level, but move characters back
                    spawn_entities();
                    pacman.dx = pacman.dy = pacman.next_dx = pacman.next_dy = 0;
                    SDL_Delay(1000); // Wait 1 second before resuming
                }
            }
        }

        // --- DRAWING ---
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        draw_map(ren);
        draw_player(ren);
        draw_all_ghosts(ren);
        // Clear screen and draw map/entities first...

        int hud_y = 15; // All on one line
        draw_ui_score(ren, score, 40, hud_y);
        draw_ui_level(ren, current_level, 400, hud_y);
        draw_ui_lives(ren, lives, 750, hud_y); // The hearts will appear here
        if (level_flash_timer > 0 && state == STATE_PLAY)
        {
            draw_level_up_flash(ren, current_level);
            level_flash_timer--;
        }

        if (state == STATE_MENU)
            draw_start_screen(ren);
        if (state == STATE_OVER)
            draw_game_over_screen(ren, score);

        SDL_RenderPresent(ren);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}