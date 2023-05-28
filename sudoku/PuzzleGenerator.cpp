#include "PuzzleGenerator.hpp"

#include <list>
#include <random>
#include <algorithm>

#include "SolvedPuzzleGenerator.hpp"
#include "FastSolver.hpp"

namespace sudoku {

namespace detail {

template <typename RANDOM>
static Puzzle get(RANDOM &random) {
	SolvedPuzzleGenerator solved_puzzle_generator;
	Puzzle puzzle = solved_puzzle_generator.get();

	// shuffle all cells in the puzzle
	std::vector<int8_t> permutation;
	permutation.resize(Puzzle::DATA_SIZE);
	for (int i = 0; i < Puzzle::DATA_SIZE; ++i)
		permutation[i] = i;

	// solver to verify that the puzzle is still solvable
	FastSolver solver;

	// keep working until no more numbers can be removed
	bool again;
	do {
		again = false;

		// iterate over all cells in a random order
		std::shuffle(permutation.begin(), permutation.end(), random);
		for (int i = 0; i < Puzzle::DATA_SIZE; ++i) {
			int cell = permutation[i];
			int row = cell / Puzzle::PUZZLE_SIZE;
			int column = cell % Puzzle::PUZZLE_SIZE;

			// remember current number
			int value = puzzle.get(row, column);
			// skip cells that are already empty
			if (value == 0)
				continue;
			// delete number
			puzzle.unset(row, column);
			// try to solve it
			auto solutions = solver.solve(puzzle);
			if (solutions.size() > 1) {
				// can't remove this number, solution would become ambiguous.
				// add the number back
				puzzle.set(row, column, value);
			}
			else {
				// remove the number for good
				again = true;
			}
		}
	} while (again);

	return puzzle;
}

// turns a random_device into a seed sequence to initialize the mersenne_twister_engine.
template <typename RANDOM>
class generator {
public:
	generator(RANDOM &random) :
		random(random)
	{}

	void generate(unsigned long *begin, unsigned long *end) {
		while (begin < end) {
			*begin++ = random();
		}
	}

private:
	RANDOM &random;
};

}

Puzzle PuzzleGenerator::get() {
	if (is_seeded) {
		std::mt19937 random(seed);
		return detail::get(random);
	}
	else {
		std::random_device r;
		detail::generator<std::random_device> generator(r);
		std::mt19937 random(generator);
		return detail::get(random);
	}
}

}
