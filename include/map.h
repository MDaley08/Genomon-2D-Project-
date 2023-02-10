#ifndef __MAP_H__
#define __MAP_H__

#include "SDL2/SDL.h"
#include "gf2d_graphics.h"


typedef struct Map_S
{
    SDL_Texture *map_texture;
    int         map_grid[WINDOW_HEIGHT][WINDOW_WIDTH];

}Map;



void map_close();

void map_init();

void map_load(char *tilemap, char *tileset);

void map_draw();





#endif
