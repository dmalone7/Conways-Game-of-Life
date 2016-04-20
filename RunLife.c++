// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2016
// Glenn P. Downing
// -------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl
#include "Life.h"
#include <string>

// ----
// main
// ----

int main () {
    using namespace std;

    // ----------------------
    // Life<ConwayCell> 21x13
    // ----------------------
    {
        cout << "*** Life<ConwayCell> 21x13 ***" << endl;
        /*
        Simulate 12 evolutions.
        Print every grid (i.e. 0, 1, 2, 3, ... 12)
        */

        Life<ConwayCell> life(21, 13);

        life.read(cin);
        cout << endl;

        for (int i = 0; i <= 12; i++) {
            int population = life.findPopulation();
            cout << "Generation = " << i << ", Population = " << population << "." << endl;
            life.print();
            life.simulate();
        }
    }

    // ----------------------
    // Life<ConwayCell> 20x29
    // ----------------------
    {
        cout << "*** Life<ConwayCell> 20x29 ***" << endl;
        /*
        Simulate 28 evolutions.
        Print every 4th grid (i.e. 0, 4, 8, ... 28)
        */
        Life<ConwayCell> life(20, 29);

        life.read(cin);
        cout << endl;

        for (int i = 0; i <= 28; i++) {
            if (i % 4 == 0) {
                int population = life.findPopulation();
                cout << "Generation = " << i << ", Population = " << population << "." << endl;
                life.print();
            }
            life.simulate();
        }
    }

    // -----------------------
    // Life<ConwayCell> 109x69
    // -----------------------
    {
        cout << "*** Life<ConwayCell> 109x69 ***" << endl;
        /*
        Simulate 283 evolutions.
        Print the first 10 grids (i.e. 0, 1, 2, ... 9).
        Print the 283rd grid.
        Simulate 40 evolutions.
        Print the 323rd grid.
        Simulate 2177 evolutions.
        Print the 2500th grid.
        */
        Life<ConwayCell> life(109, 69);

        life.read(cin);
        cout << endl;

        for (int i = 0; i <= 2500; i++) {
            if (i < 10) {
                int population = life.findPopulation();
                cout << "Generation = " << i << ", Population = " << population << "." << endl;
                life.print();
            }
            if (i == 283) {
                int population = life.findPopulation();
                cout << "Generation = " << i << ", Population = " << population << "." << endl;
                life.print();               
            }
            if (i == 323) {
                int population = life.findPopulation();
                cout << "Generation = " << i << ", Population = " << population << "." << endl;
                life.print();
            }
            if (i == 2500) {
                int population = life.findPopulation();
                cout << "Generation = " << i << ", Population = " << population << "." << endl;
                life.print();
            }
            life.simulate();
        }
    }

    // -----------------------
    // Life<FredkinCell> 20x20
    // -----------------------
    {
        cout << "*** Life<FredkinCell> 20x20 ***" << endl;
        /*
        Simulate 5 evolutions.
        Print every grid (i.e. 0, 1, 2, ... 5)
        */
        Life<FredkinCell> life(20, 20);
        
        life.read(cin);
        cout << endl;

        for (int i = 0; i <= 5; i++) {
            int population = life.findPopulation();
            cout << "Generation = " << i << ", Population = " << population << "." << endl;
            life.print();
            life.simulate();
        }
    }

    // ----------------
    // Life<Cell> 20x20
    // ----------------
    {
        cout << "*** Life<Cell> 20x20 ***" << endl;
        /*
        Simulate 5 evolutions.
        Print every grid (i.e. 0, 1, 2, ... 5)
        */
        Life<Cell> life(20, 20);

        life.read(cin);
        cout << endl;

        for (int i = 0; i <= 5; i++) {
            int population = life.findPopulation();
            cout << "Generation = " << i << ", Population = " << population << "." << endl;
            life.print();
            life.simulate();
        }
    }

    return 0;
}
