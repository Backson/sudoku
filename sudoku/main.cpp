#include <iostream>
#include <list>
#include <chrono>

#include "Puzzle.hpp"

#include "StackSolver.hpp"
#include "HumanSolver.hpp"

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

void test_human_solver(const sudoku::Puzzle puzzle) {
	typedef chrono::steady_clock clock;
	auto start = clock::now();
	sudoku::HumanSolver solver;
	auto solutions = solver.solve(puzzle);
	auto end = clock::now();
	auto duration = end - start;
	auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration).count();
	auto seconds = nanoseconds * 1e-9;

	cout << "I solved it in " << seconds * 1e3 << " milliseconds!" << endl;
	if (solutions.size() <= 0) {
		cout << "There are no valid solutions!";
	}
	else if (solutions.size() == 1) {
		cout << "Here is the solution:";
	}
	else {
		cout << "Here are all " << solutions.size() << " valid solutions:";
	}

	for (const auto &solution : solutions) {
		cout << endl << endl << solution.toString(sudoku::RenderFrameArgument::Yes);
	}

	cout << endl;
}

void test_stack_solver(const sudoku::Puzzle puzzle) {
	typedef chrono::steady_clock clock;
	auto start = clock::now();
	sudoku::StackSolver solver;
	auto solutions = solver.solve(puzzle);
	auto end = clock::now();
	auto duration = end - start;
	auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration).count();
	auto seconds = nanoseconds * 1e-9;

	cout << "I solved it in " << seconds * 1e3 << " milliseconds!" << endl;
	cout << "I checked " << solver.get_num_puzzles_checked() << " candidates!" << endl;
	cout << "I stored up to " << solver.get_max_list_length() << " candidates at the same time!" << endl;
	if (solutions.size() <= 0) {
		cout << "There are no valid solutions!";
	}
	else if (solutions.size() == 1) {
		cout << "Here is the solution:";
	}
	else {
		cout << "Here are all " << solutions.size() << " valid solutions:";
	}

	for (const auto &solution : solutions) {
		cout << endl << endl << solution.toString(sudoku::RenderFrameArgument::Yes);
	}

	cout << endl;
}

int main() {
	using namespace sudoku;

	// parse the puzzle
	auto puzzle = Puzzle::fromString(example_puzzle);

	// print it back out
	cout << "Here is your puzzle:" << endl << endl;
	cout << puzzle.toString(RenderFrameArgument::Yes) << endl << endl;

	cout << "Testing the StackSolver:" << endl;
	test_stack_solver(puzzle);
	cout << endl;

	cout << "Testing the HumanSolver:" << endl;
	test_human_solver(puzzle);
	cout << endl;

	return 0;
}
