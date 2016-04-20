#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "Life.h"

using namespace std;

// ----------
// ConwayCell
// ----------

TEST(ConwayCell, defaultConstrutor1) {
    ConwayCell cell;
    ASSERT_EQ('.', cell.print());
}

TEST(ConwayCell, defaultConstrutor2) {
    ConwayCell cell;
    ASSERT_EQ(false, cell.alive);
}

TEST(ConwayCell, defaultConstrutor3) {
    ConwayCell cell;
    cell.evolve(1);
    ASSERT_EQ('.', cell.print());
}

TEST(ConwayCell,charConstrutor1) {
    ConwayCell cell('*');
    ASSERT_EQ('*', cell.print());
}

// TEST(ConwayCell,charConstrutor2) {
//     ConwayCell cell('*');
//     ASSERT_EQ('*', cell.print());
// }

TEST(ConwayCell,charConstrutor3) {
    try {
        ConwayCell cell('c');
        ASSERT_EQ('.', cell.print());
    }
    catch (runtime_error re)
    {
        ConwayCell cell('.');
        ASSERT_EQ('.', cell.print());
    }
}

TEST(ConwayCell, isAlive1) {
    ConwayCell cell('*');
    ASSERT_EQ(true, cell.isAlive());
}

// -----------
// FredkinCell
// -----------

TEST(FredkinCell, defaultConstrutor1) {
    FredkinCell cell;
    ASSERT_EQ('-', cell.print());
}

TEST(FredkinCell, defaultConstrutor2) {
    FredkinCell cell;
    ASSERT_EQ(false, cell.alive);
}

TEST(FredkinCell, defaultConstrutor3) {
    FredkinCell cell;
    cell.evolve(1);
    ASSERT_EQ('0', cell.print());
}

// ----
// Cell
// ----



// ----
// Life
// ----

// TEST(Life, simulate1) {
//     Life<ConwayCell> life(3, 3);
//     istringstream is(".*.\n.*.\n.*.");
//     life.read(is);
//     for(int i = 0; i < 3; i++) {
//         life.print();
//         life.simulate();
//     }
// }

// TEST(Life, simulate2) {
//     Life<FredkinCell> life(3, 3);
//     istringstream is("-0-\n---\n---");
//     life.read(is);
//     for(int i = 0; i < 11; i++) {
//         life.print();
//         life.simulate();
//     }
// }

// TEST(Life, simulate3) {
//     Life<FredkinCell> life(2, 2);
//     istringstream is("0-\n0-");
//     life.read(is);
//     for(int i = 0; i < 11; i++) {
//         life.print();
//         life.simulate();
//     }
// }

TEST(Life, getNumNeighbors1) {
    Life<ConwayCell> life(2, 2);
    istringstream is(".*\n*.");
    life.read(is);
    ASSERT_EQ(2, life.getNumNeighbors(0, 0));
    ASSERT_EQ(1, life.getNumNeighbors(1, 0));
    ASSERT_EQ(1, life.getNumNeighbors(0, 1));
    ASSERT_EQ(2, life.getNumNeighbors(1, 1));
}

TEST(Life, getNumNeighbors2) {
    Life<FredkinCell> life(3, 3);
    istringstream is("000\n000\n000");
    life.read(is);
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

// TEST(Life, getNumNeighbors3) {
//     Life<Cell> life(2, 2);
//     istringstream is(".*\n*.");
//     life.read(is);
//     ASSERT_EQ(2, life.getNumNeighbors(0, 0));
//     ASSERT_EQ(1, life.getNumNeighbors(1, 0));
//     ASSERT_EQ(1, life.getNumNeighbors(0, 1));
//     ASSERT_EQ(2, life.getNumNeighbors(1, 1));
// }