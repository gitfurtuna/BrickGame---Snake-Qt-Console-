
#include "model.h"
///////////////////////  ПОЛЕ  ////////////////////////
// Конструктор по умолчанию - поле с шириной = 10 и высотой = 20
Model::Field::Field() {
  width = 10;
  height = 20;
}

// Геттеры для получения неизменныx значений ширины и высоты
int Model::Field::GetWidth() const { return width; }

int Model::Field::GetHeight() const { return height; }

///////////////////////  ФРУКТ  ////////////////////////
// Конструктор по умолчанию, установим начальные координаты фрукта на середине
// поля
Model::Fruit::Fruit() { fruitX = 5, fruitY = 9; }

// Геттеры для получения текущих координат фрукта
int Model::Fruit::GetFruitX() { return fruitX; }

int Model::Fruit::GetFruitY() { return fruitY; }

// Зарождение нового фрукта, если предыдущее съела змейка
void Model::Fruit::RespawnFruit(Field &field, Snake &snake) {
  bool isOnSnake;
  do {
    isOnSnake = false;
    srand(time(NULL));
    fruitX = rand() % field.width;
    fruitY = rand() % field.height;

    for (int i = 0; i < snake.size_body; i++) {
      if (fruitX == snake.tailX[i] && fruitY == snake.tailY[i]) {
        isOnSnake = true;
        break;
      }
    }
  } while (isOnSnake);
}

///////////////////////  ЗМЕЙКА  ////////////////////////
// Конструктор змейки по умолчанию
Model::Snake::Snake() {
  size_body = 4;
  headX = 7;
  headY = 5;
  dir = RIGHT;
  StartPosition();
}

// Геттеры для получения текущих координат и размера змейки
int Model::Snake::GetHeadX() { return headX; }

int Model::Snake::GetHeadY() { return headY; }

int Model::Snake::GetTailX(int index) { return tailX[index]; }

int Model::Snake::GetTailY(int index) { return tailY[index]; }

int Model::Snake::GetSizeBody() { return size_body; }

int Model::Snake::GetDirection() { return dir; }

// Начальное положение змейки
void Model::Snake::StartPosition() {
  for (int i = 0; i < size_body; i++) {
    if (dir == DOWN) {
      tailX[i] = headX;
      tailY[i] = headY - i;
    }
    if (dir == UP) {
      tailX[i] = headX;
      tailY[i] = headY + i;
    }
    if (dir == RIGHT) {
      tailX[i] = headX - i;
      tailY[i] = headY;
    }
    if (dir == LEFT) {
      tailX[i] = headX + i;
      tailY[i] = headY;
    }
  }
}

// Изменение направления движения змейки
void Model::Snake::SnakeShifting() {
  // if (info.pause == false){
  switch (dir) {
    case LEFT:
      headX--;
      break;
    case RIGHT:
      headX++;
      break;
    case UP:
      headY--;
      break;
    case DOWN:
      headY++;
      break;
  }
  UpdateTail(size_body);
  // }
}

// Движение хвоста змейки с учетом текущей(обновленной) длины змейки
void Model::Snake::UpdateTail(int nTail) {
  size_body = nTail;
  int prevX = tailX[0];
  int prevY = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = headX;
  tailY[0] = headY;
  for (int i = 1; i < size_body; i++) {
    prev2X = tailX[i];
    prev2Y = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }
}

// Столкновение с границами поля или своим хвостом
bool Model::Snake::SnakeAttaching(Field &field) {
  if (headX > field.width - 1 || headX < 2 || headY > field.height - 1 ||
      headY < 2)
    return true;
  for (int i = 1; i < size_body; i++) {
    if (tailX[i] == headX && tailY[i] == headY) {
      return true;
    }
  }
  return false;
}

// Змейка съела фрукт - результаты
bool Model::Snake::HungrySnakeTastyFruit(Fruit &fruit, Info &info) {
  if (headX == fruit.fruitX && headY == fruit.fruitY) {
    size_body++;
    info.score++;
    info.LevelUp();
    info.SpeedUP();
    info.TimerDown();
    if (info.score > info.high_score) info.high_score = info.score;
    return true;
  }
  return false;
}

///////////////////////  ИНФО  ////////////////////////
// Конструктор по умолчанию c начальными параметрами игры
Model::Info::Info() {
  score = 0, high_score = ReadHighScore(), level = 1, speed = 1, timer = 1000;
  pause = false;
}

// Геттеры для получения информации о текущих параметрах игры
bool Model::Info::GetPause() { return pause; }

int Model::Info::GetHighScore() { return high_score; }

int Model::Info::GetScore() { return score; }

int Model::Info::GetLevel() { return level; }

int Model::Info::GetSpeed() { return speed; }

int Model::Info::GetTimer() { return timer; }

// Запись в файл рекордного счета
void Model::Info::SaveHighScore(int high_score) {
  FILE *f = fopen("data_h_score_snake.bin", "wb");
  fwrite(&high_score, sizeof(high_score), 1, f);
  fclose(f);
}

// Cчитывание из файла рекордного счета
int Model::Info::ReadHighScore() {
  FILE *f = fopen("data_h_score_snake.bin", "rb");
  int high_score = 0;
  if (!f)
    SaveHighScore(high_score);
  else {
    fread(&high_score, sizeof(high_score), 1, f);
    fclose(f);
  }
  return high_score;
}

// Повышение уровня
void Model::Info::LevelUp() {
  level = score / 5;
  level = level + 1;
  if (level >= 11) level = 10;
}

// Увеличение скорости(значение)
void Model::Info::SpeedUP() { speed = level; }

// Увеличение скорости(временной шаг)
void Model::Info::TimerDown() { timer = 1000 / 10 * (11 - speed); }

///////////////////////  КОНЕЧНЫЙ АВТОМАТ  ////////////////////////
// Конструктор по умолчанию
Model::FSM::FSM() {
  state = START;
  sig = NOSIG;
}

// Геттер для получения информации о текущeм состоянии игры
int Model::FSM::GetState() { return state; }

// Cтартовое состояние
void Model::FSM::Start([[maybe_unused]] Model &model) {
  state = START;
  model.info.high_score = model.info.GetHighScore();
  model.info.score = 0;
  model.info.level = 1;
  model.info.speed = 1;
  model.info.timer = 1000;
  model.info.pause = false;
  model.fruit.fruitX = 5;
  model.fruit.fruitY = 9;
  model.snake.headX = 7;
  model.snake.headY = 5;
  model.snake.size_body = 4;
  model.snake.dir = Snake::RIGHT;
  model.snake.StartPosition();
  state = MOVING;
}

// Состояние зарождения фрукта
void Model::FSM::Spawn([[maybe_unused]] Model &model) {
  model.fruit.RespawnFruit(model.field, model.snake);
  state = MOVING;
}

// Cдвиг влево на 1 "пиксель"
void Model::FSM::MoveLeft([[maybe_unused]] Model &model) {
  if (model.snake.dir != Snake::RIGHT) {
    model.snake.dir = Snake::LEFT;
  }
  state = MOVING;
}

// Cдвиг вправо на 1 "пиксель"
void Model::FSM::MoveRight([[maybe_unused]] Model &model) {
  if (model.snake.dir != Snake::LEFT) {
    model.snake.dir = Snake::RIGHT;
  }
  state = MOVING;
}

// Cдвиг вверх на 1 "пиксель"
void Model::FSM::MoveUp([[maybe_unused]] Model &model) {
  if (model.snake.dir != Snake::DOWN) {
    model.snake.dir = Snake::UP;
  }
  state = MOVING;
}

// Cдвиг вниз на 1 "пиксель"
void Model::FSM::MoveDown([[maybe_unused]] Model &model) {
  if (model.snake.dir != Snake::UP) {
    model.snake.dir = Snake::DOWN;
  }
  state = MOVING;
}

// Движение змейки самостоятельное
void Model::FSM::Shifting([[maybe_unused]] Model &model) {
  model.snake.SnakeShifting();
  if (model.snake.SnakeAttaching(model.field) || model.snake.size_body == 200) {
    model.info.SaveHighScore(model.info.high_score);
    state = GAMEOVER;
  } else if ((model.snake.HungrySnakeTastyFruit(model.fruit, model.info)) ==
                 true &&
             model.snake.size_body != 200) {
    state = SPAWN;
  } else {
    state = MOVING;
  }
}

// Пауза
void Model::FSM::Pause([[maybe_unused]] Model &model) {
  if (state == MOVING) {
    model.info.timer = -1;
    model.info.pause = true;
    state = PAUSE;
  } else if (state == PAUSE) {
    model.info.timer = (11 - model.info.speed) * 100;
    model.info.pause = false;
    state = MOVING;
  }
}

// Принудительный выход из игры
void Model::FSM::Exit([[maybe_unused]] Model &model) {
  model.info.SaveHighScore(model.info.high_score);
  state = EXIT;
}

// Конечный автомат
void Model::FSM::doFSM_table(int signal, Model &model) {
  sig = static_cast<eSignal>(signal);

  action_state FSM_table[6][9] = {
      {&FSM::Start, nullptr, &FSM::Exit, nullptr, nullptr, nullptr, nullptr,
       nullptr, nullptr},
      {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
       &FSM::Spawn, &FSM::Spawn},
      {nullptr, &FSM::Pause, &FSM::Exit, &FSM::MoveLeft, &FSM::MoveRight,
       &FSM::MoveUp, &FSM::MoveDown, &FSM::Shifting, &FSM::Shifting},
      {nullptr, &FSM::Pause, &FSM::Exit, nullptr, nullptr, nullptr, nullptr,
       nullptr, nullptr},
      {&FSM::Start, nullptr, &FSM::Exit, nullptr, nullptr, nullptr, nullptr,
       nullptr, nullptr},
      {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
       nullptr}

  };
  action_state act = FSM_table[state][sig];

  if (act) (this->*act)(model);
}

///////////////////////  МОДЕЛЬ  ////////////////////////
// Конструктор по умолчанию
Model::Model() : field(), fruit(), snake(), info(), fsm() {}