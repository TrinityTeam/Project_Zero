#pragma once
#include "Core/StdTypes.hpp"
#include "Core/CommonEvents.hpp"
#include "Field.hpp"
#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>
using std::list;
using std::string;
using std::vector;


struct Hero {
    string name;
    string ownersName;
    u16 hp {};
};

struct Player {
    string name;
    u16 hp {};
};



class Logic {

    enum class Phase {Combat, Support, Assault, Preparing, PickingHeroes};

public:
    Logic(string firstPlayerName, string secondPlayerName):
        firstPlayer{firstPlayerName}, secondPlayer{secondPlayerName} {
        phases = {Phase::PickingHeroes};
        currentPhase = phases.begin();
        currentPlayer = &firstPlayer;
    }

    void startGame() {
        phases = {Phase::Assault, Phase::Combat, Phase::Preparing, Phase::Support};
        currentPlayer = &firstPlayer;
        field.clear();
        setHeroes();
        for(auto& hero: heroes) {
            if(hero.ownersName == firstPlayer.name) {
                field.placeHeroAt(0, 2, hero);
            } else {
                field.placeHeroAt(4, 2, hero);                
            }
        }
        firstPlayer.hp = 16;
        secondPlayer.hp = 16;

        std::cout << "The battle begins\n";
    }


    void processEvent(Event* event) {
        std::cout << "...\n";
        if(is_of_type<NextPhaseEvent>(event)) {
            nextPhase();
        }
        switch(*currentPhase) {
        case Phase::Combat:
            if(is_of_type<CellPickEvent>(event)) {
                auto _event = event_cast<CellPickEvent>(event);
                std::cout << "Picked (" << _event->row << ", " << _event->column << ")\n";
            }
            break;

        case Phase::Assault:
            break;

        case Phase::Preparing:
            break;

        case Phase::Support:
            break;

        case Phase::PickingHeroes:
            break;
        }
    }

private:
    void printPhase(Phase phase) {
        if(phase == Phase::Combat) std::cout << "Combat phase\n";
        else if(phase == Phase::Assault) std::cout << "Assault phase\n";
        else if(phase == Phase::Preparing) std::cout << "Preparing phase\n";
        else if(phase == Phase::Support) std::cout << "Support phase\n";
        else if(phase == Phase::PickingHeroes) std::cout << "All pick!\n";
    }
    
    void nextPhase() {
        currentPhase++;
        if(currentPhase == std::end(phases)) {
            currentPhase = std::begin(phases);
            currentPlayer = getNextPlayer();
            if(currentPlayer == &firstPlayer) std::cout << "First player's turn\n";
            else std::cout << "Second player's turn\n";
        }
        printPhase(*currentPhase);
    }

    void setHeroes() {
        heroes = {
            {"Vinktum", firstPlayer.name, 4},
            {"Ballistarius", firstPlayer.name, 3},
            {"Messum", firstPlayer.name, 2},

            {"Saxum", secondPlayer.name, 4},
            {"Cerberus", secondPlayer.name, 3},
            {"Manus", secondPlayer.name, 2}};
    }

    Player* getNextPlayer() {
        if(currentPlayer == &firstPlayer) {
            return &secondPlayer;
        } else {
            return &firstPlayer;
        }
    }

    Player firstPlayer, secondPlayer;
    Player* currentPlayer {};

    vector<Hero> heroes;
    list<Phase> phases;
    list<Phase>::const_iterator currentPhase;
    Field field;
};
