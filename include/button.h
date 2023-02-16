#ifndef __GF2D_BUTTON_H__
#define __GF2D_BUTTON_H__

#include <SDL2/SDL.h>
#include "gfc_shape.h"
#include "gfc_types.h"
#include "gf2d_sprite.h"

// we must adjust sdl rect to automatically shift with button image.
typedef struct Button_S
{
    Uint8           _inUse;
    Bool            hidden;
    Bool            selected;
    Bool            clicked;
    SDL_Rect        button_rect;
    SDL_Texture     *texture;
    char            *text;
    void            (*think)(struct Button_S *button); //what button does on call
    void            (*update)(struct Button_S *button); //what button does on call
}Button;

/**
 * @brief launches button system allocating memory for button.
*/
void button_system_init(Uint16 max_buttons);

/**
 * @brief creates a new button object
 * @return returns NULL if error or pointer to valid entry on success
*/
Button *button_new();
/**
 * @brief runs function that occurs on button click
 * @param button button which to execute think function for.
*/
void button_think(Button *self);

/**
 * @brief draws button to screen
 * @param button button to draw
*/
void button_draw(Button *self);

/**
 * @brief draws all buttons created to screen
*/
void button_draw_all();

/**
 * @brief executes think function of a button
 * @param self button in question
*/
void button_think(Button *self);

/**
 * @brief executes think function for all buttons
*/
void button_think_all();

/**
 * @brief executes the update function 
 * @param self button in question
*/
void button_update(Button *self);

/**
 * @brief executes update function for all buttons
*/
void button_update_all();


/**
 * @brief frees previously created system from memory
 * @param self entity to be freed
*/
void button_free(Button *self);

/**
 * @brief checks if a button has been selected by mouse.
 * @param self button to check.
 * @return returns true if a button has been clicked
*/
Uint8 button_interacted(Button *self);




#endif

