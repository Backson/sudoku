#include "DepthSearchSolver.hpp"

namespace sudoku {

std::list<Puzzle> DepthSearchSolver::solve(const Puzzle &input) {
	// solved puzzles
	std::list<Puzzle> solutions;

	// if the input puzzle is invalid, return an empty list (no solutions)
	if (!input.valid())
		return solutions;

	Puzzle candidate = input;

	int index = 0;

	while (index >= 0) {
		// find an empty cell
		while (index < Puzzle::DATA_SIZE && input.get(index) > 0)
			index++;

		if (index < Puzzle::DATA_SIZE) {
			// find a number without conflicts to put in
			// start with the number currently in the cell plus 1
			int value = candidate.get(index) + 1;
			while (value <= Puzzle::PUZZLE_SIZE) {
				candidate.set(index, value);
				if (candidate.valid(index))
					break;
				value++;
			}

			// we found a number that is valid
			if (value <= Puzzle::PUZZLE_SIZE) {
				// fill in the next number
				index++;
				continue;
			}
			else {
				// we didn't find any valid number, so we clear this cell and backtrack
				candidate.unset(index);
			}
		}
		else {
			// found a solution
			solutions.emplace_back(candidate);
		}

		// backtrack
		do {
			index--;
		} while (index >= 0 && input.get(index) > 0);
	}

	return solutions;
}

}
