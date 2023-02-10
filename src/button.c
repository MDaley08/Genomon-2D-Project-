#include "simple_logger.h"
#include "gfc_types.h"
#include "gf2d_graphics.h"
#include "button.h"



typedef struct 
{
    Uint16 max_buttons;
    Button *button_list;
    
}ButtonManager;

static ButtonManager button_manager = {0};

void button_close(){
    int i;
    for(i = 0; i < button_manager.max_buttons; i++){
        button_free(&button_manager.button_list[i]);
    }
    free(button_manager.button_list);
    memset(&button_manager,0,sizeof(button_manager));
    slog("button_close: button system closed");
}

void button_system_init(Uint16 max_buttons){
    button_manager.button_list = gfc_allocate_array(sizeof(Button),max_buttons);
    if(button_manager.button_list == NULL){
        slog("button_system_init: unable to initialize button system, button_list not allocated");
        return;
    }
    button_manager.max_buttons = max_buttons;
    slog("button_system_init: button system initialized.");
    atexit(button_close);
}

Button *button_new(){
    int i;
    for(i = 0; i < button_manager.max_buttons; i++){
        if (button_manager.button_list[i]._inUse)continue;
        button_manager.button_list[i]._inUse = true;
        return &button_manager.button_list[i];
    }
    slog("button_new: max buttons allocated, unable to allocate new button");
    return NULL;
}

void button_free(Button *self){
    if(!self){
        slog("button_free: cannot free unalocated button");
        return;
    }
    memset(&self->button_rect,0,sizeof(self->button_rect));
    memset(&self->think,0,sizeof(self->think));
    memset(&self->text,0,sizeof(self->text));
    if(self->sprite) gf2d_sprite_delete(self->sprite);
}

void button_draw(Button *self){
    if(!self->sprite){
        slog("button_draw: unable to draw button");
        return;
    } 
    if(!self->hidden)gf2d_sprite_draw_image(self->sprite, self->position);
}

void button_draw_all(){
        int i;
    for(i = 0; i < button_manager.max_buttons; i++){
        if((!button_manager.button_list[i]._inUse) || button_manager.button_list[i].hidden ) continue;
        button_draw(&button_manager.button_list[i]);
    }
}

void button_think(Button *self){
    if(!self->think)return;
    self->think(self);
}

void button_think_all(){
    int i;
    for(i = 0; i < button_manager.max_buttons; i++){
        if(!button_manager.button_list[i]._inUse) continue;
        button_think(&button_manager.button_list[i]);
    }
}

