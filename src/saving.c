#include "saving.h"

int check_record() {
	int record = 0;

	FILE* file = fopen("Tetris_save/record", "r");
	if (file != NULL) {
		char buff[4];
		fgets(buff, 4, file);
		sscanf(buff, "%d", &record);
		fclose(file);
	}

	return record;
}

int new_record(int score, int record) {
	printf("Your score: %d\n\n", score);

	if (score > record) {
		char buff[8];
		system("mkdir -p Tetris_save");
		FILE* file = fopen("Tetris_save/record", "w");
		if (file != NULL) {
			sprintf(buff, "%d", score);
			fputs(buff, file);
			fclose(file);
			printf("New record saved!\n");
		} else {
			printf("Aa");
		}
	}

	return 0;
}