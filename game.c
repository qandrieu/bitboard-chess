#include "game.h"

void init_player(Shift *player, char *hit)
{
    player->from = GetPosition(hit[0],hit[1]);
    player->to = GetPosition(hit[2],hit[3]);
}

int GetPosition(char file, char rank)
{
        return toupper(file)-65 +(rank-48-1)*8;
}
