#ifndef SNAKE_MODEL_H_
#define SNAKE_MODEL_H_

#include <cmath>
#include <ctime>
#include <fstream>
#include <vector>

/**
 * @file snake_model.h
 *
 * @brief Whole backend snake model.
 *
 * @details This file contains declarations of classes SnakeLogic, Apple, Snake
 * etc.
 */

#include "lib_specification.h"

namespace s21 {

/**
 * @brief struct representing a point on board
 */
typedef struct Point {
  int x; /**< an integer value for horizontal coordinate */
  int y; /**< an integer value for vertical coordinate */

  /** Point constructor that defaults to (0, 0)*/
  explicit Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

  /** comparison operator overload for easier comparison between Points */
  bool operator==(const Point &other) const {
    return (x == other.x && y == other.y);
  }
} Point;

/**
 * @class Entity
 *
 * @brief Base class that can represent all possible entities in game
 */
class Entity {
 protected:
  /** vector of points */
  std::vector<Point> position_;

  /** basic constructor */
  Entity() : position_{} {};
  /** parametrized constructor */
  Entity(int x, int y) : position_{Point(x, y)} {}
  /** defauld destructor that frees allocated vector */
  ~Entity() = default;
};

/**
 * @class Snake
 *
 * @brief class that represents snake as a vector of points, can perform moves
 * and check collision
 */
class Snake : public Entity {
  friend class SnakeLogic;
  friend class TestHelper;

 public:
  /**
   * @enum Move directions of snake
   */
  typedef enum { kUp = 0, kRight, kDown, kLeft } SnakeDirection;

 private:
  /** basic Snake constructor */
  Snake() : Entity(0, 0) { SnakeReset(); }
  /**
   * @brief resets snake to its starting position and length
   *
   * @details starting x position is 5, y position is 10 and length is 3,
   * approximately in the middle of the field and pointing upwards
   */
  void SnakeReset();

  /**
   * @brief moves snake one block in the direction ```dir```
   *
   * @param dir direction of snake move
   *
   * @param apple point on field where apple is located
   *
   * @returns 0 - no collision , 1 - collision
   * */
  bool MoveForward(int dir, Point apple);

  /**
   * @brief moves snake to the right, if new head position contains apple, adds
   * 1 to snake's length
   *
   * @param apple position of apple on the field
   *
   * @returns 0 - no collision , 1 - collision
   */
  bool MoveRight(Point apple);

  /**
   * @brief moves snake to the left, if new head position contains apple, adds
   * 1 to snake's length
   *
   * @param apple position of apple on the field
   *
   * @returns 0 - no collision , 1 - collision
   */
  bool MoveLeft(Point apple);

  /**
   * @brief moves snake upwards, if new head position contains apple, adds
   * 1 to snake's length
   *
   * @param apple position of apple on the field
   *
   * @returns 0 - no collision , 1 - collision
   */
  bool MoveUp(Point apple);

  /**
   * @brief moves snake downwards, if new head position contains apple, adds
   * 1 to snake's length
   *
   * @param apple position of apple on the field
   *
   * @returns 0 - no collision , 1 - collision
   */
  bool MoveDown(Point apple);

  /**
   * @brief calculates default snake movement direction
   *
   * @returns integer representing SnakeDirection from 0 to 3
   */
  int GetDirection();

  /**
   * @brief Checks if snake collides with borders or tail
   *
   * @returns 0 - no collision , 1 - collision
   */
  bool CheckCollision(Point head, int dir);
};

/** @class Apple */
class Apple : public Entity {
  friend class SnakeLogic;
  friend class TestHelper;

 private:
  /** basic constructor */
  Apple() : Entity() {}

  /**
   * @brief randomly generates new apple position on the empty field
   *
   * @param empty_field vector of empty points on field, needs to be calculated
   * beforehand
   */
  void Spawn(std::vector<Point> empty_field);
};

/**
 * @class Snake Logic
 *
 * @brief main class that holds all game information and calculates logic
 */
class SnakeLogic {
  friend class TestHelper;
  using signals = void (SnakeLogic::*)();

  const int kMaxLength = 200;
  const int kHeight = 20, kWidth = 10;
  const int kApplePixel = 1, kSnakePixel = 2;
  const int kPointsPerLevel = 5, kMaxLevel = 10;

 public:
  /** @enum Snake states */
  typedef enum { kStart = 0, kSpawn, kMoving, kGameOver, kExit } SnakeState;
  /** @enum Different types of pause */
  typedef enum {
    kNoPause = 0,  /**< Game is not paused */
    kStartPause,   /**< Game is paused on the starting screen */
    kDefaultPause, /**< Game is paused */
    kGameWonPause, /**< Game is paused due to player winning*/
    kGameOverPause /**< Game is paused due to player losing */
  } PauseType;

 private:
  Snake snake_;           /**< Snake object */
  Apple apple_;           /**< Apple object */
  GameInfo_t *game_info_; /**< Struct for easier storing and transporting of
                             game information for interface */
  SnakeState state_;      /**< Game state for FSM */
  /** Latest registered direction of snake movement */
  Snake::SnakeDirection direction_;
  int last_tick_; /**< Time in milliseconds of the latest snake movement */

 public:
  /**
   * @brief creates a static instance of class SnakeLogic
   *
   * @details classic singleton pattern
   *
   * @returns reference of static SnakeLogic
   */
  static SnakeLogic &GetInstance();

  /**
   * @brief updates snake and apple position
   *
   * @returns GameInfo_t ready for use in the interface
   */
  GameInfo_t UpdateCurrentState();

  /**
   * @brief processes user input
   *
   * @param action button that the user has pressed
   *
   * @param hold unused parameter
   */
  void UserInput(UserAction_t action, bool hold);

 private:
  /** basic constructor */
  SnakeLogic() : snake_(), apple_(), game_info_(new GameInfo_t{}) {
    InitializeGame();
  };
  /** basic destructor */
  ~SnakeLogic() { FreeResources(); }

  /**
   * @brief fills game info struct with starting parameters
   *
   * @details also allocates memory for ```int **field``` and defaults initial
   * snake direction to Up
   */
  void InitializeGame();
  /**
   * @brief frees memory allocated for ```int** field``` from game info struct
   */
  void FreeResources();

  /**
   * @brief allocates memory for matrix ```rows``` * ```cols```
   */
  int **InitializeMatrix(int rows, int cols);

  /**
   * @brief calculates points on field that are empty
   *
   * @returns vector of empty points
   */
  std::vector<Point> GetEmptyField();

  /** @brief updates snake and apple position, updates ```speed``` field  */
  void UpdateGameInfo();

  /** @brief changes state to ```kSpawn``` and removes pause. */
  void StartGame();
  /** @brief changes state to ```kExit```. */
  void Exitstate();
  /** @brief changes state to ```kMoving``` and spawns(or respawns) apple. */
  void Spawn();
  /** @brief pauses or unpauses. */
  void PauseGame();
  /** @brief changes move direction to left if it is possible. */
  void MoveLeft();
  /** @brief changes move direction to right if it is possible. */
  void MoveRight();
  /** @brief changes move direction to up if it is possible. */
  void MoveUp();
  /** @brief changes move direction to down if it is possible. */
  void MoveDown();
  // void SpeedUp();
  /** @brief shifts snake one block forward */
  void Shift();
  /** @brief resets snake and game info to start state */
  void Restart();
  /** @brief saves high score and changes pause to win or lose */
  void GameOver();

  /**
   * @brief checks if snake head is located in the same point as apple
   *
   * @returns 0 - if not the same point, 1 - same point
   */
  bool CheckForApple();

  /**
   * @brief calculates interval between snake moves based on current game level
   *
   * @returns ```integer``` time interval in milliseconds
   */
  int CalculateTickInterval();

  /**
   * @brief adds ```+1``` to score and updates level if needed
   *
   * @details level increases with each 5 points in score, but can not exceed 10
   */
  void AddScore();

  /** @brief gets high score from save file */
  int GetHighScore();
  /** @brief saves high score to save file */
  void SaveHighScore();

  /**
   *  @brief calculates current time in milliseconds
   *
   * @returns ```integer``` time in milliseconds
   */
  int GetCurrentTimeInMs();
};
}  // namespace s21

#endif  // SNAKE_MODEL_H_