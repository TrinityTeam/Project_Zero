#include "Logic/Logic.hpp"
#include <iostream>


int main() {
    Logic logic("Ventru", "Nosferatu");
    Hero hero;
    hero.name = "Vinktum";
    HeroPickEvent event(hero);
    NextPhaseEvent next;
    logic.processEvent(&next);
    logic.startGame();
    return 0;
}
