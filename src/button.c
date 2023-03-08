#include "simple_logger.h"
#include "gfc_types.h"
#include "gf2d_graphics.h"
#include "mouse.h"
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
    if(self->texture) SDL_DestroyTexture(self->texture);
    memset(&self,0,sizeof(self));
}

void button_draw(Button *self){
    if(!self)return;
    if(!self->texture){
        slog("button_draw: unable to draw button");
        return;
    } 
    if(!self->hidden) SDL_RenderCopy(gf2d_graphics_get_renderer(), self->texture, NULL, &self->button_rect);
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

void button_update(Button *self){
    if(!self->update)return;
    self->update(self);
}

void button_update_all(){
    int i;
    for(i = 0; i < button_manager.max_buttons; i++){
        if(!button_manager.button_list[i]._inUse) continue;
        button_update(&button_manager.button_list[i]);
    }
}

void button_interacted(Button *self){
    if(!self) return;
    if(mouse_in_rect(&self->button_rect)){
        self->selected = true;
        SDL_SetTextureAlphaMod(self->texture,255);
        if(mouse_button_pressed(0)){
            button_think(self);
        }
    }
    else{
        SDL_SetTextureAlphaMod(self->texture, 180);
        self->selected = false;
    }
}
/*eol@eof*/
