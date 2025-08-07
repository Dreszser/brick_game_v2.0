#include "frontend.h"

void window_init() {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);

  print_rectangle(SPACE, SPACE, HEIGHT, GAME_W);
  print_rectangle(SPACE, WIDTH - INDICATORS_W, HEIGHT, INDICATORS_W);
  print_rectangle(WIN_SPACE, SCORE_POS_X, NEXT_RECTANGLE_HEIGHT,
                  NEXT_RECTANGLE_WIDTH);
}

void print_rectangle(int y_begin, int x_begin, int vertical_size,
                     int horizontal_size) {
  for (int i = y_begin + 1; i < (vertical_size + y_begin); i++) {
    mvaddch(i, x_begin, ACS_VLINE);
    mvaddch(i, (horizontal_size + x_begin - 1), ACS_VLINE);
  }

  for (int i = x_begin + 1; i < (horizontal_size + x_begin); i++) {
    mvaddch(y_begin, i, ACS_HLINE);
    mvaddch((vertical_size + y_begin - 1), i, ACS_HLINE);
  }

  mvaddch(y_begin, x_begin, ACS_ULCORNER);
  mvaddch(y_begin, horizontal_size + x_begin - 1, ACS_URCORNER);
  mvaddch(vertical_size + y_begin - 1, x_begin, ACS_LLCORNER);
  mvaddch(vertical_size + y_begin - 1, horizontal_size + x_begin - 1,
          ACS_LRCORNER);
}

void print_starting_message(WINDOW *message) {
  mvwprintw(message, 0, 1, "start: ENTER");
  mvwprintw(message, 1, 1, " quit: ESCAPE");
}

void print_pause_message(WINDOW *message) {
  mvwprintw(message, 0, 1, "Game is paused");
  mvwprintw(message, 1, 1, "Continue: P");
}

void print_game_won_message(WINDOW *message) {
  mvwprintw(message, 0, 1, "You Won!");
  mvwprintw(message, 1, 1, "Restart: ENTER");
}

void print_game_over_message(WINDOW *message) {
  mvwprintw(message, 0, 1, "Game over!");
  mvwprintw(message, 1, 1, "Restart: ENTER");
}

void print_stats(WINDOW *next, WINDOW *score, GameInfo_t game) {
  werase(next);
  if (game.next) mvprintw(WIN_SPACE + 1, SCORE_POS_X + 1, "next:");
  for (int i = 0; i < NEXT_SIZE && game.next; ++i) {
    int tmp = 0;
    for (int j = 0; j < NEXT_SIZE; ++j) {
      if (game.next[i][j] == 1 || game.next[i][j] == 2) {
        mvwaddch(next, i, j + tmp++, ' ' | A_REVERSE);
        mvwaddch(next, i, j + tmp, ' ' | A_REVERSE);
      } else {
        tmp++;
      }
    }
  }
  werase(score);
  box(score, 0, 0);
  mvwprintw(score, 1, 1, "score: %d", game.score);
  mvwprintw(score, 4, 1, "best:  %d", game.high_score);
  mvwprintw(score, 7, 1, "level: %d", game.level);
  mvwprintw(score, 10, 1, "speed: %d", game.speed);
}

void print_field(WINDOW *board, GameInfo_t game) {
  werase(board);
  for (int i = 0; i < GAME_SIZE_H && game.field; ++i) {
    int tmp = 0;
    for (int j = 0; j < GAME_SIZE_W; ++j) {
      if (game.field[i][j] == 1) {
        mvwaddch(board, i, j + tmp++, ACS_CKBOARD);
        mvwaddch(board, i, j + tmp, ACS_CKBOARD);
      } else if (game.field[i][j] == 2) {
        mvwaddch(board, i, j + tmp++, ' ' | A_REVERSE);
        mvwaddch(board, i, j + tmp, ' ' | A_REVERSE);
      } else if (game.field[i][j] == 3) {
        mvwaddch(board, i, j + tmp++, '[');
        mvwaddch(board, i, j + tmp, ']');
      } else {
        mvwaddch(board, i, j + tmp++, ' ');
        mvwaddch(board, i, j + tmp, ' ');
      }
    }
  }
}

void print_game(WINDOW *board, WINDOW *next, WINDOW *score, WINDOW *message) {
  refresh();
  GameInfo_t game = updateCurrentState();
  switch (game.pause) {
    case 1:
      print_start(message);
      break;
    case 2:
      print_pause(message);
      break;
    case 3:
      print_game_won(message);
      break;
    case 4:
      print_game_over(message);
      break;
    default:
      werase(message);
      print_stats(next, score, game);
      print_field(board, game);
      break;
  }
  wrefresh(board);
  wrefresh(next);
  wrefresh(score);
}

void print_start(WINDOW *message) {
  print_starting_message(message);
  wrefresh(message);
}

void print_pause(WINDOW *message) {
  print_pause_message(message);
  wrefresh(message);
}

void print_game_won(WINDOW *message) {
  print_game_won_message(message);
  wrefresh(message);
}

void print_game_over(WINDOW *message) {
  print_game_over_message(message);
  wrefresh(message);
}

// Get user input
bool get_action(UserAction_t *key) {
  bool input = true;
  int ch = getch();
  switch (ch) {
    case KEY_UP:
      *key = Up;
      break;
    case KEY_DOWN:
      *key = Down;
      break;
    case KEY_LEFT:
      *key = Left;
      break;
    case KEY_RIGHT:
      *key = Right;
      break;
    case ESCAPE:
      *key = Terminate;
      break;
    case ENTER_KEY:
      *key = Start;
      break;
    case ' ':
      *key = Action;
      break;
    case 'p':
    case 'P':
      *key = Pause;
      break;
    default:
      *key = (updateCurrentState().pause ? Action : Start);
      input = false;
      break;
  }

  return input;
}

void create_windows(WINDOW **win_board, WINDOW **win_next, WINDOW **win_score,
                    WINDOW **win_message) {
  *win_board = newwin(BOARD_W, BOARD_H, BOARD_POS_Y, BOARD_POS_X);
  *win_next = newwin(NEXT_W, NEXT_H, NEXT_POS_Y, NEXT_POS_X);
  *win_score = newwin(SCORE_W, SCORE_H, SCORE_POS_Y, SCORE_POS_X);
  *win_message = newwin(MESSAGE_W, MESSAGE_H, MESSAGE_POS_Y, MESSAGE_POS_X);
}

void delete_windows(WINDOW **win_board, WINDOW **win_next, WINDOW **win_score,
                    WINDOW **win_message) {
  delwin(*win_board);
  delwin(*win_score);
  delwin(*win_next);
  delwin(*win_message);
}