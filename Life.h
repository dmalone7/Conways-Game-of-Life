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
    virtual char print(void) = 0;
    virtual bool isNeighbor(int myrow, int mycol, int n_row, int n_col) = 0;
    virtual ~AbstractCell() {}
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
    bool isNeighbor(int myrow, int mycol, int n_row, int n_col);
    void evolve(const int neighbors);
    char print(void);
    bool checkConway(void);
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
    void print(void) {
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


        if(r == 0) {
            //A North cells are false
            isCell[1] = false; 
            isCell[2] = false;
            isCell[3] = false;  
        }

        if(c == 0) {
            //A West cells are false
            isCell[0] = false; 
            isCell[1] = false;
            isCell[7] = false;  
        }

        if(r == row-1) {
            //A North cells are false
            isCell[5] = false; 
            isCell[6] = false;
            isCell[7] = false;  
        }

        if(c == col-1) {
            //A North cells are false
            isCell[3] = false; 
            isCell[4] = false;
            isCell[5] = false;  
        }

        for(int i = 0; i < directions; i++) {
            if(isCell[i]) {
                int n_row = r + neighPos[i].first;
                int n_col = c + neighPos[i].second;
                
                if(cellGrid[n_row * col + n_col].isAlive() == ALIVE && cellGrid[r * col + c].isNeighbor(r, c, n_row, n_col))            
                    numAlive++;
            }
        }

        return numAlive;
    }

    T& at(int r, int c) {
        return cellGrid.at(r * col + c);
    }


    // void simulateCorners() {
    //     int cases[4] = {0, col-1, (row-1)*col, row*col-1};

    //     //b c d
    //     //a * e
    //     //h g f
    //     //neighbors = {a, b, c, d, e, f, g, h}
    //     pair<int, int> neighbors[3];

    //     for (int corner : cases) {
    //         if(corner == 0) {
    //             neighbors[0] = make_pair(0, 1);
    //             neighbors[1] = make_pair(1, 0);
    //             neighbors[2] = make_pair(1, 1);
    //         }
    //         if(corner == col-1) {
    //             neighbors[0] = make_pair(0, col-2);
    //             neighbors[1] = make_pair(1, col-1);
    //             neighbors[2] = make_pair(1, col-2);
    //         }
    //         if(corner == (row-1)*col) {
    //             neighbors[0] = make_pair(row-2, 0);
    //             neighbors[1] = make_pair(row-1, 1);
    //             neighbors[2] = make_pair(row-2, 1);
    //         }
    //         if(corner == row*col-1) {
    //             neighbors[0] = make_pair(row-1, col-2);
    //             neighbors[1] = make_pair(row-2, col-1);
    //             neighbors[2] = make_pair(row-2, col-2);
    //         }

    //         int num_neighbor = 0;

    //         for(pair<int, int> neighbor : neighbors) {
    //             int myrow = corner / col;
    //             int mycol = corner % col;
    //             int n_row = neighbor.first;
    //             int n_col = neighbor.second;
    //             if (cellGrid[n_row * col + n_col].isAlive == ALIVE && cellGrid[corner].isNeighbor(myrow, mycol, n_row, n_col))
    //                 ++num_neighbor;
    //         }

    //         neighborGrid[corner] = num_neighbor;
    //     }
    // }

    // void simulateEdges() {
    //     int left[col-2];
    //     int right[col-2];
    //     int top[row-2];
    //     int bottom[row-2];

    //     for (int i = 1; i < col-1; i++) {
    //         left[i] = i * col;
    //         right[i] = (i + 1) * col - 1;
    //     }
    //     for (int i = 1; i < row-1; i++) {
    //         top[i] = i;
    //         bottom[i] = (row - 1) * col + i;
    //     }

    //     pair<int, int> neighbors[5];
    //     for (int edge : left) {
    //         int myrow = edge / col;
    //         int mycol = edge % col;
    //         neighbors[0] = make_pair(myrow-1, mycol);
    //         neighbors[1] = make_pair(myrow-1, mycol+1);
    //         neighbors[2] = make_pair(myrow, mycol+1);
    //         neighbors[3] = make_pair(myrow+1, mycol+1);
    //         neighbors[4] = make_pair(myrow+1, mycol);
    //     }
    //     for (int edge : right) {
    //         int myrow = edge / col;
    //         int mycol = edge % col;
    //         neighbors[0] = make_pair(myrow-1, mycol);
    //         neighbors[1] = make_pair(myrow-1, mycol-1);
    //         neighbors[2] = make_pair(myrow, mycol-1);
    //         neighbors[3] = make_pair(myrow+1, mycol-1);
    //         neighbors[4] = make_pair(myrow+1, mycol);
    //     }
    //     for (int edge : top) {
    //         int myrow = edge / col;
    //         int mycol = edge % col;
    //         neighbors[0] = make_pair(myrow, mycol-1);
    //         neighbors[1] = make_pair(myrow+1, mycol-1);
    //         neighbors[2] = make_pair(myrow+1, mycol);
    //         neighbors[3] = make_pair(myrow+1, mycol+1);
    //         neighbors[4] = make_pair(myrow, mycol+1);
    //     }
    //     for (int edge : bottom) {
    //         int myrow = edge / col;
    //         int mycol = edge % col;
    //         neighbors[0] = make_pair(myrow, mycol-1);
    //         neighbors[1] = make_pair(myrow-1, mycol-1);
    //         neighbors[2] = make_pair(myrow-1, mycol);
    //         neighbors[3] = make_pair(myrow-1, mycol+1);
    //         neighbors[4] = make_pair(myrow, mycol+1);
    //     }
    // }
};