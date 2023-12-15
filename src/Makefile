CC = gcc
FLAGS = -Wall -Werror -Wextra
LIB_FLAGS = -lm

NAME = tetris
O_FILES = main.o tetris.o block.o conf.o saving.o

DATE = $(shell date +"%Y.%m.%d | %H:%M:%S")
comment ?= $(DATE)  


all: clang $(NAME)

rebuild: clean all

tetris: $(O_FILES)
	$(CC) $(FLAGS) $(O_FILES) -o $(NAME) $(LIB_FLAGS)

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	rm -rf .clang-format

git: 
	git add ../.
	git commit -m'$(comment)'
	git push origin develop

bin_remove:
	rm -rf $(NAME).bin

clean:
	rm -rf $(NAME) *.o