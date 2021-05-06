
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "function.h"

void save_file(){
    FILE *fp;
    fp = fopen("file.txt", "w");
    int a,b;
    for(a=0;a<HEIGHT;a++){
        for(b=0;b<WIDTH;b++){
            fprintf(fp,"%d",buffer1[a][b]);
            fprintf(fp," ");
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}
