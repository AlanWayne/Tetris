#ifndef GAME_H
#define GAME_H

#include <unistd.h>
#include <stdio.h>
#include "block.h"
#define FPS 1000000 / 30

void logic(int *action, Block *block);
void draw(int field[WIDTH][HEIGHT], Block block);
void game();

#endif