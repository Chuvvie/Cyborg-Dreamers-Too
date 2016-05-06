#include <thread>
#include <boost/asio.hpp>
#include <map>
#include <set>
#include <string>
#include <mutex>
#include "Message.h"
#include "ServerSide.h"
#include "GameState.h"

serverSide::serverSide(io_service* service, uint8_t players) :
	socket(*service, ip::udp::endpoint(ip::udp::v4(), GameState::serverListenPort)), 
	expectedClients(players), totalClients(0), mapLoadedClients(0),
	monotonousCounter(0), inGame(false) 
{
	generateMap();
	compressMap();
	receive();
}

void serverSide::receive() {
	recBuffer.resize(500);
	socket.async_receive_from(buffer(recBuffer.data(), sizeof(MessageHeader)), tempEndpoint,
		[&](boost::system::error_code ec, size_t size) {
		MessageHeader* mh = reinterpret_cast<MessageHeader*>(recBuffer.data());
		switch (mh->type)
		{
		case MessageType::CONNECT: {
			if (totalClients == expectedClients)
				break;

			std::string name = std::string(reinterpret_cast<char*>(recBuffer.data() + sizeof(MessageHeader)));
			entryMtx.lock();

			name = correctUsername(name);
			std::string toSend = std::to_string(monotonousCounter) + " " + name;
			MessageHeader toSendHeader = MessageHeader{ MessageType::CONFIRM, toSend.length()+1};
			sendBuffer.resize(sizeof(MessageHeader) + toSend.length() + 1);
			memcpy(sendBuffer.data(), &toSendHeader, sizeof(MessageHeader));
			memcpy(sendBuffer.data()+sizeof(MessageHeader), toSend.data(), toSend.length() + 1);
			send(tempEndpoint);

			auto cl = std::make_shared<client>(client());
			cl->name = name;
			cl->remote = std::move(tempEndpoint);
			doneLoading[monotonousCounter] = false;
			clients[monotonousCounter++] = cl;

			entryMtx.unlock();
			break;
		}
		case MessageType::WAIT: {
			if (mapLoadedClients == expectedClients)
				break;

			auto id = *reinterpret_cast<uint8_t*>(recBuffer.data() + sizeof(MessageHeader));
			if (!doneLoading[id])
			{
				doneLoading[id] = true;
				mapLoadedClients++;

				if (mapLoadedClients == expectedClients)
				{
					MessageHeader toSendHeader = MessageHeader{ MessageType::GAME_START, 0 };
					sendBuffer.resize(sizeof(MessageHeader));
					memcpy(sendBuffer.data(), &toSendHeader, sizeof(MessageHeader));
					
					for (auto it = clients.begin(); it != clients.end(); it++)
					{
						uint8_t tempID = it->first;
						send(clients[tempID]->remote);
					}
				}
			}

			break;
		}
		case MessageType::POSITION: {
			PositionMessage* pm = reinterpret_cast<PositionMessage*>(recBuffer.data() + sizeof(MessageHeader));
			auto id = pm->id;
			auto order = pm->order;
			auto clientToUpdate = clients[id];
			if (order > clientToUpdate->order)
			{
				dataMtx.lock();
				clientToUpdate->order = order;
				dataMtx.unlock();

				MessageHeader toSendHeader = MessageHeader{ MessageType::POSITION, sizeof(PositionMessage) };
				sendBuffer.resize(sizeof(MessageHeader) + sizeof(PositionMessage));
				memcpy(sendBuffer.data(), &toSendHeader, sizeof(MessageHeader));
				memcpy(sendBuffer.data()+sizeof(MessageHeader), pm, sizeof(PositionMessage));

				for (auto it = clients.begin(); it != clients.end(); it++)
				{
					if (it->first != id)
					{
						uint8_t tempID = it->first;
						send(clients[tempID]->remote);
					}
				}
			}

			break;
		}
		}

		receive();
	});
}