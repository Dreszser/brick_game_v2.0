#include "test_helper.h"

#include <iostream>

namespace s21 {

void TestHelper::SetState(SnakeLogic::SnakeState state) {
  SnakeLogic::GetInstance().state_ = state;
}

SnakeLogic::SnakeState TestHelper::GetState() {
  return SnakeLogic::GetInstance().state_;
}

void TestHelper::SetDirection(Snake::SnakeDirection direction) {
  SnakeLogic::GetInstance().direction_ = direction;
}

Snake::SnakeDirection TestHelper::GetDirection() {
  return SnakeLogic::GetInstance().direction_;
}

void TestHelper::SetField(int i, int j, int value) {
  SnakeLogic::GetInstance().game_info_->field[i][j] = value;
}

std::vector<std::vector<int>> TestHelper::GetField() {
  const int kRows = 20, kCols = 10;
  const auto* field = SnakeLogic::GetInstance().game_info_->field;

  std::vector<std::vector<int>> result(kRows, std::vector<int>(kCols));

  for (int i = 0; i < kRows; ++i) {
    for (int j = 0; j < kCols; ++j) {
      result[i][j] = field[i][j];
    }
  }
  return result;
}

SnakeLogic::PauseType TestHelper::GetPause() {
  return static_cast<SnakeLogic::PauseType>(
      SnakeLogic::GetInstance().game_info_->pause);
}

void TestHelper::SetPause(SnakeLogic::PauseType pause) {
  SnakeLogic::GetInstance().game_info_->pause = static_cast<int>(pause);
}

void TestHelper::PrepareSnakeForWinning() {
  const int kRows = 20;
  const int kLastCol = 9;
  auto* logic = &SnakeLogic::GetInstance();
  logic->snake_.position_.clear();
  logic->snake_.position_.push_back(Point(0, 0));
  for (int i = 1; i < kRows; ++i) {
    for (int j = 0; j < kLastCol; ++j) {
      if (i % 2 == 0) {
        logic->snake_.position_.push_back(Point(kLastCol - 1 - j, i));
      } else {
        logic->snake_.position_.push_back(Point(j, i));
      }
    }
  }
  for (int i = 0; i < 20; ++i) {
    logic->snake_.position_.push_back(Point(kLastCol, kRows - 1 - i));
  }
  for (int i = 8; i > 2; --i) {
    logic->snake_.position_.push_back(Point(i, 0));
  }
  SetDirection(Snake::kRight);
}

void TestHelper::StartGame() {
  SnakeLogic::GetInstance().UserInput(Start, false);
}

void TestHelper::PerformAction(UserAction_t action) {
  SnakeLogic::GetInstance().UserInput(action, false);
}

void TestHelper::UpdateState() {
  SnakeLogic::GetInstance().UpdateCurrentState();
}

void TestHelper::MakeAMove() {
  UpdateState();
  PerformAction(Action);
}

void TestHelper::PrintSnakeInfo() {
  std::cout << "i = " << SnakeLogic::GetInstance().snake_.position_.front().y
            << " j = " << SnakeLogic::GetInstance().snake_.position_.front().x
            << " length = " << SnakeLogic::GetInstance().snake_.position_.size()
            << " apple = "
            << SnakeLogic::GetInstance().apple_.position_.front().y << " "
            << SnakeLogic::GetInstance().apple_.position_.front().x
            << " state = " << SnakeLogic::GetInstance().state_ << "\n";
}

void TestHelper::SpawnApple(int i, int j) {
  SnakeLogic::GetInstance().apple_.position_.front().x = j;
  SnakeLogic::GetInstance().apple_.position_.front().y = i;
  UpdateState();
}

int TestHelper::GetLength() {
  return static_cast<int>(SnakeLogic::GetInstance().snake_.position_.size());
}

void TestHelper::RestartGame() { SnakeLogic::GetInstance().Restart(); }

Point TestHelper::GetHeadPosition() {
  return Point(SnakeLogic::GetInstance().snake_.position_.front().x,
               SnakeLogic::GetInstance().snake_.position_.front().y);
}

void TestHelper::SetScore(int score) {
  SnakeLogic::GetInstance().game_info_->score = score;
}

int TestHelper::GetLevel() {
  return SnakeLogic::GetInstance().game_info_->level;
}
}  // namespace s21
