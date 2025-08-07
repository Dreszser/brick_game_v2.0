#include "stats.h"

#include "lib_specification.h"

Stats::Stats(QWidget* parent) : QWidget{parent} {
  QVBoxLayout* layout = new QVBoxLayout(this);

  score_label_ = new QLabel(this);
  high_score_label_ = new QLabel(this);
  level_label_ = new QLabel(this);
  speed_label_ = new QLabel(this);

  score_label_->setStyleSheet("font-size: 18px;");
  high_score_label_->setStyleSheet("font-size: 18px;");
  level_label_->setStyleSheet("font-size: 18px;");
  speed_label_->setStyleSheet("font-size: 18px;");

  score_label_->setAlignment(Qt::AlignLeft);
  high_score_label_->setAlignment(Qt::AlignLeft);
  level_label_->setAlignment(Qt::AlignLeft);
  speed_label_->setAlignment(Qt::AlignLeft);

  layout->addWidget(score_label_);
  layout->addWidget(high_score_label_);
  layout->addWidget(level_label_);
  layout->addWidget(speed_label_);
}

void Stats::paintEvent(QPaintEvent* event) {
  GameInfo_t game = updateCurrentState();
  score_label_->setText(QString("Score: %1").arg(game.score));
  high_score_label_->setText(QString("High score: %1").arg(game.high_score));
  level_label_->setText(QString("Level: %1").arg(game.level));
  speed_label_->setText(QString("Speed: %1").arg(game.speed));
}
