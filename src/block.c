#include "block.h"

int block_move(int x, int y, Block *block) {
	int collide = 0;
	for (int i = 0; i < 4 && !collide; ++i) {
		int temp_x = block->x[i] + x;
		int temp_y = block->y[i] + y;

		if (y && temp_y >= HEIGHT) {
			return 1;
		} else if (x && (temp_x < 0 || temp_x >= WIDTH)) {
			collide = 1;
		} else if (y && block->field[temp_x][temp_y]) {
			return 1;
		} else if (x && block->field[temp_x][temp_y]) {
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

void block_rotate(Block *block) {
	int temp_x[4];
	int temp_y[4];

	for (int i = 0; i < 4; ++i) {
		temp_x[i] = block->x[i];
		temp_y[i] = block->y[i];
	}

	switch (block->type) {
		case 1:
			switch (block->state) {
				case 0:
					temp_x[0] += 1;
					temp_y[0] += 1;
					temp_x[1] += 1;
					temp_y[1] -= 1;
					temp_x[3] -= 1;
					temp_y[3] += 1;
					break;
				case 1:
					temp_x[0] -= 1;
					temp_y[0] += 1;
					temp_x[1] += 1;
					temp_y[1] += 1;
					temp_x[3] -= 1;
					temp_y[3] -= 1;
					break;
				case 2:
					temp_x[0] -= 1;
					temp_y[0] -= 1;
					temp_x[1] -= 1;
					temp_y[1] += 1;
					temp_x[3] += 1;
					temp_y[3] -= 1;
					break;
				case 3:
					temp_x[0] += 1;
					temp_y[0] -= 1;
					temp_x[1] -= 1;
					temp_y[1] -= 1;
					temp_x[3] += 1;
					temp_y[3] += 1;
					break;
			}
			break;
		case 2:
			switch (block->state) {
				case 0:
					temp_x[0] += 2;
					temp_y[0] -= 1;
					temp_x[1] += 1;
					temp_y[2] += 1;
					temp_x[3] -= 1;
					temp_y[3] += 2;
					break;
				case 1:
					temp_x[0] += 1;
					temp_y[0] += 2;
					temp_y[1] += 1;
					temp_x[2] -= 1;
					temp_x[3] -= 2;
					temp_y[3] -= 1;
					break;
				case 2:
					temp_x[0] -= 2;
					temp_y[0] += 1;
					temp_x[1] -= 1;
					temp_y[2] -= 1;
					temp_x[3] += 1;
					temp_y[3] -= 2;
					break;
				case 3:
					temp_x[0] -= 1;
					temp_y[0] -= 2;
					temp_y[1] -= 1;
					temp_x[2] += 1;
					temp_x[3] += 2;
					temp_y[3] += 1;
					break;
			}
			break;
		case 3:
			switch (block->state) {
				case 0:
					temp_x[0] += 2;
					temp_x[1] += 1;
					temp_y[1] -= 1;
					temp_x[3] -= 1;
					temp_y[3] += 1;
					break;
				case 1:
					temp_y[0] += 2;
					temp_x[1] += 1;
					temp_y[1] += 1;
					temp_x[3] -= 1;
					temp_y[3] -= 1;
					break;
				case 2:
					temp_x[0] -= 2;
					temp_x[1] -= 1;
					temp_y[1] += 1;
					temp_x[3] += 1;
					temp_y[3] -= 1;
					break;
				case 3:
					temp_y[0] -= 2;
					temp_x[1] -= 1;
					temp_y[1] -= 1;
					temp_x[3] += 1;
					temp_y[3] += 1;
					break;
			}
			break;
		case 4:
			switch (block->state) {
				case 0:
					temp_y[0] += 2;
					temp_x[1] += 1;
					temp_y[1] -= 1;
					temp_x[3] -= 1;
					temp_y[3] += 1;
					break;
				case 1:
					temp_x[0] -= 2;
					temp_x[1] += 1;
					temp_y[1] += 1;
					temp_x[3] -= 1;
					temp_y[3] -= 1;
					break;
				case 2:
					temp_y[0] -= 2;
					temp_x[1] -= 1;
					temp_y[1] += 1;
					temp_x[3] += 1;
					temp_y[3] -= 1;
					break;
				case 3:
					temp_x[0] += 2;
					temp_x[1] -= 1;
					temp_y[1] -= 1;
					temp_x[3] += 1;
					temp_y[3] += 1;
					break;
			}
			break;
		case 5:
			switch (block->state) {
				case 0:
					temp_x[0] += 2;
					temp_x[1] += 1;
					temp_y[1] += 1;
					temp_x[3] -= 1;
					temp_y[3] += 1;
					break;
				case 1:
					temp_y[0] += 2;
					temp_x[1] -= 1;
					temp_y[1] += 1;
					temp_x[3] -= 1;
					temp_y[3] -= 1;
					break;
				case 2:
					temp_x[0] -= 2;
					temp_x[1] -= 1;
					temp_y[1] -= 1;
					temp_x[3] += 1;
					temp_y[3] -= 1;
					break;
				case 3:
					temp_y[0] -= 2;
					temp_x[1] += 1;
					temp_y[1] -= 1;
					temp_x[3] += 1;
					temp_y[3] += 1;
					break;
			}
			break;
		case 6:
			switch (block->state) {
				case 0:
					temp_x[0] += 1;
					temp_y[0] += 1;
					temp_y[1] += 2;
					temp_x[2] += 1;
					temp_y[2] -= 1;
					break;
				case 1:
					temp_x[0] -= 1;
					temp_y[0] += 1;
					temp_x[1] -= 2;
					temp_x[2] += 1;
					temp_y[2] += 1;
					break;
				case 2:
					temp_x[0] -= 1;
					temp_y[0] -= 1;
					temp_y[1] -= 2;
					temp_x[2] -= 1;
					temp_y[2] += 1;
					break;
				case 3:
					temp_x[0] += 1;
					temp_y[0] -= 1;
					temp_x[1] += 2;
					temp_x[2] -= 1;
					temp_y[2] -= 1;
					break;
			}
			break;
	}

	int collide = 0;
	for (int i = 0; i < 4 && !collide; ++i) {
		if (temp_x[i] < 0 || temp_x[i] >= WIDTH || temp_y[i] >= HEIGHT ||
			block->field[temp_x[i]][temp_y[i]]) {
			collide = 1;
		}
	}

	if (!collide) {
		for (int i = 0; i < 4; ++i) {
			block->x[i] = temp_x[i];
			block->y[i] = temp_y[i];
		}
		block->state += 1;
		if (block->state > 3) block->state = 0;
	}
}

void block_new(Block *block) {
	block->type = block->type_next;
	block->type_next = rand() % 7;

	block->state = 0;

	switch (block->type) {
		// O-shape
		case 0:
			block->x[0] = (WIDTH - 1) / 2;
			block->x[1] = (WIDTH - 1) / 2 + 1;
			block->x[2] = (WIDTH - 1) / 2;
			block->x[3] = (WIDTH - 1) / 2 + 1;

			block->y[0] = 0;
			block->y[1] = 0;
			block->y[2] = 1;
			block->y[3] = 1;

			break;

		// T-shape
		case 1:
			block->x[0] = (WIDTH - 1) / 2;
			block->x[1] = (WIDTH - 1) / 2 - 1;
			block->x[2] = (WIDTH - 1) / 2;
			block->x[3] = (WIDTH - 1) / 2 + 1;

			block->y[0] = 0;
			block->y[1] = 1;
			block->y[2] = 1;
			block->y[3] = 1;

			break;

		// I-shape
		case 2:
			block->x[0] = (WIDTH - 1) / 2 - 1;
			block->x[1] = (WIDTH - 1) / 2;
			block->x[2] = (WIDTH - 1) / 2 + 1;
			block->x[3] = (WIDTH - 1) / 2 + 2;

			block->y[0] = 0;
			block->y[1] = 0;
			block->y[2] = 0;
			block->y[3] = 0;

			break;

		// J-shape
		case 3:
			block->x[0] = (WIDTH - 1) / 2 - 1;
			block->x[1] = (WIDTH - 1) / 2 - 1;
			block->x[2] = (WIDTH - 1) / 2;
			block->x[3] = (WIDTH - 1) / 2 + 1;

			block->y[0] = 0;
			block->y[1] = 1;
			block->y[2] = 1;
			block->y[3] = 1;

			break;

		// L-shape
		case 4:
			block->x[0] = (WIDTH - 1) / 2 + 1;
			block->x[1] = (WIDTH - 1) / 2 - 1;
			block->x[2] = (WIDTH - 1) / 2;
			block->x[3] = (WIDTH - 1) / 2 + 1;

			block->y[0] = 0;
			block->y[1] = 1;
			block->y[2] = 1;
			block->y[3] = 1;

			break;

		// Z-shape
		case 5:
			block->x[0] = (WIDTH - 1) / 2 - 1;
			block->x[1] = (WIDTH - 1) / 2;
			block->x[2] = (WIDTH - 1) / 2;
			block->x[3] = (WIDTH - 1) / 2 + 1;

			block->y[0] = 0;
			block->y[1] = 0;
			block->y[2] = 1;
			block->y[3] = 1;

			break;

		//  S-shape
		case 6:
			block->x[0] = (WIDTH - 1) / 2;
			block->x[1] = (WIDTH - 1) / 2 + 1;
			block->x[2] = (WIDTH - 1) / 2 - 1;
			block->x[3] = (WIDTH - 1) / 2;

			block->y[0] = 0;
			block->y[1] = 0;
			block->y[2] = 1;
			block->y[3] = 1;

			break;
	}

	switch (block->type_next) {
		// O-shape
		case 0:
			block->x_next[0] = (WIDTH - 1) / 2;
			block->x_next[1] = (WIDTH - 1) / 2 + 1;
			block->x_next[2] = (WIDTH - 1) / 2;
			block->x_next[3] = (WIDTH - 1) / 2 + 1;

			block->y_next[0] = 0;
			block->y_next[1] = 0;
			block->y_next[2] = 1;
			block->y_next[3] = 1;

			break;

		// T-shape
		case 1:
			block->x_next[0] = (WIDTH - 1) / 2;
			block->x_next[1] = (WIDTH - 1) / 2 - 1;
			block->x_next[2] = (WIDTH - 1) / 2;
			block->x_next[3] = (WIDTH - 1) / 2 + 1;

			block->y_next[0] = 0;
			block->y_next[1] = 1;
			block->y_next[2] = 1;
			block->y_next[3] = 1;

			break;

		// I-shape
		case 2:
			block->x_next[0] = (WIDTH - 1) / 2 - 1;
			block->x_next[1] = (WIDTH - 1) / 2;
			block->x_next[2] = (WIDTH - 1) / 2 + 1;
			block->x_next[3] = (WIDTH - 1) / 2 + 2;

			block->y_next[0] = 0;
			block->y_next[1] = 0;
			block->y_next[2] = 0;
			block->y_next[3] = 0;

			break;

		// J-shape
		case 3:
			block->x_next[0] = (WIDTH - 1) / 2 - 1;
			block->x_next[1] = (WIDTH - 1) / 2 - 1;
			block->x_next[2] = (WIDTH - 1) / 2;
			block->x_next[3] = (WIDTH - 1) / 2 + 1;

			block->y_next[0] = 0;
			block->y_next[1] = 1;
			block->y_next[2] = 1;
			block->y_next[3] = 1;

			break;

		// L-shape
		case 4:
			block->x_next[0] = (WIDTH - 1) / 2 + 1;
			block->x_next[1] = (WIDTH - 1) / 2 - 1;
			block->x_next[2] = (WIDTH - 1) / 2;
			block->x_next[3] = (WIDTH - 1) / 2 + 1;

			block->y_next[0] = 0;
			block->y_next[1] = 1;
			block->y_next[2] = 1;
			block->y_next[3] = 1;

			break;

		// Z-shape
		case 5:
			block->x_next[0] = (WIDTH - 1) / 2 - 1;
			block->x_next[1] = (WIDTH - 1) / 2;
			block->x_next[2] = (WIDTH - 1) / 2;
			block->x_next[3] = (WIDTH - 1) / 2 + 1;

			block->y_next[0] = 0;
			block->y_next[1] = 0;
			block->y_next[2] = 1;
			block->y_next[3] = 1;

			break;

		//  S-shape
		case 6:
			block->x_next[0] = (WIDTH - 1) / 2;
			block->x_next[1] = (WIDTH - 1) / 2 + 1;
			block->x_next[2] = (WIDTH - 1) / 2 - 1;
			block->x_next[3] = (WIDTH - 1) / 2;

			block->y_next[0] = 0;
			block->y_next[1] = 0;
			block->y_next[2] = 1;
			block->y_next[3] = 1;

			break;
	}

	for (int i = 0; i < 4; ++i) {
		block->x_next[i] += WIDTH + 2;
		block->y_next[i] += 6;
	}
}