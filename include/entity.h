#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gfc_vector.h"
#include "gfc_types.h"
#include "skill.h"

typedef enum {
    GENOMON
}EntityType;

typedef struct Entity_S
{
    Bool        _inUse;//denotes if an entity is in use of not
    char        *name;
    EntityType  ent_type;
    Bool        hidden;
    Uint32      frame;
    SDL_Texture *texture;
    SDL_Rect    rect;
    Vector2D    position;
    Vector2D    velocity;

    void    (*damage)(struct Entity_S *self, struct Entity_S *inflictor, Uint16 damage); //how a entity takes damage
    void    (*think)(struct Entity_S *self);
    void    (*update)(struct Entity_S *self);
    void    (*level_up)(struct Entity_S *self);
    void    (*draw)(struct Entity_S *self, int side);// side specifies front of back, 0 for front, 1 for back
    void    (*free)(struct Entity_S *self);

    //VARIABLES SPECIFIC TO GENOMONS
    Uint8       level; //max level set at 100, though there is no hard cap to stop this.
    Uint16      experience;// experience taken to level is a sliding scale that will occur muliticatively;
    Uint16      exp_to_level; //experience needed to reach next level
    float       exp_multiplier;
    Uint16      health;
    Uint16      energy;
    Uint8       speed;
    Uint8       strength;
    Uint8       intellect;
    Skill       skill_list[4]; // skill container for Genomon, will be limited to 4
    
    void    *data; //any other data we'd like to include in our entity otherwise
}Entity;

/**
 * @brief allocates memory and initializes the entity system;
 * @param max_ent max number of entity to allocate within the system
*/
void entity_system_init(Uint16 max_ents);
/**
 * @brief creates a new entity "object"
 * @return Entity object if successful, NULL if error occurs
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
 * @brief executes the update function 
 * @param self entity in question
*/
void entity_update(Entity *self);

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
