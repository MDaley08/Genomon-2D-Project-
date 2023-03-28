#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gfc_input.h"
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "entity.h"
#include "mouse.h"
#include "button.h"
#include "player.h"
#include "item.h"
#include "inventory.h"
#include "camera.h"
#include "level.h"


static int close = 0;
static const Uint8 *keys;
Entity *player;

void game_loop();
void combat_loop();
void *use(Entity *self);

int main(int argc, char * argv[])
{
    /*variable declarations*/
    Vector3D cursor_color;
    cursor_color = vector3d(0,200,0);

    /*program initializtion*/
    init_logger("gf2d.log",true);
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize("Genomon",WINDOW_WIDTH,WINDOW_HEIGHT,WINDOW_WIDTH,WINDOW_HEIGHT,vector4d(0,0,0,255),0);
    gf2d_graphics_set_frame_delay(15);
    inventory_system_init(50);
    gf2d_sprite_init(1024);
    entity_system_init(1024);
    button_system_init(256);
    gfc_input_init("gfc/sample_config/input.cfg");
    mouse_init(vector2d(25,25), cursor_color);
    player = player_new(vector2d(100,100));

    /*demo setup*/

    /*main game loop*/
    game_loop();
    slog("---==== END ====---");
    return 0;
}


void game_loop(){
    Vector2D cam;
    Sprite      *background;
    Inventory   *inv;
    Item        *item;
    Level       *level;

    level = level_load("config/test.level");
    level_set_active_level(level);

    background = gf2d_sprite_load_image("images/backgrounds/background.png");

    item = item_new();
    inv = inventory_new();
    item->texture = IMG_LoadTexture(gf2d_graphics_get_renderer(),"images/dire-hit.png");

    inventory_add_item(item,inv);

    while(!close)
    {
        SDL_PumpEvents();
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

        /*think functions here*/
        entity_think_all();
        player_think();


        /*update things here*/
        mouse_update();
        button_update_all();
        entity_update(player);

        player_update();
        camera_world_snap();


        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //Backgrounds
            gf2d_sprite_draw_image(background,vector2d(0,0));
            level_draw(level);
            //Entities
            player_draw();
            //UI elements
            //inventory_draw(inv);

            //mouse 
            mouse_draw();
            if(keys[SDL_SCANCODE_0]) combat_loop();

        gf2d_graphics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])close = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
}

void combat_loop(){
    int done = 0;
    Sprite      *background;
    background = gf2d_sprite_load_image("images/backgrounds/battlefield_01.png");
    Entity *geno;
    geno = genomon_new("togekiss", vector2d(40,40));
    while(!done){
        SDL_PumpEvents();
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        //think functions

        //update functions
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //Background
            gf2d_sprite_draw_image(background,vector2d(0,0));
            //ents
            entity_draw(geno);

            //ui
            
            //mouse
            mouse_draw();
        gf2d_graphics_next_frame();

        if (keys[SDL_SCANCODE_1])done = 1; // exit condition
    }
}

/*eol@eof*/
