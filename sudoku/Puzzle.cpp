#include "Puzzle.hpp"

#include <sstream>

namespace sudoku {

Puzzle::Puzzle() {
	// allocate space
	table.resize(DATA_SIZE);
	// initialize data
	clear();
}

void Puzzle::clear() {
	// iterate over all cells and set them to 0 (empty)
	for (auto &cell : table) {
		cell = 0;
	}
}

int8_t Puzzle::get(int row, int column) const {
	return table[column + row * PUZZLE_SIZE];
}

void Puzzle::set(int row, int column, int8_t value) {
	table[column + row * PUZZLE_SIZE] = value;
}

void Puzzle::unset(int row, int column) {
	set(row, column, 0);
}

Puzzle Puzzle::fromString(const std::string &s) {
	int table_index = 0;
	int string_index = 0;

	Puzzle sudoku;

	while (table_index < DATA_SIZE && string_index < s.size()) {
		char c = s[string_index];
		// check if character is a digit
		if (c >= '1' && c <= '9') {
			// get numeric value of digit
			int value = c - '0';
			sudoku.table[table_index++] = value;
		}
		else if (c == '0' || c == ' ' || c == '.') {
			// empty cell
			sudoku.table[table_index++] = 0;
		}
		// next character
		string_index++;
	}

	return sudoku;
}

std::string Puzzle::toString(RenderFrameArgument render_frame_argument) const {
	// use a stringstream as a string builder
	std::stringstream ss;

	bool render_frame = (bool)render_frame_argument;

	for (int row = 0; row < PUZZLE_SIZE; ++row) {

		if (row > 0)
			ss << std::endl;

		if (row % BASE_SIZE == 0 && render_frame) {
			ss << "+---+---+---+" << std::endl;
		}

		for (int column = 0; column < PUZZLE_SIZE; ++column) {
			if (column % BASE_SIZE == 0 && render_frame) {
				ss << "|";
			}

			// print digit
			int value = get(row, column);
			char c;
			if (value <= 0)
				c = '.';
			else
				c = value + '0';
			ss << c;
		}

		if (render_frame) {
			ss << "|";
		}
	}

	if (render_frame) {
		ss << std::endl << "+---+---+---+";
	}

	return ss.str();
}

bool Puzzle::valid(int target_row, int target_column) const {
	int value = get(target_row, target_column);

	// empty cells don't cause collisions
	if (value == 0)
		return true;

	// check the row
	for (int c = 0; c < PUZZLE_SIZE; ++c) {
		// skip the target cell itself
		if (c == target_column)
			continue;

		// check for collision
		if (value == get(target_row, c))
			return false;
	}

	// check the column
	for (int r = 0; r < PUZZLE_SIZE; ++r) {
		// skip the target cell itself
		if (r == target_row)
			continue;

		// check for collision
		if (value == get(r, target_column))
			return false;
	}

	// check box
	int box_row = target_row / BASE_SIZE;
	int box_column = target_column / BASE_SIZE;
	for (int c = 0; c < BASE_SIZE; ++c) {
		for (int r = 0; r < BASE_SIZE; ++r) {
			int row = box_row * BASE_SIZE + r;
			int column = box_column * BASE_SIZE + c;

			// skip the target cell itself
			if (column == target_column && row == target_row)
				continue;

			// check for collision
			if (value == get(row, column))
				return false;
		}
	}

	return true;
}

bool Puzzle::valid() const {
	for (int row = 0; row < PUZZLE_SIZE; ++row) {
		for (int column = 0; column < PUZZLE_SIZE; ++column) {
			if (!valid(row, column))
				return false;
		}
	}
	return true;
}

bool Puzzle::full() const {
	for (int row = 0; row < PUZZLE_SIZE; ++row) {
		for (int column = 0; column < PUZZLE_SIZE; ++column) {
			if (get(row, column) == 0)
				return false;
		}
	}
	return true;
}

int Puzzle::count_empty_cells() const {
	int counter = 0;

	for (int row = 0; row < PUZZLE_SIZE; ++row) {
		for (int column = 0; column < PUZZLE_SIZE; ++column) {
			if (get(row, column) == 0)
				counter++;
		}
	}
	return counter;
}

}
