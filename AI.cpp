#include <iostream>
#include "AI.h"
#include <time.h>
#include <random>
#include <exception>

sf::Clock clock3;
void AI::moveNow(NPC *npc, Map* map)
{
    srand(time(NULL));
    float nextmove = clock3.getElapsedTime().asSeconds();
    if(nextmove >= 1)
    {
        willMoveNow = rand() % 10 + 1;
        clock3.restart();
    }
    else
    {
        willMoveNow == 0;
    }
        if(willMoveNow >= 0 && willMoveNow <= 4)
        {
            if(willMoveNow == 1)
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
            else if(willMoveNow == 2)
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
            else if(willMoveNow == 3)
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
            else if(willMoveNow == 4)
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


