#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <SDL2/SDL.h>
#include "gfc_types.h"
#include "gfc_vector.h"

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
 * @return true if mouse in rect, false if otherwise
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

/**
 * @brief check if the mouse button was pressed this frame
 * @param button the button number to check (left mouse button is 0, right mouse button is 1, etc)
 * @return 1 if it has, 0 otherwise
 */
Bool mouse_button_pressed(int button);



#endif
