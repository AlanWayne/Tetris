#include "tetris.h"

void collision(int field[WIDTH][HEIGHT], Block *block) {
	for (int i = 0; i < 4; ++i) {
		int temp_x = block->x[i];
		int temp_y = block->y[i];

		field[temp_x][temp_y] = 1;
	}

	block_new(block);
}

void movement(int *action, int field[WIDTH][HEIGHT], Block *block) {
	static int time_count = 0;
	int time_speed = 30;
	int collide = 0;

	if (time_count >= time_speed) {
		collide = block_move(0, 1, block, field);
		time_count = 0;
	} else {
		time_count += 1;
	}

	if (!collide && read(STDIN_FILENO, action, 4) == 1) {
		if (*action == 's' || *action == 'S')
			collide = block_move(0, 1, block, field);
		if (*action == 'a' || *action == 'A')
			collide = block_move(-1, 0, block, field);
		if (*action == 'd' || *action == 'D')
			collide = block_move(1, 0, block, field);
		if (*action == 'w' || *action == 'W') block_rotate(block, field);
	}

	if (collide) collision(field, block);
}

void draw(int field[WIDTH][HEIGHT], Block block) {
	char spr_wall[] = "#";
	char spr_block[] = "[]";
	char spr_empty[] = "__";

	write(STDIN_FILENO, "\033[2J", 4);
	write(STDIN_FILENO, "\033[H", 4);

	for (int k = 0; k < HEIGHT; ++k) {
		write(STDIN_FILENO, spr_wall, strlen(spr_wall));

		for (int i = 0; i < WIDTH; ++i) {
			if ((i == block.x[0] && k == block.y[0]) ||
				(i == block.x[1] && k == block.y[1]) ||
				(i == block.x[2] && k == block.y[2]) ||
				(i == block.x[3] && k == block.y[3]) || field[i][k]) {
				write(STDIN_FILENO, spr_block, strlen(spr_block));
			} else {
				write(STDIN_FILENO, spr_empty, strlen(spr_empty));
			}
		}

		write(STDIN_FILENO, spr_wall, strlen(spr_wall));
		write(STDIN_FILENO, "\n", 1);
	}
}

void draw_score(int score, int record) {
	char str[25];
	sprintf(str, "\nScore: %*d", 2 * WIDTH - 5, score);
	write(STDIN_FILENO, str, 25);
	sprintf(str, "\nRecord: %*d\n", 2 * WIDTH - 6, record);
	write(STDIN_FILENO, str, 25);
}

void check_lines(int field[WIDTH][HEIGHT], int *score) {
	int line_number[4] = {0};
	int line = 0;

	for (int k = 0; k < HEIGHT; ++k) {
		int sum = 0;

		for (int i = 0; i < WIDTH; ++i) {
			sum += field[i][k];
		}

		if (sum == WIDTH) {
			line_number[line] = k;
			line += 1;
		}
	}

	for (int l = line - 1; l >= 0; --l) {
		for (int i = 0; i < WIDTH; ++i) {
			field[i][line_number[line - 1]] = 0;
		}

		for (int k = line_number[l]; k > 0; --k) {
			for (int i = 0; i < WIDTH; ++i) {
				field[i][k] = field[i][k - 1];
			}
		}

		for (int i = 0; i < WIDTH; ++i) {
			field[i][0] = 0;
		}

		for (int i = 0; i < l; ++i) {
			line_number[i] += 1;
		}
	}

	*score += pow(2, line) - 1;
}

int check_game_over(int field[WIDTH][HEIGHT]) {
	for (int i = 0; i < WIDTH; ++i) {
		if (field[i][0]) return 1;
	}
	return 0;
}

void save_result(int score) {
	write(STDIN_FILENO, "\033[2J", 4);
	write(STDIN_FILENO, "\033[H", 4);

	char buff[50];
	FILE *file = fopen("txt/message_1.txt", "r");

	while (fgets(buff, 50, file) != NULL) {
		write(STDIN_FILENO, buff, strlen(buff));
	}

	fclose(file);
}

int tetris(int record) {
	srand(time(NULL));

	int score = 0;

	int field[WIDTH][HEIGHT] = {0};
	int action = 0;

	int game_over = 0;

	Block block = {-1};
	block_new(&block);

	while (action != 'q' && !game_over) {
		action = 0;

		check_lines(field, &score);
		game_over = check_game_over(field);
		movement(&action, field, &block);

		draw(field, block);
		draw_score(score, record);

		usleep(FPS);
	}

	if (game_over) {
		save_result(score);
	}

	return score;
}