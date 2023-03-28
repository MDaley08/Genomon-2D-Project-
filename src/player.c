#include "simple_logger.h"
#include "gfc_input.h"
#include "gf2d_graphics.h"
#include "camera.h"
#include "level.h"
#include "player.h"


static Entity player = {0};

void player_free(){
    memset(&player,0,sizeof(player));
}

Entity *player_new(Vector2D position){
    if(player._inUse)player_free();

    player._inUse = true;
    player.moveSpeed = 2; //putting a base value of 1 for speed
    player.drawOffset = vector2d(16,16);
    player.drawScale = vector2d(0.5,0.5);
    player.shape = gfc_shape_rect(player.position.x,player.position.y,60,60);
    player.sprite = gf2d_sprite_load_all("images/player.png",128,128,4,0);
    vector2d_copy(player.position,position);
    return &player;
}

void player_think(){

    if(gfc_input_key_pressed("w")){
        player.velocity.y -= player.moveSpeed;
        player.frame = 0;
    }
    else if(gfc_input_key_pressed("a")){
        player.velocity.x -= player.moveSpeed;
        player.frame = 2;
    }
    else if(gfc_input_key_pressed("s")){
        player.velocity.y += player.moveSpeed;
        player.frame = 1;
    }
    else if(gfc_input_key_pressed("d")){
        player.velocity.x += player.moveSpeed;
        player.frame = 3;
    }
    else
    {
          vector2d_clear(player.velocity);
    }

    vector2d_set_magnitude(&player.velocity,player.moveSpeed);

    camera_center_at(player.position);
}

void player_update(){
    if(level_shape_clip(level_get_active_level(),entity_get_shape_after_move(&player))){
        return;
    }
    vector2d_add(player.position,player.position,player.velocity);
}

void player_draw(){
    entity_draw(&player);
}

Entity *player_get(){
    if(player._inUse)return &player;
    return NULL;
}


/*eol@eof*/
