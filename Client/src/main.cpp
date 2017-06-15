#include "Network/Client.hpp"
#include "Graphic/GameWindow.hpp"



int main() {
    /*Client client;
    client.start();*/
    
    GameWindow window("Window");
    sf::Clock clock;
    sf::Time elapsed;
    
    while(window.isOpen()) {
        elapsed += clock.restart();
        if(elapsed < sf::milliseconds(33)) {
            continue;
        } else {
            elapsed = sf::seconds(0);
        }
        window.loop();
        //auto message = client.getMessage();
    }
    //client.stop();
    return 0;
}
