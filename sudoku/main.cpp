#include <iostream>
#include <list>
#include <chrono>

#include "Puzzle.hpp"

#include "StackSolver.hpp"
#include "MaskSolver.hpp"
#include "FastSolver.hpp"
#include "SolvedPuzzleGenerator.hpp"
#include "PuzzleGenerator.hpp"

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

void test_mask_solver(const sudoku::Puzzle puzzle) {
	typedef chrono::steady_clock clock;
	auto start = clock::now();
	sudoku::MaskSolver solver;
	auto solution = solver.solve(puzzle);
	auto end = clock::now();
	auto duration = end - start;
	auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration).count();
	auto seconds = nanoseconds * 1e-9;

	cout << "I solved it in " << seconds * 1e3 << " milliseconds!" << endl;
	if (!solution.valid())
		cout << "Unfortunately, the solution contains errors!" << endl;
	if (!solution.full())
		cout << "Unfortunately, the solution contains " << solution.count_empty_cells() << " empty cells!" << endl;
	cout << "Here is the solution:";

	cout << endl << endl << solution.toString(sudoku::RenderFrameArgument::Yes) << endl;
}

void test_fast_solver(const sudoku::Puzzle puzzle) {
	typedef chrono::steady_clock clock;
	auto start = clock::now();
	sudoku::FastSolver solver;
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

void test_solved_puzzle_generator() {
	std::list<sudoku::Puzzle> puzzles;
	sudoku::SolvedPuzzleGenerator generator;

	typedef chrono::steady_clock clock;
	auto start = clock::now();

	for (int i = 0; i < 10; ++i) {
		auto puzzle = generator.get();
		puzzles.emplace_back(std::move(puzzle));
	}

	auto end = clock::now();
	auto duration = end - start;
	auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration).count();
	auto seconds = nanoseconds * 1e-9;

	cout << "Generated " << puzzles.size() << " puzzles in " << seconds * 1e3 << " milliseconds!" << endl;

	if (puzzles.size() <= 0) {
		cout << "No puzzles were generated!";
	}
	else if (puzzles.size() == 1) {
		cout << "Here is the puzzle:";
	}
	else {
		cout << "Here are all " << puzzles.size() << " puzzles:";
	}

	for (const auto &puzzle : puzzles) {
		cout << endl << endl << puzzle.toString(sudoku::RenderFrameArgument::Yes);
	}

	cout << endl;
}

void test_puzzle_generator(int num = 10) {
	std::list<sudoku::Puzzle> puzzles;
	sudoku::PuzzleGenerator generator(42);

	typedef chrono::steady_clock clock;
	auto start = clock::now();

	for (int i = 0; i < num; ++i) {
		auto puzzle = generator.get();
		puzzles.emplace_back(std::move(puzzle));
	}

	auto end = clock::now();
	auto duration = end - start;
	auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration).count();
	auto seconds = nanoseconds * 1e-9;

	cout << "Generated " << puzzles.size() << " puzzles in " << seconds * 1e3 << " milliseconds!" << endl;

	if (puzzles.size() <= 0) {
		cout << "No puzzles were generated!";
	}
	else if (puzzles.size() == 1) {
		cout << "Here is the puzzle:";
	}
	else {
		cout << "Here are all " << puzzles.size() << " puzzles:";
	}

	for (const auto &puzzle : puzzles) {
		cout << endl << endl << puzzle.toString(sudoku::RenderFrameArgument::Yes);
	}

	cout << endl;
}

template <typename T>
void benchmark_one(const std::list<sudoku::Puzzle> &puzzles) {
	using clock = chrono::steady_clock;
	T solver;

	auto start = clock::now();

	for (const auto &puzzle : puzzles) {
		auto solution = solver.solve(puzzle);
	}

	auto end = clock::now();
	auto duration = end - start;
	auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration).count();
	auto seconds = nanoseconds * 1e-9;

	cout << "I solved it in " << seconds * 1e3 << " milliseconds!" << endl;
}

void benchmark(int num = 10) {
	using clock = chrono::steady_clock;
	std::list<sudoku::Puzzle> puzzles;

	{
		sudoku::PuzzleGenerator generator(42);

		auto start = clock::now();

		for (int i = 0; i < num; ++i) {
			auto puzzle = generator.get();
			puzzles.emplace_back(std::move(puzzle));
		}

		auto end = clock::now();
		auto duration = end - start;
		auto nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration).count();
		auto seconds = nanoseconds * 1e-9;

		cout << "Generated " << puzzles.size() << " puzzles in " << seconds * 1e3 << " milliseconds!" << endl;
	}

	cout << "Benchmarking MaskSolver:" << endl;
	benchmark_one<sudoku::MaskSolver>(puzzles);

	cout << "Benchmarking StackSolver:" << endl;
	benchmark_one<sudoku::StackSolver>(puzzles);

	cout << "Benchmarking FastSolver:" << endl;
	benchmark_one<sudoku::FastSolver>(puzzles);
}

int main() {
	using namespace sudoku;

	// parse the puzzle
	auto puzzle = Puzzle::fromString(example_puzzle);
	/*
	// print it back out
	cout << "Here is your puzzle:" << endl << endl;
	cout << puzzle.toString(RenderFrameArgument::Yes) << endl << endl;

	cout << "Testing the StackSolver:" << endl;
	test_stack_solver(puzzle);
	cout << endl;

	cout << "Testing the MaskSolver:" << endl;
	test_mask_solver(puzzle);
	cout << endl;

	cout << "Testing the FastSolver:" << endl;
	test_fast_solver(puzzle);
	cout << endl;

	cout << "Testing the SolvedPuzzleGenerator:" << endl;
	test_solved_puzzle_generator();
	cout << endl;

	cout << "Testing the PuzzleGenerator:" << endl;
	test_puzzle_generator(50);
	cout << endl;
	*/

	benchmark(4);

	return 0;
}
