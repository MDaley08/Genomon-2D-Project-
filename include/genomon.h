#ifndef __GENOMON_H__
#define __GENOMON_H__

#include "gfc_vector.h"
#include "entity.h"

/**
 * @brief creates a new instance of specified genomon, if entered name is valid a new instance of genomon created
 * @param geno which genomon is to be created
 * @param position where genomon will be spawned
 * @return returns a new genomon if successful, NULL if otherwise
*/
Entity *genomon_new(char *geno, Vector2D postion);

/**
 * @brief editing scrren for adjusting stats of genomon
 * @param genomon genomon to be edited
*/
void genomon_editor(Entity *geno);



#endif
