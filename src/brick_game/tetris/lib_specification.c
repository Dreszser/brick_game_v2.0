/**
 * @file lib_specification.c
 *
 * @brief Implementation of functions from specification.
 */

#include "backend.h"
#include "fsm.h"
#include "pieces.h"
#include "score_and_time.h"

void userInput(UserAction_t action, bool hold) {
  signals fsm_table[7][8] = {
      {start, NULL, exitstate, NULL, NULL, NULL, NULL, NULL},
      {spawn, spawn, spawn, spawn, spawn, spawn, spawn, spawn},
      {NULL, pause, exitstate, moveleft, moveright, NULL, movedown, rotate},
      {shifting, shifting, shifting, shifting, shifting, shifting, shifting,
       shifting},
      {attach, attach, attach, attach, attach, attach, attach, attach},
      {gameover, gameover, gameover, gameover, gameover, gameover, gameover,
       gameover},
      {exitstate, exitstate, exitstate, exitstate, exitstate, exitstate,
       exitstate, exitstate}};

  signals act = NULL;
  Params_t parameters = get_params();
  act = fsm_table[*parameters.state][action];
  unsigned long current_time = get_current_time_in_ms();
  unsigned long elapsed_time = current_time - *parameters.last_tick;
  if (parameters.game_info->pause && action == Terminate) {
    exitstate(&parameters);
  } else if ((parameters.game_info->pause == 1 ||
              parameters.game_info->pause == 4) &&
             action == Start) {
    if (parameters.game_info->pause == 4) *parameters.state = START;
    parameters.game_info->pause = 0;
  } else if (parameters.game_info->pause == 2 && action == Pause) {
    parameters.game_info->pause = 0;
  } else if (!parameters.game_info->pause && act) {
    act(&parameters);
  } else if (!parameters.game_info->pause &&
             elapsed_time >= calculate_tick_interval()) {
    shifting(&parameters);
    *parameters.last_tick = current_time;
  }
  if (action == Down || parameters.game_info->pause)
    *parameters.last_tick = get_current_time_in_ms();
}

GameInfo_t updateCurrentState(void) {
  Params_t parameters = get_params();
  if (!parameters.game_info->field && !parameters.game_info->next &&
      *parameters.state != EXIT_STATE)
    initialize_game(&parameters);
  static GameInfo_t game_to_print = {0};
  if (game_to_print.field == NULL && *parameters.state != EXIT_STATE) {
    init_field(&game_to_print);
  }
  if (game_to_print.next == NULL && *parameters.state != EXIT_STATE) {
    game_to_print.next = (int **)calloc(5, sizeof(int *));
    for (int i = 0; i < 5; ++i) {
      game_to_print.next[i] = (int *)calloc(5, sizeof(int));
    }
  }
  transfer_data_for_printing(&parameters, &game_to_print);

  return game_to_print;
}
