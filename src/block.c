#include "block.h"

void block_move(int x, int y, Block *block) {
	for (int i = 0; i < 4; ++i) {
		block->x[i] += x;
		block->y[i] += y;
	}
}

void block_rotate(Block *block) {}

void block_new(Block *block) {
	block->x[0] = (WIDTH - 1) / 2;
	block->x[1] = (WIDTH - 1) / 2 + 1;
	block->x[2] = (WIDTH - 1) / 2;
	block->x[3] = (WIDTH - 1) / 2 + 1;

	block->y[0] = 0;
	block->y[1] = 0;
	block->y[2] = 1;
	block->y[3] = 1;
}