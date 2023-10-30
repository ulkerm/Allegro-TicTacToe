// file: src/board.h
#pragma once
#include "resources.h"

#define FIELD_SIZE 600 / 3
#define BOARD_SIZE 9
#define LINE_SIZE 2
#define SUBBOARD 3

char square[BOARD_SIZE];

void draw_x(bool new_board);
