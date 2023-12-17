#include <stdio.h>

int main() {
	for (int i = 0; i < 100; ++i) {
		printf("\x1b[%dm %d\n", i, i);
	}
	return 0;
}