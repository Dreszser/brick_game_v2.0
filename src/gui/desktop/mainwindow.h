#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>

#include "gamefield.h"
#include "nextfield.h"
#include "stats.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();

 protected:
  void onTimerTick();

 private:
  QWidget *game_field_;
  QWidget *next_field_;
  QWidget *stats_;
};
#endif  // MAINWINDOW_H
