#ifndef TETRIS_H
#define TETRIS_H

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "block.h"

#define FPS 1000000 / 30

void collision(Block *block);
void movement(int *action, Block *block);
void draw(Block *block);
void tetris(Data *data);

#endif