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
    std::vector<Character*> chars;
public:
    void addNPC(NPC* npc);
    void addCharacter(Character* c);
    void checkPlayerCollisions(Character *c, sf::Vector2f next);
    void checkNPCCollisions();
    bool breaker = false;
};

#endif // COLLISIONDETECTOR_H_INCLUDED
