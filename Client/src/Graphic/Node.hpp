#pragma once



class Node {
public:
    Node(Node* parent = nullptr) {
        parent->addChild(this);
        position = parent->position;
    }

    void addChild(Node* child) {
        for(Node* ancestor = this; ancestor != nullptr; ancestor = ancestor->parent) {
            if(ancestor == child) throw std::logic_error("Sprite's child cannot be its ancestor");
        }
        if(child->parent != this) {
            children.push_back(child);
            child->parent = this;
        }
    }



private:
    list<Sprite*> children;
    Sprite* parent = nullptr;
    sf::Vector2f position;
};
