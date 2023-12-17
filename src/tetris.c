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

void set_color(int color) {
	char buffer[8];
	if (color == -1) {
		sprintf(buffer, "\x1b[0m");
		write(STDIN_FILENO, buffer, 7);
	} else {
		sprintf(buffer, "\x1b[%dm", 31 + color);
		write(STDIN_FILENO, buffer, 7);
	}
	return;
}

void draw(Data *data, Block *block) {
	setlocale(LC_CTYPE, "");

	wchar_t spr_walls[] = L"▓▓";
	char spr_walls_sub[MB_CUR_MAX];
	int spr_walls_len =
		wcstombs(spr_walls_sub, spr_walls, sizeof(spr_walls_sub));

	wchar_t spr_block[] = L"▒▒";
	char spr_block_sub[MB_CUR_MAX];
	int spr_block_len =
		wcstombs(spr_block_sub, spr_block, sizeof(spr_block_sub));

	wchar_t spr_empty[] = L"  ";
	// wchar_t spr_empty[] = L"░░";
	char spr_empty_sub[MB_CUR_MAX];
	int spr_empty_len =
		wcstombs(spr_empty_sub, spr_empty, sizeof(spr_empty_sub));

	write(STDIN_FILENO, "\033[2J", 4);
	write(STDIN_FILENO, "\033[H", 4);

	for (int k = 0; k < HEIGHT; ++k) {
		write(STDIN_FILENO, spr_walls_sub, spr_walls_len);

		for (int i = 0; i < WIDTH; ++i) {
			if ((i == block->x[0] && k == block->y[0]) ||
				(i == block->x[1] && k == block->y[1]) ||
				(i == block->x[2] && k == block->y[2]) ||
				(i == block->x[3] && k == block->y[3])) {
				set_color(block->type);
				write(STDIN_FILENO, spr_block_sub, spr_block_len);
				set_color(-1);
			} else if (block->field[i][k]) {
				write(STDIN_FILENO, spr_block_sub, spr_block_len);
			}

			else {
				write(STDIN_FILENO, spr_empty_sub, spr_empty_len);
			}
		}

		write(STDIN_FILENO, spr_walls_sub, spr_walls_len);

		if (k == 6 || k == 7) {
			for (int i = WIDTH; i < WIDTH + 9; ++i) {
				if ((i == block->x_next[0] && k == block->y_next[0]) ||
					(i == block->x_next[1] && k == block->y_next[1]) ||
					(i == block->x_next[2] && k == block->y_next[2]) ||
					(i == block->x_next[3] && k == block->y_next[3])) {
					set_color(block->type_next);
					write(STDIN_FILENO, spr_block_sub, spr_block_len);
					set_color(-1);
				} else {
					write(STDIN_FILENO, "  ", 2);
				}
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
	int line = 0;

	for (int k = HEIGHT; k > 0; --k) {
		int sum = 0;

		for (int i = 0; i < WIDTH; ++i) {
			sum += block->field[i][k];
		}

		if (sum == WIDTH) {
			line += 1;

			for (int k2 = k; k2 > 0; --k2) {
				for (int i = 0; i < WIDTH; ++i) {
					block->field[i][k2] = block->field[i][k2 - 1];
				}
			}
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

void print_game_over(Data *data) {
	write(STDIN_FILENO, "\033[2J", 4);
	write(STDIN_FILENO, "\033[H", 4);

	char buff[50];
	FILE *file = fopen("txt/message_1.txt", "r");

	while (fgets(buff, 50, file) != NULL) {
		write(STDIN_FILENO, buff, strlen(buff));
	}

	fclose(file);
}

void tetris() {
	Data data;
	srand(time(NULL));
	check_record(&data);
	conf_terminal(1);

	int action = 0;

	Block block = {0};
	block.type_next = rand() % 7;

	block_new(&block);

	while (action != 'q' && !block.game_over) {
		action = 0;

		check_lines(&block, &data);
		block.game_over = check_game_over(&block);
		movement(&action, &block);

		draw(&data, &block);

		usleep(FPS - 150 * data.score);
	}

	if (block.game_over) {
		print_game_over(&data);
	}

	conf_terminal(0);
	new_record(&data);
}

void print(int value) {
	char buffer[64];
	sprintf(buffer, "%d\n", value);
	write(STDIN_FILENO, buffer, strlen(buffer));
}