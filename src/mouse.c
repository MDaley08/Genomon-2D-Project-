#include "gf2d_graphics.h"
#include "SDL2/SDL_image.h"
#include "simple_logger.h"
#include "mouse.h"


static Mouse mouse_obj = {0};

void mouse_init(){
    mouse_obj.texture = IMG_LoadTexture(gf2d_graphics_get_renderer(),"images/cursor.jpeg");    
    mouse_obj.rect.w = 50;
    mouse_obj.rect.h = 50;
    mouse_obj.point.x = mouse_obj.rect.x;
    mouse_obj.point.y = mouse_obj.rect.y;
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetTextureColorMod(mouse_obj.texture, 255, 0, 0);
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

//commiting out this function until i'm able to test funtionality 
// Uint8 mouse_in_rect(SDL_Rect *rect){
//     Uint8 result;
//     result = SDL_PointInRect(&mouse_obj.point, rect);
//     return result;
// }

