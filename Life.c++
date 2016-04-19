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
    // a live cell becomes a dead cell, if less than 2 or more than 3 neighbors are alive
	if (!alive && neighbors == 3)
		alive = true;
	else if (alive && (neighbors < 2 || neighbors > 3))
		alive = false;
}

char ConwayCell::print() {
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
    // a live cell becomes a dead cell, if 0, 2, or 4 neighbors are alive
	if (!alive && (neighbors == 1 || neighbors == 3))
		alive = true;
	else if (alive && (neighbors == 0 || neighbors == 2 || neighbors == 4))
		alive = false;
	else
		++age;
}

char FredkinCell::print() {
	return alive ? age + '0' : '-'; // prints age as char
}

// ----
// Cell
// ----

// Cell::AbstractCell() {}

// Cell::AbstractCell(char c) {}

// void Cell::evolve(int neighbors) {}

// char Cell::print() {}

// ------------
// Life
// ------------

// void Life::read(std::istream &i) {}

// std::ostream& Life::print() {}

// void Life::simulate() {}