#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "Life.h"

using namespace std;

// ----------
// ConwayCell
// ----------

TEST(ConwayCellFixture, defaultConstrutor1) {
    ConwayCell cell;
    ASSERT_EQ('.', cell.write());
}

TEST(ConwayCellFixture, defaultConstrutor2) {
    ConwayCell cell;
    ASSERT_EQ(false, cell.isAlive());
}

TEST(ConwayCellFixture, defaultConstrutor3) {
    ConwayCell cell;
    cell.evolve(1);
    ASSERT_EQ('.', cell.write());
}

TEST(ConwayCellFixture,charConstrutor1) {
    ConwayCell cell('*');
    ASSERT_EQ('*', cell.write());
}

TEST(ConwayCellFixture,charConstrutor2) {
    ConwayCell cell('*');
    ASSERT_EQ('*', cell.write());
}

TEST(ConwayCellFixture,charConstrutor3) {
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

// Test(ConwayCellFixture, evolveTest1) {

// }

// Test(ConwayCellFixture, evolveTest2) {

// }

// Test(ConwayCellFixture, evolveTest3) {

// }

// Test(ConwayCellFixture, isNeighborTest1) {

// }

// Test(ConwayCellFixture, isNeighborTest2) {

// }

// Test(ConwayCellFixture, isNeighborTest3) {

// }

// Test(ConwayCellFixture, writeTest1) {

// }

// Test(ConwayCellFixture, writeTest2) {
    
// }

// Test(ConwayCellFixture, writeTest3) {
    
// }

// -----------
// FredkinCell
// -----------

TEST(FredkinCellFixture, defaultConstrutor1) {
    FredkinCell cell;
    ASSERT_EQ('-', cell.write());
}

TEST(FredkinCellFixture, defaultConstrutor2) {
    FredkinCell cell;
    ASSERT_EQ(false, cell.isAlive());
}

TEST(FredkinCellFixture, defaultConstrutor3) {
    FredkinCell cell;
    cell.evolve(1);
    ASSERT_EQ('0', cell.write());
}

// Test(FredkinCellFixture, evolveTest1) {

// }

// Test(FredkinCellFixture, evolveTest2) {

// }

// Test(FredkinCellFixture, evolveTest3) {

// }

// Test(FredkinCellFixture, isNeighborTest1) {

// }

// Test(FredkinCellFixture, isNeighborTest2) {

// }

// Test(FredkinCellFixture, isNeighborTest3) {

// }

// Test(FredkinCellFixture, writeTest1) {

// }

// Test(FredkinCellFixture, writeTest2) {
    
// }

// Test(FredkinCellFixture, writeTest3) {
    
// }

// Test(FredkinCellFixture, turnConwayTest1) {

// }

// Test(FredkinCellFixture, turnConwayTest2) {
    
// }

// Test(FredkinCellFixture, turnConwayTest3) {
    
// }


// ----
// Cell
// ----

// Test(CellFixture, defaultConstructorTest1) {

// }

// Test(CellFixture, defaultConstructorTest2) {
    
// }

// Test(CellFixture, defaultConstructorTest3) {
    
// }

// Test(CellFixture, charConstructorTest1) {

// }

// Test(CellFixture, charConstructorTest2) {

// }

// Test(CellFixture, charConstructorTest3) {

// }

// Test(CellFixture, evolveTest1) {

// }

// Test(CellFixture, evolveTest2) {

// }

// Test(CellFixture, evolveTest3) {

// }

// Test(CellFixture, isNeighborTest1) {

// }

// Test(CellFixture, isNeighborTest2) {

// }

// Test(CellFixture, isNeighborTest3) {

// }

// Test(CellFixture, writeTest1) {

// }

// Test(CellFixture, writeTest2) {
    
// }

// Test(CellFixture, writeTest3) {
    
// }

// Test(CellFixture, isAliveTest1) {

// }

// Test(CellFixture, isAliveTest2) {
    
// }

// Test(CellFixture, isAliveTest3) {
    
// }



// ----
// Life
// ----

// TEST(LifeFixture, Constructor1) {

// }

// TEST(LifeFixture, Constructor2) {

// }


// TEST(LifeFixture, Constructor3) {

// }

TEST(LifeFixture, simulate1) {
    Life<ConwayCell> life(3, 3);
    istringstream in(".*.\n.*.\n.*.");
    in >> life;
    for(int i = 0; i < 3; i++) {
        life.simulate();
    }
}

TEST(LifeFixture, simulate2) {
    Life<FredkinCell> life(3, 3);
    istringstream in("-0-\n---\n---");
    in >> life;
    for(int i = 0; i < 11; i++) {
        life.simulate();
    }
}

TEST(LifeFixture, simulate3) {
    Life<FredkinCell> life(2, 2);
    istringstream in("0-\n0-");
    in >> life;
    for(int i = 0; i < 11; i++) {
        life.simulate();
    }
}

TEST(LifeFixture, getNumNeighbors1) {
    Life<ConwayCell> life(2, 2);
    istringstream in(".*\n*.");
    in >> life;
    ASSERT_EQ(2, life.getNumNeighbors(0, 0));
    ASSERT_EQ(1, life.getNumNeighbors(1, 0));
    ASSERT_EQ(1, life.getNumNeighbors(0, 1));
    ASSERT_EQ(2, life.getNumNeighbors(1, 1));
}

TEST(LifeFixture, getNumNeighbors2) {
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

TEST(LifeFixture, getNuMNeighbors3) {
    Life<Cell> life(4, 4);
    istringstream in("----\n-00-\n-00-\n----");
    in >> life;
    life.simulate(4);
}