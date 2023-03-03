#include "item.h"
#include "simple_logger.h"

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
    item->use = NULL;
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

/*eol@eof*/
