#include <iostream>
#include "Jewel.h"

Jewel::Jewel(sf::Vector2f position): direction(Movement::STAY), lastTic(0), spriteDir(0), spriteAction(0)
{
    isJewel = true;
    spriteSheet.loadFromFile("assets/sprites/jewel.png");
    this->position = position;
}

Jewel::Jewel(const Jewel &obj)
{
    position = obj.position;
    direction = obj.direction;
    spriteSheet = obj.spriteSheet;
    isCharacter = obj.isCharacter;
    isNPC = obj.isNPC;
    isJewel = obj.isJewel;
    lastTic = obj.lastTic;
    spriteDir = obj.spriteDir;
    spriteAction = obj.spriteAction;
    isColliding = obj.isColliding;
    isAlive = obj.isAlive;
}
sf::Vector2f Jewel::getPosition()
{
    return position;
}

Movement Jewel::getDirection()
{
    return direction;
}
int Jewel::getType()
{
    return 3;
}

void Jewel::isCollidingNow()
{
    isColliding = true;
}

void Jewel::setDead()
{
    isAlive = false;
}

void Jewel::reSet()
{
    isAlive = true;
}
void Jewel::isNotColliding()
{
    isColliding = false;
}

bool Jewel::colliding()
{
    return isColliding;
}

void Jewel::setFace(Movement m)
{
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

bool Jewel::getAlive()
{
    return isAlive;
}

void Jewel::update(float dt)
{
    if(this->getAlive())
    {
        if(this->colliding() == true)
        {
            std::cout << "has collided!" << std::endl;
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
}

void Jewel::draw(sf::RenderWindow &window) const
{
    if(isAlive == true)
    {
        sf::Sprite toRender(spriteSheet, sf::IntRect(spriteAction*32, spriteDir*32, 32, 32));
        toRender.setOrigin(16, 16);
        toRender.setPosition(position);
        window.draw(toRender);
    }
}

void Jewel::setDirection(Movement m) {
    if(spriteAction!=0) return;
    direction = m;
    spriteAction = 1;

    setFace(m);
    lastTic = 4;
}

sf::Vector2i Jewel::getIndexPosition()
{
    int x = (int)floor(position.x);
    int y = (int)floor(position.y);
    return sf::Vector2i(x/32, y/32);
}
