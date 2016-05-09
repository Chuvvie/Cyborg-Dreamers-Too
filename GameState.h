#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include <thread>
//#include <boost/asio.hpp>
#include <map>
#include <set>
#include <string>
//#include <mutex>
#include "State.h"
#include "HUD.h"
#include "NPC.h"
#include "EntitySubclass.h"
#include "map.h"
#include "CollisionDetector.h"
#include <vector>
#include "mapgenerator.h"

//using namespace boost::asio;

enum InputType
{
    KeyboardInput,
    MouseInput,
    JoystickInput
};

struct MyKeys
{
    InputType myInputType;
    sf::Event::EventType myEventType;
    int myKeyCode;
    sf::Mouse::Button myMouseButton;
};

class GameState: public State {
private:
    Map* map;
    Character player;
    StateManager* sm;
	//io_service service;
    bool isActive;
    bool isHost;
//	std::thread* clientThread;
//	std::thread* serverThread;

	//friend class ClientSide;

	//NPCs
	NPC curly;
	NPC larry;
	NPC moe;
	NPC tom;
	NPC dick;

	std::vector<NPC*> npc;
	std::vector<Character*> players;

	CollisionDetector cd;

	HUD hud;
public:

    sf::Event gameevent;
    MapGenerator generator; //new
    bool isOver = false; //new
    sf::Clock gametime;


	static const uint16_t tcpPort = 8080;
	static const uint16_t serverListenPort = 8080;
	static const uint16_t clientListenPort = 8181;
    std::map<std::string,MyKeys> Keys;



    GameState(StateManager* sm);
    void serverLoop(size_t players);
    void clientLoop(std::string ip);
    void onActivate(const std::string& accept);
    void onDeactivate();
    void handleInput(int u, int v, const std::string& typed, sf::Event e);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
};

#endif // GAMESTATE_H_INCLUDED
