#include "gamefield.h"

#include "lib_specification.h"

GameField::GameField(QWidget* parent) : QWidget{parent} {
  QVBoxLayout* layout = new QVBoxLayout(this);

  message_ = new QLabel(this);
  message_->setStyleSheet("font-size: 18px;");
  message_->setAlignment(Qt::AlignCenter);
  message_->raise();

  layout->addStretch();
  layout->addWidget(message_, 0, Qt::AlignHCenter);
  layout->addStretch();

  StartMessage();

  setFocusPolicy(Qt::StrongFocus);
  setFocus();
}

void GameField::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  UserAction_t key = (updateCurrentState().pause ? Action : Start);
  userInput(key, false);
  PrintGame(painter);
  switch (updateCurrentState().pause) {
    case 1:
      StartMessage();
      break;
    case 2:
      PauseMessage();
      break;
    case 3:
      GameWonMessage();
      break;
    case 4:
      GameOverMessage();
      break;
    default:
      message_->hide();
      break;
  }
}

void GameField::StartMessage() {
  message_->setText("To start press: Enter\nTo quit press: Escape");
  message_->show();
}

void GameField::PauseMessage() {
  message_->setText("Game is paused\nTo continue press: P");
  message_->show();
}

void GameField::GameWonMessage() {
  message_->setText("You won!!\nCongratulations!\nTo restart press: Enter");
  message_->show();
}

void GameField::GameOverMessage() {
  message_->setText("Game over!\nTo restart press: Enter");
  message_->show();
}

void GameField::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Left:
      userInput(Left, false);
      break;
    case Qt::Key_Right:
      userInput(Right, false);
      break;
    case Qt::Key_Up:
      userInput(Up, false);
      break;
    case Qt::Key_Down:
      userInput(Down, false);
      break;
    case Qt::Key_P:
      userInput(Pause, false);
      break;
    case Qt::Key_Return:
      userInput(Start, false);
      break;
    case Qt::Key_Space:
      userInput(Action, false);
      break;
    case Qt::Key_Escape:
      userInput(Terminate, false);
      QApplication::quit();
      break;
    default:
      break;
  }
  this->window()->update();
}

void GameField::PrintGame(QPainter& painter) {
  GameInfo_t game = updateCurrentState();
  const int kCellSize = 25;
  const int kFieldHeight = 20;
  const int kFieldWidth = 10;
  for (int i = 0; i < kFieldHeight; ++i) {
    for (int j = 0; j < kFieldWidth; ++j) {
      if (game.pause != 1 && game.field) {
        switch (game.field[i][j]) {
          case 1:
            painter.fillRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize,
                             Qt::lightGray);
            break;
          case 2:
            painter.fillRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize,
                             Qt::white);
            break;
          case 3:
            painter.fillRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize,
                             Qt::darkGray);
            break;
          default:
            painter.fillRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize,
                             0x323232);
            break;
        }
      }
      painter.drawRect(j * kCellSize, i * kCellSize, kCellSize, kCellSize);
    }
  }
}
