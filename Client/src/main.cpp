#include "Client.hpp"
#include <iostream>



int main() {
    try {
        Client {}.run();
        
    } catch(std::exception& e) {
        std::cout << e.what() << '\n';
    }

    return 0;
}
