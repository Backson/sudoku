#include "StackSolver.hpp"

namespace sudoku {

static constexpr inline int max(int a, int b) {
	return a > b ? a : b;
}

std::list<sudoku::Puzzle> StackSolver::solve(const sudoku::Puzzle &input) {
	// solved puzzles
	std::list<sudoku::Puzzle> solutions;

	// if the input puzzle is invalid, return an empty list (no solutions)
	puzzle_counter++;
	max_list_length = max(max_list_length, 1);
	if (!input.valid())
		return solutions;

	// partially solved puzzles
	std::list<sudoku::Puzzle> candidates;

	// start with a copy of the input puzzle
	candidates.emplace_back(input);

	// keep working until all candidates are solved
	while ((int)candidates.size() > 0) {
		// performance statistics
		puzzle_counter++;
		max_list_length = max(max_list_length, (int)candidates.size());

		// remove puzzle from temporary list
		sudoku::Puzzle puzzle = std::move(candidates.back());
		candidates.pop_back();

		// find an empty cell
		int row;
		int column;
		for (int c = 0; c < puzzle.PUZZLE_SIZE; ++c) {
			for (int r = 0; r < puzzle.PUZZLE_SIZE; ++r) {
				if (puzzle.get(r, c) == 0) {
					row = r;
					column = c;
					goto FOUND;
				}
			}
		}

		// if we didn't find any empty cells, the puzzle is already solved
		// add it to the solutions
		solutions.emplace_back(std::move(puzzle));
		continue;

		FOUND:

		// try all possible numbers for the selected cell
		for (int value = 1; value <= puzzle.PUZZLE_SIZE; ++value) {
			// place the number
			puzzle.set(row, column, value);
			// If the puzzle is still valid, add it to the pool of candidates.
			// We don't need to check for collisions everywhere, just for the
			// number we added just now.
			if (puzzle.valid(row, column))
				candidates.emplace_back(puzzle);
		}
	}

	return solutions;
}

}
