#pragma once
#include "Sprite.hpp"
//#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>



class Hero: public Sprite {
public:
    explicit Hero(Sprite* parent = nullptr):
        Sprite(parent) {

    }

protected:
    void draw(sf::RenderWindow& window) override {
        window.draw(name);
        window.draw(health);
    }

private:
    sf::Text name;
    sf::Text health;
};
