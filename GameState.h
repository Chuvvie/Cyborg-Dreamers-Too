#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include <thread>
#include <boost/asio.hpp>
#include <map>
#include <set>
#include <string>
#include <mutex>
#include "State.h"

using namespace boost::asio;

class GameState: public State {
private:
    StateManager* sm;
	io_service service;
    bool isActive;
    bool isHost;
	std::thread* clientThread;
	std::thread* serverThread;

	friend class ClientSide;

public:
	static const uint16_t tcpPort = 8080;
	static const uint16_t serverListenPort = 8080;
	static const uint16_t clientListenPort = 8181;

    GameState(StateManager* sm);
    void serverLoop(size_t players);
    void clientLoop(std::string ip);
    void onActivate(const std::string& accept);
    void onDeactivate();
    void handleInput(int u, int v, const std::string& typed);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
};

#endif // GAMESTATE_H_INCLUDED
