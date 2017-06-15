#pragma once
#include "Event.hpp"



class CellPickEvent: public Event {
    EVENT

public:
    CellPickEvent(u16 row, u16 column):
        row {row}, column {column} {}

    u16 row {};
    u16 column {};
};
REGISTER_EVENT(CellPickEvent);


class Hero;
class HeroPickEvent: public Event {
    EVENT

public:
    HeroPickEvent(Hero& pickedHero):
        pickedHero {pickedHero} {}

    Hero& pickedHero;
};
REGISTER_EVENT(HeroPickEvent);



class SkillPickEvent: public Event {
    EVENT
};
REGISTER_EVENT(SkillPickEvent);



class NextPhaseEvent: public Event {
    EVENT
};
REGISTER_EVENT(NextPhaseEvent);



class HeroMovedEvent: public Event {
    EVENT
public:

    Hero& hero;
};
REGISTER_EVENT(HeroMovedEvent);



class HeroBuffedEvent: public Event {
    EVENT
};
REGISTER_EVENT(HeroBuffedEvent);



class HeroPassedAwayEvent: public Event {
    EVENT
};
REGISTER_EVENT(HeroPassedAwayEvent);