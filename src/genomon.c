#include "simple_logger.h"
#include "genomon.h"

void *level_up(Entity *self){
    if(!self) return;
    if(!self->level >= 50) return;
    self->level++;
    self->health += 10;
    self->energy += 2;
    self->experience = 0;
    self->exp_multiplier += 0.03;
    self->exp_to_level *= self->exp_multiplier;
    //TODO have more unique adjustments for increase to stats
}

void *genomon_damage(Entity *self, Entity *inflictor, Uint16 damage){
    if(!(self && inflictor)) return;
    if(self->health > 0) return;
    self->health -= damage;
}

Entity *genomon_new(){
    //TODO convert to set values utilizing a json.
    Entity *genomon;
    if(!genomon){
        slog("genomon_new: unable to create genomon");
        return NULL;
    }
    genomon->ent_type = GENOMON;
    genomon->level = 1;
    genomon->health = 100;
    genomon->energy = 50;
    genomon->speed = 50;
    genomon->strength = 50;
    genomon->intellect = 50;
    genomon->exp_multiplier = 1.0;
    genomon->exp_to_level = 200;
    genomon->level_up = level_up;
    genomon->damage = genomon_damage;
    return genomon;
}

