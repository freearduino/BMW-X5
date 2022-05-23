/*
   Программа управления сервами 4 мотора . Транзисторы коммутируют питание GND
   Версия 1.0
  26.08.20 Корректировка прошивки, собрана установка
  05.10.20 Корректировка углов поворота сервю
  29.09.21 Корректировкис
  Поднимаем ручник - замкнуто. Должна спрятаться приборка.
  Опускаем ручник - разомкнуто. Должна выехать приборка.
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
  //  Крышка приборки
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
      //Время опускания приборки ------------------------------------------
      delay(3200);
      digitalWrite(PowerSer1, LOW);
      digitalWrite(PowerSer2, LOW);
      BoxCover1.detach();
      BoxCover2.detach();
      delay(50);

      //Крышка выезжает ----------------------------------------------
      while (digitalRead(con2) == HIGH)
      {
        PanelServo1.attach(6);
        digitalWrite(PowerSer3, HIGH);
        PanelServo1.write(0);
        //Вращаем определенное время. Крышка спидометра поднимается вверх вверх  -----

      }
      delay(100);
      //              delay(1000);
      digitalWrite(PowerSer3, LOW);
      PanelServo1.detach();
      delay(50);


      //Крышка открывается -------------------------------------------
      PanelServo2.attach(9);
      digitalWrite(PowerSer4, HIGH);
      PanelServo2.write(180);
      //Время закрытия крышки которая вращается. Закрывает приборку.
      delay(2000);
      digitalWrite(PowerSer4, LOW);
      PanelServo2.detach();
      while (!digitalRead(ruchnik) == HIGH)
      {
#ifdef DEBUG
        Serial.println("Podnyli ruchnik");
#endif
      }
    }
  }
  else
  {
    //Ручник опускаем. Приборка выезжает.
    //Тут открывается крышка приборки
    PanelServo2.attach(9);
    digitalWrite(PowerSer4, HIGH);
    PanelServo2.write(0);
    //Время открытия крышки
    delay(1000);
    //Останавливаем серву
    digitalWrite(PowerSer4, LOW);
    PanelServo2.detach();
    //Заезжает крышка --------------------
    PanelServo1.attach(6);
    digitalWrite(PowerSer3, HIGH);
    PanelServo1.write(180);
    //Вращаем определенное время. Время открытия крышки спидометра. Двигатели постоянного вращения.
    delay(3000);
    digitalWrite(PowerSer3, LOW);
    PanelServo1.detach();
    delay(50);
    //Поднимаем спидометр-----------------------
    BoxCover1.attach(3);
    BoxCover2.attach(5);
    digitalWrite(PowerSer1, HIGH);
    digitalWrite(PowerSer2, HIGH);
    BoxCover1.write(180);
    BoxCover2.write(0);
    //Время поднятия спидометра -----------------------
    delay(3800);
    digitalWrite(PowerSer1, LOW);
    digitalWrite(PowerSer2, LOW);
    BoxCover1.detach();
    BoxCover2.detach();
    while (!digitalRead(ruchnik) == LOW)
    {
#ifdef DEBUG
      Serial.println("Otpustili ruchnik");
#endif
    }
  }
}
