#include <iostream>
#include <list>

#include "Puzzle.hpp"

using namespace std;

// easy example puzzle
static const std::string example_puzzle =
	" 26  1   "
	"3    9257"
	"495    1 "
	" 4  531  "
	" 6321 74 "
	"  1 9  3 "
	" 89 7   1"
	"6   8 429"
	"   96 3 8";

list<sudoku::Puzzle> solve(const sudoku::Puzzle &input) {
	// solved puzzles
	list<sudoku::Puzzle> solved;

	// if the input puzzle is invalid, return an empty list (no solutions)
	if (!input.valid())
		return solved;

	// partially solved puzzles
	list<sudoku::Puzzle> candidates;

	// start with a copy of the input puzzle
	candidates.emplace_back(input);

	// keep working until all puzzles are solved
	while (candidates.size() > 0) {
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
		solved.emplace_back(puzzle);
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

	return solved;
}

int main() {
	using namespace sudoku;

	// parse the puzzle
	auto puzzle = Puzzle::fromString(example_puzzle);

	// print it back out
	cout << "Here is your puzzle:" << endl << endl;
	cout << puzzle.toString(RenderFrameArgument::Yes) << endl << endl;

	// and solve it
	auto solutions = solve(puzzle);
	cout << "Here is the solved puzzle:";
	for (const auto & solution : solutions) {
		cout << endl << endl << solution.toString(RenderFrameArgument::Yes);
	}

	cout << endl;

	return 0;
}
