#include <SDL2/SDL_image.h>
#include "stdlib.h"
#include "gfc_types.h"
#include "gf2d_graphics.h"
#include "simple_logger.h"
#include "mouse.h"

static Mouse mouse_obj = {0};

void mouse_close(){
    if (mouse_obj.texture) SDL_DestroyTexture(mouse_obj.texture);
    memset(&mouse_obj,0,sizeof(mouse_obj));
    slog("mouse system closed");
}


void mouse_init(Vector2D cursor_size, Vector3D cursor_color){
    mouse_obj.texture = IMG_LoadTexture(gf2d_graphics_get_renderer(),"images/cursor.png");   
    mouse_obj.rect.w = cursor_size.x;
    mouse_obj.rect.h = cursor_size.y;
    mouse_obj.point.x = mouse_obj.rect.x;
    mouse_obj.point.y = mouse_obj.rect.y;
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetTextureColorMod(mouse_obj.texture, cursor_color.x, cursor_color.y, cursor_color.z);
    atexit(mouse_close);
}

void mouse_update(){
    SDL_GetMouseState(&mouse_obj.rect.x, &mouse_obj.rect.y);
    mouse_obj.point.x = mouse_obj.rect.x;
    mouse_obj.point.y = mouse_obj.rect.y;
}

void mouse_draw(){
    if(!mouse_obj.hidden){
        SDL_RenderCopy(gf2d_graphics_get_renderer(), mouse_obj.texture, NULL, &mouse_obj.rect);
    }
}

void mouse_show(){
    if(!mouse_obj.hidden){
        slog("mouse is already being displayed");
        return;
    }
    mouse_obj.hidden = 0;
}
void mouse_hide(){
    if(mouse_obj.hidden){
        slog("mouse is already hidden");
        return;
    }
    mouse_obj.hidden = 1;
}

void mouse_color(Vector3D cursor_color){
    SDL_SetTextureColorMod(mouse_obj.texture, cursor_color.x, cursor_color.y, cursor_color.z);
}

Bool mouse_in_rect(SDL_Rect *rect){
    return SDL_PointInRect(&mouse_obj.point, rect);
}

