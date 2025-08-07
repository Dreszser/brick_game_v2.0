#ifndef TEST_HELPER_H_
#define TEST_HELPER_H_

#include <vector>

#include "lib_specification.h"
#include "snake_model.h"

namespace s21 {

class TestHelper {
 public:
  void SetState(SnakeLogic::SnakeState state);
  SnakeLogic::SnakeState GetState();

  void SetDirection(Snake::SnakeDirection direction);
  Snake::SnakeDirection GetDirection();

  void SetField(int i, int j, int value);
  std::vector<std::vector<int>> GetField();

  void SetPause(SnakeLogic::PauseType pause);
  SnakeLogic::PauseType GetPause();

  void PrepareSnakeForWinning();

  void StartGame();
  void PerformAction(UserAction_t action);
  void UpdateState();
  void MakeAMove();

  void PrintSnakeInfo();

  void SpawnApple(int i, int j);

  int GetLength();

  void RestartGame();

  Point GetHeadPosition();

  void SetScore(int score);

  int GetLevel();
};

}  // namespace s21

#endif  // TEST_HELPER_H_