#include <stdio.h>

#define WIDTH 10
#define HEIGHT 20

// =========
//  block.c

typedef struct {
	int x[4];
	int y[4];
} Block;

void move(int x, int y, Block* block) {
	for (int i = 0; i < 4; ++i) {
		block->x[i] += x;
		block->y[i] += y;
	}
}

void rotate_left(Block* block) {}

void rotate_right(Block* block) {}

void new_block(Block* block) {
	block->x[0] = (WIDTH - 1) / 2;
	block->x[1] = (WIDTH - 1) / 2 + 1;
	block->x[2] = (WIDTH - 1) / 2;
	block->x[3] = (WIDTH - 1) / 2 + 1;

	block->y[0] = 0;
	block->y[1] = 0;
	block->y[2] = 1;
	block->y[3] = 1;
}

//  block.c
// =========

void draw(int field[WIDTH][HEIGHT], Block block) {
	for (int k = 0; k < HEIGHT; ++k) {
		printf("#");
		for (int i = 0; i < WIDTH; ++i) {
			if ((i == block.x[0] && k == block.y[0]) ||
				(i == block.x[1] && k == block.y[1]) ||
				(i == block.x[2] && k == block.y[2]) ||
				(i == block.x[3] && k == block.y[3]) || field[i][k]) {
				printf("[]");
			} else {
				printf("__");
			}
		}
		printf("#");
		printf("\n");
	}
}

int main() {
	int field[WIDTH][HEIGHT] = {0};

	Block block;
	new_block(&block);


	for (int i = 0; i < WIDTH; ++i) printf("#");

	draw(field, block);

	return 0;
}
