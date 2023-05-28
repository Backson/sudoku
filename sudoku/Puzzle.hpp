#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace sudoku {

// just a boolean, but strong type wrapper
enum class RenderFrameArgument : bool {
	No = false,
	Yes = true,
};

// holds the data of our puzzle
class Puzzle {
public:

	// fundamental size value
	static constexpr int BASE_SIZE = 3;

	// size of the sides of the puzzle
	static constexpr int PUZZLE_SIZE = BASE_SIZE * BASE_SIZE;

	// total number of cells of the buzzle
	static constexpr int DATA_SIZE = PUZZLE_SIZE * PUZZLE_SIZE;

	// construct sudoku puzzle from string representation.
	static Puzzle fromString(const std::string &);

	// turn sudoku puzzle into a string
	std::string toString(RenderFrameArgument render_frame) const;

	// creates an empty puzzle (all cells are empty)
	Puzzle();

	// sets all cells to empty
	void clear();

	// get the content of a cell
	int8_t get(int row, int column) const;

	// set one cell to a particular number
	void set(int row, int column, int8_t value);

	// make one cell empty
	void unset(int row, int column);

	// check if there is any collisions originating from a single cell
	bool valid(int row, int column) const;

	// check if there is any collisions anywhere in the puzzle
	bool valid() const;

	// returns true, iff every cell in the puzzle contains a number.
	bool full() const;

	// returns the number of empty cells in the puzzle
	int count_empty_cells() const;

private:
	std::vector<int8_t> table;
};

}
