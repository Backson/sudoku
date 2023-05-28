#pragma once

#include "Puzzle.hpp"

namespace sudoku {

// A solver algorithm that mimicks the strategy of a human player.
// It is very fast, but it can only handle a single solution. If there
// are multiple solutions, it fills in the cells that are unambiguous
// and returns a single partially-solved puzzle.
// It may not find a solution, because it is stuck. In that case it will
// fill in as many cells as possible and return the partial solution.
class HumanSolver {
public:
	// solve the input puzzle as far as possible.
	Puzzle solve(const Puzzle &input);
};

}
