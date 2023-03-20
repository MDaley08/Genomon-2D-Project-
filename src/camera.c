#include "simple_logger.h"
#include "gf2d_graphics.h"
#include "camera.h"


SDL_Rect _camera  = {0};

void camera_system_init(){
    _camera.x = 0;
    _camera.x = 0;
    _camera.w = WINDOW_WIDTH;
    _camera.h = WINDOW_HEIGHT;
}

void camera_follow(Entity *ent){
    if(!ent){
        slog("camera_follow: entity not found");
        return;
    }
    _camera.x = ent->rect.x - WINDOW_WIDTH / 2;
    _camera.y = ent->rect.y - WINDOW_HEIGHT / 2;
    if(_camera.x < 0) _camera.x = 0;
    if(_camera.y < 0) _camera.y = 0;
}

SDL_Rect *camera_get(){
    return &_camera;
}

/*eol@eof*/
