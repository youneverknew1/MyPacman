#include "../include/entity.h"

Player pacman;
void setup_player(){
    pacman.x=tile_size;
    pacman.y=tile_size;
    pacman.dx=0;
    pacman.dy=0;
}

void move_player(){
    float speed=2.0f;
    pacman.x=pacman.x+(pacman.dx*speed);
    pacman.y=pacman.y+(pacman.dy*speed);
}

void draw_player(SDL_Renderer* renderer){
    SDL_Rect rect;
    rect.x=(int)pacman.x+4;
    rect.y=(int)pacman.y+4;
    rect.w=24;
    rect.h=24;

    SDL_SetRenderDrawColor(renderer,255,255,0,255);
    SDL_RenderFillRect(renderer,&rect);
}