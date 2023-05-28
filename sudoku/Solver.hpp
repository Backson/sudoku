#pragma once

#include "Puzzle.hpp"

#include <list>

namespace sudoku {

class Solver {
public:
	// give it an unsolved puzzle and it will return all solutions to that puzzle
	virtual std::list<sudoku::Puzzle> solve(const sudoku::Puzzle &input) = 0;
};

}
