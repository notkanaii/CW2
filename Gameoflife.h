#ifndef GAMEOFLIFE_GUARD__H
#define GAMEOFLIFE_GUARD__H

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define CELL_SIZE 20
#define SCREEN_WIDTH (GRID_WIDTH * CELL_SIZE)
#define SCREEN_HEIGHT (GRID_HEIGHT * CELL_SIZE)


int GRID_WIDTH=20;
int GRID_HEIGHT=20;
int buffer1[8000][8000];
void load_file();
SDL_Window *createWindow(char *title);
SDL_Renderer *createRenderer(SDL_Window *window);
void drawGrid(SDL_Renderer *r);
void drawCells(SDL_Renderer *r, int a[][GRID_WIDTH]);
void updateCells(int a[][GRID_WIDTH]); 
int countLivingNeighbours(int a[][GRID_WIDTH], int x, int y);
void save_file();

#endif
