#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include "test_helper.h"

TEST(basic_tests, starting_game) {
  s21::TestHelper helper;
  helper.StartGame();
  EXPECT_EQ(helper.GetPause(), s21::SnakeLogic::kNoPause);
}

TEST(basic_tests, hitting_walls) {
  s21::TestHelper helper;
  helper.StartGame();
  for (int i = 0; i < 15; ++i) {
    helper.MakeAMove();
  }
  EXPECT_EQ(helper.GetPause(), s21::SnakeLogic::kGameOverPause);

  helper.PerformAction(Start);
  helper.MakeAMove();
  helper.PerformAction(Right);
  for (int i = 0; i < 10; ++i) {
    helper.MakeAMove();
  }
  EXPECT_EQ(helper.GetPause(), s21::SnakeLogic::kGameOverPause);

  helper.PerformAction(Start);
  helper.MakeAMove();
  helper.PerformAction(Left);
  for (int i = 0; i < 10; ++i) {
    helper.MakeAMove();
  }
  EXPECT_EQ(helper.GetPause(), s21::SnakeLogic::kGameOverPause);

  helper.PerformAction(Start);
  helper.MakeAMove();
  helper.PerformAction(Right);
  helper.MakeAMove();
  helper.PerformAction(Down);
  helper.MakeAMove();
  for (int i = 0; i < 15; ++i) {
    helper.MakeAMove();
  }
  EXPECT_EQ(helper.GetPause(), s21::SnakeLogic::kGameOverPause);
}

TEST(basic_tests, winning_game) {
  const int max_length = 200;
  s21::TestHelper helper;
  helper.StartGame();
  helper.PrepareSnakeForWinning();
  helper.MakeAMove();
  for (int i = 0; i < 5; ++i) {
    helper.MakeAMove();
  }
  EXPECT_EQ(helper.GetPause(), s21::SnakeLogic::kGameWonPause);
  EXPECT_EQ(helper.GetLength(), max_length);
}

TEST(basic_tests, hitting_tail) {
  s21::TestHelper helper;
  helper.StartGame();
  helper.PrepareSnakeForWinning();
  helper.MakeAMove();
  helper.MakeAMove();
  helper.PerformAction(Down);
  for (int i = 0; i < 5; ++i) {
    helper.MakeAMove();
  }
  EXPECT_EQ(helper.GetPause(), s21::SnakeLogic::kGameOverPause);
}

TEST(basic_tests, eating_apple_up) {
  const int starting_length = 4;
  s21::TestHelper helper;
  helper.StartGame();
  helper.MakeAMove();
  helper.SpawnApple(9, 5);
  helper.MakeAMove();
  EXPECT_NE(starting_length, helper.GetLength());
  helper.RestartGame();
}

TEST(basic_tests, eating_apple_left) {
  const int starting_length = 4;
  s21::TestHelper helper;
  helper.StartGame();
  helper.MakeAMove();
  helper.PerformAction(Left);
  helper.SpawnApple(9, 4);
  helper.MakeAMove();
  EXPECT_NE(starting_length, helper.GetLength());
  helper.RestartGame();
}

TEST(basic_tests, eating_apple_right) {
  const int starting_length = 4;
  s21::TestHelper helper;
  helper.StartGame();
  helper.MakeAMove();
  helper.PerformAction(Right);
  helper.SpawnApple(9, 6);
  helper.MakeAMove();
  EXPECT_NE(starting_length, helper.GetLength());
  helper.RestartGame();
}

TEST(basic_tests, eating_apple_down) {
  const int starting_length = 4;
  s21::TestHelper helper;
  helper.StartGame();
  helper.MakeAMove();
  helper.PerformAction(Right);
  helper.MakeAMove();
  helper.PerformAction(Down);
  helper.SpawnApple(10, 6);
  helper.MakeAMove();
  EXPECT_NE(starting_length, helper.GetLength());
  helper.RestartGame();
}

TEST(basic_tests, pausing) {
  s21::TestHelper helper;
  helper.StartGame();
  helper.MakeAMove();
  helper.PerformAction(Pause);
  helper.MakeAMove();
  helper.PerformAction(Start);
  helper.PerformAction(Down);
  EXPECT_EQ(helper.GetPause(), s21::SnakeLogic::kDefaultPause);
  helper.PerformAction(Pause);
  helper.MakeAMove();
  EXPECT_EQ(helper.GetPause(), s21::SnakeLogic::kNoPause);
  helper.RestartGame();
}

TEST(basic_tests, empty_command_and_exit) {
  s21::TestHelper helper;
  helper.PerformAction(Pause);
  helper.MakeAMove();
  helper.StartGame();
  helper.MakeAMove();
  helper.PerformAction(Terminate);
  helper.MakeAMove();
  EXPECT_EQ(helper.GetState(), s21::SnakeLogic::kExit);
  helper.RestartGame();
}

TEST(basic_tests, game_tick) {
  s21::TestHelper helper;
  helper.StartGame();
  helper.MakeAMove();
  s21::Point starting_pos = helper.GetHeadPosition();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  helper.PerformAction(Start);
  helper.UpdateState();
  EXPECT_NE(starting_pos, helper.GetHeadPosition());
  helper.RestartGame();
}

TEST(basic_tests, moving_opposite_ways) {
  s21::TestHelper helper;
  helper.StartGame();
  helper.MakeAMove();
  helper.PerformAction(Up);
  helper.MakeAMove();
  helper.PerformAction(Down);
  helper.MakeAMove();
  EXPECT_NE(helper.GetDirection(), s21::Snake::kDown);
  helper.RestartGame();

  helper.StartGame();
  helper.MakeAMove();
  helper.PerformAction(Right);
  helper.MakeAMove();
  helper.PerformAction(Left);
  helper.MakeAMove();
  EXPECT_NE(helper.GetDirection(), s21::Snake::kLeft);
  helper.RestartGame();

  helper.StartGame();
  helper.MakeAMove();
  helper.PerformAction(Left);
  helper.MakeAMove();
  helper.PerformAction(Right);
  helper.MakeAMove();
  EXPECT_NE(helper.GetDirection(), s21::Snake::kRight);
  helper.RestartGame();

  helper.StartGame();
  helper.MakeAMove();
  helper.PerformAction(Right);
  helper.MakeAMove();
  helper.PerformAction(Down);
  helper.MakeAMove();
  helper.PerformAction(Up);
  helper.MakeAMove();
  EXPECT_NE(helper.GetDirection(), s21::Snake::kUp);
  helper.RestartGame();
}

TEST(basic_tests, max_score) {
  const int max_level = 10;
  s21::TestHelper helper;
  helper.StartGame();
  int starting_level = helper.GetLevel();
  helper.SetScore(100);
  helper.SpawnApple(9, 5);
  helper.MakeAMove();
  EXPECT_NE(starting_level, helper.GetLevel());
  EXPECT_EQ(max_level, helper.GetLevel());
  helper.RestartGame();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}