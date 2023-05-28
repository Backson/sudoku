#include "SolvedPuzzleGenerator.hpp"

#include <list>
#include <random>
#include <algorithm>

namespace sudoku {

namespace detail {

// algorithm is mostly identical with StackSolver, but it returns as soon as it finds the first solution, and it is randomized
template <typename RANDOM>
static Puzzle get(RANDOM &random) {
	// partially solved puzzles
	std::list<Puzzle> candidates;

	// start with an empty puzzle
	candidates.emplace_back(Puzzle());

	// shuffle this vector to get random order of numbers
	std::vector<int8_t> permutation;
	permutation.resize(Puzzle::PUZZLE_SIZE);
	for (int i = 0; i < Puzzle::PUZZLE_SIZE; ++i)
		permutation[i] = i;

	// keep working until all candidates are solved
	while ((int)candidates.size() > 0) {
		// remove puzzle from temporary list
		Puzzle puzzle = std::move(candidates.back());
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

		// if we didn't find any empty cells, the puzzle is solved
		// return it
		return puzzle;

		FOUND:

		// try all possible numbers for the selected cell
		// randomize the order
		std::shuffle(permutation.begin(), permutation.end(), random);
		for (int index = 0; index < puzzle.PUZZLE_SIZE; ++index) {
			int value = permutation[index] + 1;

			// place the number
			puzzle.set(row, column, value);

			// If the puzzle is still valid, add it to the pool of candidates.
			// We don't need to check for collisions everywhere, just for the
			// number we added just now.
			if (puzzle.valid(row, column))
				candidates.emplace_back(puzzle);
		}
	}

	// error!
	// return an empty puzzle
	return Puzzle();
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

Puzzle SolvedPuzzleGenerator::get() {
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
