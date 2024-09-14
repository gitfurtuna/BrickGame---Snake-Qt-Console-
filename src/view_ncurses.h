#ifndef VIEW_NCURSES_H
#define VIEW_NCURSES_H

#define ENTER_KEY 10
#define ESCAPE_KEY 27
#define SPACE_KEY 32
#define NULL_KEY 48
#define MVADDCH(y, x, c) mvaddch(0 + (y), 0 + (x), c)
#define MVPRINTW(y, x, ...) mvprintw(0 + (y), 0 + (x), __VA_ARGS__)
#define INTRO_0_MESSAGE "Press ENTER to START"
#define INTRO_1_MESSAGE "Press ESCAPE to EXIT"
#define HELP_0_MESSAGE "hungry snake"
#define HELP_1_MESSAGE "tasty fruit"
#define LAST_0_MESSAGE "YOU LOSE THE GAME"
#define LAST_1_MESSAGE "YOU WON THE GAME"

#include <ncurses.h>

#include "controller.h"

class View {
 private:
  Controller *controller;

 public:
  View(Controller *c);  // Конструктор по умолчанию
  Controller *GetController();  // Геттер для получения экземпляра контроллера
  void Color();                 // Раскраска
  void Draw();                  // Визуализация
  void Input();                 // Cчитывание клавиш
  void PrintRectangle(int top_y, int bottom_y, int left_x,
                      int right_x);  // Отрисовка прямоугольных рамок
  void PrintOverlay();  // Печать поверх экрана рамок
  void DrawInfo();  // Отображение информации о игре
  void DrawSnakeFruit();  // Отрисовка яблока и змейки на поле
  void DrawStart();     // Баннер для состояния START
  void DrawGameOver();  // Баннер для состояния GAMEOVER
};

#endif  // VIEW_NCURSES_H
