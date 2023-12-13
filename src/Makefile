CC = gcc
FLAGS = -Wall -Werror -Wextra
LIB_FLAGS = -lm
O_FILES = main.o tetris.o block.o conf.o saving.o
NAME = tetris

all: clang $(NAME)

rebuild: clean all

clean:
	rm -rf $(NAME) *.o Tetris_save

tetris: $(O_FILES)
	$(CC) $(FLAGS) $(O_FILES) -o $(NAME) $(LIB_FLAGS)

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c
	rm -rf .clang-format