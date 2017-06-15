#pragma once
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Sprite.hpp"
class Event;



class GameWindow {
public:
    GameWindow(const std::string& title);

    void loop();
    bool isOpen() const;
    void processEvent(Event* event);

private:
    void render();
    void processWindowEvents();

    sf::RenderWindow window;
    Sprite field;
};
