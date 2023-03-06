#ifndef __TEAM_H__
#define __TEAM_H__

#include "gfc_types.h"
#include "entity.h"

const Uint8 MAX_TEAM_SIZE = 4;

typedef struct
{
    Bool    _inUse;
    Entity  *genomon;
}TeamSlot;

typedef struct 
{
    TeamSlot    slots[MAX_TEAM_SIZE];
}Team;

/**
 * @brief frees a team object from memory
 * @param team team to be freed
*/
void team_free(Team *team);

/**
 * @brief creates a new team object.
 * @return returns object if successful or NULL if unsuccessful/errof
*/
Team *team_new();

/**
 * @brief adds a genomon to a team putting it in a specific slot
 * @param team team to add genomon to
 * @param slot_num the slot to put the genomon in
 * @param genomon the genomon to add the team to
*/
void team_add(Team *team, Uint8 slot_num, Entity *genomon);



#endif
