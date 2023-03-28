#include "team.h"
#include "simple_logger.h"

void team_free(Team *team){
    int i;
    if(!team) return;
    for(i = 0; i < MAX_TEAM_SIZE; i++){
        entity_free(team->team_slots[i].genomon);
    }
}

Team *team_new(){
    Team *team;
    int i;
    team = gfc_allocate_array(sizeof(Team), 1);
    if(!team){
        slog("team_new: failed to allocate team");
        return NULL;
    }
    for(i = 0; i < MAX_TEAM_SIZE; i++){
        team->team_slots[i]._inUse = false;
        team->team_slots[i].genomon = NULL;
    }
    return team;
}

void team_add(Team *team, Uint8 slot_num, Entity *genomon){
    if(!team){
        slog("team_add: not a valid team to add to");
        return;
    }
    if(slot_num > MAX_TEAM_SIZE){
        slog("team_add: slot number out of range");
        return;
    }
    if(!genomon){
        slog("team_add: not a valid genomon");
        return;
    }
    if(genomon->ent_type != GENOMON){
        slog("team_add: not a valid entity type, needs to be genomon");
        return;
    }
    team->team_slots[slot_num].genomon = genomon;
    team->team_slots[slot_num]._inUse = true;
    //TODO add a location check and swap out genomon in slot either to inventory or to another slot in team if swapping slot
}


/*eol@eof*/
