#include "StateManager.h"
#include "GameState.h"
#include <sstream>
#include <cassert>
#include "Universal.h"
//#include "Message.h"
//#include "TCPServer.h"

//using namespace boost::asio;

GameState::GameState(StateManager* sm): State(sm), sm(sm){





}

void GameState::serverLoop(size_t player) {

}

void GameState::clientLoop(std::string IP) {

}

void GameState::onActivate(const std::string& activate) {
	isActive = true;
	isOver = false;

	std::cout<<"GAME STATE ACTIVATED" <<std::endl;
    gametime.restart();

    map = generator.generate(32,25,2);
     while(true)
    {
        int XPOS = rand() % (map->getWidth()-1) + 1;
        int YPOS = rand() % (map->getHeight()-1) + 1;
        //the position should be in a free tile
        if(map->getTile(YPOS,XPOS)->getType() ==   0)
        {
            player.setPosition(sf::Vector2f(XPOS*32+16,YPOS*32+16));
            break;
        }
    }
    map->printTiles();
    //set the position of the player somewhere in the map


	/*
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
	*/
}

void GameState::onDeactivate() {
     std::cout<<"deactivated"<<std::endl;
    isActive = false;
    /*
	service.stop();

    clientThread->join();
    delete clientThread;
    clientThread = nullptr;

    if(isHost) {
        serverThread->join();
        delete serverThread;
        serverThread = nullptr;
    }
    */
}

void GameState::handleInput(int u, int v, const std::string& typed) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        popSelf(1);
    }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        sf::Vector2i nextPos = player.getIndexPosition()+sf::Vector2i(0, -1);
        Tile* tile = map->getTile(nextPos.y,nextPos.x);
        if(tile->isPassable() == true)
            player.setDirection(Movement::UP);
        else
            player.setFace(Movement::UP);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        sf::Vector2i nextPos = player.getIndexPosition()+sf::Vector2i(0, 1);
        Tile* tile = map->getTile(nextPos.y,nextPos.x);
        if(tile->isPassable() == true)
            player.setDirection(Movement::DOWN);
        else
            player.setFace(Movement::DOWN);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        sf::Vector2i nextPos = player.getIndexPosition()+sf::Vector2i(-1, 0);
        Tile* tile = map->getTile(nextPos.y,nextPos.x);
        if(tile->isPassable() == true)
            player.setDirection(Movement::LEFT);
        else
            player.setFace(Movement::LEFT);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sf::Vector2i nextPos = player.getIndexPosition()+sf::Vector2i(1, 0);
        Tile* tile = map->getTile(nextPos.y,nextPos.x);
        if(tile->isPassable() == true)
            player.setDirection(Movement::RIGHT);
        else
            player.setFace(Movement::RIGHT);
    }
    if(sf::Keyboard::isKeyPressed((sf::Keyboard::Space)))
    {
        sf::Vector2i nextPos;
        switch(player.getFace())
        {
        case 0:
        {
            nextPos = player.getIndexPosition() + sf::Vector2i(0,1);
            break;
        }
        case 1:
        {
            nextPos = player.getIndexPosition() + sf::Vector2i(-1,0);
            break;
        }
        case 2:
        {
            nextPos = player.getIndexPosition() + sf::Vector2i(1,0);
            break;
        }
        case 3:
        {
            nextPos = player.getIndexPosition() + sf::Vector2i(0,-1);
            break;
        }
        }
        Tile* tile = map->getTile(nextPos.y,nextPos.x);
        if(tile->getType() == 2)
        {
            tile ->setColor(sf::Color::Red);
            tile ->setType(4);
            // sm->push(1);
        }
    }
}

void GameState::update(float dt) {


     sf::Time elapsed = gametime.getElapsedTime();
    //std::cout<<elapsed.asSeconds()<<std::endl;
    // timer
    if(elapsed.asSeconds() >= Universal::GAME_DURATION && elapsed.asSeconds() <= 3600 )
    {
      std::cout<<"TIME UP"<<std::endl;
        isOver = true;
    }

    player.update(dt);


    //End condition #2. If all the jewels are taken, end.
    /*
    for(sf::Vector2i x : generator.objectTiles)
    {

        if(map->getTile(x.y,x.x)->getType() == 4)
        {

            map->getTile(x.y,x.x)->setColor(sf::Color::Red);
            isOver = true;
        }
        else
        {
            isOver = false;
            break;
        }
    }
    */

    if(isOver)
    {
        uint8_t** savemap = map->printTiles();
        std::string passmap = "";
        for(int i = 0; i <25; i++)
        {
            for(int j = 0; j < 32; j++)
            {
               passmap += std::to_string((int)savemap[i][j]);
            }
            std::cout<<std::endl;
        }
        generator.clearAll();
        sm->push(5,passmap);
    }



}

void GameState::draw(sf::RenderWindow& window) const {

       sf::View minimap_view(sf::FloatRect(0,0, window.getSize().x,window.getSize().y));
    minimap_view.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));


//time text
    /*
        sf::Time elapsed = gametime.getElapsedTime();
        sf::Text time;
        time.setString(std::to_string(elapsed.asSeconds()));
         sf::Font font;
        if (!font.loadFromFile("assets/yuyuko.ttf"))
        {
            // error...
        }
        time.setFont(font); // font is a sf::Font

    // set the character size
        time.setCharacterSize(24);

        //time.setPosition(player.getPosition());
        window.draw(time);
        */
    map->drawTiles(&window);
    window.setView(minimap_view);
    map->drawTiles(&window);
    player.draw(window);

}


