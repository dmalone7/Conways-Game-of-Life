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

status ConwayCell::isAlive () const {
	return alive ? ALIVE : DEAD;
}

bool ConwayCell::isNeighbor(int myrow, int mycol, int n_row, int n_col) {
	int val = abs(myrow - n_row) + abs(mycol - n_col);
	return val == 1 || val == 2;
}

void ConwayCell::evolve(int neighbors) {
	assert(neighbors >= 0);
    // a dead cell becomes a live cell, if exactly 3 neighbors are alive
    // a live cell becomes a dead cell, if less than 2 or more than 3 neighbors are alive
	if (!alive && neighbors == 3)
		alive = true;
	else if (alive && (neighbors < 2 || neighbors > 3))
		alive = false;
}

char ConwayCell::print() const{
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

status FredkinCell::isAlive () const {
	return alive ? ALIVE : DEAD;
}

bool FredkinCell::isNeighbor(int myrow, int mycol, int n_row, int n_col)
{
	int val = abs(myrow - n_row) + abs(mycol - n_col);
	return val == 1;
}

void FredkinCell::evolve(const int neighbors) {
	assert(neighbors >= 0);
    // a dead cell becomes a live cell, if 1 or 3 neighbors are alive
    // a live cell becomes a dead cell, if 0, 2, or 4 neighbors are alive
	if (!alive && (neighbors == 1 || neighbors == 3))
		alive = true;
	else if (alive && (neighbors == 0 || neighbors == 2 || neighbors == 4))
		alive = false;
	else if (alive)
		++age;
}

char FredkinCell::print() const {
	char c = alive ? age + '0' : '-'; // prints age as char
	return (age > 9 && alive) ? '+' : c;
}

bool FredkinCell::checkConway() const {
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

status Cell::isAlive () const {
	return cell->isAlive();
}

bool Cell::isNeighbor(int myrow, int mycol, int n_row, int n_col) {
	return cell->isNeighbor(myrow, mycol, n_row, n_col);
}

void Cell::evolve(int neighbors) {
	cell->evolve(neighbors);

	if (type == FREDKIN && static_cast<FredkinCell*>(cell)->checkConway()) {
		delete cell;
		cell = new ConwayCell('*');
		type = CONWAY;
	}
}

char Cell::print() const{
	return cell->print();
}

// ------------
// Life
// ------------
