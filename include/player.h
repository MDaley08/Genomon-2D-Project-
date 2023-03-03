#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"
#include "genomon.h"
#include "item.h"

typedef struct {
    struct Entity_S      ent_info;
    Entity               team[4];//Genomon currently in the players team
    Item                 *inventory; //handles all items in game and creation of iventory
    // Dex       *pokedex;   utilizing pokedex as placeholder this will hold information on all of discovered/caught mon.
    // Genomon   *storage;   all the Genomon the player has caught.
}Player;

/**
 * @brief frees created player object;
*/
void player_free();

/**
 * @brief creates new player object
 * @return returns player object if successful or NULL if it failed.
*/
Player *player_new();

/**
 * @brief performs think sequence for plyaer(how to handle input from world)
*/
void player_think();

/**
 * @brief draws player object to screen.
*/
void player_draw();
/**
 * @brief updates player data each frame.
*/
void player_update();

//Collision *player_collision(); this will be the how collisions will be handled for the player as we are creating it seperate from other ents

#endif
