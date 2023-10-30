// file: src/game.h

#pragma once

#include <allegro5/allegro5.h>

#define SUBBOARD 3


int player_second();
int find_index(int x, int y) ;
bool is_valid(int choice);
void markBoard(int index, char mark);
int check_for_win(char mark);

void game_redraw(void);

void mouse_down(ALLEGRO_MOUSE_EVENT event);
void key_down(ALLEGRO_KEYBOARD_EVENT event);
