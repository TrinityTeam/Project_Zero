#include "Server.hpp"
#include <list>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <mutex>
#include "Core/ExceptionSafeWrapper.hpp"



void Server::start() {
    if (listener.listen(53000) != sf::Socket::Done) {
        throw std::runtime_error {"Error: unable to listen port 53000"};
    }
    sockets.add(listener);
    sf::Clock clock;
    while (true) {
        sf::Time elapsed = clock.restart();
        if(elapsed > sf::seconds(1)) {
            int direction = rand()%4;
            sf::Packet packet;
            packet << direction;
            std::cout << "Sending " << direction << "\n";
            sendBroadcastMessage(packet);
        }
        if(sockets.wait(sf::seconds(1))) {
            if(sockets.isReady(listener)) {
                acceptConnection();
            } else {
                processSockets();
            }
        }
    }
}



void Server::acceptConnection() {
    clients.emplace_back();
    if(listener.accept(clients.back()) != sf::Socket::Done) {
        throw std::runtime_error {"Error: unable to accept client"};
    }
    sockets.add(clients.back());
    std::cout << "Accepted " << clients.back().getRemoteAddress().toString() << "\n";
}



void Server::processSockets() {
    std::list<decltype(clients.begin())> disconnectedSockets;
    for(auto client_it = clients.begin(); client_it != clients.end(); client_it++) {
        sf::TcpSocket& client = *client_it;
        if(sockets.isReady(client)) {
            sf::Packet packet;
            switch(client.receive(packet)) {
            case sf::Socket::Done:{
                sendBroadcastMessage(packet);
                std::string message;
                packet >> message;
                std::cout << "Recieved message: " << message << "\n";
                break;
            }
            case sf::Socket::Disconnected:
                std::cout << "Disconnected " << client.getRemoteAddress().toString() << "\n";
                disconnectedSockets.push_back(client_it);
                break;

            default:
                throw std::runtime_error {"Error recieving data"};
            }
        }
    }
    for(auto& disconnected: disconnectedSockets) {
        sockets.remove(*disconnected);
        clients.erase(disconnected);
    }
}



void Server::sendBroadcastMessage(sf::Packet packet) {
    for(auto& socket: clients) {
        if(socket.send(packet) != sf::Socket::Done) {
            throw std::runtime_error {"Error sending message to "+socket.getRemoteAddress().toString()};
        }
    }
}
