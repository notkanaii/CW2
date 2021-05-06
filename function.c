
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "function.h"

void update(int cells[][WIDTH]){
    int new[HEIGHT][WIDTH];
    int v, h; // vertical count, horizontal count
    for(v = 0; v < HEIGHT; v++){
        for(h = 0; h < WIDTH; h++){
            if(cells[v][h] == 1 && count(cells, h, v) < 2) new[v][h] = 0;
            else if(cells[v][h] == 1 && (count(cells, h, v) == 2 || count(cells, h, v) == 3)) new[v][h] = 1;
            else if(cells[v][h] == 1 && count(cells, h, v) > 3) new[v][h] = 0;
            else if(cells[v][h] == 0 && count(cells, h, v) == 3) new[v][h] = 1;
            else new[v][h] = 0;
        }
    }
    for(v = 0; v < HEIGHT; v++){
        for(h = 0; h < WIDTH; h++){
            cells[v][h] = new[v][h];
        }
    }
    for(v = 0; v < HEIGHT; v++){
        for(h = 0; h < WIDTH; h++){
            buffer1[v][h] = new[v][h];
        }
    }
}

int count(int cells[][WIDTH], int x, int y){
    int count = 0;
    int v=0;
    int h=0;
    for(v = y - 1; v <= y + 1; v++){
        for(h = x - 1; h <= x + 1; h++){
            if(h==x&&v==y) continue;
            if(!(v < 0 || h < 0 || v >= HEIGHT || h >= WIDTH)){
                if(cells[v][h] == 1)
                    count++;
            }
        }
    }
    return count;
}

void drawGrid(SDL_Renderer *r, int cells[][WIDTH]){
    // Draw vertical grid lines
    int v,h=0;
    for(v = CELL_SIZE; v < SCREEN_WIDTH; v += CELL_SIZE){
        //color
        SDL_SetRenderDrawColor(r, 110, 110, 110, 110);
        // vertical line
        SDL_RenderDrawLine(r, v, 0, v, SCREEN_HEIGHT);
    }
    for(h = CELL_SIZE; h < SCREEN_HEIGHT; h += CELL_SIZE){
        //color
        SDL_SetRenderDrawColor(r, 110, 110, 110, 110);
        //horizontal line
        SDL_RenderDrawLine(r, 0, h, SCREEN_WIDTH, h);
    }
    SDL_Rect Rect;
    Rect.w = CELL_SIZE + 1;
    Rect.h = CELL_SIZE + 1;
    for(v = 0; v < HEIGHT; v++){
        for(h = 0; h < WIDTH; h++){
            if(cells[v][h] == 1){
                //x/y pos
                Rect.x = h * CELL_SIZE;
                Rect.y = v * CELL_SIZE;

                SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
                SDL_RenderFillRect(r, &Rect);
            }
        }
    }
}



SDL_Window *createWindow(char *title){
    SDL_Window *window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            0
    );
    if(window == NULL){
        printf("Create window failed. %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}

SDL_Renderer *createRenderer(SDL_Window *window){
    SDL_Renderer *renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
    );

    if(renderer == NULL){
        printf("Create renderer failed. %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return renderer;
}

