#include "controller.h"

///////////////////////  КОНТРОЛЛЕР  ////////////////////////
// Конструктор по умолчанию
Controller::Controller(Model *m) : model(m) {}

// Геттер для получения экземпляра модели
Model *Controller::GetModel() { return model; }

// Преобразование логики в визуализацию
void Controller::Conversion(int signal) {
  model->fsm.doFSM_table(signal, *model);
}
