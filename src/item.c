#include "simple_logger.h"
#include "gf2d_graphics.h"
#include "item.h"

void item_free(Item *self){
    if(!self)return;
    free(self->name);
    if(self->texture){
        SDL_DestroyTexture(self->texture);
    }
    free(self);
}
Item *item_new(){
    Item *item;
    item = malloc(sizeof(*item));
    if(!item){
        slog("item_new: unable to create item.");
        return NULL;
    }
    item->name = NULL;
    item->texture = NULL;
    item->current_count = 1;
    item->max_count = 99;
    return item;
}

void item_use(Item *self, Entity *target){
    if(!self) return;
    if(!target) return;
    if(!self->use){
        slog("item_use: item has no use function");
        return;
    }
    if(self->current_count <= 0){
        slog("item_use: not enough of this item to be used");
        return;
    }
    self->use(target);
    self->current_count--;
    if(self->current_count <= 0) item_free(self);
}

void item_draw(Item *self){
    if(!self)return;
    if(!self->texture){
        slog("item_draw: unable to draw item");
        return;
    } 
    SDL_RenderCopy(gf2d_graphics_get_renderer(), self->texture, NULL, &self->rect);
}

/*eol@eof*/
