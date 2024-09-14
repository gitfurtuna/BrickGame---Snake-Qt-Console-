#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

class Controller {
 private:
  Model *model;

 public:
  Controller(Model *m);  // Конструктор по умолчанию
  Model *GetModel();  // Геттер для получения экземпляра модели
  void Conversion(int signal);  // Преобразование логики в визуализацию
};

#endif
