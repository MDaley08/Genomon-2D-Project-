#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"
#include "genomon.h"
#include  "inventory.h"
#include "team.h"


/**
 * @brief frees created player object;
*/
void player_free();

/**
 * @brief creates new player object
 * @return returns player object if successful or NULL if it failed.
*/
Entity *player_new();

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

/**
 * @brief returns the current player object
 * @return returns players object if there is one, NULL if otherwise.
*/
Entity *player_get();

//Collision *player_collision(); this will be the how collisions will be handled for the player as we are creating it seperate from other ents

#endif
