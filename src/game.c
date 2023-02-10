#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "entity.h"
#include "mouse.h"
#include "button.h"

static int done = 0;
static const Uint8 *keys;

void game_loop();
void combat_loop();
void think(Button *self);

int main(int argc, char * argv[])
{
    /*variable declarations*/
    Vector3D cursor_color;
    
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize("Genomon",1280,768,1280,768,vector4d(0,0,0,255),0);
    gf2d_graphics_set_frame_delay(15);
    gf2d_sprite_init(1024);
    entity_system_init(1024);
    button_system_init(256);
    cursor_color = vector3d(0,200,0);
    mouse_init(vector2d(25,25), cursor_color);

    /*demo setup*/

    /*main game loop*/
    game_loop();
    slog("---==== END ====---");
    return 0;
}

void game_loop(){
    Sprite  *background;
    Entity *test;
    Button *test2;
    test = entity_new();
    test->position = vector2d(0,0);
    background = gf2d_sprite_load_image("images/backgrounds/background.png");
    test2 = button_new();
    test2->sprite= gf2d_sprite_load_image("images/health_bar.png");
    test2->position = vector2d(10,100);
    test2->think = think;
    test2->button_rect.h = 100;
    test2->button_rect.w = 100;
    test2->button_rect.x = 0;
    test2->button_rect.y = 0;

    while(!done)
    {
    
        //if(mouse_in_rect(test)) mouse_color(vector3d(0,0,200));
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

        /*think functions here*/
        //entity_think_all();
        button_think_all();
        /*update things here*/
        mouse_update();
        //SDL_GetMouseState(&mx,&my);


        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //Backgrounds
            gf2d_sprite_draw_image(background,vector2d(0,0));
            
            //Entities
            entity_draw_all();
            //UI elements
            button_draw_all();
            mouse_draw();
            SDL_RenderDrawRect(gf2d_graphics_get_renderer(),&test2->button_rect);
        gf2d_graphics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
}
void combat_loop(){
    if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
}

void think(Button *self){
    if((mouse_in_rect(&self->button_rect))){
        self->position.x += 0.5;
        self->position.y += 0.5;
    }
}


/*eol@eof*/
