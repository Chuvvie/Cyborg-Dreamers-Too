#ifndef SERVERSIDE_H_INCLUDED
#define SERVERSIDE_H_INCLUDED
#include <vector>
#include <memory>
#include <map>
#include <boost/asio.hpp>

using namespace boost::asio;

struct client {
	uint16_t order;
	std::string name;
	ip::udp::endpoint remote;
};

struct serverSide {
	ip::udp::socket socket;
	ip::udp::endpoint tempEndpoint;

	uint8_t expectedClients;
	uint8_t totalClients;
	uint8_t mapLoadedClients;
	uint8_t monotonousCounter;
	std::map<uint8_t, bool> doneLoading;
	std::map<uint8_t, std::shared_ptr<client>> clients;
	std::set<std::string> username;
	std::vector<uint8_t> recBuffer;
	std::vector<uint8_t> sendBuffer;
	std::thread* receiveThread;
	std::thread* sendThread;
	std::mutex entryMtx;
	std::mutex dataMtx;

	uint8_t** map;
	std::vector<uint8_t> compressedMap;
	bool inGame;

	serverSide(io_service* service, uint8_t players);
	void send(const ip::udp::endpoint& ep);
	void receive();
	void receiveUpdate();
	void sendUpdate();
	void broadcast();

	std::string correctUsername(const std::string& proposed);
	void generateMap();
	void compressMap();
	void update(float delta);
};

#endif // SERVERSIDE_H_INCLUDED