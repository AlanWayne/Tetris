CC = gcc
FLAGS = -Wall -Werror -Wextra

all: clang tetris

rebuild: clean all

clean:
	rm -rf tetris *.o

tetris: main.o
	$(CC) $(FLAGS) main.o -o tetris
	./tetris

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c
	clang-format -i *.c
	rm -rf .clang-format