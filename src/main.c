#include "main.h"

int main() {
	Data data;
	check_record(&data);

	conf_terminal(1);
	tetris(&data);
	conf_terminal(0);

	new_record(&data);

	return 0;
}
