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
	
	map = generator->generate(32, 25, 2);
	mapData = map->printTiles();

	compressedMap = "";
	for (int i = 0; i < map->getHeight(); i++)
	{
		std::string line = "";
		for (int j = 0; j < map->getWidth(); j++)
		{
			line += std::to_string( (unsigned int)mapData[i][j] );
		}
		compressedMap += line;
	}

	nameList = new std::set<std::string>();
	endpoint = new ip::tcp::endpoint(ip::tcp::v4(), GameState::tcpPort);
	acceptor = new ip::tcp::acceptor(service, *endpoint);
	socket = new ip::tcp::socket(service);
	sessions = new std::vector<std::shared_ptr<ServerSession>>();
	
	readyClients = 1;
	totalClients = stillConnected = player;
	sessions->push_back(nullptr);
	registerName(username);

	vacantPlayers = player - 1;
	if (vacantPlayers == 0)
		inGame = true;

	accept();

	service.run();
	std::cout << "Finished server thread" << std::endl;
}

void GameState::accept() {
	if (vacantPlayers == 0)
		return;

	std::cout << "Waiting for " << vacantPlayers << " more player/s" << std::endl;
	acceptor->async_accept(*socket, [&](boost::system::error_code ec) {
		sessions->push_back(std::make_shared<ServerSession>(std::move(*socket), sessions->size(), this));
		std::cout << "Someone went in!" << std::endl;
		vacantPlayers--;
		accept();
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
	while (nameList->find(curr) != nameList->end()) {
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

void GameState::registerName(std::string username) {
	std::cout << username << " is being registered" << std::endl;
	(*nameList).insert(username);
}

void GameState::clientLoop(std::string IP, std::string username) {
	client = new ClientConnection(service, this);
	client->connect(IP, username);
	service.run();
	std::cout << "Finished client thread" << std::endl;
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
		isHost = true;
		ss >> current;
		size_t players = std::atoi(current.c_str());

		std::string username = "";
		while (ss >> current)
			username += current + " ";
		if (username.length() > 0)
			username = username.substr(0, username.length()-1);

		networkThread = new std::thread(&GameState::serverLoop, this, players, username);
	}
	else
	{
		isHost = false;
		std::string ipAddress;
		ss >> ipAddress;

		std::string username = "";
		while (ss >> current)
			username += current + " ";
		if (username.length() > 0)
			username = username.substr(0, username.length() - 1);

		networkThread = new std::thread(&GameState::clientLoop, this, ipAddress, username);
	}
}

void GameState::onDeactivate() {
    isActive = false;
}

void GameState::handleInput(int u, int v, const std::string& typed) {
	if (isHost) {

	}
	else {
	
	}
}

void GameState::update(float dt) {
	if (inGame) {
		static int counter = 1;
		std::cout << "update: " << counter++ << std::endl;
		if (isHost)
		{
			static float k = 1;
			k -= dt;
			if (k <= 0)
			{
				inGame = false;

				std::string toSend = "";
				MessageHeader mh = MessageHeader{ MessageType::GAME_FINISH, toSend.length() + 1 };
				std::vector<uint8_t> sendBuffer;
				sendBuffer.resize(sizeof(MessageHeader) + mh.size);
				memcpy(sendBuffer.data(), &mh, sizeof(MessageHeader));
				memcpy(sendBuffer.data() + sizeof(MessageHeader), toSend.data(), mh.size);
				broadcast(sendBuffer);

				for (auto session : *sessions) {
					if (session != nullptr)
						session->activate(false);
				}

				std::cout << "Broadcasted GAME FINISH to everyone" << std::endl;
			}
			else
			{
				std::cout << "Send dummy update data message to everyone" << std::endl;

				auto toSend = UpdateDataMessage{ 0, true, 300, 300, 0, 0 };
				auto mh = MessageHeader{ MessageType::UPDATE_DATA, sizeof(UpdateDataMessage) };
				std::vector<uint8_t> sendBuffer;
				sendBuffer.resize(sizeof(MessageHeader) + mh.size);
				memcpy(sendBuffer.data(), &mh, sizeof(MessageHeader));
				memcpy(sendBuffer.data() + sizeof(MessageHeader), &toSend, mh.size);
				broadcast(sendBuffer);
			}
		}
		else
		{
			std::cout << "Send dummy update input message to server" << std::endl;

			auto toSend = UpdateInputMessage{ client->id, true, false, false, false, false, false, false };
			auto mh = MessageHeader{ MessageType::UPDATE_INPUT, sizeof(UpdateInputMessage) };
			std::vector<uint8_t> sendBuffer;
			sendBuffer.resize(sizeof(MessageHeader) + mh.size);
			memcpy(sendBuffer.data(), &mh, sizeof(MessageHeader));
			memcpy(sendBuffer.data() + sizeof(MessageHeader), &toSend, mh.size);
			client->send(sendBuffer);
		}
	}
	else {

	}
}

void GameState::draw(sf::RenderWindow& window) const {
	
}