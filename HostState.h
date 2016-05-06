#ifndef HOSTSTATE_H_INCLUDED
#define HOSTSTATE_H_INCLUDED
#include "Button.h"

class StateManager;
class HostState: public State
{
private:
    StateManager* sm;
    sf::Font font;
    Button back;
    Button players1;
    Button players2;
    Button players3;
    Button players4;
    sf::Text nameInput;
    sf::Text nameLabel;
    std::string name;
public:
    HostState(StateManager* sm);
    void update(float dt);
    void draw(sf::RenderWindow&) const;
    void handleInput(int u, int v, const std::string& typed);
};

#endif // HOSTSTATE_H_INCLUDED
