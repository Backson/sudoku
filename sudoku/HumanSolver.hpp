#pragma once

#include "Solver.hpp"

namespace sudoku {

// A solver algorithm that mimicks the strategy of a human player
class HumanSolver : public Solver {
public:
	// get all solutions to the unput puzzle.
	// if the input puzzle is unsolvable or contains conflicts, returns an empty list.
	std::list<Puzzle> solve(const Puzzle &input) override;
};

}
