#include <stdlib.h>
#include "Life.h"

// -----------
// Conway Cell
// -----------

ConwayCell::ConwayCell(const char c) {
	if (c == '.')
		alive = false;
	else if (c == '*')
		alive = true;
	else
		throw std::runtime_error(std::string("Invalid char: ") + c);
}

void ConwayCell::evolve(int neighbors) {
	assert(neighbors >= 0);

	// a dead cell becomes a live cell, if exactly 3 neighbors are alive
	if (!alive && neighbors == 3)
		alive = true;
	// a live cell becomes a dead cell, if less than 2 or more than 3 neighbors are alive 
	else if (alive && (neighbors < 2 || neighbors > 3))
		alive = false;
}

bool ConwayCell::isNeighbor(int myrow, int mycol, int n_row, int n_col) {
	int val = abs(myrow - n_row) + abs(mycol - n_col);
	return val == 1 || val == 2;
}

char ConwayCell::write() const {
	return alive ? '*' : '.';
}

// ------------
// Fredkin Cell
// ------------

FredkinCell::FredkinCell(const char c) : age(0) {
	if (c == '0')
		alive = true;
	else if (c == '-')
		alive = false;
	else
		throw std::runtime_error(std::string("Invalid char: ") + c);
}

void FredkinCell::evolve(const int neighbors) {
	assert(neighbors >= 0);

	// a dead cell becomes a live cell, if 1 or 3 neighbors are alive
	if (!alive && (neighbors == 1 || neighbors == 3))
		alive = true;
	// a live cell becomes a dead cell, if 0, 2, or 4 neighbors are alive
	else if (alive && (neighbors == 0 || neighbors == 2 || neighbors == 4))
		alive = false;
	// increase age if still alive
	else if (alive)
		++age;
}

bool FredkinCell::isNeighbor(int myrow, int mycol, int n_row, int n_col) {
	int val = abs(myrow - n_row) + abs(mycol - n_col);
	return val == 1;
}

char FredkinCell::write() const {
	char c = alive ? age + '0' : '-'; // writes age as char
	return (age > 9 && alive) ? '+' : c;
}

bool FredkinCell::turnConway() const {
	return age == 2;
}

// ----
// Cell
// ----

Cell::Cell() : type(FREDKIN) {
	cell = new FredkinCell();
}

Cell::Cell(char c) : type(FREDKIN) {
	cell = new FredkinCell(c);
}

void Cell::evolve(int neighbors) {
	cell->evolve(neighbors);

	if (type == FREDKIN && static_cast<FredkinCell*>(cell)->turnConway()) {
		// AbstractCell *nCell = new ConwayCell('*');
		delete cell;
    	// cell = nCell->clone();
    	cell = new ConwayCell('*');
    	type = CONWAY;
    	// delete nCell;
	}
}

bool Cell::isNeighbor(int myrow, int mycol, int n_row, int n_col) {
	return cell->isNeighbor(myrow, mycol, n_row, n_col);
}

char Cell::write() const {
	return cell->write();
}

status Cell::isAlive () const {
	return cell->isAlive();
}

// ------------
// Life
// ------------
