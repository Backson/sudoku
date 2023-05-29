#pragma once

#include "Puzzle.hpp"

#include <list>

namespace sudoku {

// A combination of the MaskSolver and the StackSolver. It should be very fast (like
// the MaskSolver) and always return all solutions (like the StackSolver).
class FastSolver {
public:
	// get all solutions to the unput puzzle.
	// if the input puzzle is unsolvable or contains conflicts, returns an empty list.
	std::list<Puzzle> solve(const Puzzle &input);
};

}
