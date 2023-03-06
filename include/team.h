#ifndef __TEAM_H__
#define __TEAM_H__

#include "gfc_types.h"
#include "entity.h"

typedef struct
{
    Bool    _inUse;
    Entity  *genomon;
}Slot;

typedef struct 
{
    Slot    slots[4];
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



#endif
