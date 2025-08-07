#include "frontend.h"
#include "lib_specification.h"

#define DELAY_MS 20

void game_loop(void);

int main(void) {
  window_init();
  game_loop();
  endwin();
  return 0;
}

void game_loop(void) {
  WINDOW *win_board, *win_next, *win_score, *win_message;  // game windows
  create_windows(&win_board, &win_next, &win_score, &win_message);

  bool hold = false;
  UserAction_t key = Start;

  while (key != Terminate) {
    get_action(&key);
    userInput(key, hold);
    print_game(win_board, win_next, win_score, win_message);
    napms(DELAY_MS);
  }
  delete_windows(&win_board, &win_next, &win_score, &win_message);
}
