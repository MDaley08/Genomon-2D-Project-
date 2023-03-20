#ifndef __GENOMON_H__
#define __GENOMON_H__

#include "entity.h"

/**
 * @brief creates a new instance of specified genomon, if entered name is valid a new instance of genomon created
 * @param genomon which genomon is to be created
 * @param position where genomon will be spawned
 * @return returns a new genomon if successful, NULL if otherwise
*/
Entity *genomon_new(char *genomon, Vector2D postion;);



#endif
