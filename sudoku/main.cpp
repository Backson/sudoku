#include <iostream>
#include <list>
#include <chrono>

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

struct PerformanceMetrics {
	size_t max_number_of_candidates = 0;
	size_t number_of_candidates_checked = 0;
};

list<sudoku::Puzzle> solve(const sudoku::Puzzle &input, PerformanceMetrics *metrics = nullptr) {
	// solved puzzles
	list<sudoku::Puzzle> solved;

	// if the input puzzle is invalid, return an empty list (no solutions)
	if (metrics) {
		metrics->number_of_candidates_checked++;
		metrics->max_number_of_candidates = std::max(metrics->max_number_of_candidates, 1ull);
	}
	if (!input.valid())
		return solved;

	// partially solved puzzles
	list<sudoku::Puzzle> candidates;

	// start with a copy of the input puzzle
	candidates.emplace_back(input);

	// keep working until all puzzles are solved
	while (candidates.size() > 0) {
		// performance statistics
		if (metrics) {
			metrics->number_of_candidates_checked++;
			metrics->max_number_of_candidates = std::max(metrics->max_number_of_candidates, candidates.size());
		}


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
	PerformanceMetrics metrics;

	typedef chrono::steady_clock clock;
	auto start = clock::now();
	auto solutions = solve(puzzle, &metrics);
	auto end = clock::now();
	auto duration = end - start;
	auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration).count();
	auto seconds = nanoseconds * 1e-9;

	cout << "I solved it in " << seconds * 1e3 << " milliseconds!" << endl;
	cout << "I checked " << metrics.number_of_candidates_checked << " candidates!" << endl;
	cout << "I stored up to " << metrics.max_number_of_candidates << " candidates at the same time!" << endl;
	if (solutions.size() <= 0) {
		cout << "There are no valid solutions!";
	}
	else if (solutions.size() == 1) {
		cout << "Here is the solution:";
	}
	else {
		cout << "Here are all " << solutions.size() << " valid solutions:";
	}

	for (const auto & solution : solutions) {
		cout << endl << endl << solution.toString(RenderFrameArgument::Yes);
	}

	cout << endl;

	return 0;
}
