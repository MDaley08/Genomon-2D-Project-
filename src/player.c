#include "player.h"
#include "simple_logger.h"
#include "gfc_input.h"

static Player player = {0};

void player_movement(float move_speed);

void player_free(){
    entity_free(&player.ent_info);
    memset(&player,0,sizeof(player));
}

Player *player_new(Vector2D position){
    if(player.ent_info._inUse){
        slog("player_new: unable to create a new player object while one exists");
        return NULL;
    }
    player.ent_info._inUse = true;
    player.ent_info.position = position;
    player.ent_info.sprite = gf2d_sprite_load_image("images/health_bar.png");
    return &player;
}

void player_think(){
    float move_distance = 0.7;

    if(gfc_input_key_pressed("w"))player.ent_info.position.y -= move_distance;
    else if(gfc_input_key_pressed("a"))player.ent_info.position.x -= move_distance;
    else if(gfc_input_key_pressed("s"))player.ent_info.position.y += move_distance;
    else if(gfc_input_key_pressed("d"))player.ent_info.position.x += move_distance;
}

void player_update(){
}

void player_draw(){
    if(!player.ent_info.sprite){
        slog("player_draw: unable to draw player");
        return;
    }
    if(!player.ent_info.hidden)gf2d_sprite_draw(player.ent_info.sprite,player.ent_info.position,NULL,NULL,NULL,NULL,NULL,player.ent_info.frame);
}

/*eol@eof*/
