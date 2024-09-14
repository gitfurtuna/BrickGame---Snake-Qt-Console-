#ifndef VIEW_QT_H
#define VIEW_QT_H

#include <QKeyEvent>
#include <QPainter>
#include <QTimerEvent>
#include <QWidget>

#include "controller.h"

#define INTRO_0_MESSAGE "Press ENTER to START"
#define INTRO_1_MESSAGE "Press ESCAPE to EXIT"
#define INTRO_2_MESSAGE "Press  F5  to RESTART"
#define HELP_0_MESSAGE "hungry snake"
#define HELP_1_MESSAGE "tasty fruit"
#define LAST_0_MESSAGE "YOU LOSE THE GAME"
#define LAST_1_MESSAGE "YOU WON THE GAME"

class View_qt : public QWidget {
  Q_OBJECT

 public:
  View_qt(Controller *controller,
          QWidget *parent = nullptr);  // Конструктор по умолчанию
  Controller *GetController();  // Геттер для получения экземпляра контроллера
  void PrintRectangle(QPainter *);  // Отрисовка прямоугольных рамок
  void DrawInfo(QPainter *);  // Отображение информации о игре
  void DrawSnakeFruit(QPainter *);  // Отрисовка яблока и змейки на поле
  void DrawStart(QPainter *);  // Баннер для состояния START
  void DrawGameOver(QPainter *);  // Баннер для состояния GAMEOVER
  void ExitState();               // Состояние EXIT

 protected:
  void keyPressEvent(
      QKeyEvent *) override;  // Метод keyPressEvent для считывание клавиш
  void paintEvent(QPaintEvent *) override;  // Метод paintEvent для рисования
  void timerEvent(QTimerEvent *) override;  // Метод timerEvent для таймера

 private:
  Controller *controller;
  static const int DOT_WIDTH = 20;   // размер точек
  static const int DOT_HEIGHT = 20;  // размер точек
  int signal;
  int timer;
};

#endif  // VIEW_QT_H
