#ifndef BLOCK_H
#define BLOCK_H

typedef struct {
	int x[4];
	int y[4];
	int x_next[4];
	int y_next[4];

	int type;
	int type_next;
	int state;

	int field[10][20];
	int game_over;
} Block;

typedef struct {
	int score;
	int record;
	char name[16];
} Data;

#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 20

int block_move(int x, int y, Block *block);
void block_rotate(Block *block);
void block_new(Block *block);

#endif