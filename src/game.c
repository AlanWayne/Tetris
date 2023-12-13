#include "game.h"

void logic(int *action, Block *block) {
	static int time_count = 0;
	int time_speed = 30;

	if (time_count >= time_speed) {
		block_move(0, 1, block);
		time_count = 0;
	} else {
		time_count += 1;
	}

	if (read(STDIN_FILENO, action, 4) == 1) {
		if (*action == 's' || *action == 'S') block_move(0, 1, block);
		if (*action == 'a' || *action == 'A') block_move(-1, 0, block);
		if (*action == 'd' || *action == 'D') block_move(1, 0, block);
		if (*action == 'w' || *action == 'W') block_rotate(block);
	}
}

void draw(int field[WIDTH][HEIGHT], Block block) {
	write(STDIN_FILENO, "\033[2J", 4);
	write(STDIN_FILENO, "\033[H", 4);

	for (int k = 0; k < HEIGHT; ++k) {
		write(STDIN_FILENO, "#", 1);

		for (int i = 0; i < WIDTH; ++i) {
			if ((i == block.x[0] && k == block.y[0]) ||
				(i == block.x[1] && k == block.y[1]) ||
				(i == block.x[2] && k == block.y[2]) ||
				(i == block.x[3] && k == block.y[3]) || field[i][k]) {
				write(STDIN_FILENO, "[]", 2);
			} else {
				write(STDIN_FILENO, "__", 2);
			}
		}
		write(STDIN_FILENO, "#\n", 2);
	}
}

void game() {
	int field[WIDTH][HEIGHT] = {0};
	int action = 0;

	Block block;
	block_new(&block);

	while (action != 'q') {
		action = 0;

		logic(&action, &block);
		draw(field, block);

		usleep(FPS);
	}
}