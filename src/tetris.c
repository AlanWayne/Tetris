#include "tetris.h"

void collision(Block *block) {
	for (int i = 0; i < 4; ++i) {
		int temp_x = block->x[i];
		int temp_y = block->y[i];

		block->field[temp_x][temp_y] = 1;
	}

	block_new(block);
}

void movement(int *action, Block *block) {
	static int time_count = 0;
	int time_speed = 30;
	int collide = 0;

	if (time_count >= time_speed) {
		collide = block_move(0, 1, block);
		time_count = 0;
	} else {
		time_count += 1;
	}

	if (!collide && read(STDIN_FILENO, action, 4) == 1) {
		if (*action == 's' || *action == 'S') collide = block_move(0, 1, block);
		if (*action == 'a' || *action == 'A')
			collide = block_move(-1, 0, block);
		if (*action == 'd' || *action == 'D') collide = block_move(1, 0, block);
		if (*action == 'w' || *action == 'W') block_rotate(block);
	}

	if (collide) collision(block);
}

void draw(Data *data, Block *block) {
	setlocale(LC_CTYPE, "");

	wchar_t spr_wall[] = L"▒▒";
	char spr_wall_sub[MB_CUR_MAX];
	int spr_wall_len = wcstombs(spr_wall_sub, spr_wall, sizeof(spr_wall_sub));

	wchar_t spr_block[] = L"▓▓";
	char spr_block_sub[MB_CUR_MAX];
	int spr_block_len =
		wcstombs(spr_block_sub, spr_block, sizeof(spr_block_sub));

	wchar_t spr_empty[] = L"░░";
	char spr_empty_sub[MB_CUR_MAX];
	int spr_empty_len =
		wcstombs(spr_empty_sub, spr_empty, sizeof(spr_empty_sub));

	write(STDIN_FILENO, "\033[2J", 4);
	write(STDIN_FILENO, "\033[H", 4);

	for (int k = 0; k < HEIGHT; ++k) {
		write(STDIN_FILENO, spr_wall_sub, spr_wall_len);

		for (int i = 0; i < WIDTH; ++i) {
			if ((i == block->x[0] && k == block->y[0]) ||
				(i == block->x[1] && k == block->y[1]) ||
				(i == block->x[2] && k == block->y[2]) ||
				(i == block->x[3] && k == block->y[3]) || block->field[i][k]) {
				write(STDIN_FILENO, spr_block_sub, spr_block_len);
			} else {
				write(STDIN_FILENO, spr_empty_sub, spr_empty_len);
			}
		}

		write(STDIN_FILENO, spr_wall_sub, spr_wall_len);

		if (k == 6 || k == 7) {
			write(STDIN_FILENO, "  ", 2);
		}

		for (int i = 0; i < WIDTH; ++i) {
			if ((i + 2 + WIDTH == block->x_next[0] && k == block->y_next[0]) ||
				(i + 2 + WIDTH == block->x_next[1] && k == block->y_next[1]) ||
				(i + 2 + WIDTH == block->x_next[2] && k == block->y_next[2]) ||
				(i + 2 + WIDTH == block->x_next[3] && k == block->y_next[3])) {
				write(STDIN_FILENO, spr_block_sub, spr_block_len);
			}
		}

		if (k == 0) {
			char str[27];
			sprintf(str, "  Record: %5d", data->record);
			write(STDIN_FILENO, str, 15);
		}
		if (k == 2) {
			char str[32];
			sprintf(str, "  Score: %6d", data->score);
			write(STDIN_FILENO, str, 15);
		}
		if (k == 4) {
			char str[27];
			sprintf(str, "  Next:");
			write(STDIN_FILENO, str, 8);
		}

		write(STDIN_FILENO, "\n", 1);
	}
}

void check_lines(Block *block, Data *data) {
	int line_number[4] = {0};
	int line = 0;

	for (int k = 0; k < HEIGHT; ++k) {
		int sum = 0;

		for (int i = 0; i < WIDTH; ++i) {
			sum += block->field[i][k];
		}

		if (sum == WIDTH) {
			line_number[line] = k;
			line += 1;
		}
	}

	for (int l = line - 1; l >= 0; --l) {
		for (int i = 0; i < WIDTH; ++i) {
			block->field[i][line_number[line - 1]] = 0;
		}

		for (int k = line_number[l]; k > 0; --k) {
			for (int i = 0; i < WIDTH; ++i) {
				block->field[i][k] = block->field[i][k - 1];
			}
		}

		for (int i = 0; i < WIDTH; ++i) {
			block->field[i][0] = 0;
		}

		for (int i = 0; i < l; ++i) {
			line_number[i] += 1;
		}
	}

	data->score += pow(2, line) - 1;
}

int check_game_over(Block *block) {
	for (int i = 0; i < WIDTH; ++i) {
		if (block->field[i][0]) return 1;
	}
	return 0;
}

void save_result(Data *data) {
	write(STDIN_FILENO, "\033[2J", 4);
	write(STDIN_FILENO, "\033[H", 4);

	char buff[50];
	FILE *file = fopen("txt/message_1.txt", "r");

	while (fgets(buff, 50, file) != NULL) {
		write(STDIN_FILENO, buff, strlen(buff));
	}

	fclose(file);
}

void tetris(Data *data) {
	srand(time(NULL));

	int action = 0;

	int game_over = 0;

	Block block = {0};
	block.type_next = rand() % 7;

	block_new(&block);

	while (action != 'q' && !game_over) {
		action = 0;

		check_lines(&block, data);
		game_over = check_game_over(&block);
		movement(&action, &block);

		draw(data, &block);

		usleep(FPS);
	}

	if (game_over) {
		save_result(data);
	}
}