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
         * @param 
         * @return 
         */
        AbstractCell() :
            alive(false) 
            {}

        virtual ~AbstractCell() 
            {}

        virtual void evolve(const int neighbors) = 0;

        virtual bool isNeighbor(int myrow, int mycol, int n_row, int n_col) = 0;

        virtual char write(void) const = 0;

        // virtual AbstractCell* clone (void) const = 0;

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
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
         * @param 
         * @return 
         */
        ConwayCell() :
            AbstractCell() 
            {}

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        ConwayCell(const char c);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        void evolve(const int neighbors);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        bool isNeighbor(int myrow, int mycol, int n_row, int n_col);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */   
        char write(void) const;

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        // ConwayCell* clone () const {
        //     return new ConwayCell(*this);
        // }
};

class FredkinCell : public AbstractCell {
    private:
        int age;

    public:
        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        FredkinCell() : 
            AbstractCell(), age(0) 
            {}

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        FredkinCell(const char c);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        void evolve(const int neighbors);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        bool isNeighbor(int myrow, int mycol, int n_row, int n_col);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        char write(void) const;

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        // FredkinCell* clone () const {
        //     return new FredkinCell(*this);
        // }

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
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
         * @param 
         * @return 
         */
        Cell(void);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        Cell(const char c);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        void evolve(const int neighbors);

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        bool isNeighbor(int myrow, int mycol, int n_row, int n_col);
  
        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */      
        char write(void) const;

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
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
        std::vector<T> cellGrid;
        std::vector<int> neighborGrid;
        int row;
        int col;

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
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
         * @param 
         * @return 
         */
        std::ostream& write(std::ostream& out) const {
            int count = 0;
            while (count < row * col) {
                out << cellGrid[count].write();
                count++;
                if (count % col == 0)
                    out << std::endl;
            }
            out << std::endl;
            return out;
        }

    public:
        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        Life(int r, int c) : row(r), col(c) {
            cellGrid = std::vector<T>(0);
            neighborGrid = std::vector<int>(r * c);
        }

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        void simulate(void) {
            for (int i = 0; i < row * col; i++) {
                neighborGrid[i] = getNumNeighbors(i / col, i % col);
            }
            for (int i = 0; i < row * col; i++) {
                cellGrid[i].evolve(neighborGrid[i]);
            }
        }

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
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
         * @param 
         * @return 
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
            //A North cells are false
            if (r == row-1) {
                isCell[5] = false; 
                isCell[6] = false;
                isCell[7] = false;  
            }
            //A North cells are false
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
         * O(1) in time
         * 
         * @param 
         * @return 
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
         * @param 
         * @return 
         */
        T& at(int r, int c) {
            return cellGrid.at(r * col + c);
        }

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        T& begin() {
            return cellGrid.begin();
        }

        /**
         * O(1) in space
         * O(1) in time
         * 
         * @param 
         * @return 
         */
        T& end() {
            return cellGrid.end();
        }
};