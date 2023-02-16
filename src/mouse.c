#include <SDL2/SDL_image.h>
#include "stdlib.h"
#include "gf2d_graphics.h"
#include "simple_logger.h"
#include "mouse.h"
typedef struct
{
    Uint32 buttons;     /**<buttons mask*/
    Vector2D position;  /**<position of mouse*/
}MouseState;

typedef struct Mouse_S
{
    MouseState  mouse[2];
    SDL_Texture *texture; 
    SDL_Rect    rect;
    SDL_Point   point;
    Uint8       hidden;
}Mouse;

static Mouse _mouse_obj = {0};

void mouse_close(){
    if (_mouse_obj.texture) SDL_DestroyTexture(_mouse_obj.texture);
    memset(&_mouse_obj,0,sizeof(_mouse_obj));
    slog("mouse system closed");
}


void mouse_init(Vector2D cursor_size, Vector3D cursor_color){
    _mouse_obj.texture = IMG_LoadTexture(gf2d_graphics_get_renderer(),"images/cursor.png");   
    _mouse_obj.rect.w = cursor_size.x;
    _mouse_obj.rect.h = cursor_size.y;
    _mouse_obj.point.x = _mouse_obj.rect.x;
    _mouse_obj.point.y = _mouse_obj.rect.y;
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetTextureColorMod(_mouse_obj.texture, cursor_color.x, cursor_color.y, cursor_color.z);
    atexit(mouse_close);
}

void mouse_update(){
    memcpy(&_mouse_obj.mouse[1],&_mouse_obj.mouse[0],sizeof(MouseState));
    _mouse_obj.mouse[0].buttons = SDL_GetMouseState(&_mouse_obj.rect.x, &_mouse_obj.rect.y);
    _mouse_obj.point.x = _mouse_obj.rect.x;
    _mouse_obj.point.y = _mouse_obj.rect.y;
}

void mouse_draw(){
    if(!_mouse_obj.hidden){
        SDL_RenderCopy(gf2d_graphics_get_renderer(), _mouse_obj.texture, NULL, &_mouse_obj.rect);
    }
}

void mouse_show(){
    if(!_mouse_obj.hidden)return;
    _mouse_obj.hidden--;
}
void mouse_hide(){
    if(_mouse_obj.hidden)return;
    _mouse_obj.hidden++;
}

void mouse_color(Vector3D cursor_color){
    SDL_SetTextureColorMod(_mouse_obj.texture, cursor_color.x, cursor_color.y, cursor_color.z);
}
Bool mouse_button_pressed(int button)
{
    int mask;
    if (_mouse_obj.hidden)return false;
    mask = 1 << button;
    if ((_mouse_obj.mouse[0].buttons & mask) &&
        !(_mouse_obj.mouse[1].buttons & mask))
    {
        return true;
    }
    return false;
}

Bool mouse_in_rect(SDL_Rect *rect){
    return SDL_PointInRect(&_mouse_obj.point, rect);
}

/*eol@eof*/
