#include "view_qt.h"

///////////////////////  ВИЗУАЛИЗЦИЯ  ////////////////////////
// Конструктор по умолчанию
View_qt::View_qt(Controller *controller, QWidget *parent)
    : QWidget(parent), controller(controller) {
  timer = startTimer((11 - controller->GetModel()->info.GetSpeed()) * 100);
  setFocusPolicy(Qt::StrongFocus);
}

// Геттер для получения экземпляра контроллера
Controller *View_qt::GetController() { return controller; }

// Метод paintEvent для рисования
void View_qt::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  PrintRectangle(&painter);
  DrawSnakeFruit(&painter);
  DrawInfo(&painter);
  if (controller->GetModel()->fsm.GetState() == 4) DrawGameOver(&painter);
  if (controller->GetModel()->fsm.GetState() == 5) ExitState();
  if (signal == 0) DrawStart(&painter);
}

// Метод keyPressEvent для считывание клавиш
void View_qt::keyPressEvent(QKeyEvent *e) {
  int choice = e->key();
  switch (choice) {
    case Qt::Key_F5:
      signal = 0;
      break;
    case Qt::Key_Space:
      signal = 1;
      if (controller->GetModel()->info.GetPause() == true) {
        signal = 8;
      }
      break;
    case Qt::Key_Escape:
      signal = 2;
      break;
    case Qt::Key_Left:
      signal = 3;
      break;
    case Qt::Key_Right:
      signal = 4;
      break;
    case Qt::Key_Up:
      signal = 5;
      break;
    case Qt::Key_Down:
      signal = 6;
      break;
    case Qt::Key_0:
      signal = 7;
      break;
    default:
      signal = 8;
      break;
  }
}

// Метод timerEvent для таймера
void View_qt::timerEvent(QTimerEvent *e) {
  Q_UNUSED(e);

  if (signal == 8) {
    if (controller->GetModel()->info.GetPause() == true) {
      controller->GetModel()->fsm.Pause(*controller->GetModel());
    }
  }

  if (controller->GetModel()->info.GetPause() == false) {
    if (signal == 6 || signal == 5 || signal == 4 || signal == 3) {
      controller->Conversion(signal);
      controller->Conversion(8);
    } else {
      controller->Conversion(signal);
    }
    repaint();
  }
}

// Баннер для состояния START
void View_qt::DrawStart(QPainter *painter) {
  QFont font = painter->font();
  font.setBold(true);
  painter->setFont(font);
  painter->setPen(QColor(Qt::cyan));
  painter->drawText(4 * DOT_WIDTH, 4 * DOT_HEIGHT, HELP_0_MESSAGE);
  painter->drawText(4 * DOT_WIDTH, 8 * DOT_HEIGHT, HELP_1_MESSAGE);
  painter->setPen(QColor(Qt::yellow));
  painter->drawText(
      2 * DOT_WIDTH,
      (controller->GetModel()->field.GetHeight() / 2 + 1) * DOT_HEIGHT,
      INTRO_0_MESSAGE);
  painter->setPen(QColor(Qt::green));
  painter->drawText(
      2 * DOT_WIDTH,
      (controller->GetModel()->field.GetHeight() / 2 + 3) * DOT_HEIGHT,
      INTRO_1_MESSAGE);
}

// Баннер для состояния GAMEOVER
void View_qt::DrawGameOver(QPainter *painter) {
  QFont font = painter->font();
  font.setBold(true);
  painter->setFont(font);

  if (controller->GetModel()->snake.GetSizeBody() == 200) {
    painter->setPen(QColor(Qt::cyan));
    painter->drawText(2 * DOT_WIDTH, 9 * DOT_HEIGHT, LAST_1_MESSAGE);
  } else {
    painter->setPen(QColor(Qt::red));
    painter->drawText(2 * DOT_WIDTH, 9 * DOT_HEIGHT, LAST_0_MESSAGE);
  }

  painter->setPen(QColor(Qt::yellow));
  painter->drawText(
      2 * DOT_WIDTH,
      (controller->GetModel()->field.GetHeight() / 2 + 1) * DOT_HEIGHT,
      INTRO_2_MESSAGE);
  painter->setPen(QColor(Qt::green));
  painter->drawText(
      2 * DOT_WIDTH,
      (controller->GetModel()->field.GetHeight() / 2 + 3) * DOT_HEIGHT,
      INTRO_1_MESSAGE);
}

// Состояние EXIT
void View_qt::ExitState() { close(); }

// Отрисовка прямоугольных рамок
void View_qt::PrintRectangle(QPainter *painter) {
  QFont font = painter->font();
  font.setBold(true);
  painter->setFont(font);
  painter->setPen(QColor(Qt::white));
  painter->drawRect(1 * DOT_WIDTH, 1 * DOT_HEIGHT,
                    controller->GetModel()->field.GetWidth() * DOT_WIDTH,
                    controller->GetModel()->field.GetHeight() * DOT_HEIGHT);
  painter->drawRect((controller->GetModel()->field.GetWidth() + 1) * DOT_WIDTH,
                    1 * DOT_HEIGHT,
                    (controller->GetModel()->field.GetWidth() - 3) * DOT_WIDTH,
                    controller->GetModel()->field.GetHeight() * DOT_HEIGHT);
  painter->drawRect(
      (controller->GetModel()->field.GetWidth() + 2) * DOT_WIDTH,
      1 * DOT_HEIGHT,
      (controller->GetModel()->field.GetWidth() - 5) * DOT_WIDTH,
      (controller->GetModel()->field.GetHeight() - 17) * DOT_HEIGHT);
  painter->drawRect(
      (controller->GetModel()->field.GetWidth() + 2) * DOT_WIDTH,
      5 * DOT_HEIGHT,
      (controller->GetModel()->field.GetWidth() - 5) * DOT_WIDTH,
      (controller->GetModel()->field.GetHeight() - 17) * DOT_HEIGHT);
  painter->drawRect(
      (controller->GetModel()->field.GetWidth() + 2) * DOT_WIDTH,
      9 * DOT_HEIGHT,
      (controller->GetModel()->field.GetWidth() - 5) * DOT_WIDTH,
      (controller->GetModel()->field.GetHeight() - 17) * DOT_HEIGHT);
  painter->drawRect(
      (controller->GetModel()->field.GetWidth() + 2) * DOT_WIDTH,
      13 * DOT_HEIGHT,
      (controller->GetModel()->field.GetWidth() - 5) * DOT_WIDTH,
      (controller->GetModel()->field.GetHeight() - 17) * DOT_HEIGHT);
  painter->drawRect(
      (controller->GetModel()->field.GetWidth() + 2) * DOT_WIDTH,
      17 * DOT_HEIGHT,
      (controller->GetModel()->field.GetWidth() - 5) * DOT_WIDTH,
      (controller->GetModel()->field.GetHeight() - 17) * DOT_HEIGHT);
}

// Отображение информации о игре
void View_qt::DrawInfo(QPainter *painter) {
  QFont font = painter->font();
  font.setBold(true);
  painter->setFont(font);
  painter->setPen(QColor(Qt::cyan));
  painter->drawText((controller->GetModel()->field.GetWidth() + 3) * DOT_WIDTH,
                    2 * DOT_HEIGHT, "H_SCORE ");
  painter->drawText((controller->GetModel()->field.GetWidth() + 3) * DOT_WIDTH,
                    6 * DOT_HEIGHT, "C_SCORE ");
  painter->drawText((controller->GetModel()->field.GetWidth() + 3) * DOT_WIDTH,
                    10 * DOT_HEIGHT, "LEVEL ");
  painter->drawText((controller->GetModel()->field.GetWidth() + 3) * DOT_WIDTH,
                    14 * DOT_HEIGHT, "SPEED ");
  painter->drawText((controller->GetModel()->field.GetWidth() + 3) * DOT_WIDTH,
                    18 * DOT_HEIGHT, "PAUSE ");

  painter->setPen(QColor(Qt::magenta));
  painter->drawText(
      (controller->GetModel()->field.GetWidth() + 4) * DOT_WIDTH,
      3 * DOT_HEIGHT,
      QString::number(controller->GetModel()->info.GetHighScore()));
  painter->drawText((controller->GetModel()->field.GetWidth() + 4) * DOT_WIDTH,
                    7 * DOT_HEIGHT,
                    QString::number(controller->GetModel()->info.GetScore()));
  painter->drawText((controller->GetModel()->field.GetWidth() + 4) * DOT_WIDTH,
                    11 * DOT_HEIGHT,
                    QString::number(controller->GetModel()->info.GetLevel()));
  painter->drawText((controller->GetModel()->field.GetWidth() + 4) * DOT_WIDTH,
                    15 * DOT_HEIGHT,
                    QString::number(controller->GetModel()->info.GetSpeed()));
  painter->drawText((controller->GetModel()->field.GetWidth() + 4) * DOT_WIDTH,
                    19 * DOT_HEIGHT,
                    (controller->GetModel()->info.GetPause() == true)
                        ? QString("stop")
                        : QString("active"));
}

// Отрисовка яблока и змейки на поле
void View_qt::DrawSnakeFruit(QPainter *painter) {
  for (int i = 1; i <= controller->GetModel()->field.GetHeight(); i++) {
    for (int j = 1; j <= controller->GetModel()->field.GetWidth(); j++) {
      if (i == controller->GetModel()->snake.GetHeadY() &&
          j == controller->GetModel()->snake.GetHeadX()) {
        painter->setPen(QColor(Qt::black));
        painter->setBrush(Qt::yellow);
        painter->drawEllipse(j * DOT_WIDTH, i * DOT_HEIGHT, DOT_WIDTH,
                             DOT_HEIGHT);
      } else if (i == controller->GetModel()->fruit.GetFruitY() &&
                 j == controller->GetModel()->fruit.GetFruitX()) {
        painter->setPen(QColor(Qt::black));
        painter->setBrush(Qt::red);
        painter->drawEllipse(j * DOT_WIDTH, i * DOT_HEIGHT, DOT_WIDTH,
                             DOT_HEIGHT);
      } else {
        for (int k = 0; k < controller->GetModel()->snake.GetSizeBody(); k++) {
          if (controller->GetModel()->snake.GetTailY(k) == i &&
              controller->GetModel()->snake.GetTailX(k) == j) {
            painter->setPen(QColor(Qt::black));
            painter->setBrush(Qt::green);
            painter->drawEllipse(j * DOT_WIDTH, i * DOT_HEIGHT, DOT_WIDTH,
                                 DOT_HEIGHT);
            break;
          }
        }
      }
    }
  }
}
