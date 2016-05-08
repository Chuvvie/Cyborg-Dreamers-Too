#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "NPC.h"
#include "Map.h"

class AI
{
private:
    int move = 0;
    int willMoveNow;
public:
    void moveNow(NPC *npc, Map *map, int command);
};

#endif // AI_H_INCLUDED
