#ifndef BLOCK_H
#define BLOCK_H

typedef struct {
	int x[4];
	int y[4];
} Block;

#define WIDTH 10
#define HEIGHT 20

void block_move(int x, int y, Block *block);
void block_rotate(Block *block);
void block_new(Block *block);

#endif