#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "gfc_vector.h"
#include "gfc_types.h"
#include "gf2d_sprite.h"

typedef struct Entity_S
{
    Bool        _inUse;//denotes if an entity is in use of not
    Bool        hidden;
    Uint16      health;//mainly for genomon health
    Uint16      stamina;//mainly for genomon abilities
    Uint32      frame;
    Sprite      *sprite;
    Vector2D    position;

    void    (*think)(struct Entity_S *self);
    void    (*update)(struct Entity_S *self);
    void    (*free)(struct Entity_S *self);    
    void    *data; //any other data we'd like to include in our entity otherwise
} Entity;

/**
 * @brief allocates memory and initializes the entity system;
 * @param max_ent max number of entity to allocate within the system
*/
void entity_system_init(Uint16 max_ents);
/**
 * @brief creates a new entity "object"
*/
Entity *entity_new();
/**
 * @brief frees previously created system from memory
 * @param self entity to be freed
*/
void entity_free(Entity *self);

/**
 * @brief draws entity to screen
 * @param self entity to be drawn
*/
void entity_draw(Entity *self);
    
/**
 * @brief draws all entities to screen
*/
void entity_draw_all();

/**
 * @brief runs update function for all entities.
*/
void entity_update_all();


/**
 * @brief executes think function of a entity
 * @param self entity in question
*/
void entity_think(Entity *self);

/**
 * @brief executes think function for all entities
*/
void entity_think_all();


#endif
