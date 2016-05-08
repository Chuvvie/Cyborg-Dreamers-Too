#include "CollisionDetector.h"
#include <vector>
#include <iterator>
#include <iostream>
#include <SFML/Graphics.hpp>

void CollisionDetector::addNPC(NPC npc)
{
    npcs.push_back(&npc);
}

void CollisionDetector::checkNPCCollisions()
{
    for (std::vector<NPC*>::iterator i = npcs.begin(); i != npcs.end(); ++i) {
		for (std::vector<NPC*>::iterator j = i; j != npcs.end(); ++j) {
            sf::IntRect npc1((*i)->getPosition().x * 32, (*i)->getPosition().y * 32, 32, 32);
            sf::IntRect npc2((*j)->getPosition().x * 32, (*j)->getPosition().y * 32, 32, 32);
            if(npc1.intersects(npc2))
            {
                (*i)->setFace((*i)->getDirection());
                (*j)->setFace((*j)->getDirection());
            }
		}
	}
}

void CollisionDetector::checkPlayerCollisions(Character *c)
{
    sf::IntRect chars(c->getIndexPosition().x * 32, c->getPosition().y * 32, 32, 32);
    for (std::vector<NPC*>::iterator i = npcs.begin(); i != npcs.end(); ++i) {
            sf::IntRect npc1((*i)->getPosition().x * 32, (*i)->getPosition().y * 32, 32, 32);
            if(chars.intersects(npc1))
            {
               c->setFace(c->getDirection());
               (*i)->setFace((*i)->getDirection());
            }
	}
}
