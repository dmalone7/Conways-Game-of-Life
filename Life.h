#include <iostream>
#include <cassert>
#include <stdexcept>
#include "gtest/gtest.h"

class AbstractCell {
protected:
    FRIEND_TEST(ConwayCell, defaultConstrutor2);
    FRIEND_TEST(FredkinCell, defaultConstrutor2);
    FRIEND_TEST(Cell, defaultConstrutor2);
    bool alive;
public:
    AbstractCell() 
        : alive(false) 
        {}
    virtual void evolve(const int neighbors) = 0;
    virtual char print(void) = 0;
};

class ConwayCell : public AbstractCell {
public:
    ConwayCell() 
        : AbstractCell() 
        {}
    ConwayCell(const char c) ;
    void evolve(const int neighbors);
    char print(void);
};

class FredkinCell : public AbstractCell {
private:
    int age;
public:
    FredkinCell() 
        : AbstractCell(), age(0) 
        {}
    FredkinCell(const char c);
    void evolve(const int neighbors);
    char print(void);
};

class Cell {
private:
    AbstractCell *cell; // starts off fredkin, turns into conway
    bool alive;
    int age;
public:
    Cell();
    Cell(const char c);
    void evolve(const int neighbors); // pointer to conway cell after turn 2
    char print(void);
};

template <typename T>
class Life {
    void read(std::istream &i);
    std::ostream& print(void);
    void simulate(void);
};