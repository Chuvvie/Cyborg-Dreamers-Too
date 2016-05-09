#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED
#include "Entity.h"
#include "Map.h"
class NPC: public Entity{
protected:
    Movement direction;
    sf::Texture spriteSheet;
    Map map2;
    int lastTic;
    int spriteDir;
    int spriteAction;
    int ctr = 0;
    int currentCostume;
    bool isColliding;
public:
    sf::Vector2f position;
    void update(float);
    void randomCommand();
    void setMap(Map map);
    void setCostume(int);
    NPC();
    void draw(sf::RenderWindow& window) const;
    void setDirection(Movement m);
    void setFace(Movement m);
    sf::Vector2i getIndexPosition();
    sf::Vector2f getPosition();
    void setSpeed(float spd);
    Movement getDirection();
    void setPosition(sf::Vector2f add);
    void setPositionFix(sf::Vector2f tis);
    void printDirection();
    void isCollidingNow();
    void isNotColliding();
    bool colliding();
    sf::Vector2i getSprite();
    int getCostume();
};
#endif // NPC_H_INCLUDED
