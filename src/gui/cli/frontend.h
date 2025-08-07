#ifndef FRONTEND_H
#define FRONTEND_H

#include <locale.h>
#include <ncurses.h>
#include <string.h>

#include "lib_specification.h"

#define SPACE 1
#define GAME_W 22
#define INDICATORS_W 22

#define HEIGHT 22

#define WIDTH 46

#define NEXT_RECTANGLE_HEIGHT 8
#define NEXT_RECTANGLE_WIDTH INDICATORS_W - 4

#define WIN_SPACE 2

#define ESCAPE 27
#define ENTER_KEY 10

#define BOARD_W 20
#define BOARD_H 20

#define BOARD_POS_Y 2
#define BOARD_POS_X 2

#define NEXT_W 5
#define NEXT_H 10

#define NEXT_POS_Y 4
#define NEXT_POS_X 31

#define SCORE_W 12
#define SCORE_H 18

#define SCORE_POS_Y 10
#define SCORE_POS_X 26

#define MESSAGE_W 2
#define MESSAGE_H 16

#define MESSAGE_POS_Y 11
#define MESSAGE_POS_X 4

#define NEXT_SIZE 5
#define GAME_SIZE_H 20
#define GAME_SIZE_W 10

void print_rectangle(int y_begin, int x_begin, int vertical_size,
                     int horizontal_size);

void print_starting_message(WINDOW *message);
void print_pause_message(WINDOW *message);
void print_game_won_message(WINDOW *message);
void print_game_over_message(WINDOW *message);

void print_stats(WINDOW *next, WINDOW *score, GameInfo_t game);
void print_field(WINDOW *board, GameInfo_t game);
void print_game(WINDOW *board, WINDOW *next, WINDOW *score, WINDOW *message);

void print_pause(WINDOW *message);
void print_start(WINDOW *messgae);
void print_game_won(WINDOW *message);
void print_game_over(WINDOW *message);

void window_init(void);

bool get_action(UserAction_t *key);

void create_windows(WINDOW **, WINDOW **, WINDOW **, WINDOW **);
void delete_windows(WINDOW **, WINDOW **, WINDOW **, WINDOW **);

#endif  // FRONTEND_H
