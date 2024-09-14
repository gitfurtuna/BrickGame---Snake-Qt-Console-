#include <QApplication>

#include "view_qt.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Model model;
  Controller controller(&model);
  View_qt w(&controller);
  w.show();
  return a.exec();
}
