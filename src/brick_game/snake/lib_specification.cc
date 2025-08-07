/**
 * @file lib_specification.cc
 *
 * @brief Implementation of two C-style functions from library specification.
 */

#include "snake_model.h"

void userInput(UserAction_t action, bool hold) {
  s21::SnakeLogic::GetInstance().UserInput(action, hold);
}

GameInfo_t updateCurrentState() {
  return s21::SnakeLogic::GetInstance().UpdateCurrentState();
}