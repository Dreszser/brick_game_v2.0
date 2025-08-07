#include <random>

/**
 * @file apple.cc
 *
 * @brief Apple class has only one method that generates new positon for apple,
 * this file bascially has only that method.
 */

#include "snake_model.h"

namespace s21 {
void Apple::Spawn(const std::vector<Point> empty_field) {
  std::random_device rand_dev;
  std::mt19937 gen(rand_dev());
  std::uniform_int_distribution<> distr(0, empty_field.size() - 1);
  Point new_apple = empty_field.at(distr(gen));
  position_.clear();
  position_.push_back(new_apple);
}
}  // namespace s21