#include "CollisionDetector.h"
#include <vector>
#include <iterator>
#include <iostream>
#include <SFML/Graphics.hpp>

void CollisionDetector::addNPC(NPC* npc)
{
    npcs.push_back(npc);
}

void CollisionDetector::addCharacter(Character *c)
{
    chars.push_back(c);
}

void CollisionDetector::addEntity(Entity *e)
{
    entities.push_back(e);
}

void CollisionDetector::checkEntityCollisions(Entity *c)
{
    int ctr = 0;
    sf::Vector2f next(0, 0);
    switch(c->getDirection())
    {
        case Movement::UP: next.y = -6;
            break;
        case Movement::DOWN: next.y = 6;
            break;
        case Movement::LEFT: next.x = -6;
            break;
        case Movement::RIGHT: next.x = 6;
            break;
    }
    sf::IntRect chars(c->getPosition().x + next.x, c->getPosition().y + next.y, 32, 32);
    for (std::vector<Entity*>::iterator i = entities.begin(); i != entities.end(); ++i)
     {
            if(c->getPosition() != (*i)->getPosition())
            {
                sf::IntRect npc1((*i)->getPosition().x, (*i)->getPosition().y, 32, 32);
                if(chars.intersects(npc1))
                {
                    ctr++;
                    if(c->getType() == 1)c->setCostume((*i)->getCostume());
                    if(c->getType() == 1)c->setTarget((*i));
                    break;
                }
                else
                {
                    if(c->getType() == 1)c->setCostume(0);
                    if(c->getType() == 1)c->setTarget(nullptr);
                }
            }
	}
	if(ctr > 0)
    {
        c->isCollidingNow();
    }
    else
    {
        c->isNotColliding();
    }
}
