#include "view_ncurses.h"

int main() {
  initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  noecho();
  start_color();
  Model model;
  Controller controller(&model);
  View view(&controller);
  view.Input();
  endwin();
  return 0;
}
