#include "Client.hpp"
#include "Core/ExceptionSafeWrapper.hpp"
#include <SFML/Network.hpp>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <list>



void Client::start() {
    shouldStop = false;
    connect("127.0.0.1");
    socket.setBlocking(false);

    std::list<std::exception_ptr> exceptions;
    std::mutex exceptionsMutex;
    std::thread inputThread(make_exception_safe([this]()->void{receiveLoop();}, exceptions, exceptionsMutex));
    inputThread.detach();

    /*while(true) {
        if(not exceptions.empty()) {
            std::rethrow_exception(exceptions.front());
        }
        std::string message {readUserInput()};
        if(not message.empty()) {
            sendMessage(message);
        }
    }
    std::cout << "Quiting\n";*/
}



void Client::stop() {
    shouldStop = true;
}



Client::~Client() {
    stop();
}


sf::Packet Client::getMessage() {
    if(not incomings.empty()) {
        auto message = incomings.front();
        incomings.pop();
        return message;
    } else {
        return sf::Packet();
    }
}



void Client::connect(const sf::IpAddress& address) {
    std::lock_guard<std::mutex> socketLock(socketMutex);
    socket.setBlocking(true);
    auto status = socket.connect(address, 53000, sf::seconds(10));
    socket.setBlocking(false);
    if (status != sf::Socket::Done) {
        throw std::runtime_error {"Error: Failed to connect to "+address.toString()+":53000"};
    }
    std::lock_guard<std::mutex> coutLock(coutMutex);
    std::cout << "Successfully connected to " + address.toString() + ":53000\n";
}



void Client::receiveLoop() {
    std::string message;
    while(not shouldStop) {
        receiveMessage();
    }
}



void Client::receiveMessage() {
    sf::Socket::Status status;
    sf::IpAddress address;
    sf::Packet packet;
    {
        std::lock_guard<std::mutex> socketLock(socketMutex);
        status = socket.receive(packet);
        address = socket.getRemoteAddress();
    }
    switch(status) {
    case sf::Socket::Done:{
        std::cout << "Received a message\n";
        incomings.push(packet);
    }
    case sf::Socket::NotReady:
        break;

    case sf::Socket::Disconnected:{
        {
            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << "Disconnected from server, trying to reconnect...\n";
        }
        connect(address);
        break;
    }
    default:
        throw std::runtime_error {"Error receiving data"};   
    }
}



std::string Client::readUserInput() {
    std::string message;
    std::getline(std::cin, message);
    return message;
}



void Client::sendMessage(const std::string& message) {
    sf::Packet packet;
    packet << message;
    
    std::lock_guard<std::mutex> socketLock(socketMutex);
    auto result = socket.send(packet);
    int attempt = 0;
    while(result != sf::Socket::Done) {
        if(result == sf::Socket::Partial and attempt < 11) {
            attempt++;
            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << "Error sending data, attempt " << attempt << "/10\n";
            
        } else {
            throw std::runtime_error {"Error sending data"};
        }
        result = socket.send(packet);
    }
}
