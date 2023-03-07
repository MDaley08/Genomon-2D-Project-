#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gfc_types.h"
#include "item.h"

#define MAX_INV_SIZE 25
typedef struct
{
    Bool    _inUse;
    Item    *item;
    Button  *button;
}InvSlot;

typedef struct Inventory_S
{   
    SDL_Rect    inv_rect;
    SDL_Texture *inv_tex;
    Bool        _inUse;
    InvSlot     inv_slots[MAX_INV_SIZE];
    void        (*free)(struct Inventory_S *self);
}Inventory;

/**
 * @brief inits inventory system, allocates a list holding all inventories in game.
 * @param max_inventories max number of inventories to create in game.
*/
void inventory_system_init(Uint16 max_inventories);

/**
 * @brief creates a new inventory object.
 * @return returns a new inventory object if successful  or NULL if error or unsuccessful.
*/
Inventory *inventory_new(Vector2D postion);

/**
 * @brief adds a new item to first free inventory slot.
 * @param item item to put in inventory.
*/
void inventory_add_item(Item *item, Inventory *self);

/**
 * @brief item to remove from inventory.
 * @param item item to remove from inventory.
 * @param self inventory to remove item from
 */
void inventory_remove_item(Item *item, Inventory *self);

/**
 * @brief draws a given inventory to screen
 * @param self inventory to draw to screen
*/
void inventory_draw(Inventory *self);

/**
 * @brief frees an inventory from inventory list and clears slots
 * @param self inventory to be freed
*/
void inventory_free(Inventory *self);

#endif
