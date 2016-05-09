#include "CollisionDetector.h"
#include <vector>
#include <iterator>
#include <iostream>
#include <SFML/Graphics.hpp>

void CollisionDetector::addNPC(NPC* npc)
{
    npcs.push_back(npc);
}

void CollisionDetector::checkNPCCollisions()
{
    for (std::vector<NPC*>::iterator i = npcs.begin(); i != npcs.end(); ++i) {
		for (std::vector<NPC*>::iterator j = i; j != npcs.end(); ++j) {
            sf::IntRect npc1((*i)->getPosition().x, (*i)->getPosition().y, 32, 32);
            sf::IntRect npc2((*j)->getPosition().x, (*j)->getPosition().y, 32, 32);
            if(npc1.intersects(npc2))
            {
                (*i)->isCollidingNow();
                (*j)->isCollidingNow();
                //std::cout << "NPC colliding!" <<std::endl;
            }
            else
            {
                (*i)->isNotColliding();
                (*j)->isNotColliding();
            }
		}
	}
}

void CollisionDetector::checkPlayerCollisions(Character *c, sf::Vector2f next)
{
    sf::IntRect chars(c->getPosition().x + next.x, c->getPosition().y + next.y, 32, 32);
    for (std::vector<NPC*>::iterator i = npcs.begin(); i != npcs.end(); ++i) {
            sf::IntRect npc1((*i)->getPosition().x, (*i)->getPosition().y, 32, 32);
            if(chars.intersects(npc1))
            {
               c->isCollidingNow();
               (*i)->isCollidingNow();

               std::cout << "colliding!" <<std::endl;
            }
            else
            {
                c->isNotColliding();
                (*i)->isNotColliding();
                //std::cout << "not colliding!" <<std::endl;
            }
	}
}
