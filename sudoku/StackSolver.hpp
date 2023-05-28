#pragma once

#include "Solver.hpp"

namespace sudoku {

// A solver algorithm that keeps a number of solution candidates on a stack
class StackSolver : public Solver {
public:
	// get all solutions to the unput puzzle.
	// if the input puzzle is unsolvable or contains conflicts, returns an empty list.
	std::list<Puzzle> solve(const Puzzle &input) override;

	// get the number of solution candidates that were checked.
	int get_num_puzzles_checked() const { return puzzle_counter; }

	// get the maximum size that the list of candidates had.
	int get_max_list_length() const { return max_list_length; }

private:
	// performance metrics
	int puzzle_counter = 0;
	int max_list_length = 0;
};

}
