#include "main.h"

int main() {
	conf_terminal(1);

	int record = check_record();
	int score = tetris(record);

	conf_terminal(0);

	new_record(score, record);

	return 0;
}
