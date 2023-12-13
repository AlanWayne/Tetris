#ifndef BLOCK_H
#define BLOCK_H

typedef struct {
	int x[4];
	int y[4];
} Block;

#define WIDTH 10
#define HEIGHT 20

int block_move(int x, int y, Block *block, int field[WIDTH][HEIGHT]);
void block_rotate(Block *block);
void block_new(Block *block);

#endif