#include "mainwindow.h"

MainWindow::MainWindow() {
  const int kWindowWidth = 500, kWindowHeight = 530;
  const int kWidgetWidth = 250, kGameFieldHeight = 500;
  const int kNextHeight = 200, kStatsHeight = 300;
  const int kInfoWidth = 200;
  const int kRefreshTimeMS = 20;

  QWidget* central = new QWidget(this);
  QGridLayout* grid = new QGridLayout(central);

  game_field_ = new GameField(central);
  next_field_ = new NextField;
  stats_ = new Stats(central);

  grid->addWidget(game_field_, 0, 0, 5, 1, Qt::AlignTop);
  grid->addWidget(next_field_, 0, 1, 2, 1, Qt::AlignTop);
  grid->addWidget(stats_, 2, 1, 3, 1, Qt::AlignTop);

  game_field_->setFixedSize(kWidgetWidth, kGameFieldHeight);
  next_field_->setFixedSize(kInfoWidth, kNextHeight);
  stats_->setFixedSize(kInfoWidth, kStatsHeight);

  this->setFixedSize(kWindowWidth, kWindowHeight);
  this->setStyleSheet("background-color: #323232;");

  central->setLayout(grid);
  setCentralWidget(central);

  QTimer* timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTick);
  timer->start(kRefreshTimeMS);

  resize(kWindowWidth, kWindowHeight);
}

void MainWindow::onTimerTick() {
  game_field_->update();
  next_field_->update();
  stats_->update();
}
