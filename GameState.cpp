#include "StateManager.h"
#include "GameState.h"
#include <sstream>
#include <cassert>
#include "Universal.h"
#include "ServerSession.h"

//using namespace boost::asio;

GameState::GameState(StateManager* sm): State(sm), sm(sm){
	
}

void GameState::serverLoop(size_t player, std::string username) {
	std::cout << "Imma server: " << username << std::endl;
	std::cout << "Players: " << player << std::endl;

	map = generator->generate(32, 25, 2);
	mapData = map->printTiles();

	compressedMap = new std::vector<uint8_t>();
	compressedMap->resize(map->getHeight() * map->getWidth());
	for (int i = 0; i < map->getHeight(); i++)
	{
		for (int j = 0; j < map->getWidth(); j++)
		{
			(*compressedMap)[i*map->getWidth() + j] = mapData[i][j];
		}
	}

	endpoint = new ip::tcp::endpoint(ip::tcp::v4(), 8080);
	acceptor = new ip::tcp::acceptor(service, *endpoint);
	socket = new ip::tcp::socket(service);
	sessions = new std::vector<std::shared_ptr<ServerSession>>();
	
	readyClients = 1;
	totalClients = player;
	sessions->push_back(nullptr);
	registerSession(0, username);

	accept(player-1);

	service.run();
}

void GameState::accept(size_t player) {
	if (player == 0)
		return;

	acceptor->async_accept(*socket, [&](boost::system::error_code ec) {
		sessions->push_back(std::make_shared<ServerSession>(std::move(*socket), sessions->size(), this));
		accept(player-1);
	});
}

void GameState::broadcast(const std::vector<uint8_t>& copy) {
	for (auto session : *sessions) {
		if(session!=nullptr)
			session->send(copy);
	}
}

std::string GameState::checkName(const std::string& desired) {

	std::string curr = desired;
	while (nameList->find(curr) == nameList->end()) {
		auto length = curr.length();
		auto firstIndex = curr.length();

		for (int i = curr.length() - 1; i >= 0; i--)
		{
			if ('0' <= curr[i] && curr[i] <= '9')
				firstIndex--;
			else
				break;
		}

		if (firstIndex == curr.length())
			curr += "0";
		else {
			auto substringA = curr.substr(0, firstIndex);
			auto substringB = curr.substr(firstIndex, length - firstIndex);
			auto currCount = std::atoi(substringB.c_str());
			curr = substringA + std::to_string(currCount + 1);
		}
	}
	return curr;
}

void GameState::registerSession(int index, std::string username) {

}

void GameState::clientLoop(std::string IP, std::string username) {
	std::cout << "Imma client: " << username << std::endl;
	std::cout << "Host: " << IP << std::endl;


}

void GameState::onActivate(const std::string& activate) {
	isActive = true;
	inGame = false;

	generator = new MapGenerator();

	std::stringstream ss(activate);
	std::string current;

	ss >> current;
	if (current == "host")
	{
		ss >> current;
		size_t players = std::atoi(current.c_str());
		
		std::string username = "";
		while (ss >> current)
			username += " " + current + " ";

		networkThread = new std::thread(&GameState::serverLoop, this, players, username);
	}
	else
	{
		std::string ipAddress;
		ss >> ipAddress;

		std::string username = "";
		while (ss >> current)
			username += current + " ";

		networkThread = new std::thread(&GameState::clientLoop, this, ipAddress, username);
	}
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


