#include <SDL2/SDL_image.h>
#include "gf2d_graphics.h"
#include "inventory.h"

#define SLOT_SIZE 50
typedef struct 
{
    Uint16      max_inventories;
    Inventory   *inv_list;
}InventoryManager;

static InventoryManager  inventory_manager = {0};

void test_think(){
    slog("test");
}

void inventory_system_close(){
    int i;
    for(i = 0; i < inventory_manager.max_inventories; i++){
        inventory_free(&inventory_manager.inv_list[i]);
    }
    free(inventory_manager.inv_list);
    memset(&inventory_manager,0,sizeof(InventoryManager));
    slog("inventory system closed");
}

void inventory_system_init(Uint16 max_inventories){

    inventory_manager.inv_list = gfc_allocate_array(sizeof(Inventory),max_inventories);
    if(inventory_manager.inv_list == NULL){
        slog("inventory_system_init: unable to initialize inventory system, inventory_list not allocated");
        return;
    }
    inventory_manager.max_inventories = max_inventories;
    atexit(inventory_system_close);
    slog("inventory_system_init: inventory system initialized.");
}

Inventory *inventory_new(){
    int i;
    int x_offset;
    int y_offset;
    Inventory *inv;

    for(i = 0; i < inventory_manager.max_inventories; i++){
        if(inventory_manager.inv_list[i]._inUse)continue;
        inventory_manager.inv_list[i]._inUse = true;
        inv = &inventory_manager.inv_list[i];
    }
    if(!inv){
        slog("inventory_new: max inventories allocated, unable to allocate new inventory");
        return NULL;
    }

    inv->inv_rect.h = 370; // hardcoding inv size(mainly used for displayed inv limited to shop and player)
    inv->inv_rect.w = 370; // hardcoding inv size(mainly used for displayed inv limited to shop and player)
    inv->inv_rect.x = 300; //setting default to 0
    inv->inv_rect.y = 300; //setting default to 0
    inv->inv_tex =  IMG_LoadTexture(gf2d_graphics_get_renderer(),"images/inventory.png");


    x_offset = inv->inv_rect.x + 20; //hard coded space between each slot for offset
    y_offset = inv->inv_rect.y + 20; //hard coded space between each slot for offset
    for(i = 0; i < MAX_INV_SIZE; i++){
        //TODO setup proper initial allocation of inventory, we utilize buttons to create inv slots
        inv->inv_slots[i].button = button_new();
        inv->inv_slots[i]._inUse = false;
        inv->inv_slots[i].button->texture = IMG_LoadTexture(gf2d_graphics_get_renderer(),"images/slot.png");
        inv->inv_slots[i].button->button_rect.h = SLOT_SIZE;
        inv->inv_slots[i].button->button_rect.w = SLOT_SIZE;
        inv->inv_slots[i].button->button_rect.x = x_offset;
        inv->inv_slots[i].button->button_rect.y = y_offset;
        x_offset += 20 + SLOT_SIZE;
        if(x_offset >= (inv->inv_rect.x + inv->inv_rect.w)){
            x_offset = inv->inv_rect.x + 20;
            y_offset += SLOT_SIZE + 20;
        }
    }
    return inv;
}

void inventory_free(Inventory *self){
    if(!self) return;
    if(self->free){
        self->free(self);
    }
}

void inventory_draw(Inventory *self){
    int i;
    if(!self){
        slog("inventory_draw: not a valid inventory");
        return;
    }
    if(!self->inv_tex){
        slog("inventory_draw: inventory has no background texture");
        return;
    }
    SDL_RenderCopy(gf2d_graphics_get_renderer(), self->inv_tex, NULL, &self->inv_rect);
    for(i = 0; i  < MAX_INV_SIZE; i++){
        button_draw(self->inv_slots[i].button);
        button_interacted(self->inv_slots[i].button);
    }
}

void inventory_add_item(Item *item, Inventory *self){
    int i;
    if(!self)return;
    if(!item)return;
    for(i = 0; i < MAX_INV_SIZE; i++){
        if(self->inv_slots[i]._inUse)continue;
        self->inv_slots[i].item = item;
        if(item->use)self->inv_slots[i].button->think = item->use;
        if(item->texture){
            slog("inventory_add_item: item has no texture");
            return;
        }
        item->rect = self->inv_slots[i].button->button_rect;
        return;
    }
    slog("item_add: inventory has no more free slots");
    return;
}

