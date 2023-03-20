#include "simple_logger.h"
#include "gfc_input.h"
#include "gf2d_graphics.h"
#include "player.h"
#include "camera.h"


static Player player = {0};

void player_free(){
    entity_free(&player.ent_info);
    memset(&player,0,sizeof(player));
}

Player *player_new(Vector2D position){
    if(player.ent_info._inUse){
        slog("player_new: unable to create a new player object while one exists");
        return NULL;
    }
    int i; // 4 sprites in image
    int sprite_size; // sprite sheet has 32 x 32 sprits 
    sprite_size = 128;

    player.ent_info._inUse = true;
    player.ent_info.rect.x = player.ent_info.position.x = position.x;
    player.ent_info.rect.y = player.ent_info.position.y = position.y;
    player.ent_info.rect.h = 64;
    player.ent_info.rect.w = 64;
    player.ent_info.texture = IMG_LoadTexture(gf2d_graphics_get_renderer(),"images/player.png");
    for(i = 0; i < 4; i++){//sprite sheet we are using has 4 sprites, hard coding
        player.frames[i].x =  i * sprite_size;
        player.frames[i].y = 0;
        player.frames[i].h = sprite_size;
        player.frames[i].w = sprite_size;
    }
    return &player;
}

void player_think(){
    float move_distance = 1;

    if(gfc_input_key_pressed("w")){
        player.ent_info.position.y -= move_distance;
        player.frame_num = 0;
    }
    else if(gfc_input_key_pressed("a")){
        player.ent_info.position.x -= move_distance;
        player.frame_num = 2;
    }
    else if(gfc_input_key_pressed("s")){
        player.ent_info.position.y += move_distance;
        player.frame_num = 1;
    }
    else if(gfc_input_key_pressed("d")){
        player.ent_info.position.x += move_distance;
        player.frame_num = 3;
    }
}

void player_update(){
    player.ent_info.rect.x = player.ent_info.position.x;
    player.ent_info.rect.y = player.ent_info.position.y;
}

void player_draw(){
    if(!player.ent_info.texture){
        slog("player_draw: unable to draw player");
        return;
    }
    if(!player.ent_info.hidden)SDL_RenderCopy(gf2d_graphics_get_renderer(),player.ent_info.texture,&player.frames[player.frame_num],&player.ent_info.rect);
}

Player *player_get(){
    if(player.ent_info._inUse)return &player;
    return NULL;
}


/*eol@eof*/
