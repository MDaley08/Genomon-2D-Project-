#ifndef __UI_H__
#define __UI_H__

#include <SDL2/SDL_ttf.h>
#include "gf2d_sprite.h"
#include "gf2d_draw.h"
#include "player.h"

/**
* @brief draws ui for when player is in combat.
*/
void combat_ui_draw();

/**
 * @brief draws game ui for out of combat.
*/
void ui_draw();

#endif
