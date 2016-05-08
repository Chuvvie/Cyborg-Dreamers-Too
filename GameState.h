#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include <thread>
#include <boost/asio.hpp>
#include <map>
#include <set>
#include <string>
#include <mutex>
#include "State.h"
#include "EntitySubclass.h"
#include "map.h"
#include <vector>
#include "mapgenerator.h"
#include "ServerSession.h"

using namespace boost::asio;

class GameState: public State {
private:
    Map* map;
    Character player;
    StateManager* sm;
	io_service service;
    bool isActive;
    bool isHost;
	bool inGame;
	std::thread* networkThread;
	std::thread* service_runner;

	// SERVER STUFF
	MapGenerator* generator; //new
	std::vector<uint8_t>* compressedMap;
	std::vector<std::shared_ptr<ServerSession>>* sessions;
	std::map<std::string, std::shared_ptr<ServerSession>>* nameList;
	uint8_t** mapData;
	size_t totalClients;
	size_t readyClients;

	ip::tcp::endpoint* endpoint;
	ip::tcp::acceptor* acceptor;
	ip::tcp::socket* socket;
	void accept(size_t player);
	void broadcast(const std::vector<uint8_t>& copy);
	std::string checkName(const std::string& desired);
	void registerSession(int index, std::string username);

	friend struct ServerSession;
public:
	static const uint16_t tcpPort = 8080;

    GameState(StateManager* sm);
    void serverLoop(size_t players, std::string username);
    void clientLoop(std::string ip, std::string username);
    void onActivate(const std::string& accept);
    void onDeactivate();
    void handleInput(int u, int v, const std::string& typed);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
};

#endif // GAMESTATE_H_INCLUDED
