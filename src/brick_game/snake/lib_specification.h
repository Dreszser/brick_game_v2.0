#ifndef LIB_SPECIFICATION_H_
#define LIB_SPECIFICATION_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file lib_specification.h
 *
 * @brief Library specification from the task.
 *
 * @attention This specification can not be changed.
 *
 * @details This file contains structures and function declarations, that are
 * used to draw game scene in frontend. Basically this is a thin controller that
 * allows Qt(or ncurces) interface to get data from snake model.
 *
 * @details To pause the interface ```pause``` field from GameInfo_t is used.
 * There are 4 default pause states:
 * - ```0``` - no pause;
 * - ```1``` - starting screen pause(before the player presses play);
 * - ```2``` - default pause;
 * - ```3``` - winning game screen;
 * - ```4``` - losing game screen;
 *
 * @details Interface supports 4 values:
 * - 0 - empty cell;
 * - 1 - apple cell;
 * - 2 - snake cell;
 * - 3 - projection cell(unused in snake);
 */

#include <stdbool.h>

/**
 * @brief Represents the signal that user can send by pressing a key on the
 * keyboard.
 */
typedef enum {
  Start = 0, /**< Enter key. */
  Pause,     /**< 'P' key. */
  Terminate, /**< Escape key. */
  Left,      /**< Left arrow key. */
  Right,     /**< Right arrow key. */
  Up,        /**< Up arrow key. */
  Down,      /**< Down arrow key. */
  Action     /**< Spacebar key. */
} UserAction_t;

/**
 * @brief Structure that contains all information for frontend to print the game
 * scene.
 */
typedef struct {
  int **field;    /**< Game field. */
  int **next;     /**< Next piece. */
  int score;      /**< Current score integer. */
  int high_score; /**< High score integer. */
  int level;      /**< Current level integer. */
  int speed; /**< Current game speed integer. Time between snake movements in
                milliseconds */
  int pause; /**< 0 - default; 1 - start state pause; 2 - pause; 3 - game won; 4
              * - game over.
              */
} GameInfo_t;

/**
 * @brief This function takes user input and transfers it to the model.
 *
 * @param action User input.
 * @param hold Bool parameter responsible for keeping the button pressed.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Gathers all necessary resources from model for the interface.
 *
 * @return Copy of GameInfo_t from SnakeLogic object with updated locations of
 * apple and snake.
 */
GameInfo_t updateCurrentState();

#ifdef __cplusplus
}
#endif

#endif  // LIB_SPECIFICATION_H_
