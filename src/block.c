#include "block.h"

int block_move(int x, int y, Block *block, int field[WIDTH][HEIGHT]) {
	int collide = 0;

	for (int i = 0; i < 4 && !collide; ++i) {
		int temp_x = block->x[i] + x;
		int temp_y = block->y[i] + y;

		if (y && temp_y >= HEIGHT) {
			return 1;
		} else if (x && (temp_x < 0 || temp_x >= WIDTH)) {
			collide = 1;
		} else if (y && field[temp_x][temp_y]) {
			return 1;
		} else if (x && field[temp_x][temp_y]) {
			collide = 1;
		}
	}

	if (!collide) {
		for (int i = 0; i < 4; ++i) {
			block->x[i] += x;
			block->y[i] += y;
		}
	}

	return 0;
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