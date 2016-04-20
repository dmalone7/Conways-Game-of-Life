#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "Life.h"

using namespace std;

// ----------
// ConwayCell
// ----------

TEST(ConwayCellFixture, defaultConstrutorTest1) {
    ConwayCell cell;
    ASSERT_EQ('.', cell.write());
}

TEST(ConwayCellFixture, defaultConstrutorTest2) {
    ConwayCell cell;
    ASSERT_EQ(false, cell.isAlive());
}

TEST(ConwayCellFixture, defaultConstrutorTest3) {
    ConwayCell cell;
    cell.evolve(4);
    ASSERT_EQ('.', cell.write());
}

TEST(ConwayCellFixture,charConstrutorTest1) {
    ConwayCell cell('*');
    ASSERT_EQ('*', cell.write());
}

TEST(ConwayCellFixture,charConstrutorTest2) {
    ConwayCell cell('.');
    ASSERT_EQ('.', cell.write());
}

TEST(ConwayCellFixture,charConstrutorTest3) {
    try {
        ConwayCell cell('c');
        ASSERT_EQ('.', cell.write());
    }
    catch (runtime_error re)
    {
        ConwayCell cell('.');
        ASSERT_EQ('.', cell.write());
    }
}

TEST(ConwayCellFixture, evolveTest1) {
    ConwayCell cell('.');
    cell.evolve(3);
    ASSERT_EQ(ALIVE, cell.isAlive());
}

TEST(ConwayCellFixture, evolveTest2) {
    ConwayCell cell('.');
    cell.evolve(4);
    ASSERT_EQ(DEAD, cell.isAlive());
}

TEST(ConwayCellFixture, evolveTest3) {
    ConwayCell cell('*');
    cell.evolve(1);
    ASSERT_EQ(DEAD, cell.isAlive());
}

TEST(ConwayCellFixture, evolveTest4) {
    ConwayCell cell('*');
    cell.evolve(3);
    ASSERT_EQ(ALIVE, cell.isAlive());
}

TEST(ConwayCellFixture, isNeighborTest1) {
    ConwayCell cell('*');
    bool b = cell.isNeighbor(0, 0, 2, 1);
    ASSERT_FALSE(b);
}

TEST(ConwayCellFixture, isNeighborTest2) {
    ConwayCell cell('*');
    bool b = cell.isNeighbor(0, 0, 1, 0);
    ASSERT_TRUE(b);
}

TEST(ConwayCellFixture, isNeighborTest3) {
    ConwayCell cell('*');
    bool b = cell.isNeighbor(1, 0, 2, 1);
    ASSERT_TRUE(b);
}

TEST(ConwayCellFixture, writeTest1) {
    ConwayCell cell('*');
    ASSERT_EQ('*', cell.write());
}

TEST(ConwayCellFixture, writeTest2) {
    ConwayCell cell('.');
    ASSERT_EQ('.', cell.write());
}

TEST(ConwayCellFixture, writeTest3) {
    ConwayCell cell;
    ASSERT_EQ('.', cell.write());
}

// -----------
// FredkinCell
// -----------

TEST(FredkinCellFixture, defaultConstrutorTest1) {
    FredkinCell cell;
    ASSERT_EQ('-', cell.write());
}

TEST(FredkinCellFixture, defaultConstrutorTest2) {
    FredkinCell cell;
    ASSERT_EQ(false, cell.isAlive());
}

TEST(FredkinCellFixture, defaultConstrutorTest3) {
    FredkinCell cell;
    cell.evolve(1);
    ASSERT_EQ('0', cell.write());
}

TEST(FredkinCellFixture, defaultConstrutorTest4) {
    try {
        FredkinCell cell('+');
        cell.evolve(1);
        ASSERT_TRUE(false);
    }
    catch(std::runtime_error e) {
        ASSERT_TRUE(true);
    }
    
}
//Test FredkinCell::evolve(const int neighbors)
//Test all four cases
TEST(FredkinCellFixture, evolveTest1) {
    //DEAD -> ALIVE
    FredkinCell cell('-');
    cell.evolve(3);
    ASSERT_EQ(ALIVE, cell.isAlive());
}

TEST(FredkinCellFixture, evolveTest2) {
    //DEAD -> DEAD
    FredkinCell cell('-');
    cell.evolve(2);
    ASSERT_EQ(DEAD, cell.isAlive());
}

TEST(FredkinCellFixture, evolveTest3) {
    //ALIVE -> ALIVE
    FredkinCell cell('0');
    cell.evolve(3);
    ASSERT_EQ(ALIVE, cell.isAlive());
}

TEST(FredkinCellFixture, evolveTest4) {
    //ALIVE -> DEAD
    FredkinCell cell('0');
    cell.evolve(0);
    ASSERT_EQ(DEAD, cell.isAlive());
}

TEST(FredkinCellFixture, isNeighborTest1) {
    //neighbor is diagnol to cell
    FredkinCell cell;
    bool isNeigh = cell.isNeighbor(0,0,1,1);
    ASSERT_FALSE(isNeigh);
}

TEST(FredkinCellFixture, isNeighborTest2) {
    //neighbor is one below cell
    FredkinCell cell;
    bool isNeigh = cell.isNeighbor(0,0,1,0);
    ASSERT_TRUE(isNeigh);
}

TEST(FredkinCellFixture, isNeighborTest3) {
    //neighbor is far away from neighbor
    FredkinCell cell;
    bool isNeigh = cell.isNeighbor(0,0,2,2);
    ASSERT_FALSE(isNeigh);
}

//output of Fredkin Cell
TEST(FredkinCellFixture, writeTest1) {
    //Test "+"
    FredkinCell cell('0');
    ASSERT_EQ(cell.write(), '0');
    for(int i = 0; i < 10; i++)
        cell.evolve(3);
    ASSERT_EQ(cell.write(), '+');
}

TEST(FredkinCellFixture, writeTest2) {
    FredkinCell cell;
    ASSERT_EQ(cell.write(), '-');
}

TEST(FredkinCellFixture, writeTest3) {
    FredkinCell cell('0');
    ASSERT_EQ(cell.write(), '0');
    //Test if age is printed properly
    for(int i = 1; i <= 5; i++)
        cell.evolve(3);
    ASSERT_EQ(cell.write(), '5');
}
//Test if Fredkin should become Conway in Cell simulation
TEST(FredkinCellFixture, turnConwayTest1) {
    FredkinCell cell('0');
    //ALIVE
    ASSERT_FALSE(cell.turnConway());
    cell.evolve(3);
    //ALIVE
    ASSERT_FALSE(cell.turnConway());
    cell.evolve(3);
    //ALIVE
    ASSERT_TRUE(cell.turnConway());
}

TEST(FredkinCellFixture, turnConwayTest2) {
    FredkinCell cell('-');
    //DEAD
    ASSERT_FALSE(cell.turnConway());
    cell.evolve(2);
    //DEAD
    ASSERT_FALSE(cell.turnConway());
    cell.evolve(2);
    //DEAD
    ASSERT_FALSE(cell.turnConway());
}

TEST(FredkinCellFixture, turnConwayTest3) {
    FredkinCell cell('-');
    //DEAD
    ASSERT_FALSE(cell.turnConway());
    cell.evolve(3);
    //ALIVE
    ASSERT_FALSE(cell.turnConway());
    cell.evolve(3);
    //ALIVE
    ASSERT_FALSE(cell.turnConway());
    //DEAD
    cell.evolve(0);
    ASSERT_FALSE(cell.turnConway());
}


// ----
// Cell
// ----
//Test Cell constructors
//all intialize of Cell should be a dead Fredkin Cell
TEST(CellFixture, defaultConstructorTest1) {
    Cell cell;
    ASSERT_EQ('-', cell.write());
}

TEST(CellFixture, defaultConstructorTest2) {
    Cell cell;
    ASSERT_EQ(DEAD, cell.isAlive());
}

TEST(CellFixture, defaultConstructorTest3) {
    Cell cell;
    ASSERT_EQ(DEAD, cell.isAlive());
    cell.evolve(3);
    ASSERT_EQ(ALIVE, cell.isAlive());
}

TEST(CellFixture, charConstructorTest1) {
    //try to initialize Cell to a live Fredkin Cell
    try {
        Cell cell('9');
        ASSERT_FALSE(true);
    }
    catch(std::runtime_error e) {
        ASSERT_TRUE(true);
    }
}

TEST(CellFixture, charConstructorTest2) {
    Cell cell('0');
    ASSERT_EQ('0', cell.write());
}

TEST(CellFixture, charConstructorTest3) {
    //try to initialize Cell to a Conway cell
    try {
        Cell cell('*');
        ASSERT_FALSE(true);
    }
    catch(std::runtime_error e) {
        ASSERT_TRUE(true);
    }
}

TEST(CellFixture, evolveTest1) {
    Cell cell;
    //Fredkin Cell - DEAD
    ASSERT_EQ('-', cell.write());
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Conway Cell - ALIVE
    ASSERT_EQ('*', cell.write());
}

TEST(CellFixture, evolveTest2) {
    Cell cell;
    ASSERT_EQ('-', cell.write());
    //Fredkin Cell - DEAD
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Conway Cell - ALIVE
    ASSERT_EQ('*', cell.write());
    cell.evolve(2);  
    //Conway Cell - ALIVE
    ASSERT_EQ('*', cell.write());
    cell.evolve(1);
    //Conway Cell - DEAD
    ASSERT_EQ('.', cell.write());
}

TEST(CellFixture, evolveTest3) {
    Cell cell;
    ASSERT_EQ('-', cell.write());
    //Fredkin Cell - DEAD
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(2);
    //Fredkin Cell - DEAD
    ASSERT_EQ('-', cell.write());
    cell.evolve(2);  
    //Fredkin Cell - DEAD
    ASSERT_EQ('-', cell.write());
    cell.evolve(1);
    //Fredkin Cell - ALIVE
    ASSERT_EQ('1', cell.write());
    cell.evolve(3);
    ASSERT_EQ('*', cell.write());    
}

TEST(CellFixture, isNeighborTest1) {
    Cell cell;
    //Fredkin Cell - DEAD
    ASSERT_FALSE(cell.isNeighbor(0,0,1,1));
}

TEST(CellFixture, isNeighborTest2) {
     Cell cell;
    //Fredkin Cell - DEAD
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Conway Cell - ALIVE
    ASSERT_TRUE(cell.isNeighbor(0,0,1,1));
}

TEST(CellFixture, isNeighborTest3) {
    Cell cell;
    //Fredkin Cell - DEAD
    ASSERT_FALSE(cell.isNeighbor(1,3,2,2));
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Conway Cell - ALIVE
    ASSERT_TRUE(cell.isNeighbor(0,0,1,1));
}

TEST(CellFixture, writeTest1) {
    Cell cell;
    //Fredkin Cell - DEAD
    ASSERT_EQ('-',cell.write());
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    ASSERT_EQ('0',cell.write());
}

TEST(CellFixture, writeTest2) {
    Cell cell;
    //Fredkin Cell - DEAD
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Conway Cell - ALIVE
    ASSERT_EQ('*',cell.write());
}

TEST(CellFixture, writeTest3) {
    Cell cell;
    //Fredkin Cell - DEAD
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Conway Cell - ALIVE
    ASSERT_EQ('*',cell.write());
    cell.evolve(1);
    //Conway Cell - DEAD
    ASSERT_EQ('.',cell.write());
}

TEST(CellFixture, isAliveTest1) {
    Cell cell;
    //Fredkin Cell - DEAD
    ASSERT_EQ(DEAD,cell.isAlive());
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    ASSERT_EQ(ALIVE,cell.isAlive());
}

TEST(CellFixture, isAliveTest2) {
    Cell cell;
    //Fredkin Cell - DEAD
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Conway Cell - ALIVE
    ASSERT_EQ(ALIVE,cell.isAlive());    
}

TEST(CellFixture, isAliveTest3) {
    Cell cell;
    //Fredkin Cell - DEAD
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Fredkin Cell - ALIVE
    cell.evolve(3);
    //Conway Cell - ALIVE
    ASSERT_EQ(ALIVE,cell.isAlive());
    cell.evolve(1);
    //Conway Cell - DEAD
    ASSERT_EQ(DEAD,cell.isAlive());
}



// ----
// Life
// ----

TEST(LifeFixture, constructorTest1) {
    Life<ConwayCell> life(2, 2);
    ASSERT_EQ(0, life.cellGrid.size());
    ASSERT_EQ(4, life.neighborGrid.size());
}

TEST(LifeFixture, constructorTest2) {
    Life<FredkinCell> life(0, 0);
    ASSERT_EQ(0, life.cellGrid.size());
    ASSERT_EQ(0, life.neighborGrid.size());
}


TEST(LifeFixture, constructorTest3) {
    Life<Cell> life(2, 6);
    ASSERT_EQ(0, life.cellGrid.size());
    ASSERT_EQ(12, life.neighborGrid.size());
}

TEST(LifeFixture, simulateTest1) {
    Life<ConwayCell> life(3, 3);
    istringstream in(".*.\n.*.\n.*.");
    in >> life;
}

TEST(LifeFixture, simulateTest2) {
    Life<FredkinCell> life(3, 3);
    istringstream in("-0-\n---\n---");
    in >> life;
}

TEST(LifeFixture, simulateTest3) {
    Life<FredkinCell> life(2, 2);
    istringstream in("0-\n-0");
    in >> life;
}

TEST(LifeFixture, getNumNeighborsTest1) {
    Life<ConwayCell> life(2, 2);
    istringstream in(".*\n*.");
    in >> life;
    ASSERT_EQ(2, life.getNumNeighbors(0, 0));
    ASSERT_EQ(1, life.getNumNeighbors(1, 0));
    ASSERT_EQ(1, life.getNumNeighbors(0, 1));
    ASSERT_EQ(2, life.getNumNeighbors(1, 1));
}

TEST(LifeFixture, getNumNeighborsTest2) {
    Life<FredkinCell> life(3, 3);
    istringstream in("000\n000\n000");
    in >> life;
    ASSERT_EQ(2, life.getNumNeighbors(0, 0));
    ASSERT_EQ(2, life.getNumNeighbors(0, 2));
    ASSERT_EQ(2, life.getNumNeighbors(2, 0));
    ASSERT_EQ(2, life.getNumNeighbors(2, 2));
    ASSERT_EQ(4, life.getNumNeighbors(1, 1));
    ASSERT_EQ(3, life.getNumNeighbors(0, 1));
    ASSERT_EQ(3, life.getNumNeighbors(1, 0));
    ASSERT_EQ(3, life.getNumNeighbors(1, 2));
    ASSERT_EQ(3, life.getNumNeighbors(2, 1));
}

TEST(LifeFixture, getNuMNeighborsTest3) {
    Life<Cell> life(4, 4);
    istringstream in("----\n-00-\n-00-\n----");
    in >> life;
}

/*TEST(LifeFixture, findPopulationTest1) {

}

TEST(LifeFixture, findPopulationTest1) {
    
}

TEST(LifeFixture, findPopulationTest1) {
    
}

TEST(LifeFixture, atTest1) {

}

TEST(LifeFixture, atTest2) {
    
}

TEST(LifeFixture, atTest3) {
    
}

TEST(LifeFixture, beginTest1) {

}

TEST(LifeFixture, beginTest2) {
    
}

TEST(LifeFixture, beginTest3) {
    
}

TEST(LifeFixture, endTest1) {

}

TEST(LifeFixture, endTest2) {
    
}

TEST(LifeFixture, endTest3) {
    
}
*/