#pragma once

#include "Puzzle.hpp"

namespace sudoku {

// generate a random puzzle
class PuzzleGenerator {
public:
	// Initialize with non-deterministic randomness.
	PuzzleGenerator() = default;

	// Initialize with specific seed.
	// Useful for reproducable results, like in tests.
	PuzzleGenerator(uint32_t seed) :
		seed(seed), is_seeded(true)
	{}

	// produce a new puzzle.
	// This is relatively computationally expensive.
	Puzzle get();

private:
	uint32_t seed = 0;
	bool is_seeded = false;
};

}
