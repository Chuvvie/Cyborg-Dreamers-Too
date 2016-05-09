#ifndef ENTITYSUBCLASS_H_INCLUDED
#define ENTITYSUBCLASS_H_INCLUDED
#include "Entity.h"
#include "map.h"
#include "NPC.h"
#include "Jewel.h"

class Character: public Entity {
private:

protected:

    sf::Vector2f position;
    Movement direction;
    sf::Texture spriteSheet;
    int lastTic;
    int spriteDir;
    int spriteAction;
    bool isColliding;
    int currentCostume;
    Entity* target;
    bool isAlive = true;
    std::vector<Jewel*> jewels;
public:
    Character();
    void update(float dt);
    void addJewel(Jewel *jewel);
    int getJewels();
    void loseJewels();
    void draw(sf::RenderWindow& window) const;
    void setDirection(Movement m);
    void setFace(Movement m);
    int getFace();
    sf::Vector2i getIndexPosition();
    sf::Vector2f getPosition();
    sf::Vector2f setPosition(sf::Vector2f pos);
    Movement getDirection();
    void isCollidingNow();
    void isNotColliding();
    bool colliding();
    void setCostume(int);
    void changeCostume();
    int getCostume();
    bool getAlive();
    void setDead();
    void setTarget(Entity*);
    void kill();
    sf::Vector2i getSprite();
    int getType();
};

#endif // ENTITYSUBCLASS_H_INCLUDED
