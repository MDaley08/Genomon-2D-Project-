#include "simple_logger.h"
#include "simple_json.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "genomon.h"

void genomon_draw(Entity *self){
    gf2d_sprite_draw(self->sprite,self->position,NULL,NULL,NULL,NULL,NULL,1);
}
void level_up(Entity *self){
    if(!self) return;
    if(self->level >= 50) return;
    self->level++;
    self->health += 10;
    self->energy += 2;
    self->experience = 0;
    self->exp_multiplier += 0.03;
    self->exp_to_level *= self->exp_multiplier;
    //TODO have more unique adjustments for increase to stats
}

void genomon_damage(Entity *self, Entity *inflictor, Uint16 damage){
    if(!(self && inflictor)) return;
    if(self->health > 0) return;
    self->health -= damage;
}

Entity *genomon_new(char *name, Vector2D position){
    SJson *json,*gjson;
    Entity *genomon;
    genomon = entity_new();
    if(!genomon){
        slog("genomon_new: unable to create genomon");
        return NULL;
    }
    json = sj_load("config/genomons.json");
    if (!json)
    {
        slog("failed to load json file (%s) for genomon data", "config/genomons.json");
        entity_free(genomon);
        return NULL;
    }
    gjson = sj_object_get_value(json,name);
    if(!gjson){
        slog("failed to find genomon in %s genomon config file", "config/genomons.json");
        entity_free(genomon);
        sj_free(json);
        return NULL;
    }
    genomon->name = sj_get_string_value(sj_object_get_value(gjson,"name"));
    genomon->ent_type = GENOMON;
    genomon->level = 1;
    genomon->exp_multiplier = 1.0; //setting a hardcoded level 1 started multiplier, to be adjusted later
    genomon->exp_to_level = 200; // setting a hardcoded level 1 value, to be adjust later
    genomon->level_up = level_up;
    genomon->damage = genomon_damage;
    genomon->draw = genomon_draw;
    genomon->sprite = gf2d_sprite_load_all(sj_get_string_value(sj_object_get_value(gjson,"sprite")),32,32,2,0);
    sj_get_integer_value(sj_object_get_value(gjson,"health"), &genomon->health);
    sj_get_integer_value(sj_object_get_value(gjson,"energy"), &genomon->energy);
    sj_get_integer_value(sj_object_get_value(gjson,"speed"), &genomon->speed);
    sj_get_integer_value(sj_object_get_value(gjson,"strength"), &genomon->strength);
    sj_get_integer_value(sj_object_get_value(gjson,"intellect"), &genomon->intellect);
    vector2d_copy(genomon->position,position);
    
    sj_free(json);
    return genomon;
}

void genomon_editor(Entity *genomon){
    Sprite *background;
    

}
