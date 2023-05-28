#pragma once

#include "Puzzle.hpp"

namespace sudoku {

// generate a random, solved puzzle
class PuzzleGenerator {
public:
	// initialize with non-deterministic randomness
	PuzzleGenerator() = default;

	// initialize with specific seed
	// useful for reproducable results, like in tests
	PuzzleGenerator(uint32_t seed) :
		seed(seed), is_seeded(true)
	{}

	// return a random puzzle.
	Puzzle get();

private:
	uint32_t seed = 0;
	bool is_seeded = false;
};

}
