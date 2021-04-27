#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "Gameoflife.h"



int main(int argc, char *argv[]){

	int choice = 0; 
	printf("1.Create new gird\n2.Load grid\n");
	
	scanf("%i",&choice);
    int cx, cy;
    if(choice==1){
    printf("\nSet grid height: ");
    scanf("%d",&GRID_HEIGHT);
    printf("\nSet grid width: ");
    scanf("%d",&GRID_WIDTH);
	}
	else if(choice==2){
		char check;
		int counth = 0;
		int countw = 0;
		FILE*fp;
		int f=0;
		fp = fopen("file.txt", "r"); 
		if ((fp = fopen("file.txt", "r")) == NULL){
			printf("\nNo such file, create a new grid ");
			printf("\nSet grid height: ");
    		scanf("%d",&GRID_HEIGHT);
    		printf("\nSet grid width: ");
    		scanf("%d",&GRID_WIDTH);
    		choice=1;
		}
		else if(fp){
			while((check=fgetc(fp)) != EOF){
			if(check=='\n') counth++;
			else if(check==' ');
			else countw++;
		}
		GRID_WIDTH=countw/counth;
		GRID_HEIGHT=counth;
		printf("\n%i",GRID_WIDTH);
		printf("\n%i\n",GRID_HEIGHT);
    	fclose(fp);
    }
	}
	int map[GRID_HEIGHT][GRID_WIDTH];
	if(choice==1){
		for(cy = 0; cy < GRID_HEIGHT; cy++){
        for(cx = 0; cx < GRID_WIDTH; cx++){
            map[cy][cx] = 0;
        	}
		}
	}
	else if(choice==2){
		FILE*fp;
    	fp = fopen("file.txt", "r+");
    	for(cy=0;cy<GRID_HEIGHT;cy++){
    	    for(cx=0;cx<GRID_WIDTH;cx++){
        	    fscanf(fp,"%d",&map[cy][cx]);
        	}
        	fgetc(fp);
    	}
    	fclose(fp);
	}
    // Initialise SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create window and renderer
    SDL_Window *window = createWindow("Game of Life");
    SDL_Renderer *renderer = createRenderer(window);

    // Event
    SDL_Event event;
    int mouseX, mouseY;
    bool mouse_left_down = false;
    bool mouse_right_down = false;

    
    while(1){
        while(SDL_PollEvent(&event) != 0){
            switch(event.type){
                case SDL_QUIT: // Check if user has quit
                    return 1;
                // Set the status of cells
                case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
                    switch(event.button.button){
                        case SDL_BUTTON_LEFT:
						mouse_left_down = !mouse_left_down;
						break;
                        case SDL_BUTTON_RIGHT:
						mouse_right_down = !mouse_right_down;
						break;
                    }
                // If user presses space, simulate a single change
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_SPACE){
                        updateCells(map);
                        for(cy = 0; cy < GRID_HEIGHT; cy++){
        					for(cx = 0; cx < GRID_WIDTH; cx++){
            					map[cy][cx] = buffer1[cy][cx];
        						}
   						 }
                        save_file();
                    }
						
            }
        }


        SDL_GetMouseState(&mouseX, &mouseY);
        if(mouse_left_down == true)
            map[mouseY / CELL_SIZE][mouseX / CELL_SIZE] = 1;
        else if(mouse_right_down == true)
            map[mouseY / CELL_SIZE][mouseX / CELL_SIZE] = 0;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        drawGrid(renderer);
        drawCells(renderer, map);
        SDL_RenderPresent(renderer);
    }

    // Exit SDL and SDL_image
    SDL_Quit();
    return 0;
}


void save_file(){
    FILE *fp;
    fp = fopen("file.txt", "w");
    int a,b;
    for(a=0;a<GRID_HEIGHT;a++){
        for(b=0;b<GRID_WIDTH;b++){
            fprintf(fp,"%d",buffer1[a][b]);
            fprintf(fp," ");
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}


//the rule of game
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
        // Draw vertical line
        SDL_RenderDrawLine(r, v, 0, v, SCREEN_HEIGHT);
    }
    for(h = CELL_SIZE; h < SCREEN_HEIGHT; h += CELL_SIZE){
        //color
        SDL_SetRenderDrawColor(r, 110, 110, 110, 110);
        // Draw horizontal line
        SDL_RenderDrawLine(r, 0, h, SCREEN_WIDTH, h);
    }
}

void drawCells(SDL_Renderer *r, int a[][GRID_WIDTH]){
    SDL_Rect cellRect;
    cellRect.w = CELL_SIZE + 1;
    cellRect.h = CELL_SIZE + 1;
    int cx, cy;
    for(cy = 0; cy < GRID_HEIGHT; cy++){
        for(cx = 0; cx < GRID_WIDTH; cx++){
            if(a[cy][cx] == 1){
                //x/y pos
                cellRect.x = cx * CELL_SIZE;
                cellRect.y = cy * CELL_SIZE;

                SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
                SDL_RenderFillRect(r, &cellRect);
            }
        }
    }
}
/*
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
        printf("Failed to create window. %s\n", SDL_GetError());
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
        printf("Failed to create renderer. %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return renderer;
}*/
