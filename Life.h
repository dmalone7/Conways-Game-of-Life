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

class AbstractCell {
    protected:
        bool alive;

    public:
        /**
         * O(1) in space
         * O(1) in time
         * 
         * AbstractCell constructor that initializes
         * alive to false
         */
        AbstractCell() :
            alive(false) 
            {}

        /**
        * AbstractCell destructor
        */
        virtual ~AbstractCell() 
            {}

        /**
        * abstract method
        * @param neighbors taking the number of numbers around cell
        */
        virtual void evolve(const int neighbors) = 0;

        /**
        * abstract method
        * Given current row and col and another cell's row and coll
        * checks to see if the other cell is a neighbor
        *
        * @param myrow is the row position of this cell
        * @param mycol is the col position of this cell
        * @param n_row is the row position of neighbor cell
        * @param n_col is the col position of neighbor cell
        * @return true if considered neighbor for the implemented cell
        */
        virtual bool isNeighbor(int myrow, int mycol, int n_row, int n_col) = 0;

        virtual char write(void) const = 0;

        // virtual AbstractCell* clone (void) const = 0;

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @return if data member of alive is true then return
         * ALIVE else return DEAD
         */
        virtual status isAlive() const {
            return alive ? ALIVE : DEAD;
        }
};

class ConwayCell : public AbstractCell {
    public:
        /**
         * O(1) in space
         * O(1) in time
         * 
         * ConwayCell default constructor.
         * Initializes alive to false
         */
        ConwayCell() :
            AbstractCell() 
            {}

        /**
         * O(1) in space
         * O(1) in time
         * 
         * ConwayCell constructor.
         * Initialive alive member to true if '*'
         * else false
         */
        ConwayCell(const char c);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * Follows the rules of conway cell.
         *  a dead cell becomes a live cell, if exactly 3 neighbors are alive
         *  a live cell becomes a dead cell, if less than 2 or more than 3 neighbors are alive
         *
         * @param neighbors is the number of neighbors around this cell
         */
        void evolve(const int neighbors);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * If the other cell diagonally or otherwise one away
         * then it is a neighbor
         * @param myrow is the row position of this cell
         * @param mycol is the col position of this cell
         * @param n_row is the row position of neighbor cell
         * @param n_col is the col position of neighbor cell
         * @return true if cell diagonally or otherwise one away
         * then return true
         */
        bool isNeighbor(int myrow, int mycol, int n_row, int n_col);

        /**
         * O(1) in space
         * O(1) in time
         * return the appropriate symbol for Conway Cell. Either
         * '*' or '.' 
         *
         * @return '*' if cell is alive and '.' if dead
         */   
        char write(void) const;

};

class FredkinCell : public AbstractCell {
    private:
        int age;

    public:
        /**
         * O(1) in space
         * O(1) in time
         * 
         * Default constructor for Fredkin Cell.
         * Initialize age to 0 and alive to false.
         */
        FredkinCell() : 
            AbstractCell(), age(0) 
            {}

        /**
         * O(1) in space
         * O(1) in time
         *
         * Constructor for Fredkin Cell.
         * Initialize age to 0 and alive to appropriate
         * value for char c
         *
         * @param c is either '0' which sets alive to true
         * or '-' which sets alive to false
         */
        FredkinCell(const char c);

        /**
         * O(1) in space
         * O(1) in time
         *
         * Follow the rules of Fredkin Cell:
         *  a dead cell becomes a live cell, if 1 or 3 neighbors are alive
         *  a live cell becomes a dead cell, if 0, 2, or 4 neighbors are alive
         * 
         * @param neighbors is the number of neighbors around this Cell 
         */
        void evolve(const int neighbors);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * If the other cell NORTH, SOUTH, EAST, or WEST 
         * then it is a neighbor
         *
         * @param myrow is the row position of this cell
         * @param mycol is the col position of this cell
         * @param n_row is the row position of neighbor cell
         * @param n_col is the col position of neighbor cell
         * @return true if NORTH, SOUTH, EAST, or WEST otherwise
         * false
         */
        bool isNeighbor(int myrow, int mycol, int n_row, int n_col);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * if alive and age is between 0 to 9 then return char of age
         * else if alive return '+'
         * else return '-'
         * 
         * @return a char that is either 0-9, '-', '+' based on age
         * and alive data members
         */
        char write(void) const;


        /**
         * O(1) in space
         * O(1) in time
         * 
         * checks to see if the current Fredkin Cell should
         * be transformed to a Conway Cell
         * 
         * @return true if age is 2
         */
        bool turnConway(void) const;
};

class Cell {
    private:
        AbstractCell *cell;
        cellType type;

    public:
        /**
         * O(1) in space
         * O(1) in time
         * 
         * Default constructor for Cell
         * Initialize cell to a dead Fredkin Cell,
         * alive to false, and type to FREDKIN
         */
        Cell(void);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * Default constructor for Cell
         * Initialize cell to a dead Fredkin Cell,
         * alive to false, and type to FREDKIN
         *
         * @param c is a char that only be '0' or '*'
         * otherwise an error is thrown
         */
        Cell(const char c);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * If Fredkin cell is alive and age is 2 then
         * convert cell to a Conway cell.
         * Otherwise follow cell's corresponding rule
         * 
         * @param neighbors is the number of neighbors around
         * this cell
         */
        void evolve(const int neighbors);

        /**
         * O(1) in space
         * O(1) in time
         * calls the this cell's isNeighbor
         * 
         * @param myrow is the row position of this cell
         * @param mycol is the col position of this cell
         * @param n_row is the row position of neighbor cell
         * @param n_col is the col position of neighbor cell
         * @return if other cell is a neighbor to this cell
         */
        bool isNeighbor(int myrow, int mycol, int n_row, int n_col);
  
        /**
         * O(1) in space
         * O(1) in time
         *
         * call this cell's write method
         * 
         * @return this cell's corresponding symbol
         */      
        char write(void) const;

        /**
         * O(1) in space
         * O(1) in time
         * 
         * call the abstract class implementation
         * of isAlive
         * @return status which is ALIVE if alive is true else DEAD
         */
        status isAlive(void) const;
};

template <typename T>
class Life {
    /**
     * O(1) in space
     * O(1) in time
     * 
     * @param 
     * @return 
     */
    friend void operator >> (std::istream& lhs, Life& rhs) {
        return rhs.read(lhs);}

    /**
     * O(1) in space
     * O(1) in time
     * 
     * @param 
     * @return 
     */
    friend std::ostream& operator << (std::ostream& lhs, const Life& rhs) {
        return rhs.write(lhs);}

    private:
        FRIEND_TEST(LifeFixture, constructorTest1);
        FRIEND_TEST(LifeFixture, constructorTest2);
        FRIEND_TEST(LifeFixture, constructorTest3);
        FRIEND_TEST(LifeFixture, readTest1);
        FRIEND_TEST(LifeFixture, readTest2);
        FRIEND_TEST(LifeFixture, readTest3);
        FRIEND_TEST(LifeFixture, writeTest1);
        FRIEND_TEST(LifeFixture, writeTest2);
        FRIEND_TEST(LifeFixture, writeTest3);
        FRIEND_TEST(LifeFixture, operatorReadTest1);
        FRIEND_TEST(LifeFixture, operatorReadTest2);
        FRIEND_TEST(LifeFixture, operatorReadTest3);
        std::vector<T> cellGrid;
        std::vector<int> neighborGrid;
        int row;
        int col;

        /**
         * O(N) in space
         * O(N) in time
         * 
         * Read the istream and get each char.
         * Add a new cell to cellGrid
         * 
         * @param in is the input stream
         */
        void read(std::istream& in) {
            char c;
            for (int ndx = 0; ndx < row * col; ndx++) {
                in >> c;
                T cell(c);
                cellGrid.push_back(cell);
            }
        }

        /**
         * O(1) in space
         * O(1) in time
         * 
         * Writes all the cell in the grid to an output stream
         *
         * @param the output stream to write to
         * @return output stream that has been written to
         */
        std::ostream& write(std::ostream& out) const {
            int count = 0;
            while (count < row * col) {
                out << cellGrid[count].write();
                count++;
                if (count % col == 0)
                    out << std::endl;
            }
            return out;
        }

    public:
        /**
         * O(1) in space
         * O(1) in time
         * 
         * Initialize row and col to r and c, respectively,
         * and initalize cellGrida and neighborGrid
         *
         * @param r is the number of rows in the grid
         * @param c is the number of columns in the grid
         */
        Life(int r, int c) : row(r), col(c) {
            cellGrid = std::vector<T>(0);
            neighborGrid = std::vector<int>(r * c);
        }

        /**
         * O(1) in space
         * O(1) in time
         * 
         * Iterate through each cell, update the number of neighbors
         * in the neighborGrid vector, then iterate through again
         * evolving each creature.
         */
        void simulate() {
            for (int i = 0; i < row * col; i++) {
                neighborGrid[i] = getNumNeighbors(i / col, i % col);
            }
            for (int i = 0; i < row * col; i++) {
                cellGrid[i].evolve(neighborGrid[i]);
            }
        }

        /**
         * O(1) in space
         * O(n) in time
         * 
         * Call simulate rounds times
         * 
         * @param rounds is the number of times that
         * simulate() will be called
         */
        void simulate(int rounds) {
            for (int i = 0; i < rounds; i++) {
                simulate();
            }
        }

        /**
         * O(1) in space
         * O(1) in time
         * 
         * Takes the care of all corner cases.
         * Checks all adjacent cells and counts the number of neighbors
         *
         * @param r is the row position in the grid
         * @param c is the column position in the grid
         * @return is the number of neighbors for cell at (r,c)
         */
        int getNumNeighbors(int r, int c) {
            int directions = 8;
            bool isCell[8] = {true, true, true, true, true, true, true, true};
            int numAlive = 0;
            std::pair<int, int> neighPos[8] = {  std::make_pair(0, -1), std::make_pair(-1, -1), 
                                                 std::make_pair(-1, 0), std::make_pair(-1, 1),
                                                 std::make_pair(0, 1), std::make_pair(1, 1),
                                                 std::make_pair(1, 0), std::make_pair(1, -1) };
            //A North cells are false
            if (r == 0) {
                isCell[1] = false; 
                isCell[2] = false;
                isCell[3] = false;  
            }
            //A West cells are false
            if (c == 0) {
                isCell[0] = false; 
                isCell[1] = false;
                isCell[7] = false;  
            }
            //A South cells are false
            if (r == row-1) {
                isCell[5] = false; 
                isCell[6] = false;
                isCell[7] = false;  
            }
            //A East cells are false
            if (c == col-1) {
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

        /**
         * O(1) in space
         * O(N) in time
         * 
         * Iterate through each cell in grid and count the number
         * of alive cells
         *
         * @return the number of alive cells in grid
         */
        int findPopulation() {
            int count = 0;
            for (int i = 0; i < row * col; i++) {
                count = cellGrid[i].isAlive() ? count + 1 : count;
            }
            return count;
        }

        /**
         * O(1) in space
         * O(1) in time
         * 
         * Get the cell at (r,c)
         *
         * @param r is the row position of the cell
         * @param c is the column postion of the cell
         * @return the desired cell
         */
        T& at(int r, int c) {
            return cellGrid.at(r * col + c);
        }

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @return pointer to the first cell
         */
        T* begin() {
            return &cellGrid[0];
        }

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @return pointer to the end of the vector gridCell
         */
        T* end() {
            T* p = &cellGrid[row*col - 1];
            return ++p;
        }
};