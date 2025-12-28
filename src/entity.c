#include "../include/entity.h"
#include "../include/map.h"
#include "../include/constants.h"
#include <time.h>
#include <stdlib.h>

Player pacman;
Ghost blinky;

void setup_player()
{
    // SWAPPED: Place Pacman in the middle of the maze (Tile 9, 10)
    pacman.x = 32.0f * 9; 
    pacman.y = 32.0f * 10;
    pacman.dx = 0;
    pacman.dy = 0;
    pacman.next_dx = 0;
    pacman.next_dy = 0;
}

void setup_ghost(){
    srand(time(NULL));
    // SWAPPED: Place ghost in the top-left corner (Tile 1, 1)
    blinky.x = 32.0f; 
    blinky.y = 32.0f;
    blinky.dx = 1; // Start moving right
    blinky.dy = 0;
    blinky.color = (SDL_Color){255, 0, 0, 255};
}

bool check_wall(int x, int y)
{
    int left = x / 32;
    int right = (x + 31) / 32;
    int top = y / 32;
    int bottom = (y + 31) / 32;

    // Boundary check fixed to match your constants: cols=19, rows=20
    if (left < 0 || right >= map_cols || top < 0 || bottom >= map_rows) 
        return true;

    return (game_map[top][left] == 1 ||
            game_map[top][right] == 1 ||
            game_map[bottom][left] == 1 ||
            game_map[bottom][right] == 1);
}

void move_player()
{
    int speed = 2; 
    for (int i = 0; i < speed; i++){
        if ((int)pacman.x % 32 == 0 && (int)pacman.y % 32 == 0){
            if (pacman.next_dx != 0 || pacman.next_dy != 0){
               if (!check_wall((int)pacman.x + pacman.next_dx, (int)pacman.y + pacman.next_dy)){
                    pacman.dx = pacman.next_dx;
                    pacman.dy = pacman.next_dy;
                }
            }
        }
        if (!check_wall((int)pacman.x + pacman.dx, (int)pacman.y + pacman.dy)){
            pacman.x += (float)pacman.dx;
            pacman.y += (float)pacman.dy;
        }else{
            break;
        }
        
        // Scoring logic
        int current_col = ((int)pacman.x + 16) / 32;
        int current_row = ((int)pacman.y + 16) / 32;
        if(current_row >= 0 && current_row < map_rows && current_col >= 0 && current_col < map_cols){
            if(game_map[current_row][current_col] == 2){
                game_map[current_row][current_col] = 0; // 0 = empty path
                score += 10;
            }
        }
    }
}

void move_ghost() {
    int speed = 2; 
    for (int i = 0; i < speed; i++) {
        if ((int)blinky.x % 32 == 0 && (int)blinky.y % 32 == 0) {
            int dirs[4][2] = {{0,-1}, {0,1}, {-1,0}, {1,0}};
            
            // Logic: Change direction if hitting wall OR random choice at intersection
            if (check_wall((int)blinky.x + blinky.dx, (int)blinky.y + blinky.dy) || rand() % 10 == 0) {
                int r = rand() % 4;
                if (!check_wall((int)blinky.x + dirs[r][0], (int)blinky.y + dirs[r][1])) {
                    blinky.dx = dirs[r][0];
                    blinky.dy = dirs[r][1];
                }
            }
        }

        if (!check_wall((int)blinky.x + blinky.dx, (int)blinky.y + blinky.dy)) {
            blinky.x += (float)blinky.dx;
            blinky.y += (float)blinky.dy;
        }
    }
}

void draw_player(SDL_Renderer *renderer)
{
    SDL_Rect rect = {(int)pacman.x, (int)pacman.y, 32, 32};
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void draw_ghost(SDL_Renderer *renderer) {
    SDL_Rect rect = {(int)blinky.x, (int)blinky.y, 32, 32};
    SDL_SetRenderDrawColor(renderer, blinky.color.r, blinky.color.g, blinky.color.b, 255); 
    SDL_RenderFillRect(renderer, &rect);
}