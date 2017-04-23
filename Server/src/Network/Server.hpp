#pragma once
#include <list>
#include <memory>
#include <SFML/Network.hpp>



class Server {
public:
    void start();

private:
    void acceptConnection();
    void processSockets();
    void sendBroadcastMessage(sf::Packet packet);

    sf::TcpListener listener;
    std::list<sf::TcpSocket> clients;
    sf::SocketSelector sockets;

};