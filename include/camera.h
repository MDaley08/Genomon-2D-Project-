#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL2/SDL.h>
#include "entity.h"

/**
 * @brief allocates resouse and assigns initial values for camera system
*/
void camera_system_init();

/**
 * @brief camera follows an entity
 * @param ent entity to follow
*/
void camera_follow(Entity *ent);

SDL_Rect *camera_get();

#endif
