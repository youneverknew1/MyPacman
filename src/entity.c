#include "../include/entity.h"
#include "../include/map.h"

Player pacman;
void setup_player(){
    pacman.x=tile_size; //st (1,1)
    pacman.y=tile_size;
    pacman.dx=0;
    pacman.dy=0;
}

void move_player(){
    float speed=2.0f;

    float nextX=pacman.x+(pacman.dx*speed); //pos
    float nextY=pacman.y+(pacman.dy*speed);
    int col=(int)(nextX+16)/tile_size;
    int row=(int)(nextY+16)/tile_size;

    if(game_map[row][col]!=1){
        pacman.x=nextX;
        pacman.y=nextY;
    }else{
        pacman.dx=0;
        pacman.dy=0;
    }
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