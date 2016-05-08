#ifndef COLLISIONDETECTOR_H_INCLUDED
#define COLLISIONDETECTOR_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include "EntitySubclass.h"
#include "NPC.h"

class CollisionDetector
{
private:
    std::vector<NPC*> npcs;
public:
    void addNPC(NPC npc);
    void checkPlayerCollisions(Character *c);
    void checkNPCCollisions();
};

#endif // COLLISIONDETECTOR_H_INCLUDED
