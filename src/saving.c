#include "saving.h"

void check_record(Data* data) {
	Data temp;
	FILE* file = fopen("tetris.bin", "rb");

	if (file != NULL) {
		fread(&temp, sizeof(temp), 1, file);
		data->record = temp.record;
		strcpy(data->name, temp.name);
		fclose(file);
	} else {
		data->record = 0;
	}
	data->score = 0;
}

void new_record(Data* data) {
	if (data->score > data->record) {
		data->record = data->score;
		FILE* file = fopen("tetris.bin", "wb");

		if (file != NULL) {
			fwrite(data, sizeof(data), 1, file);
			fclose(file);
			printf("New record saved!\n");
		}
	}
}