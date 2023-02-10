#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <SDL2/SDL.h>
#include "gfc_vector.h"

typedef struct Mouse_S
{
    SDL_Texture *texture;
    SDL_Rect    rect;
    SDL_Point   point;
    Uint8       hidden;
}Mouse;


/**
 * @brief initializes mouse system
*/
void mouse_init(Vector2D cursor_size, Vector3D cursor_color);


/**
 * @brief updates mouse values each frame
*/
void mouse_update();

/**
 * @brief draws mouse to screen
*/
void mouse_draw();

/**
 * @brief checks if mouse is present in a rect
 * @param rect the rect to check aganist
*/
Bool mouse_in_rect(SDL_Rect *rect);

/**
 * @brief shows mouse cursor on screen
*/
void mouse_show();

/**
 * @brief hides/ doesn't drawn mouse cursor to screen
*/
void mouse_hide();

/**
 * @brief changes color of mouse cursor
 * @param cursor_color the color to assign to cursor
*/
void mouse_color(Vector3D cursor_color);





#endif
