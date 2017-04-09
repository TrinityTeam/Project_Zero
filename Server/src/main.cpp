#include "Server.hpp"
#include <iostream>



int main() {
    try {
        Server{}.start();

    } catch(std::exception& e) {
        std::cout << e.what() << '\n';
    }
}