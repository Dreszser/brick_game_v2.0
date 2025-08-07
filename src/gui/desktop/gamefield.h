#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

class GameField : public QWidget {
  Q_OBJECT
 public:
  explicit GameField(QWidget* parent = nullptr);

 private:
  QLabel* message_;
  void StartMessage();
  void PauseMessage();
  void GameOverMessage();
  void GameWonMessage();
  void PrintGame(QPainter&);

 protected:
  void paintEvent(QPaintEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
};

#endif  // GAMEFIELD_H
