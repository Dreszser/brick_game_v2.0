#include "nextfield.h"

#include "lib_specification.h"

NextField::NextField(QWidget* parent) : QWidget{parent} {
  text_ = new QLabel("next:", this);
  text_->setStyleSheet("font-size: 18px;");
  text_->raise();
}

void NextField::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  GameInfo_t game = updateCurrentState();
  const int kCellSize = 25;
  const int kNextSize = 5;
  const int kStartX = 30, kStartY = 50;
  if (game.next) {
    text_->show();
  } else {
    text_->hide();
  }
  for (int i = 0; i < kNextSize && game.next; ++i) {
    for (int j = 0; j < kNextSize; ++j) {
      if (game.next[i][j] && game.pause != 1) {
        painter.fillRect(kStartX + j * kCellSize, kStartY + i * kCellSize,
                         kCellSize, kCellSize, Qt::white);
      } else {
        painter.fillRect(kStartX + j * kCellSize, kStartY + i * kCellSize,
                         kCellSize, kCellSize, 0x323232);
      }
    }
  }
}
