#pragma once

#include "Puzzle.hpp"

#include <list>

namespace sudoku {

// A combination of the HumanSolver and the StackSolver. It should be very fast (like
// the HumanSolver) and always return all soltions (like the StackSolver).
class FastSolver {
public:
	// get all solutions to the unput puzzle.
	// if the input puzzle is unsolvable or contains conflicts, returns an empty list.
	std::list<Puzzle> solve(const Puzzle &input);
};

}
