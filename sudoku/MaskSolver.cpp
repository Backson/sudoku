#include "MaskSolver.hpp"

#include <vector>

namespace sudoku {

static constexpr inline int get_box_number(int row, int column) {
	int box_row = row / Puzzle::BASE_SIZE;
	int box_column = column / Puzzle::BASE_SIZE;
	return box_row * Puzzle::BASE_SIZE + box_column;
}

// Helper class for the algorithm.
// This contains the "notes" that a human player would write in the cells.
class Notes {
public:
	// Initialize empty, i.e. all numbers are valid for all cells
	Notes() :
		row_notes(Puzzle::PUZZLE_SIZE, 0),
		column_notes(Puzzle::PUZZLE_SIZE, 0),
		box_notes(Puzzle::PUZZLE_SIZE, 0)
	{}

	// Initialize with markings according to the given puzzle.
	Notes(const Puzzle &input) :
		row_notes(Puzzle::PUZZLE_SIZE, 0),
		column_notes(Puzzle::PUZZLE_SIZE, 0),
		box_notes(Puzzle::PUZZLE_SIZE, 0)
	{
		mark(input);
	}

	// Mark all numbers in the puzzle
	void mark(const Puzzle &puzzle) {
		// iterate over all cells in the puzzle
		for (int c = 0; c < Puzzle::PUZZLE_SIZE; ++c) {
			for (int r = 0; r < Puzzle::PUZZLE_SIZE; ++r) {
				int value = puzzle.get(r, c);
				// mark all non-empty cells
				if (value > 0) {
					mark(r, c, value);
				}
			}
		}
	}

	// When a cell is marked, mark all cells in the same row/column/box as this number.
	void mark(int row, int column, int8_t value) {
		uint16_t mask = 1 << (value - 1);
		int box = get_box_number(row, column);
		row_notes[row] |= mask;
		column_notes[column] |= mask;
		box_notes[box] |= mask;
	}

	// Get a bit-field for the given cell, which indicates which numbers are already used-up
	// and will result in a conflict in this cell.
	uint16_t get(int row, int column) {
		int box = get_box_number(row, column);
		return row_notes[row] | column_notes[column] | box_notes[box];
	}

private:
	// Our notes indicating number candidates for each row/column/box.
	// Each element is a bit-field with 1s for numbers that are used-up and
	// 0s for numbers that are still possible for a row/column/box.
	// The first bit is for number 1, i.e. 0b0_0000_0001 and the ninth bit is
	// for number 9, i.e. 0b1_0000_0000.
	// To get possible numbers for a cell, get the three corresponding
	// elements from the vectors and bitwise-or them together.
	std::vector<uint16_t> row_notes;
	std::vector<uint16_t> column_notes;
	std::vector<uint16_t> box_notes;
};

Puzzle MaskSolver::solve(const Puzzle &input) {
	Puzzle puzzle = input;
	Notes notes(input);

	bool again;
	do {
		again = false;

		for (int c = 0; c < Puzzle::PUZZLE_SIZE; ++c) {
			for (int r = 0; r < Puzzle::PUZZLE_SIZE; ++r) {
				if (puzzle.get(r, c) != 0)
					continue;
				// Each bit in the bitfield indicates a number that is already used-up
				// for this cell and would lead to conflicts.
				uint16_t mask = notes.get(r, c);

				// Check for cells that have only a single possible number left unset.
				switch (mask) {
				case ~(1 << 0) & 0x1FF:
					puzzle.set(r, c, 1);
					notes.mark(r, c, 1);
					again = true;
					break;
				case ~(1 << 1) & 0x1FF:
					puzzle.set(r, c, 2);
					notes.mark(r, c, 2);
					again = true;
					break;
				case ~(1 << 2) & 0x1FF:
					puzzle.set(r, c, 3);
					notes.mark(r, c, 3);
					again = true;
					break;
				case ~(1 << 3) & 0x1FF:
					puzzle.set(r, c, 4);
					notes.mark(r, c, 4);
					again = true;
					break;
				case ~(1 << 4) & 0x1FF:
					puzzle.set(r, c, 5);
					notes.mark(r, c, 5);
					again = true;
					break;
				case ~(1 << 5) & 0x1FF:
					puzzle.set(r, c, 6);
					notes.mark(r, c, 6);
					again = true;
					break;
				case ~(1 << 6) & 0x1FF:
					puzzle.set(r, c, 7);
					notes.mark(r, c, 7);
					again = true;
					break;
				case ~(1 << 7) & 0x1FF:
					puzzle.set(r, c, 8);
					notes.mark(r, c, 8);
					again = true;
					break;
				case ~(1 << 8) & 0x1FF:
					puzzle.set(r, c, 9);
					notes.mark(r, c, 9);
					again = true;
					break;
				default:
					// more than one possibility, keep going...
					break;
				}
			}
		}

	} while (again);

	return puzzle;
}

}
