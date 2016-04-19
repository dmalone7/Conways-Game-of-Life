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

TEST(ConwayCell, isAlive1) {
    ConwayCell cell('*');
    ASSERT_EQ(true, cell.isAlive());
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
