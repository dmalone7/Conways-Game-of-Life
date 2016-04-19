#include <iostream>
#include <cassert>
#include <stdexcept>
#include <vector>
#include "gtest/gtest.h"

enum status { 
    DEAD, ALIVE
};

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
    virtual status isAlive(void) const = 0;
    virtual void evolve(const int neighbors) = 0;
    virtual char print(void) = 0;
};

class ConwayCell : public AbstractCell {
public:
    ConwayCell() 
        : AbstractCell() 
        {}
    ConwayCell(const char c) ;
    status isAlive(void) const;
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
    status isAlive(void) const;
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
    status isAlive(void) const;
    void evolve(const int neighbors); // pointer to conway cell after turn 2
    char print(void);
};

template <typename T>
class Life {
private:
    int row;
    int col;
    std::vector<T> cellGrid;
    std::vector<int> neighborGrid;
public:
    /* */
    Life(int r, int c) : row(r), col(c) {
        cellGrid = std::vector<T>(0);
        neighborGrid = std::vector<int>(r * c);
    }

    /* */
    void read(std::istream& i) {
        char c;
        int count = 0;
        while (count < row * col) {
            i >> c;
            T cell(c);
            cellGrid.push_back(cell);
            count++;
        }
    }

    /* */
    std::ostream& print(void) {
        int count = 0;
        while (count < row * col) {
            std::cout << cellGrid[count].print();
            count++;
            if (count % col == 0)
                std::cout << std::endl;
        }
        return std::cout;
    }

    /* */
    void simulate(void) {
        return;
    }
};