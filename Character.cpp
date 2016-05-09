#include "EntitySubclass.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Character::Character(): direction(Movement::STAY), position(sf::Vector2f(144, 144)), lastTic(0), spriteDir(0), spriteAction(0) {
    spriteSheet.loadFromFile("assets/sprites/lady1.png");
}

void Character::setDirection(Movement m) {
    if(spriteAction!=0) return;
    direction = m;
    spriteAction = 1;

    setFace(m);
    lastTic = 4;
}

void Character::isCollidingNow()
{
    isColliding = true;
}

void Character::isNotColliding()
{
    isColliding = false;
}
bool Character::colliding()
{
    return isColliding;
}
Movement Character::getDirection()
{
    return direction;
}
void Character::setFace(Movement m) {
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
int Character::getFace()
{
    return spriteDir;
}

void Character::setCostume(int a)
{
    currentCostume = a;
}

int Character::getCostume()
{
    return currentCostume;
}
void Character::changeCostume()
{
    switch(currentCostume)
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
void Character::update(float dt) {
    if(isColliding == false)
    {
        if(spriteAction!=0  ) {
        if(direction==Movement::DOWN) {
            position += sf::Vector2f(0, 4);
        } else if(direction==Movement::LEFT) {
            position += sf::Vector2f(-4, 0);
        } else if(direction==Movement::RIGHT) {
            position += sf::Vector2f(4, 0);
        } else if(direction==Movement::UP) {
            position += sf::Vector2f(0, -4);
        }
        }
    }
    else
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
    direction = Movement::STAY;
}

void Character::draw(sf::RenderWindow& window) const {
    sf::Sprite toRender(spriteSheet, sf::IntRect(spriteAction*32, spriteDir*32, 32, 32));
    sf::View player_view(sf::FloatRect(0, 0, window.getSize().x/2, window.getSize().y/2));

    toRender.setOrigin(16,16);
    toRender.setPosition(position);

    player_view.setCenter(toRender.getPosition());
    window.setView(player_view);

    window.draw(toRender);
}

sf::Vector2i Character::getIndexPosition() {
    int x = (int)floor(position.x);
    int y = (int)floor(position.y);
    return sf::Vector2i(x/32, y/32);
}
sf::Vector2f Character::getPosition() {
    return position;
}
sf::Vector2f Character::setPosition(sf::Vector2f pos) {
     position = pos;
}

sf::Vector2i Character::getSprite()
{
    return sf::Vector2i(spriteAction, spriteDir);
}


