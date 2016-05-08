#include "StateManager.h"
#include "GameState.h"
#include <sstream>
#include <cassert>
#include "Universal.h"

//using namespace boost::asio;

GameState::GameState(StateManager* sm): State(sm), sm(sm){





}


}


}

void GameState::onActivate(const std::string& activate) {
	isActive = true;
	}
	else

}

void GameState::onDeactivate() {
    isActive = false;
}

void GameState::handleInput(int u, int v, const std::string& typed) {
   
}

void GameState::update(float dt) {

}

void GameState::draw(sf::RenderWindow& window) const {
	
}


