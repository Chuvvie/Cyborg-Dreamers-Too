#include <iostream>
#include "AI.h"
#include <time.h>
#include <random>
#include <exception>

void AI::moveNow(NPC *npc, Map* map, int command)
{

        if(command >= 0 && willMoveNow <= 4)
        {
            if(command == 1)
            {
                sf::Vector2i next = npc->getIndexPosition() + sf::Vector2i(0, -1);
                Tile* tile = map->getTile(next.y, next.x);
                if(tile->isPassable())
                {
                    npc->setDirection(Movement::UP);
                    move = 1;
                }
                //npc->setDirection(Movement::UP);
                else
                {
                    npc->setFace(Movement::UP);
                }
            }
            else if(command == 2)
            {
                sf::Vector2i next = npc->getIndexPosition() + sf::Vector2i(0, 1);
                Tile* tile = map->getTile(next.y, next.x);
                if(tile->isPassable())
                {
                    npc->setDirection(Movement::DOWN);
                    move = 1;
                }
                //npc->setDirection(Movement::UP);
                else
                {
                    npc->setFace(Movement::DOWN);
                }
            }
            else if(command == 3)
            {
                sf::Vector2i next = npc->getIndexPosition() + sf::Vector2i(1, 0);
                Tile* tile = map->getTile(next.y, next.x);
                if(tile->isPassable())
                {
                    npc->setDirection(Movement::RIGHT);
                    move = 1;
                }
                //npc->setDirection(Movement::UP);
                else
                {
                    npc->setFace(Movement::RIGHT);
                }
            }
            else if(command == 4)
            {
                sf::Vector2i next = npc->getIndexPosition() + sf::Vector2i(-1, 0);
                Tile* tile = map->getTile(next.y, next.x);
                if(tile->isPassable())
                {
                    npc->setDirection(Movement::LEFT);
                    move = 1;
                }
                //npc->setDirection(Movement::UP);
                else
                {
                    npc->setFace(Movement::LEFT);
                }
            }
        }
        if(move == 1)
        {
            sf::Vector2f lastPos = npc->getPosition();
            if(npc->getDirection()==Movement::DOWN) {
            npc->setPosition(sf::Vector2f(0, 4));
            } else if(npc->getDirection()==Movement::LEFT) {
                npc->setPosition(sf::Vector2f(-4, 0));
            } else if(npc->getDirection()==Movement::RIGHT) {
                npc->setPosition(sf::Vector2f(4, 0));
            } else if(npc->getDirection()==Movement::UP) {
                npc->setPosition(sf::Vector2f(0, -4));
            }
            move = 0;
        }
}


