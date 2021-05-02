
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "function.h"

void updateCells(int a[][GRID_WIDTH]){
    int new[GRID_HEIGHT][GRID_WIDTH];
    int cy, cx; // vertical count, horizontal count

    for(cy = 0; cy < GRID_HEIGHT; cy++){
        for(cx = 0; cx < GRID_WIDTH; cx++){
            if(a[cy][cx] == 1 && countLivingNeighbours(a, cx, cy) < 2) new[cy][cx] = 0;
            else if(a[cy][cx] == 1 && (countLivingNeighbours(a, cx, cy) == 2 || countLivingNeighbours(a, cx, cy) == 3)) new[cy][cx] = 1;
            else if(a[cy][cx] == 1 && countLivingNeighbours(a, cx, cy) > 3) new[cy][cx] = 0;
            else if(a[cy][cx] == 0 && countLivingNeighbours(a, cx, cy) == 3) new[cy][cx] = 1;
            else new[cy][cx] = 0;
        }
    }
    for(cy = 0; cy < GRID_HEIGHT; cy++){
        for(cx = 0; cx < GRID_WIDTH; cx++){
            a[cy][cx] = new[cy][cx];
        }
    }
    for(cy = 0; cy < GRID_HEIGHT; cy++){
        for(cx = 0; cx < GRID_WIDTH; cx++){
            buffer1[cy][cx] = new[cy][cx];
        }
    }
}

int countLivingNeighbours(int a[][GRID_WIDTH], int x, int y){
    int count = 0, cx, cy;

    for(cy = y - 1; cy <= y + 1; cy++){
        for(cx = x - 1; cx <= x + 1; cx++){
            if(cx==x&&cy==y) continue;
            if(!(cy < 0 || cx < 0 || cy >= GRID_HEIGHT || cx >= GRID_WIDTH)){
                if(a[cy][cx] == 1)
                    count++;
            }
        }
    }
    return count;
}

void drawGrid(SDL_Renderer *r){
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
}

void drawCells(SDL_Renderer *r, int c[][GRID_WIDTH]){
    SDL_Rect cellRect;
    cellRect.w = CELL_SIZE + 1;
    cellRect.h = CELL_SIZE + 1;
    int cx, cy;
    for(cy = 0; cy < GRID_HEIGHT; cy++){
        for(cx = 0; cx < GRID_WIDTH; cx++){
            if(c[cy][cx] == 1){
                //x/y pos
                cellRect.x = cx * CELL_SIZE;
                cellRect.y = cy * CELL_SIZE;

                SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
                SDL_RenderFillRect(r, &cellRect);
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

