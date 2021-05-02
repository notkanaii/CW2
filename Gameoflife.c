#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "function.h"




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
        	save_file();
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
    SDL_Quit();
    return 0;
}


