#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "gfc_vector.h"
#include "gfc_types.h"
#include "gfc_shape.h"
#include "gf2d_sprite.h"
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
    Uint8       frame;
    Vector2D    drawOffset;
    Vector2D    drawScale;
    Sprite      *sprite;

    //VARIBLES RELATED TO ENT PHYSICS
    Shape       shape;
    Vector2D    position;
    Vector2D    velocity;
    float       moveSpeed;

    void    (*damage)(struct Entity_S *self, struct Entity_S *inflictor, Uint16 damage); //how a entity takes damage
    void    (*think)(struct Entity_S *self);
    void    (*update)(struct Entity_S *self);
    void    (*level_up)(struct Entity_S *self);
    void    (*draw)(struct Entity_S *self);
    void    (*free)(struct Entity_S *self);

    //VARIABLES SPECIFIC TO GENOMONS
    Uint8       level; //max level set at 100, though there is no hard cap to enforce this.
    Uint16      experience;// experience taken to level is a sliding scale that will occur muliticatively;
    Uint16      exp_to_level; //experience needed to reach next level
    float       exp_multiplier;
    Uint16      health;
    Uint16      energy;
    Uint8       speed;
    Uint8       strength;
    Uint8       intellect;
    Skill       skill_list[4]; // skill container for Genomon, will be limited to 4
    
    //VARIABLES SPECIFIC TO PLAYER/SHOPKEEPER/NPC
    //Team                 *team;//Genomon currently in the players team

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

/**
 * @brief given an entity get its shape in world space
 * @param ent the entity to check
 * @return a shape where its position is set to the world position
 */
Shape entity_get_shape(Entity *self);

/**
 * @brief given an entity get its shape in world space where it will be after it moves
 * @param ent the entity to check
 * @return a shape where its position + velocity is set to the world position
 */
Shape entity_get_shape_after_move(Entity *self);


#endif
