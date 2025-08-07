#ifndef STATS_H
#define STATS_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class Stats : public QWidget {
  Q_OBJECT
 public:
  explicit Stats(QWidget* parent = nullptr);

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  QLabel* score_label_;
  QLabel* high_score_label_;
  QLabel* level_label_;
  QLabel* speed_label_;
};

#endif  // STATS_H
