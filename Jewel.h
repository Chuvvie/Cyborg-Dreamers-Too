#ifndef JEWEL_H_INCLUDED
#define JEWEL_H_INCLUDED
#include "Entity.h"
#include <iostream>

class Jewel: public Entity {
protected:
    sf::Vector2f position;
    Movement direction;
    sf::Texture spriteSheet;
    bool isCharacter = false;
    bool isNPC = false;
    bool isJewel = false;
    int lastTic;
    int spriteDir;
    int spriteAction;
    bool isColliding = false;
    bool isAlive = true;
public:
    Jewel(sf::Vector2f position);
    sf::Vector2i getIndexPosition();
    virtual ~Jewel() {std::cout << "BYE JEWEL" << std::endl;}
    Jewel(const Jewel &obj);
    void update(float dt);
    sf::Vector2f getPosition();
    void draw(sf::RenderWindow& window) const;
    Movement getDirection();
    void setDirection(Movement m);
    void setFace(Movement m);
    void isCollidingNow();
    void isNotColliding();
    bool getAlive();
    void setDead();
    void reSet();
    bool colliding();
    void setCostume(int a){};
    int getCostume(){};
    int getType();
    virtual void setTarget(Entity*){};
};

#endif // JEWEL_H_INCLUDED
