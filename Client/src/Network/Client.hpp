#pragma once
#include <SFML/Network.hpp> 
#include <mutex>
#include <queue>



class Client {
public:
    ~Client();

    void start();
    void stop();
    sf::Packet getMessage();

private:
    void connect(const sf::IpAddress& address);
    void receiveLoop();
    void receiveMessage();
    std::string readUserInput();
    void sendMessage(const std::string& message);

    sf::TcpSocket socket;
    std::mutex socketMutex;
    std::mutex coutMutex;
    std::queue<sf::Packet> incomings;
    bool shouldStop = false;
};
