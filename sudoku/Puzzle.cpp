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

}
