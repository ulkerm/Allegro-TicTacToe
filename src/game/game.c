// file: src/game.c
#include "game.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "resources.h"
#include "utils.h"
#include "board.h"

const char* you_won_text = "YOU WON";
const char* looser_text = "YOU LOST";
const char* continue_text = "Press ESC to play";

bool running = true;
bool redraw = false;
bool new_board;
bool game_over = false;
int mouse_x;
int mouse_y;
int player = 3;
int choice;

int player_second() {
    srand(time(NULL));
    int nr = rand() % BOARD_SIZE;
    return nr;
}

int find_index(int x, int y) {
    int check_board[SUBBOARD] = {200, 400, 600};
    for(int i = 0; i <= LINE_SIZE; i ++) {
        if(check_board[i] >= x) {x = i; break;}
    }   
    for(int i = 0; i <= LINE_SIZE; i ++) {
        if(check_board[i] >= y) {y = i; break;}
    } 
    int index = y * SUBBOARD + x;
    return index;
}

bool is_valid(int choice) {
    bool return_value;
    return_value = true;
    if(square[choice] == 'X' || square[choice] == 'o')
        return_value = false;
    return return_value;
}

void markBoard(int index, char mark) { 
    square[index] = mark;
}

int check_for_win(char mark) {
    int return_value = 0;
    int count = 0;
    int count1= 0;
    for(int i = 0; i <= LINE_SIZE; i++) {
        for(int j = 0; j <= LINE_SIZE; j++) {
            if(square[i * SUBBOARD + j] == mark) count++;
            if(square[j * SUBBOARD + i] == mark) count1++;
        }
        if(count == SUBBOARD || count1 == SUBBOARD) {
            return_value = 1;
        } else {
            count = 0;
            count1 = 0;
        }
    }
    if(square[0] == mark && square[4] == mark && square[8] == mark)
        return_value = 1;
    if(square[2] == mark && square[4] == mark && square[6] == mark)
        return_value = 1;
    return return_value;
}

void game_redraw(void) {
    al_clear_to_color(al_map_rgb_f(1, 1, 1));
    for(int i = 1; i <= LINE_SIZE; i++) {
                al_draw_line(i * 200, 0, i *200,
                    al_get_display_height(disp),
                    al_map_rgb_f(1, 0, 0), 5);
                al_draw_line(0 ,i * 200, 
                    al_get_display_width(disp),
                    i *200,
                    al_map_rgb_f(1, 0, 0), 5);
            }    
    draw_x(new_board);
    if(check_for_win('X') == 1) {
        game_over = true;
        al_draw_text(font, al_map_rgb(255, 0, 0), (al_get_display_width(disp) / SUBBOARD), (al_get_display_height(disp) / SUBBOARD), 0, you_won_text);
        al_draw_text(font, al_map_rgb(255, 0, 0), (al_get_display_width(disp) / SUBBOARD / 6), (al_get_display_height(disp) / SUBBOARD * 2), 0, continue_text);
    }
    if(check_for_win('o') == 1) {
        game_over = true;
        al_draw_text(font, al_map_rgb(255, 0, 0), (al_get_display_width(disp) / SUBBOARD), (al_get_display_height(disp) / SUBBOARD), 0, looser_text);
        al_draw_text(font, al_map_rgb(255, 0, 0), (al_get_display_width(disp) / SUBBOARD / 6), (al_get_display_height(disp) / SUBBOARD * 2), 0, continue_text);
    }   
    al_flip_display();
}

void mouse_down(ALLEGRO_MOUSE_EVENT event) {    
    if(event.button & 1 && !game_over) {
        new_board = false;        
        player = (player % 2) ? 1 : 2;
        if(player == 1) {
            mouse_x = event.x;
            mouse_y = event.y;
            choice = find_index(mouse_x, mouse_y);
            if(is_valid(choice)) {
                player++;
                markBoard(choice, 'X');};                   
            } 
        if(player == 2) {
            choice = player_second();
            if(is_valid(choice)) {
                player++;
                markBoard(choice, 'o');}
            }
        } 
    redraw = true;            
}

void key_down(ALLEGRO_KEYBOARD_EVENT event) {
    if(event.keycode == ALLEGRO_KEY_ESCAPE) {
        new_board = true;
        game_over = false;
        for(int i = 0; i < BOARD_SIZE; i++)
            square[i] = '0';
        redraw = true;
    }
}

