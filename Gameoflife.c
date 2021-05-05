#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "function.h"




int main(int argc, char *argv[]){

    int choice= 0;
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
    for(cy = 0; cy < GRID_HEIGHT; cy++){
        for(cx = 0; cx < GRID_WIDTH; cx++){
            buffer1[cy][cx] = map[cy][cx];
        }
    }
    // Initialise SDL
    SDL_Init(SDL_INIT_VIDEO);
    // Create window and renderer
    SDL_Window *window = createWindow("Game of Life");
    SDL_Renderer *renderer = createRenderer(window);
    // Event
    SDL_Event event;
    int posX, posY;
    bool leftmouse = false;
    bool rightmouse = false;
	int last_time = 0;
    int simulate_speed = 500;
    int paused = 1;
    
    
    while(1)
	{
		save_file();
        while(SDL_PollEvent(&event) != 0)
		{
            switch(event.type)
			{
                case SDL_QUIT:
                    return 1;
                    // Set the status of cells
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_SPACE)
					{
                        update(map);
                        for(cy = 0; cy < GRID_HEIGHT; cy++){
                            for(cx = 0; cx < GRID_WIDTH; cx++){
                                map[cy][cx] = buffer1[cy][cx];
                            }
                        }
                    }
				case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
                    switch(event.button.button){
                        case SDL_BUTTON_LEFT:
                            leftmouse = !leftmouse;
                            break;
                        case SDL_BUTTON_RIGHT:
                            rightmouse = !rightmouse;
                            break;
                    }
            }
            if ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP )
            {
                bool isKeydown = event.type == SDL_KEYDOWN;
                switch ( event.key.keysym.scancode )
                {
                case SDL_SCANCODE_LEFT:
                    paused = isKeydown ^ paused;
                    break;
                }
            }
            save_file();
        }
         if ( !( ( SDL_GetTicks( ) - last_time ) < simulate_speed ) && !paused )
        {
            update(map);
            last_time = SDL_GetTicks( );
        }
        // Get user mouse button input - left click gives life to cell at current co-ords, right click kills
        SDL_GetMouseState(&posX, &posY);
        if(leftmouse == true)
            map[posY / CELL_SIZE][posX / CELL_SIZE] = 1;
        else if(rightmouse == true)
            map[posY / CELL_SIZE][posX / CELL_SIZE] = 0;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        drawGrid(renderer,map);
        //drawCells(renderer, map);
        SDL_RenderPresent(renderer);
    }
    save_file();
    SDL_Quit();
    return 0;
}


