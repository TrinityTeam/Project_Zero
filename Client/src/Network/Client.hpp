#pragma once
#include <SFML/Network.hpp> 
#include <mutex>



class Client {
public:
    void start();

private:
    void connect(const sf::IpAddress& address);
    void receiveLoop();
    std::string receiveMessage();
    std::string readUserInput();
    void sendMessage(const std::string& message);

    sf::TcpSocket socket;
    std::mutex socketMutex;
    std::mutex coutMutex;
};
