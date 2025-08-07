#include "snake_model.h"

/**
 * @file snake.cc
 *
 * @brief Implementation of Snake class that contains movement and collision
 * checks.
 */

namespace s21 {

bool Snake::MoveForward(int dir, Point apple) {
  bool result = 0;
  switch (dir) {
    case kUp:
      result = MoveUp(apple);
      break;
    case kRight:
      result = MoveRight(apple);
      break;
    case kDown:
      result = MoveDown(apple);
      break;
    default:
      result = MoveLeft(apple);
      break;
  }
  return result;
}

bool Snake::MoveRight(Point apple) {
  bool result = 0;
  Point temp = position_.front();
  ++temp.x;
  if (apple == temp) position_.push_back(Point(0, 0));
  result = CheckCollision(temp, kRight);
  int size = position_.size();
  for (int i = 0; i < size && !result; ++i) {
    if (i == 0) {
      temp = position_[i];
      ++position_[i].x;
    } else
      std::swap(position_[i], temp);
  }
  return result;
}

bool Snake::MoveLeft(Point apple) {
  bool result = 0;
  Point temp = position_.front();
  --temp.x;
  if (apple == temp) position_.push_back(Point(0, 0));
  result = CheckCollision(temp, kLeft);
  int size = position_.size();
  for (int i = 0; i < size && !result; ++i) {
    if (i == 0) {
      temp = position_[i];
      --position_[i].x;
    } else
      std::swap(position_[i], temp);
  }
  return result;
}

bool Snake::MoveUp(Point apple) {
  bool result = 0;
  Point temp = position_.front();
  --temp.y;
  if (apple == temp) position_.push_back(Point(0, 0));
  result = CheckCollision(temp, kUp);
  int size = position_.size();
  for (int i = 0; i < size && !result; ++i) {
    if (i == 0) {
      temp = position_[i];
      --position_[i].y;
    } else
      std::swap(position_[i], temp);
  }
  return result;
}

bool Snake::MoveDown(Point apple) {
  bool result = 0;
  Point temp = position_.front();
  ++temp.y;
  if (apple == temp) position_.push_back(Point(0, 0));
  result = CheckCollision(temp, kDown);
  int size = position_.size();
  for (int i = 0; i < size && !result; ++i) {
    if (i == 0) {
      temp = position_[i];
      ++position_[i].y;
    } else
      std::swap(position_[i], temp);
  }
  return result;
}

int Snake::GetDirection() {
  int x_diff = position_[0].x - position_[1].x;
  int y_diff = position_[0].y - position_[1].y;
  int result = 0;
  if (x_diff != 0) {
    result = (x_diff < 0) ? kLeft : kRight;
  } else {
    result = (y_diff < 0) ? kUp : kDown;
  }
  return result;
}

bool Snake::CheckCollision(Point head, int move_dir) {
  const int max_y = 19, max_x = 9;
  const int min_y = 0, min_x = 0;

  bool result = false;
  if (move_dir == kDown) result = head.y > max_y;
  if (move_dir == kUp) result = head.y < min_y;
  if (move_dir == kLeft) result = head.x < min_x;
  if (move_dir == kRight) result = head.x > max_x;
  for (long unsigned i = 1; (i < position_.size() - 1) && !result; ++i) {
    if (position_[i] == head) result = true;
  }
  return result;
}

void Snake::SnakeReset() {
  const int starting_pos_x = 5, starting_pos_y = 10, starting_length = 4;

  position_.clear();
  for (int i = 0; i < starting_length; ++i) {
    position_.push_back(Point(starting_pos_x, starting_pos_y + i));
  }
}

}  // namespace s21