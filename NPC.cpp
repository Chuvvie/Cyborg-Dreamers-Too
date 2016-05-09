#include "NPC.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <functional>
#include <thread>
#include "AI.h"

AI ai;
int command;
int moved = 0;
typedef enum
{
    Kid, Look, Go, Stop, Fast
} aitype1;

void NPC::randomCommand()
{
    while(true)
    {
        int a = rand() % 10 + 1;
        if(a != command)
        {
            command = a;
            break;
        }
    }
}

void NPC::isCollidingNow()
{
    isColliding = true;
}

void NPC::isNotColliding()
{
    isColliding = false;
}

bool NPC::colliding()
{
    return isColliding;
}

sf::Vector2i NPC::getSprite()
{
    return sf::Vector2i(spriteAction, spriteDir);
}

NPC::NPC(): direction(Movement::STAY), lastTic(0), spriteDir(0), spriteAction(0){
}

int NPC::getCostume()
{
    return currentCostume;
}

void NPC::setCostume(int a)
{
    currentCostume = a;
    switch(a)
    {
        case 1:spriteSheet.loadFromFile("assets/sprites/lady1.png");
            break;
        case 2:spriteSheet.loadFromFile("assets/sprites/lady2.png");
            break;
        case 3:spriteSheet.loadFromFile("assets/sprites/lady3.png");
            break;
        case 4:spriteSheet.loadFromFile("assets/sprites/man1.png");
            break;
        case 5:spriteSheet.loadFromFile("assets/sprites/man2.png");
            break;
        case 6:spriteSheet.loadFromFile("assets/sprites/man3.png");
            break;
    }
}

void NPC::setMap(Map map)
{
    map2 = map;
}

void NPC::setDirection(Movement m) {
    if(spriteAction!=0) return;
    direction = m;
    spriteAction = 1;

    setFace(m);
    lastTic = 4;
}

void NPC::setFace(Movement m) {
    if(m==Movement::DOWN) {
        spriteDir = 0;
    } else if(m==Movement::LEFT) {
        spriteDir = 1;
    } else if(m==Movement::RIGHT) {
        spriteDir = 2;
    } else if(m==Movement::UP) {
        spriteDir = 3;
    }
}

void NPC::update(float dt)
{
    ai.moveNow(this, &map2);
    if(this->colliding() == true)
    {
        this->setFace(this->getDirection());
    }

    if(lastTic>0) {
        lastTic--;
        if(lastTic>0) return;
    }
    lastTic = 4;

    if(spriteAction==1) {
        spriteAction = 2;
        return;
    }

    spriteAction = 0;
}
void NPC::draw(sf::RenderWindow& window) const {
    sf::Sprite toRender(spriteSheet, sf::IntRect(spriteAction*32, spriteDir*32, 32, 32));
    toRender.setOrigin(16, 16);
    toRender.setPosition(position);
    window.draw(toRender);
}

sf::Vector2i NPC::getIndexPosition() {
    int x = (int)floor(position.x);
    int y = (int)floor(position.y);
    return sf::Vector2i(x/32, y/32);
}

Movement NPC::getDirection()
{
    return direction;
}

void NPC::setPosition(sf::Vector2f add)
{
    position += add;
}

sf::Vector2f NPC::getPosition()
{
    return position;
}
void NPC::printDirection()
{
    std::cout << direction << std::endl;
}

