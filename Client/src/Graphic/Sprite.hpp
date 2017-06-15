#pragma once
#include <list>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
namespace sf { class RenderWindow; }
using std::list;



class Sprite {
public:
    explicit Sprite(Node* parent = nullptr):
        Node {parent} {
        sprite.setPosition(parent != nullptr ? parent->getPosition() : sf::Vector2f());
    }

    void setPosition(const sf::Vector2f& pos) {
        sprite.setPosition(pos);
        for(Sprite* ancestor = parent; ancestor != nullptr; ancestor = ancestor->parent) {
            sprite.move(ancestor->getPosition());
        }
    }

    void move(const sf::Vector2f& delta) {
        sprite.move(delta);
    }

    sf::Vector2f getPosition() const {
        return position;
    }

    void loadFromTexture(const std::string& filePath, sf::IntRect rect = {}) {
        if (!texture.loadFromFile(filePath)) {
            throw std::runtime_error(filePath + " is not found");
        }
        sprite.setTexture(texture);
        if(rect != sf::IntRect(0, 0, 0, 0)){
           sprite.setTextureRect(rect);
        }
        sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);

    }

    void onDraw(sf::RenderWindow& window) {
        draw(window);
        for(auto child: children) {
            child->onDraw(window);
        }
    }

protected:
    virtual void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Sprite sprite;
    sf::Texture texture;
};
