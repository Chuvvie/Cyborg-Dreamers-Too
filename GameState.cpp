#include "StateManager.h"
#include "GameState.h"
#include <sstream>
#include <cassert>
#include "Message.h"
#include "TCPServer.h"

using namespace boost::asio;

GameState::GameState(StateManager* sm): State(sm), sm(sm){

}

void GameState::serverLoop(size_t player) {
	
}

void GameState::clientLoop(std::string IP) {
	
}

void GameState::onActivate(const std::string& activate) {
	isActive = true;
	service.reset();

    std::istringstream split(activate);
	std::string type; split >> type;
    isHost = false;
	std::string serverIP = "localhost";
    if(type=="host") {
		isHost = true;
		size_t players;
		split >> players;

		serverThread = new std::thread(&GameState::serverLoop, this, players);
	}
	else
		split >> serverIP;

	std::string username; split >> username;
	clientThread = new std::thread(&GameState::clientLoop, this, serverIP);
}

void GameState::onDeactivate() {
    isActive = false;
	service.stop();

    clientThread->join();
    delete clientThread;
    clientThread = nullptr;

    if(isHost) {
        serverThread->join();
        delete serverThread;
        serverThread = nullptr;
    }
}

void GameState::handleInput(int u, int v, const std::string& typed) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        popSelf(1);
    }
}

void GameState::update(float dt) {

}

void GameState::draw(sf::RenderWindow& window) const {
}