#include "entity.h"
#include "simple_logger.h"

typedef struct 
{
    Uint16  max_ents;
    Entity  *entity_list;
}EntityManager;

static EntityManager entity_manager = {0};

void entity_system_close(){
    int i;
    for(i = 0; i < entity_manager.max_ents; i++){
        entity_free(&entity_manager.entity_list[i]);
    }
    free(entity_manager.entity_list);
    memset(&entity_manager,0,sizeof(EntityManager));
    slog("entity system closed");
}

void entity_system_init(Uint16 max_ents){
    entity_manager.entity_list = gfc_allocate_array(sizeof(Entity),max_ents);
    if(entity_manager.entity_list == NULL){
        slog("entity_system_init: unable to initialize entity system, entity_list not allocated");
        return;
    }
    entity_manager.max_ents = max_ents;
    atexit(entity_system_close);
    slog("entity_system_init: entity system initialized.");
}

Entity *entity_new(){
    int i;
    for(i = 0; i < entity_manager.max_ents; i++){
        if(entity_manager.entity_list[i]._inUse)continue;
        entity_manager.entity_list[i]._inUse = true;
        return &entity_manager.entity_list[i];
    }
    slog("entity_new: max ents allocated, unable to allocate new ent");
    return NULL;
}

void entity_free(Entity *self){
    if(!self){
        slog("entity_free: cannot free an un-alocated entity");
        return;
    }
    if(self->free){//checking if free variable of Entity is populated, if it is run code 
        self->free(self);
    }
    gf2d_sprite_delete(self->sprite);
}

void entity_draw(Entity *self){
    if(!self->sprite)return;
    if(!self->hidden)gf2d_sprite_draw(self->sprite,self->position,NULL,NULL,NULL,NULL,NULL,self->frame);
}

void entity_draw_all(){
    int i;
    for(i = 0; i < entity_manager.max_ents; i++){
        if((!entity_manager.entity_list[i]._inUse) || entity_manager.entity_list[i].hidden ) continue;
        entity_draw(&entity_manager.entity_list[i]);
    }
}
void entity_think(Entity *self){
    if(!self->think)return;
    self->think(self);
}

void entity_think_all(){
    int i;
    for(i = 0; i < entity_manager.max_ents; i++){
        if(!entity_manager.entity_list[i]._inUse) continue;
        entity_think(&entity_manager.entity_list[i]);
    }
}

void entity_update(Entity *self){
    if(!self->update)return;
    self->update(self);
}

void entity_update_all(){
    int i;
    for(i = 0; i < entity_manager.max_ents; i++){
        if(!entity_manager.entity_list[i]._inUse) continue;
        entity_update(&entity_manager.entity_list[i]);
    }
}
/*eol@eof*/
