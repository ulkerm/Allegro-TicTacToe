// file: src/board.c
#include "board.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "resources.h"
#include "utils.h"

void draw_x(bool new_board) {
    if(new_board == false) {
        for(int i = 0; i <= LINE_SIZE; i++) {
            for(int j = 0; j <= LINE_SIZE; j++) {
                if(square[j * SUBBOARD + i] == 'X') {
                    al_draw_line((FIELD_SIZE * i) + 50, (FIELD_SIZE * j) + 50, (FIELD_SIZE * i) + 150, (FIELD_SIZE * j) + 150, al_map_rgb(0, 0, 255), 15);
                    al_draw_line((FIELD_SIZE * i) + 50, (FIELD_SIZE * j) + 150, (FIELD_SIZE * i) + 150, (FIELD_SIZE * j) + 50, al_map_rgb(0, 0, 255), 15);
                } 
                if(square[i * SUBBOARD + j] == 'o') {
                    al_draw_circle((FIELD_SIZE * j) + 100, (FIELD_SIZE * i) + 100, 60, al_map_rgb(0, 255, 0), 15);
                }
            }
        }
    }
}

