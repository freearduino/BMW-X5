/*
   Программа управления сервами 4 мотора . Транзисторы коммутируют питание GND
   Версия 1.0
  26.08.20 Корректировка прошивки, собрана установка
  05.10.20 Корректировка углов поворота сервю
*/
#include <Servo.h>
//Создаем переменные серво
#define DEBUG 1 //1- посылаем в сериал, 0 не отсылаем
//Выезжает спидометр
Servo BoxCover1;
Servo BoxCover2;
//Крышка спидометра
Servo PanelServo1;
Servo PanelServo2;

int angle1 = 0;     // Переменная,в которой хранится положение первого сервопривода
int interval1 = 10; // Интервал времени, через который будет производиться поворот первого сервопривода на один градус

int angle2 = 0;     // Переменная,в которой хранится положение второго сервопривода
int interval2 = 20; // Интервал времени, через который будет производиться поворот второго сервопривода на один градус
int pin = 2;
bool flag = true;
int n = 3;

//Описание переменных концевиков
int con1 = 10; //Концевик поворота крышки
int con2 = 11; //Концевик заезда крышки

int ruchnik = 12;

//Управление питанием
int PowerSer1 = 2;
int PowerSer2 = 4;
int PowerSer3 = 7;
int PowerSer4 = 8; //Выезжает крышка

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif

  BoxCover1.attach(3);
  BoxCover2.attach(5);
  PanelServo1.attach(6);
  PanelServo2.attach(9);

  pinMode(con1, INPUT_PULLUP);
  pinMode(con2, INPUT_PULLUP);
  pinMode(ruchnik, INPUT_PULLUP);
  //Транзисторы управления питанием
  pinMode(PowerSer1, OUTPUT);
  pinMode(PowerSer2, OUTPUT);
  pinMode(PowerSer3, OUTPUT);
  pinMode(PowerSer4, OUTPUT);

  digitalWrite(PowerSer1, LOW);
  digitalWrite(PowerSer2, LOW);
  digitalWrite(PowerSer3, LOW);
  digitalWrite(PowerSer4, LOW);

  //Проверяем начальное положение
  /*
    Проверяем закрыта или нет крышка спидометра. Тут должен быть код который проверяет в каком положении система. Если она не "дома" то мы должны ее приввести домой.
    Необходимо учесть положение ручника. Минимизировать количество срабатываний.
  */
  //  if (digitalRead(con2) == HIGH)
  //  {
  //    delay(60);
  //    while (digitalRead(con2) == HIGH)
  //    {
  //      //Запускаем серву
  //      digitalWrite(PowerSer4, HIGH);
  //      PanelServo2.write(0);
  //      Serial.println("tut");
  //    }
  //    //Останавливаем серву
  //    digitalWrite(PowerSer4, LOW);
  //    PanelServo2.detach();
  //    Serial.println("Stop");
  //  }
  //  //Спидометр приехал вниз, теперь нужно закрыть крышку. Просто вращаем по времени
  //  digitalWrite(PowerSer3, HIGH);
  //  PanelServo1.write(0);
  //  delay(2000); //Вращаем определенное время
  //  digitalWrite(PowerSer3, LOW);
  //  PanelServo1.detach();
  //  //Возможно тут нужно будет поработать сервами , которые вращаются в разные стороны
  //  digitalWrite(PowerSer1, HIGH);
  //  digitalWrite(PowerSer2, HIGH);
  //  BoxCover1.write(180);
  //  BoxCover2.write(0);
  //  delay(2000);
  //  digitalWrite(PowerSer1, LOW);
  //  digitalWrite(PowerSer2, LOW);
  //  BoxCover1.detach();
  //  BoxCover2.detach();
}
void loop()
{
  //Ручник поднят
  if (!digitalRead(ruchnik))
  {
    delay(50);
    if (!digitalRead(ruchnik))
    {
#ifdef DEBUG
      Serial.println("Podnyli ruchnik");
#endif
      //Алгоритм который работает пока поднят ручник
      //Приборка поехала вниз
      BoxCover1.attach(3);
      BoxCover2.attach(5);
      digitalWrite(PowerSer1, HIGH);
      digitalWrite(PowerSer2, HIGH);
      BoxCover1.write(0);
      BoxCover2.write(180);

      //Здесь мы тусуемся пока ручник поднят
      while (!digitalRead(ruchnik) == HIGH)
      {
#ifdef DEBUG
        Serial.println("Podnyli ruchnik while");
#endif
        delay(50);
      }

      //------------Конец тусовки --------------------------
    }
    else
    {
      //--------------------Заезжаем обратно-------------------------------
      //Ручник опущен
      //Алгоритм который работает пока поднят ручник
      //----------------------------------------------------

      //---------------------Конец заезда обратно----------------
    }
  }
}
