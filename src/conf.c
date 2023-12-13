#include "conf.h"

void conf_terminal(int arg) {
	static struct termios old, new;

	if (arg == 1) {
		tcgetattr(STDIN_FILENO, &old);
		new = old;
		new.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &new);
		int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
		fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
	} else if (arg == 0) {
		tcsetattr(STDIN_FILENO, TCSANOW, &old);
	}
}