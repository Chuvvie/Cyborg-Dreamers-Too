#include "HUD.h"
#include "Universal.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <iostream>
sf::Clock clock2;
HUD::HUD(Character *c): c(c)
{
    std::cout << "LOADING HUD" << std::endl;
    total_time = 300;
    shoot_time = 0;
    reload_time = 0;
    jewelctr = 0;
    minute = 5;
    tens = 0;
    ones = 0;
    isFired = false;
    isReloading = false;
    font.loadFromFile("assets/fonts/black_jack.ttf");
    /*
    Green (Weapon is ready to fire) 85, 255, 0
    Red (Weapon is reloading) 201, 33, 0
    Black (Weapon was fired) 0, 0, 0
    Turquoise (Jewel color) 0, 242, 242
    */
    //set the position of the jewel sprite
    jewel.setPosition(sf::Vector2f(50.f, (float)(Universal::window_height - 100.f)));
    jewel.setSize(sf::Vector2f(50, 50));
    jewel.setOutlineColor(sf::Color(0, 0, 0, 255));
    jewel.setFillColor(sf::Color(0, 242, 242, 255));

    jewels.setPosition(sf::Vector2f(120.f, float(Universal::window_height - 100.f)));
    jewels.setFont(font);
    jewels.setString("x" + std::to_string(jewelctr));
    jewels.setColor(sf::Color::Yellow);

    //set the position of the weapon sprite
    weapon.setPosition(sf::Vector2f(200.f, (float)(Universal::window_height - 100.f)));
    weapon.setSize(sf::Vector2f(50, 50));
    weapon.setOutlineColor(sf::Color(0, 0, 0, 255));
    weapon.setFillColor(sf::Color(85, 255, 0, 255));

    std::to_string(minute) + ":" + std::to_string(tens) + std::to_string(ones);

    timer.setPosition(sf::Vector2f(Universal::window_width/2, 0));
    timer.setFont(font);
    timer.setString(updater);
    timer.setColor(sf::Color::White);

    std::cout << "HUD LOADED" << std::endl;

}

void HUD::update(float dt)
{
    float count = clock2.getElapsedTime().asSeconds();
    if(count >= 1)
    {
        std::cout << "1 second" <<std::endl;
        total_time--;
        if(shoot_time > 0)
        {
            shoot_time--;
            std::cout << shoot_time <<std::endl;
            if(shoot_time == 0)
            {
                isReloading = true;
                isFired = false;
                reload_time = 5;
            }
        }
        else if(reload_time > 0)
        {
            reload_time--;
            if(reload_time == 0) isReloading = false;
        }
        clock2.restart();
    }
    minute = (int) total_time/60;
    tens = (int) (total_time - (minute * 60))/10;
    ones = (int) total_time - (int)(total_time/10)*10;
    updater = std::to_string(minute) + ":" + std::to_string(tens) + std::to_string(ones);
    jewels.setString("x" + std::to_string(jewelctr));
    //updater = "sadasddsadasdsad";
    if(isFired)
    {
        //std::cout << "Fired"<< std::endl;
        weapon.setFillColor(sf::Color::Black);
    }
    else if(isReloading)
    {
        //std::cout << "Reload"<< std::endl;
        weapon.setFillColor(sf::Color(sf::Color::Yellow));
    }
    else
    {
        weapon.setFillColor(sf::Color(sf::Color::Green));
    }
    timer.setString(updater);
}

void HUD::jewelInc()
{
    jewelctr++;
}

void HUD::hasFired()
{
    isFired = true;
    shoot_time = 2;
}

bool HUD::wasUsed()
{
    if((isFired == true) || (isReloading == true))
    {
        return true;
    }
    return false;
}
void HUD::draw(sf::RenderWindow &rw) const
{
    //std::cout << "Drawing...." << std::endl;
    rw.draw(weapon);
    rw.draw(jewel);
    rw.draw(timer);
    rw.draw(jewels);
}
