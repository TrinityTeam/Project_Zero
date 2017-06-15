#pragma once
#include <vector>
#include <string>
#include <stdexcept>
using std::vector;
using std::string;
class Hero;



class Field {
public:
    struct Cell {
        Cell(const string& type, bool hasTower = false): type {type}, hasTower{hasTower} {}
        string type;
        bool hasTower = false;
        vector<Hero*> heroes;
    };

    Field() {
        setDefault();
    }

    void placeHeroAt(u16 row, u16 column, Hero& hero) {
        if(isValidCoords(row, column)) {
            if(cells[column][row].type == "Castle" or cells[column][row].heroes.size() == 0) {
                cells[column][row].heroes.push_back(&hero);
            } else {
                throw std::logic_error("Cell is already occupated");
            }
        } else {
            throw std::out_of_range("Invalid cell coordinates");
        }
    }

    Hero& getHeroAt(u16 row, u16 column) {
        if(isValidCoords(row, column)) {
            if(cells[column][row].heroes.size() == 1)  {
                return *cells[column][row].heroes.front();
            
            } else if (cells[column][row].heroes.size() == 0) {
                throw std::logic_error("The cell ("+std::to_string(row)+", "+
                                        std::to_string(column)+") is empty");
            } else {
                throw std::logic_error("The cell ("+std::to_string(row)+", "+
                                        std::to_string(column)+") has several heroes");
            }
        } else {
            throw std::out_of_range("Invalid cell coordinates");
        }
    }

    vector<Hero*>& getHeroesAt(u16 row, u16 column) {
        if(isValidCoords(row, column)) {
            return cells[column][row].heroes;
        }
    }

    void clear() {
        setDefault();
    }

private:
    void setDefault() {
        cells = {
                    {Cell("Forest"), Cell("Plains", true), Cell("Hill")},
                {Cell("Plains"), Cell("Hill"), Cell("Forest"), Cell("Plains")},
            {Cell("Castle"), Cell("Plains"), Cell("Lake"), Cell("Plains"), Cell("Castle")},
                {Cell("Forest"), Cell("Lake"), Cell("Lake"), Cell("Plains")},
                    {Cell("Plains"), Cell("Hill", true), Cell("Forest")}
        };
    }

    bool isValidCoords(u16 row, u16 column) {
        if(column < 5 and (((column == 0 or column == 4) and row < 3) or 
                           ((column == 1 or column == 3) and row < 4) or 
                           row < 5))  {
            return true;
        }
        return false;
    }

    vector<vector<Cell>> cells;
};
