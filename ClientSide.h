#ifndef CLIENTSIDE_H_INCLUDED
#define CLIENTSIDE_H_INCLUDED
#include <vector>
#include <memory>
#include <set>
#include <boost/asio.hpp>
#include <thread>
#include <mutex>

using namespace boost::asio;

struct clientSide {
	uint8_t ka;
};

#endif // CLIENTSIDE_H_INCLUDED