#include "FastSolver.hpp"

#include "MaskSolver.hpp"

namespace sudoku {

std::list<Puzzle> FastSolver::solve(const Puzzle &input) {
	// solved puzzles
	std::list<Puzzle> solutions;

	// if the input puzzle is invalid, return an empty list (no solutions)
	if (!input.valid())
		return solutions;

	// partially solved puzzles
	std::list<Puzzle> candidates;

	// start with a copy of the input puzzle
	candidates.emplace_back(input);

	// keep working until all candidates are solved
	while ((int)candidates.size() > 0) {
		// remove puzzle from temporary list
		Puzzle puzzle = std::move(candidates.back());
		candidates.pop_back();

		// fill in as many numbers as we can using the MaskSolver strategy
		puzzle = MaskSolver().solve(puzzle);

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
