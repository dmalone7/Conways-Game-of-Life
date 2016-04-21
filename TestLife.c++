#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "Life.h"

using namespace std;

// ----------
// AbstractCell
// ----------

TEST(AbstractCellFixture, isAliveTest1) {
    AbstractCell *cell = new ConwayCell();
    ASSERT_EQ(DEAD, cell->isAlive());
    delete cell;
}

TEST(AbstractCellFixture, isAliveTest2) {
    AbstractCell *cell = new FredkinCell('0');
    ASSERT_EQ(ALIVE, cell->isAlive());
    delete cell;
}

TEST(AbstractCellFixture, isAliveTest3) {
    AbstractCell *cell = new ConwayCell('.');
    ASSERT_EQ(DEAD, cell->isAlive());
    cell->evolve(3);
    ASSERT_EQ(ALIVE, cell->isAlive());
    delete cell;
}

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
        ASSERT_TRUE(false);
    }
    catch (runtime_error re)
    {
        ASSERT_FALSE(false);
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
    bool b = cell.isNeighbor(0, 0, 2, 0);
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

TEST(FredkinCellFixture, charConstrutorTest1) {
    try {
        FredkinCell cell('+');
        cell.evolve(1);
        ASSERT_TRUE(false);
    }
    catch(std::runtime_error e) {
        ASSERT_TRUE(true);
    }
}

TEST(FredkinCellFixture, charConstrutorTest2) {
    try {
        FredkinCell cell('2');
        cell.evolve(1);
        ASSERT_TRUE(false);
    }
    catch(std::runtime_error e) {
        ASSERT_TRUE(true);
    }
}

TEST(FredkinCellFixture, charConstrutorTest3) {
    FredkinCell cell('0');
    ASSERT_EQ('0', cell.write());
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

TEST(LifeFixture, operator>>Test1) {
    Life<ConwayCell> life(2, 2);
    istringstream in(".*.*");
    life.read(in);
    ASSERT_EQ(4, life.cellGrid.size());
}

TEST(LifeFixture, operator>>Test2) {
    Life<FredkinCell> life(3, 2);
    istringstream in("--00--");
    life.read(in);
    ASSERT_EQ(6, life.cellGrid.size());
}

TEST(LifeFixture, operator>>Test3) {
    Life<Cell> life(4, 4);
    istringstream in("---00---00----");
    life.read(in);
    ASSERT_EQ(16, life.cellGrid.size());
}

TEST(LifeFixture, operator<<Test1) {
    Life<Cell> life(4, 4);
    istringstream in("---00---00------");
    // read input stream into life
    in >> life;
    ostringstream out;
    // write output into out stream
    life.write(out);
    // compare string with output string
    ASSERT_EQ("---0\n0---\n00--\n----\n", out.str());
}

TEST(LifeFixture, operator<<Test2) {
    Life<FredkinCell> life(4, 4);
    istringstream in("-----00--00-----");
    // read input stream into life
    in >> life;
    ostringstream out;
    // write output into out stream
    life.write(out);
    // compare string with output string
    ASSERT_EQ("----\n-00-\n-00-\n----\n", out.str());
    life.simulate();
    // clears output stream
    out.str("");
    life.write(out);
    ASSERT_EQ("-00-\n0--0\n0--0\n-00-\n", out.str());
}

TEST(LifeFixture, operator<<Test3) {
    Life<ConwayCell> life(3, 3);
    istringstream in("...***...");
    // read input stream into life
    in >> life;
    ostringstream out;
    // write output into out stream
    life.write(out);
    // compare string with output string
    ASSERT_EQ("...\n***\n...\n", out.str());
}

TEST(LifeFixture, readTest1) {
    Life<ConwayCell> life(2, 2);
    istringstream in(".*.*");
    life.read(in);
    ASSERT_EQ(4, life.cellGrid.size());
}

TEST(LifeFixture, readTest2) {
    Life<FredkinCell> life(3, 2);
    istringstream in("--00--");
    life.read(in);
    ASSERT_EQ(6, life.cellGrid.size());
}

TEST(LifeFixture, readTest3) {
    Life<Cell> life(4, 4);
    istringstream in("---00---00----");
    life.read(in);
    ASSERT_EQ(16, life.cellGrid.size());
}

TEST(LifeFixture, writeTest1) {
    Life<Cell> life(4, 4);
    istringstream in("---00---00------");
    // read input stream into life
    in >> life;
    ostringstream out;
    // write output into out stream
    life.write(out);
    // compare string with output string
    ASSERT_EQ("---0\n0---\n00--\n----\n", out.str());
}

TEST(LifeFixture, writeTest2) {
    Life<FredkinCell> life(4, 4);
    istringstream in("-----00--00-----");
    // read input stream into life
    in >> life;
    ostringstream out;
    // write output into out stream
    life.write(out);
    // compare string with output string
    ASSERT_EQ("----\n-00-\n-00-\n----\n", out.str());
    life.simulate();
    // clears output stream
    out.str("");
    life.write(out);
    ASSERT_EQ("-00-\n0--0\n0--0\n-00-\n", out.str());
}

TEST(LifeFixture, writeTest3) {
    Life<ConwayCell> life(3, 3);
    istringstream in("...***...");
    // read input stream into life
    in >> life;
    ostringstream out;
    // write output into out stream
    life.write(out);
    // compare string with output string
    ASSERT_EQ("...\n***\n...\n", out.str());
}

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
    // 3x3 Grid of ConwayCells
    Life<ConwayCell> life(3, 3);
    istringstream in(".*.\n.*.\n.*.");
    in >> life;
    ostringstream out;
    out << life;
    // Blinker, oscillates between two states
    ASSERT_EQ(".*.\n.*.\n.*.\n", out.str());
    life.simulate();
    // clears ostringstream
    out.str("");
    out << life;
    ASSERT_EQ("...\n***\n...\n", out.str());
}

TEST(LifeFixture, simulateTest2) {
    // 3x3 Grid of FredkinCells
    Life<FredkinCell> life(3, 3);
    istringstream in("-0-\n---\n---");
    in >> life;
    ostringstream out;
    out << life;
    ASSERT_EQ("-0-\n---\n---\n", out.str());
    // simulate 3 turns
    life.simulate();
    // clears ostringstream
    out.str("");
    out << life;
    ASSERT_EQ("0-0\n-0-\n---\n", out.str());
}

TEST(LifeFixture, simulateTest3) {
    // 3x2 Grid of Cells
    Life<Cell> life(3, 2);
    istringstream in("-0\n--\n0-");
    in >> life;
    ostringstream out;
    out << life;
    ASSERT_EQ("-0\n--\n0-\n", out.str());
    // simulate 6 turns
    life.simulate();
    // clears ostringstream
    out.str("");
    out << life;
    ASSERT_EQ("0-\n00\n-0\n", out.str());
}

TEST(LifeFixture, simulateIntTest1) {
    // 3x3 Grid of ConwayCells
    Life<ConwayCell> life(3, 3);
    istringstream in(".*.\n.*.\n.*.");
    in >> life;
    ostringstream out;
    out << life;
    // Blinker, oscillates between two states
    ASSERT_EQ(".*.\n.*.\n.*.\n", out.str());
    life.simulate(3);
    // clears ostringstream
    out.str("");
    out << life;
    ASSERT_EQ("...\n***\n...\n", out.str());
}

TEST(LifeFixture, simulateIntTest2) {
    // 3x3 Grid of FredkinCells
    Life<FredkinCell> life(3, 3);
    istringstream in("-0-\n---\n---");
    in >> life;
    ostringstream out;
    out << life;
    ASSERT_EQ("-0-\n---\n---\n", out.str());
    // simulate 3 turns
    life.simulate(3);
    // clears ostringstream
    out.str("");
    out << life;
    ASSERT_EQ("0-0\n---\n0-0\n", out.str());
}

TEST(LifeFixture, simulateIntTest3) {
    // 3x2 Grid of Cells
    Life<Cell> life(3, 2);
    istringstream in("-0\n--\n0-");
    in >> life;
    ostringstream out;
    out << life;
    ASSERT_EQ("-0\n--\n0-\n", out.str());
    // simulate 6 turns
    life.simulate(6);
    // clears ostringstream
    out.str("");
    out << life;
    ASSERT_EQ("*-\n--\n-*\n", out.str());
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
    Life<Cell> life(2, 2);
    istringstream in("0-\n-0");
    in >> life;
    // corner cells alive
    ASSERT_EQ(0, life.getNumNeighbors(0, 0));
    ASSERT_EQ(2, life.getNumNeighbors(1, 0));
    ASSERT_EQ(2, life.getNumNeighbors(0, 1));
    ASSERT_EQ(0, life.getNumNeighbors(1, 1));
    // all cells are dead
    life.simulate();
    ASSERT_EQ(0, life.getNumNeighbors(0, 0));
    ASSERT_EQ(0, life.getNumNeighbors(1, 0));
    ASSERT_EQ(0, life.getNumNeighbors(0, 1));
    ASSERT_EQ(0, life.getNumNeighbors(1, 1));
}

TEST(LifeFixture, findPopulationTest1) {
    Life<FredkinCell> life(3, 3);
    istringstream in("000\n000\n000");
    in >> life;
    ASSERT_EQ(9, life.findPopulation());
    life.simulate();
    ASSERT_EQ(4, life.findPopulation());
}

TEST(LifeFixture, findPopulationTest2) {
    Life<ConwayCell> life(3, 3);
    // Still life
    istringstream in("**.\n*.*\n.*.");
    in >> life;
    ASSERT_EQ(5, life.findPopulation());
    life.simulate();
    ASSERT_EQ(5, life.findPopulation());
    // stays the same forever
    life.simulate(1000);
    ASSERT_EQ(5, life.findPopulation());
}

TEST(LifeFixture, findPopulationTest3) {
    Life<ConwayCell> life(4, 4);
    // Beacon oscillator
    istringstream in("**..\n**..\n..**\n..**");
    in >> life;
    ASSERT_EQ(8, life.findPopulation());
    life.simulate();
    ASSERT_EQ(6, life.findPopulation());
    // switches back and forth between 6 and 8 population
    life.simulate();
    ASSERT_EQ(8, life.findPopulation());
    life.simulate(100);
    ASSERT_EQ(8, life.findPopulation());
}

TEST(LifeFixture, atTest1) {
    Life<ConwayCell> life(3, 3);
    istringstream in("...\n.*.\n...");
    in >> life;

    ConwayCell live = life.at(1, 1);
    ConwayCell dead = life.at(0, 1);
    ASSERT_EQ(ALIVE, live.isAlive());
    ASSERT_EQ(DEAD, dead.isAlive());
}

TEST(LifeFixture, atTest2) {
    Life<FredkinCell> life(3, 3);
    istringstream in("-0-\n-0-\n-0-");
    in >> life;

    FredkinCell cell = life.at(1,1);
    // starts off alive
    ASSERT_EQ(ALIVE, cell.isAlive());
    life.simulate();
    cell = life.at(1,1);
    // ends up dead
    ASSERT_EQ(DEAD, cell.isAlive());
}

TEST(LifeFixture, atTest3) {
    Life<Cell> life(4, 4);
    istringstream in("----\n-00-\n-00-\n----");
    in >> life;
    Cell cell = life.at(0, 1);
    // starts off dead
    ASSERT_EQ(DEAD, cell.isAlive());
    life.simulate(5);
    cell = life.at(0, 1);
    // ends up alive
    ASSERT_EQ(ALIVE, cell.isAlive());
    ASSERT_EQ('*', cell.write());
}

TEST(LifeFixture, beginTest1) {
    Life<ConwayCell> life(3, 3);
    istringstream in("...\n.*.\n...");
    in >> life;
    // first cell in array
    ConwayCell *cell = life.begin();
    ASSERT_EQ('.', cell->write());
}

TEST(LifeFixture, beginTest2) {
    Life<FredkinCell> life(3, 3);
    istringstream in("---\n0-0\n---");
    in >> life;
    // first cell in array
    FredkinCell *cell = life.begin();
    ASSERT_EQ('-', cell->write());
    life.simulate();
    ASSERT_EQ('0', cell->write());
}

TEST(LifeFixture, beginTest3) {
    Life<Cell> life(3, 3);
    istringstream in("0--\n0-0\n0--");
    in >> life;
    // first cell in array
    Cell *cell = life.begin();
    // starts off alive FredkinCell
    ASSERT_EQ('0', cell->write());
    life.simulate(5);
    // turns into dead ConwayCell
    ASSERT_EQ('.', cell->write());
}

TEST(LifeFixture, endTest1) {
    Life<ConwayCell> life(3, 3);
    istringstream in("...\n...\n..*");
    in >> life;
    // last cell in array
    ConwayCell *cell = life.end()-1;
    ASSERT_EQ('*', cell->write());
}

TEST(LifeFixture, endTest2) {
    Life<FredkinCell> life(3, 3);
    istringstream in("---\n0-0\n---");
    in >> life;
    // last cell in array
    FredkinCell *cell = life.end()-1;
    // end starts dead
    ASSERT_EQ('-', cell->write());
    life.simulate();
    // ends alive
    ASSERT_EQ('0', cell->write());
}

TEST(LifeFixture, endTest3) {
    Life<Cell> life(3, 3);
    istringstream in("0--\n0-0\n0--");
    in >> life;
    // last cell in array
    Cell *cell = life.end()-1;
    // starts off alive FredkinCell
    ASSERT_EQ('-', cell->write());
    life.simulate(5);
    // stays dead FredkinCell
    ASSERT_EQ('-', cell->write());
}

