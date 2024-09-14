#include "view_ncurses.h"

///////////////////////  ВИЗУАЛИЗЦИЯ  ////////////////////////
// Конструктор по умолчанию
View::View(Controller *c) : controller(c) {}

// Геттер для получения экземпляра контроллера
Controller *View::GetController() { return controller; }

// Отрисовка прямоугольных рамок
void View::PrintRectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);
  int i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);
  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }
  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

// Печать поверх экрана рамок
void View::PrintOverlay() {
  PrintRectangle(0, controller->GetModel()->field.GetHeight() + 1, 0,
                 controller->GetModel()->field.GetWidth() + 11);
  PrintRectangle(0, controller->GetModel()->field.GetHeight() + 1,
                 controller->GetModel()->field.GetWidth() + 12,
                 controller->GetModel()->field.GetWidth() + 23);
  PrintRectangle(1, 4, controller->GetModel()->field.GetWidth() + 13,
                 controller->GetModel()->field.GetWidth() + 22);
  PrintRectangle(5, 8, controller->GetModel()->field.GetWidth() + 13,
                 controller->GetModel()->field.GetWidth() + 22);
  PrintRectangle(9, 12, controller->GetModel()->field.GetWidth() + 13,
                 controller->GetModel()->field.GetWidth() + 22);
  PrintRectangle(13, 16, controller->GetModel()->field.GetWidth() + 13,
                 controller->GetModel()->field.GetWidth() + 22);
  PrintRectangle(17, 20, controller->GetModel()->field.GetWidth() + 13,
                 controller->GetModel()->field.GetWidth() + 22);
}

// Раскраска
void View::Color() {
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_GREEN, COLOR_BLACK);
  init_pair(6, COLOR_BLUE, COLOR_BLACK);
  init_pair(7, COLOR_RED, COLOR_BLACK);
}

// Отображение информации о игре
void View::DrawInfo() {
  attron(A_BOLD);
  attron(COLOR_PAIR(4));
  MVPRINTW(2, controller->GetModel()->field.GetWidth() + 14, "H_SCORE ");
  MVPRINTW(6, controller->GetModel()->field.GetWidth() + 14, "С_SCORE ");
  MVPRINTW(10, controller->GetModel()->field.GetWidth() + 14, "LEVEL ");
  MVPRINTW(14, controller->GetModel()->field.GetWidth() + 14, "SPEED ");
  MVPRINTW(18, controller->GetModel()->field.GetWidth() + 14, "PAUSE ");
  attroff(COLOR_PAIR(4));
  attroff(A_BOLD);

  attron(A_BOLD);
  attron(COLOR_PAIR(2));
  MVPRINTW(3, controller->GetModel()->field.GetWidth() + 16, "%d",
           controller->GetModel()->info.GetHighScore());
  MVPRINTW(7, controller->GetModel()->field.GetWidth() + 16, "%d",
           controller->GetModel()->info.GetScore());
  MVPRINTW(11, controller->GetModel()->field.GetWidth() + 16, "%d",
           controller->GetModel()->info.GetLevel());
  MVPRINTW(15, controller->GetModel()->field.GetWidth() + 16, "%d",
           controller->GetModel()->info.GetSpeed());
  MVPRINTW(19, controller->GetModel()->field.GetWidth() + 16, "%s",
           controller->GetModel()->info.GetPause() ? "stop" : "active");
  attroff(COLOR_PAIR(2));
  attroff(A_BOLD);
}

// Отрисовка яблока и змейки на поле
void View::DrawSnakeFruit() {
  for (int i = 1; i <= controller->GetModel()->field.GetHeight(); i++) {
    for (int j = 1; j <= controller->GetModel()->field.GetWidth(); j++) {
      int x = j * 2 - 1;

      if (i == controller->GetModel()->snake.GetHeadY() &&
          j == controller->GetModel()->snake.GetHeadX()) {
        attron(A_BOLD);
        attron(COLOR_PAIR(3));
        MVPRINTW(i, x, "%s", "*@");
        attroff(COLOR_PAIR(3));
        attroff(A_BOLD);
      } else if (i == controller->GetModel()->fruit.GetFruitY() &&
                 j == controller->GetModel()->fruit.GetFruitX()) {
        attron(A_BOLD);
        attron(COLOR_PAIR(7));
        MVPRINTW(i, x, "%s", "FR");
        attroff(COLOR_PAIR(7));
        attroff(A_BOLD);
      } else {
        bool print = false;
        for (int k = 0; k < controller->GetModel()->snake.GetSizeBody(); k++) {
          if (controller->GetModel()->snake.GetTailY(k) == i &&
              controller->GetModel()->snake.GetTailX(k) == j) {
            attron(A_BOLD);
            attron(COLOR_PAIR(5));
            MVPRINTW(i, x, "%s", "*@");
            attroff(COLOR_PAIR(5));
            attroff(A_BOLD);
            print = true;
            break;
          }
        }
        if (!print) {
          MVPRINTW(i, x, "%s", "  ");
        }
      }
    }
  }
}

// Баннер для состояния START
void View::DrawStart() {
  attron(A_BOLD);
  attron(COLOR_PAIR(4));
  MVPRINTW(3, 5, "%s", HELP_0_MESSAGE);
  MVPRINTW(7, 5, "%s", HELP_1_MESSAGE);
  attroff(COLOR_PAIR(4));
  attroff(A_BOLD);
  attron(A_BOLD);
  attron(COLOR_PAIR(3));
  MVPRINTW(controller->GetModel()->field.GetHeight() / 2 + 1, 1, "%s",
           INTRO_0_MESSAGE);
  attroff(COLOR_PAIR(3));
  attroff(A_BOLD);
  attron(A_BOLD);
  attron(COLOR_PAIR(6));
  MVPRINTW(controller->GetModel()->field.GetHeight() / 2 + 3, 1, "%s",
           INTRO_1_MESSAGE);
  attroff(COLOR_PAIR(6));
  attroff(A_BOLD);
}

// Баннер для состояния GAMEOVER
void View::DrawGameOver() {
  if (controller->GetModel()->snake.GetSizeBody() == 200) {
    attron(A_BOLD);
    attron(COLOR_PAIR(6));
    MVPRINTW(7, 3, "%s", LAST_1_MESSAGE);
    attroff(COLOR_PAIR(6));
    attroff(A_BOLD);
  } else {
    attron(A_BOLD);
    attron(COLOR_PAIR(7));
    MVPRINTW(7, 3, "%s", LAST_0_MESSAGE);
    attroff(COLOR_PAIR(7));
    attroff(A_BOLD);
  }
  attron(A_BOLD);
  attron(COLOR_PAIR(3));
  MVPRINTW(9, 1, "%s", INTRO_0_MESSAGE);
  attroff(COLOR_PAIR(3));
  attron(COLOR_PAIR(6));
  MVPRINTW(11, 1, "%s", INTRO_1_MESSAGE);
  attroff(COLOR_PAIR(6));
  attroff(A_BOLD);
}

// Визуализация
void View::Draw() {
  clear();
  Color();
  PrintOverlay();
  DrawSnakeFruit();
  DrawInfo();
  if (controller->GetModel()->fsm.GetState() == 0) DrawStart();
  if (controller->GetModel()->fsm.GetState() == 4) DrawGameOver();
}

// Cчитывание клавиш
void View::Input() {
  while (controller->GetModel()->fsm.GetState() != 5) {
    Draw();
    timeout(controller->GetModel()->info.GetTimer());
    int signal;
    int choice = getch();
    switch (choice) {
      case ENTER_KEY:
        signal = 0;
        break;
      case SPACE_KEY:
        signal = 1;
        break;
      case ESCAPE_KEY:
        signal = 2;
        break;
      case KEY_LEFT:
        signal = 3;
        break;
      case KEY_RIGHT:
        signal = 4;
        break;
      case KEY_UP:
        signal = 5;
        break;
      case KEY_DOWN:
        signal = 6;
        break;
      case NULL_KEY:
        signal = 7;
        break;
      default:
        signal = 8;
        break;
    }

    controller->Conversion(signal);
  }
}
