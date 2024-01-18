#pragma once

#include "Puzzle.hpp"

#include <list>

namespace sudoku {

// Very lean solver
class DepthSearchSolver {
public:
	// get all solutions to the input puzzle.
	// if the input puzzle is unsolvable or contains conflicts, returns an empty list.
	std::list<Puzzle> solve(const Puzzle &input);
};

}
