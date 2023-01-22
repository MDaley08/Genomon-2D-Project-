#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <SDL2/SDL.h>

typedef struct
{
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Point point;
    Uint8   hidden;
}Mouse;

void mouse_init();
void mouse_update();
void mouse_draw();
Uint8 mouse_in_rect(SDL_Rect *rect);
void mouse_show();
void mouse_hide();



#endif