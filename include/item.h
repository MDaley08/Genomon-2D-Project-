#ifndef __ITEM_H__
#define __ITEM_H__

#include <SDL2/SDL.h>
#include "simple_logger.h"
#include "gfc_types.h"
#include "entity.h"

typedef struct Item_S
{
    char            *name;
    Uint8           max_count;
    Uint8           current_count;
    SDL_Texture     *texture;
    SDL_Rect        rect;

    void            (*use)(Entity *target);
}Item;
/**
 * @brief removes a item from memory
 * @param self item to be freed
*/
void item_free(Item *self);
/**
 * @brief creates a new instance of Item struct
 * @return item that was created;
*/
Item *item_new();
/**
 * @brief executes use function applying item's use function to a entity.
 * @param self item to be used.
 * @param target entity to use item upon.
*/
void item_use(Item *self, Entity *target);

/**
 * @brief draws item to screen
 * @param self item to draw
*/
void item_draw(Item *self);

//TODO figure out why item image not loading.


#endif
