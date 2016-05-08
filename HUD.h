#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include "EntitySubclass.h"

class HUD
{
private:
    Character *c;
    std::string updater;
    sf::Text timer;
    sf::Font font;
    sf::Text jewels;
    sf::RectangleShape weapon;
    sf::RectangleShape jewel;
    int total_time;
    int shoot_time;
    int reload_time;
    int jewelctr;
    int minute;
    int tens;
    int ones;
    bool isFired;
    bool isReloading;
    //sf::Clock clock2;
public:
    HUD(Character *c);
    void jewelInc();
    void hasFired();
    void update(float dt);
    void initializeClock();
    bool wasUsed();
    void draw(sf::RenderWindow &rw) const;
};
#endif //HUD_H_INCLUDED
