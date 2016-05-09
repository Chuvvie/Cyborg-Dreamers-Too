#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <SFML/Graphics.hpp>

enum Movement {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STAY
};

class Entity {
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
    virtual void update(float dt) = 0;
    virtual sf::Vector2f getPosition() {};
    virtual void reSet() {};
    virtual sf::Vector2i getIndexPosition() {};
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual Movement getDirection(){};
    virtual void setDirection(Movement m) = 0;
    virtual void setFace(Movement m) = 0;
    virtual void isCollidingNow() = 0;
    virtual void isNotColliding() = 0;
    virtual bool getAlive(){};
    virtual void setDead() = 0;
    virtual bool colliding(){};
    virtual void setCostume(int a){};
    virtual int getCostume() = 0;
    virtual int getType() = 0;
    virtual void setTarget(Entity*) = 0;
};

#endif // ENTITY_H_INCLUDED
