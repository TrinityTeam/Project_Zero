#include "GameWindow.hpp"
#include "Core/Event.hpp"
#include <SFML/Window/Event.hpp>



GameWindow::GameWindow(const std::string& title):
    window(sf::VideoMode(1024, 768), title) {

    field.loadFromTexture("../data/field.png");
    field.setPosition({window.getSize().x/2.f, window.getSize().y/2.f});
}



bool GameWindow::isOpen() const {
    return window.isOpen();
}



void GameWindow::loop() {
    processWindowEvents();
    render();
}



void GameWindow::render() {
    window.clear(sf::Color(0, 0, 0));

    field.onDraw(window);

    window.display();
}



void GameWindow::processWindowEvents() {
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window.close();
        }
    }    
}
