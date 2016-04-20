#include <iostream>
#include <cassert>
#include <stdexcept>
#include <vector>
#include "gtest/gtest.h"
#include <utility> // make_pair, pair
#include <array>

enum status { 
    DEAD, ALIVE
};

enum cellType {
    FREDKIN, CONWAY
};

using namespace std;

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
    virtual char print(void) const = 0;
    virtual bool isNeighbor(int myrow, int mycol, int n_row, int n_col) = 0;
    virtual ~AbstractCell() {};
};

class ConwayCell : public AbstractCell {
public:
    ConwayCell() 
        : AbstractCell() 
        {}
    ConwayCell(const char c) ;
    status isAlive(void) const;
    bool isNeighbor(int myrow, int mycol, int n_row, int n_col);
    void evolve(const int neighbors);
    char print(void) const;
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
    bool isNeighbor(int myrow, int mycol, int n_row, int n_col);
    void evolve(const int neighbors);
    char print(void) const;
    bool checkConway(void) const;
};

class Cell {
private:
    AbstractCell *cell; // starts off fredkin, turns into conway
    cellType type;
public:
    Cell();
    Cell(const char c);
    status isAlive(void) const;
    bool isNeighbor(int myrow, int mycol, int n_row, int n_col);
    void evolve(const int neighbors); // pointer to conway cell after turn 2
    char print(void) const;
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
    void print(void) const{
        int count = 0;
        while (count < row * col) {
            std::cout << cellGrid[count].print();
            count++;
            if (count % col == 0)
                std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    /* */
    void simulate(void) {
        for (int i = 0; i < row * col; i++) {
            neighborGrid[i] = getNumNeighbors(i / col, i % col);
        }
        for (int i = 0; i < row * col; i++) {
            cellGrid[i].evolve(neighborGrid[i]);
        }
    }

    int getNumNeighbors(int r, int c) {
        int directions = 8;
        bool isCell[8] = {true, true, true, true, true, true, true, true};
        int numAlive = 0;
        pair<int, int> neighPos[8] = {  make_pair(0, -1), make_pair(-1, -1), 
                                        make_pair(-1, 0), make_pair(-1, 1),
                                        make_pair(0, 1), make_pair(1, 1),
                                        make_pair(1, 0), make_pair(1, -1)};


        if (r == 0) {
            //A North cells are false
            isCell[1] = false; 
            isCell[2] = false;
            isCell[3] = false;  
        }

        if (c == 0) {
            //A West cells are false
            isCell[0] = false; 
            isCell[1] = false;
            isCell[7] = false;  
        }

        if (r == row-1) {
            //A North cells are false
            isCell[5] = false; 
            isCell[6] = false;
            isCell[7] = false;  
        }

        if (c == col-1) {
            //A North cells are false
            isCell[3] = false; 
            isCell[4] = false;
            isCell[5] = false;  
        }

        for (int i = 0; i < directions; i++) {
            if (isCell[i]) {
                int n_row = r + neighPos[i].first;
                int n_col = c + neighPos[i].second;
                
                if (cellGrid[n_row * col + n_col].isAlive() == ALIVE && cellGrid[r * col + c].isNeighbor(r, c, n_row, n_col))            
                    numAlive++;
            }
        }

        return numAlive;
    }

    int findPopulation() {
        int count = 0;
        for (int i = 0; i < row * col; i++) {
            count = cellGrid[i].isAlive() ? count + 1 : count;
        }
        return count;
    }

    T& at(int r, int c) {
        return cellGrid.at(r * col + c);
    }
};