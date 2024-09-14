#ifndef MODEL_H
#define MODEL_H

#include <iostream>

class Model {
 public:
  class Field;
  class Fruit;
  class Snake;
  class Info;
  class FSM;

  // Параметры поля
  class Field {
    friend Fruit;
    friend Snake;
    friend FSM;

   private:
    int width;
    int height;

   public:
    Field();  // Конструктор по умолчанию - поле с шириной = 10 и высотой = 20
    int GetWidth() const;  // Геттер для получения неизменного значения ширины
    int GetHeight() const;  // Геттер для получения неизменного значения высоты
  };

  // Координаты фрукта
  class Fruit {
    friend Snake;
    friend FSM;

   private:
    int fruitX;
    int fruitY;

   public:
    Fruit();  // Конструктор по умолчанию, установим начальные координаты фрукта
              // на середине поля
    int GetFruitX();  // Геттер для получения текущей координаты фрукта по Х
    int GetFruitY();  // Геттер для получения текущей координаты фрукта по Y
    void RespawnFruit(Field &field,
                      Snake &snake);  // Зарождение нового фрукта, если
                                      // предыдущее съела змейка
  };

  // Змейка
  class Snake {
    friend Fruit;
    friend FSM;

   private:
    int tailX[100], tailY[100];
    int headX, headY;
    int size_body;
    enum eDirection { LEFT = 3, RIGHT = 4, UP = 5, DOWN = 6 };
    eDirection dir;

   public:
    Snake();  // Конструктор змейки по умолчанию
    int GetHeadX();  // Геттер для получения текущих координат головы змейки
    int GetHeadY();  // Геттер для получения текущих координат головы змейки
    int GetTailX(
        int index);  // Геттер для получения текущих координат хвоста змейки
    int GetTailY(
        int index);  // Геттер для получения текущих координат хвоста змейки
    int GetSizeBody();  // Геттер для получения текущего размера змейки
    int GetDirection();  // Геттер для получения текущего направления змейки
    void StartPosition();  // Начальное положение змейки
    void SnakeShifting();  // Направление движения змейки
    void UpdateTail(int nTail);  // Увеличение и движение хвоста змейки
    bool SnakeAttaching(
        Field &field);  // Столкновение с границами поля или своим хвостом
    bool HungrySnakeTastyFruit(Fruit &fruit, Info &info);  // Змейка съела фрукт
  };

  // Информация о игре
  class Info {
    friend Snake;
    friend FSM;

   private:
    int high_score;
    int score;
    int level;
    int speed;
    bool pause;
    int timer;

   public:
    Info();  // Конструктор по умолчанию c начальными параметрами игры
    bool GetPause();  // Геттер для получения информации о текущeй игре(в
                      // процессе или нет)
    int GetHighScore();  // Геттер для получения информации о текущeм рекордном
                         // счете
    int GetScore();  // Геттер для получения информации о текущeм счете
    int GetLevel();  // Геттер для получения информации о текущeм уровне
    int
    GetSpeed();  // Геттер для получения информации о текущeй скорости(значение)
    int GetTimer();  // Геттер для получения информации о текущeй
                     // скорости(временной шаг)
    void SaveHighScore(int high_score);  // Запись в файл рекордного счета
    int ReadHighScore();  // Cчитывание из файла рекордного счета
    void LevelUp();  // Повышение уровня
    void SpeedUP();  // Увеличение скорости
    void TimerDown();  // Увеличение скорости(временной шаг)
  };

  class FSM {
   private:
    friend Snake;
    enum eSignal { ENTER, SPACE, ESCAPE, LEFT, RIGHT, UP, DOWN, ACTION, NOSIG };
    eSignal sig;
    enum eGameState { START, SPAWN, MOVING, PAUSE, GAMEOVER, EXIT };
    eGameState state;

   public:
    FSM();           // Конструктор по умолчанию
    int GetState();  // Геттер для получения информации о текущeм состоянии игры
    void Start(Model &model);  // Cтартовое состояние
    void Spawn(Model &model);  // Состояние зарождения фрукта
    void MoveLeft(Model &model);  // Cдвиг влево на 1 "пиксель"
    void MoveRight(Model &model);  // Cдвиг вправо на 1 "пиксель"
    void MoveUp(Model &model);  // Cдвиг вверх на 1 "пиксель"
    void MoveDown(Model &model);  // Cдвиг вниз на 1 "пиксель"
    void Shifting(Model &model);  // Движение змейки самостоятельное
    void Pause(Model &model);  // Пауза
    void Exit(Model &model);  // Принудительный выход из игры
    typedef void (FSM::*action_state)(
        Model
            &model);  // Определение типа action_state как указателя на функцию
    void doFSM_table(int signal, Model &model);  // Конечный автомат
  };

 public:
  Field field;
  Fruit fruit;
  Snake snake;
  Info info;
  FSM fsm;

 public:
  Model();  // Конструктор по умолчанию
};

#endif
