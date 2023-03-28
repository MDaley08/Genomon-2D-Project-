#include "simple_logger.h"
#include "gf2d_graphics.h"
#include "gf2d_draw.h"
#include "camera.h"
#include "level.h"
#include "entity.h"

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
    slog("entity_system_init: entity system initialized.");
    atexit(entity_system_close);
}

Entity *entity_new(){
    int i;
    for(i = 0; i < entity_manager.max_ents; i++){
        if(entity_manager.entity_list[i]._inUse)continue;
        entity_manager.entity_list[i]._inUse = true;
        entity_manager.entity_list[i].drawScale = vector2d(1,1);
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
    if(self->sprite)gf2d_sprite_free(self->sprite);
    memset(self,0,sizeof(Entity));
}

void entity_draw(Entity *self){
    Vector2D drawPosition, camera_offset;
    if(!self)return;
    if(!self->sprite)return;
    if(self->hidden)return;
    if(self->draw){
        self->draw(self);
        return;
    }
    camera_offset = camera_get_draw_offset();
    vector2d_add(drawPosition,self->position,camera_offset);
    gf2d_sprite_draw(self->sprite,drawPosition,&self->drawScale,&self->drawOffset,NULL,NULL,NULL,self->frame);
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
    if (level_shape_clip(level_get_active_level(),entity_get_shape_after_move(self)))
    {
        //our next position is a hit, so don't move
        return;
    }
    vector2d_add(self->position,self->position,self->velocity);
}

void entity_update_all(){
    int i;
    for(i = 0; i < entity_manager.max_ents; i++){
        if(!entity_manager.entity_list[i]._inUse) continue;
        entity_update(&entity_manager.entity_list[i]);
    }
}

Shape entity_get_shape_after_move(Entity *self){
    Shape shape = {0};
    if (!self)return shape;
    gfc_shape_copy(&shape,self->shape);
    gfc_shape_move(&shape,self->position);
    gfc_shape_move(&shape,self->velocity);
    return shape;
}

Shape entity_get_shape(Entity *self)
{
    Shape shape = {0};
    if (!self)return shape;
    gfc_shape_copy(&shape,self->shape);
    gfc_shape_move(&shape,self->position);
    return shape;
}


/*eol@eof*/
