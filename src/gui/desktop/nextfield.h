#ifndef NEXTFIELD_H
#define NEXTFIELD_H

#include <QLabel>
#include <QPainter>
#include <QWidget>

class NextField : public QWidget {
  Q_OBJECT
 public:
  explicit NextField(QWidget* parent = nullptr);

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  QLabel* text_;
};

#endif  // NEXTFIELD_H