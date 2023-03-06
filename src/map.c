#include "stdio.h"
#include "stdlib.h"
#include "map.h"



static Map map = {0};

void map_close();

void map_init();

// void map_load(char *tilemap, char *tileset){
//     FILE *map_file;
//     int i;
//     int j;
//     char *c; //input char from file

//     map_file = fopen(tilemap, "r");
//     while((c = fgetc(map_file))){
//         while(c != '/n'){
//             map.map_grid[i][j] = atoi(c);
//         }
//         j++;
//         i++;
//     }


// }

void map_draw();

/*eol@eof*/
