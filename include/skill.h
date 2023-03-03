#ifndef __SKILL_H__
#define __SKILL_H__

#include "gfc_types.h"
#include "entity.h"

typedef struct Skill_S
{
    char    *name;
    Uint8   energy_cost; //cost to use a skill;
    Uint8   skill_charge; //one is gained per round, each skill takes x amount to use

    void    (*cast)(struct Skill_S *self);// effect to occur when casted.    
}Skill;


#endif
