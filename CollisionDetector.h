#ifndef COLLISIONDETECTOR_H_INCLUDED
#define COLLISIONDETECTOR_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include "EntitySubclass.h"
#include "NPC.h"
#include "Entity.h"


class CollisionDetector
{
private:
    std::vector<NPC*> npcs;
    std::vector<Character*> chars;
    std::vector<Entity*> entities;
public:
    void addNPC(NPC* npc);
    void addCharacter(Character* c);
    void addEntity(Entity *e);
    void checkEntityCollisions(Entity *c);
    void checkNPCCollisions();
};

#endif // COLLISIONDETECTOR_H_INCLUDED
