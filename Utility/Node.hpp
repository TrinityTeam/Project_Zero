#pragma once
#include <list>
#include <memory>
#include <algorithm>



class Node {
public:
    Node() = default;
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;

    void attachChild(std::unique_ptr<Node> child) {
        if(child != nullptr) {
            child->parent = this;
            children.emplace_back(child.release());
        } else {
            throw std::invalid_argument {"Child pointer is null"};
        }
    }

    std::unique_ptr<Node> detachChild(const Node* child) {
        auto childIter = 
            std::find_if(children.begin(), children.end(), 
                         [child](auto& elem){ return elem.get() == child;});
        if(childIter != children.end()) {
            Node* child = childIter->release();
            children.erase(childIter);
            child->parent = nullptr;
            
            return std::unique_ptr<Node>(child);

        } else {
            throw std::out_of_range {"Node " + std::to_string(intptr_t(child)) +
                                     " is not a child of " + std::to_string(intptr_t(this))};
        }
    }

    const Node* getParent() const {
        return parent;
    }

private:
    std::list<std::unique_ptr<Node>> children;
    const Node* parent;
};