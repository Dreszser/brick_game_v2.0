#include "snake_model.h"

/**
 * @file snake_logic.cc
 *
 * @brief Implementation of SnakeLogic class that contains FSM and basic game
 * logic.
 */

namespace s21 {
SnakeLogic &SnakeLogic::GetInstance() {
  static SnakeLogic game;
  return game;
}

GameInfo_t SnakeLogic::UpdateCurrentState() {
  UpdateGameInfo();
  return *game_info_;
}

void SnakeLogic::UserInput(UserAction_t action, bool hold) {
  (void)hold;
  signals fsm_table[5][8] = {
      {&SnakeLogic::StartGame, nullptr, &SnakeLogic::Exitstate, nullptr,
       nullptr, nullptr, nullptr, nullptr},
      {&SnakeLogic::Spawn, &SnakeLogic::Spawn, &SnakeLogic::Spawn,
       &SnakeLogic::Spawn, &SnakeLogic::Spawn, &SnakeLogic::Spawn,
       &SnakeLogic::Spawn, &SnakeLogic::Spawn},
      {nullptr, &SnakeLogic::PauseGame, &SnakeLogic::Exitstate,
       &SnakeLogic::MoveLeft, &SnakeLogic::MoveRight, &SnakeLogic::MoveUp,
       &SnakeLogic::MoveDown, &SnakeLogic::Shift},
      {&SnakeLogic::GameOver, &SnakeLogic::GameOver, &SnakeLogic::GameOver,
       &SnakeLogic::GameOver, &SnakeLogic::GameOver, &SnakeLogic::GameOver,
       &SnakeLogic::GameOver, &SnakeLogic::GameOver},
      {&SnakeLogic::Exitstate, &SnakeLogic::Exitstate, &SnakeLogic::Exitstate,
       &SnakeLogic::Exitstate, &SnakeLogic::Exitstate, &SnakeLogic::Exitstate,
       &SnakeLogic::Exitstate, &SnakeLogic::Exitstate}};

  signals act = nullptr;
  act = fsm_table[state_][action];

  bool is_paused = game_info_->pause != kNoPause;
  bool is_at_start_or_end = game_info_->pause == kStartPause ||
                            game_info_->pause == kGameOverPause ||
                            game_info_->pause == kGameWonPause;
  bool is_at_end =
      game_info_->pause == kGameOverPause || game_info_->pause == kGameWonPause;
  int current_time = GetCurrentTimeInMs();
  int elapsed_time = current_time - last_tick_;

  if (is_at_start_or_end && action == Start) {
    if (is_at_end) Restart();
    game_info_->pause = kNoPause;
  } else if (game_info_->pause == kDefaultPause && action == Pause) {
    game_info_->pause = kNoPause;
  } else if (!is_paused && act) {
    (this->*act)();
  } else if (!is_paused && elapsed_time >= game_info_->speed) {
    Shift();
    last_tick_ = current_time;
  }
  if (action == Action || game_info_->pause) {
    last_tick_ = GetCurrentTimeInMs();
  }
}

void SnakeLogic::InitializeGame() {
  game_info_->field = InitializeMatrix(kHeight, kWidth);
  game_info_->high_score = GetHighScore();
  game_info_->level = 0;
  game_info_->pause = kStartPause;
  game_info_->score = 0;
  game_info_->speed = CalculateTickInterval();
  state_ = kStart;
  last_tick_ = GetCurrentTimeInMs();
  direction_ = Snake::kUp;
}

void SnakeLogic::FreeResources() {
  for (int i = 0; i < kHeight; i++) {
    delete[] game_info_->field[i];
  }
  delete[] game_info_->field;

  delete game_info_;
}

std::vector<Point> SnakeLogic::GetEmptyField() {
  std::vector<Point> empty_field;
  for (int i = 0; i < kHeight; ++i) {
    for (int j = 0; j < kWidth; ++j) {
      if (!game_info_->field[i][j]) {
        empty_field.push_back(Point(j, i));
      }
    }
  }
  return empty_field;
}

void SnakeLogic::UpdateGameInfo() {
  for (int i = 0; i < kHeight; ++i) {
    for (int j = 0; j < kWidth; ++j) {
      game_info_->field[i][j] = 0;
    }
  }
  for (const auto &[x, y] : apple_.position_) {
    game_info_->field[y][x] = kApplePixel;
  }
  for (const auto &[x, y] : snake_.position_) {
    game_info_->field[y][x] = kSnakePixel;
  }
  game_info_->speed = CalculateTickInterval();
}

int SnakeLogic::CalculateTickInterval() {
  int base_speed = 300;
  int diff = 20;
  return (base_speed - (diff * game_info_->level));
}

int **SnakeLogic::InitializeMatrix(int rows, int cols) {
  int **field = new int *[rows];
  for (int i = 0; i < rows; ++i) {
    field[i] = new int[cols]();
  }
  return field;
}

void SnakeLogic::StartGame() {
  state_ = kSpawn;
  game_info_->pause = kNoPause;
}

void SnakeLogic::Exitstate() { state_ = kExit; }

void SnakeLogic::Spawn() {
  apple_.Spawn(GetEmptyField());
  state_ = kMoving;
}

void SnakeLogic::PauseGame() {
  game_info_->pause =
      (game_info_->pause == kNoPause ? kDefaultPause : kNoPause);
}

void SnakeLogic::MoveLeft() {
  if (snake_.GetDirection() != Snake::kRight) direction_ = Snake::kLeft;
}

void SnakeLogic::MoveRight() {
  if (snake_.GetDirection() != Snake::kLeft) direction_ = Snake::kRight;
}

void SnakeLogic::MoveUp() {
  if (snake_.GetDirection() != Snake::kDown) direction_ = Snake::kUp;
}

void SnakeLogic::MoveDown() {
  if (snake_.GetDirection() != Snake::kUp) direction_ = Snake::kDown;
}

void SnakeLogic::Shift() {
  if (snake_.MoveForward(direction_, apple_.position_.front())) {
    state_ = kGameOver;
  } else if (CheckForApple()) {
    AddScore();
    if ((int)snake_.position_.size() != kMaxLength) {
      Spawn();
    } else {
      state_ = kGameOver;
    }
  }
}

void SnakeLogic::AddScore() {
  ++game_info_->score;
  int new_level = game_info_->score / kPointsPerLevel;
  game_info_->level = (new_level <= kMaxLevel) ? new_level : kMaxLevel;
}

// void SnakeLogic::SpeedUp() { Shift(); }

void SnakeLogic::Restart() {
  snake_.SnakeReset();
  game_info_->high_score = GetHighScore();
  game_info_->level = 0;
  game_info_->score = 0;
  game_info_->speed = CalculateTickInterval();
  direction_ = Snake::kUp;
  state_ = kSpawn;
}

void SnakeLogic::GameOver() {
  if (game_info_->score > game_info_->high_score) {
    SaveHighScore();
  }
  if (snake_.position_.size() == (size_t)kMaxLength) {
    game_info_->pause = kGameWonPause;
  } else {
    game_info_->pause = kGameOverPause;
  }
}

bool SnakeLogic::CheckForApple() {
  return (snake_.position_.front() == apple_.position_.front());
}

void SnakeLogic::SaveHighScore() {
  std::ofstream file("/tmp/s.s21");
  if (file.is_open()) {
    file << game_info_->score;
    file.close();
  }
}

int SnakeLogic::GetHighScore() {
  std::ifstream file("/tmp/s.s21");
  int high_score = 0;
  if (file.is_open()) {
    file >> high_score;
    file.close();
  }
  return high_score;
}

int SnakeLogic::GetCurrentTimeInMs() {
  struct timespec spec;
  clock_gettime(CLOCK_MONOTONIC, &spec);
  return spec.tv_sec * 1000 + spec.tv_nsec / 1000000;
}

}  // namespace s21
