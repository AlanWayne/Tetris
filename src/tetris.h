#ifndef TETRIS_H
#define TETRIS_H

#include <unistd.h>
#include <stdio.h>

#include "block.h"

#define FPS 1000000 / 30

void collision(int field[WIDTH][HEIGHT], Block* block);
void movement(int *action, int field[WIDTH][HEIGHT], Block *block);
void draw(int field[WIDTH][HEIGHT], Block block);
void tetris();

#endif