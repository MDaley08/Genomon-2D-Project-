#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "gfc_types.h"
#include "item.h"

const Uint8 MAX_INV_SIZE = 20;
typedef struct
{
    Bool    _inUse;
    Item    *item;
}InvSlot;

typedef struct
{
    InvSlot slots[MAX_INV_SIZE];
}Inventory;

#endif
