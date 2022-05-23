/*
  Управление стробами. Управление с пульта 4 кнопки: A, B, C, D.
  Описание функций кнопок:
  A - Вкл,выкл все горит
  B - вкл,выкл моргает по бокам
  C - вкл,выкл быстрого моргания как у ментов
*/
#include "GyverButton.h"
#include <Arduino.h>
// Мотор 2
#define Led1 5
#define Led2 4
#define Led3 3
#define Led4 2

// Пины пульта
#define BUTTON_A 10
#define BUTTON_B 11
#define BUTTON_C 12
#define BUTTON_D 13
GButton ButtButtonA(BUTTON_A);
GButton ButtButtonB(BUTTON_B);
GButton ButtButtonC(BUTTON_C);
GButton ButtButtonD(BUTTON_D);

//Флаги
bool flagLed1 = false;
bool flagLed2 = true;
bool flagLed3 = false;
bool flagLed4 = false;
void setup()
{
  Serial.begin(9600);

  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);

  // Описание концевиков и кнопок пульта
  // HIGH_PULL - кнопка подключена к GND, пин подтянут к VCC (BTN_PIN --- КНОПКА --- GND)
  // LOW_PULL  - кнопка подключена к VCC, пин подтянут к GND
  // по умолчанию стоит HIGH_PULL

  // NORM_OPEN - нормально-разомкнутая кнопка
  // NORM_CLOSE - нормально-замкнутая кнопка
  // по умолчанию стоит NORM_OPEN
  // Кнопки пульта
  ButtButtonA.setDebounce(50);
  ButtButtonA.setTimeout(300);
  ButtButtonA.setClickTimeout(600);
  ButtButtonA.setType(HIGH_PULL);
  ButtButtonA.setDirection(NORM_OPEN);

  ButtButtonB.setDebounce(50);
  ButtButtonB.setTimeout(300);
  ButtButtonB.setClickTimeout(600);
  ButtButtonB.setType(HIGH_PULL);
  ButtButtonB.setDirection(NORM_OPEN);

  ButtButtonC.setDebounce(50);
  ButtButtonC.setTimeout(300);
  ButtButtonC.setClickTimeout(600);
  ButtButtonC.setType(HIGH_PULL);
  ButtButtonC.setDirection(NORM_OPEN);

  ButtButtonD.setDebounce(50);
  ButtButtonD.setTimeout(300);
  ButtButtonD.setClickTimeout(600);
  ButtButtonD.setType(HIGH_PULL);
  ButtButtonD.setDirection(NORM_OPEN);
}

void loop()
{
  // Циклы обязательные
  ButtButtonA.tick();
  ButtButtonB.tick();
  ButtButtonC.tick();
  ButtButtonD.tick();
  //Обработка события A
  if (ButtButtonA.isClick())
  {
    Serial.println("ClickA"); // проверка на один клик
    //Вкл.Выкл фонарей
    if (!flagLed1)
    {
      digitalWrite(Led1, HIGH);
      digitalWrite(Led2, HIGH);
      digitalWrite(Led3, HIGH);
      digitalWrite(Led4, HIGH);
      flagLed1 = true;
    }
    else
    {
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, LOW);
      digitalWrite(Led4, LOW);
      flagLed1 = false;
    }
  }
  //обработка события B
  if (ButtButtonB.isClick())
  {
    Serial.println("ClickB");
    if (!flagLed2)
    {
      flagLed2 = true;
    }
    else
    {
      digitalWrite(Led1, LOW);
      digitalWrite(Led2, LOW);
      digitalWrite(Led3, LOW);
      digitalWrite(Led4, LOW);
      flagLed2 = false;
    }
  }
  //обработка события C
  if (ButtButtonC.isClick())
  {
    Serial.println("ClickC");
    if (!flagLed3)
    {
      flagLed3 = true;
    }
    else
    {
      flagLed3 = false;
    }
  }

  //обработка события D
  if (ButtButtonD.isClick())
  {
    Serial.println("ClickD");
    if (!flagLed4)
    {
      flagLed4 = true;
    }
    else
    {
      flagLed4 = false;
    }
  }
  //События
  if (flagLed2)
  {
    //Включаем перед
    digitalWrite(Led1, HIGH);
    digitalWrite(Led3, HIGH);
    delay(50);
    digitalWrite(Led1, LOW);
    digitalWrite(Led3, LOW);
    delay(50);
    digitalWrite(Led1, HIGH);
    digitalWrite(Led3, HIGH);
    delay(50);
    digitalWrite(Led1, LOW);
    digitalWrite(Led3, LOW);
    delay(50);
    digitalWrite(Led1, HIGH);
    digitalWrite(Led3, HIGH);
    delay(50);
    digitalWrite(Led1, LOW);
    digitalWrite(Led3, LOW);
    delay(50);
    digitalWrite(Led1, HIGH);
    digitalWrite(Led3, HIGH);
    delay(50);
    digitalWrite(Led1, LOW);
    digitalWrite(Led3, LOW);
    delay(50);
    digitalWrite(Led1, HIGH);
    digitalWrite(Led3, HIGH);
    delay(50);
    digitalWrite(Led1, LOW);
    digitalWrite(Led3, LOW);
    //Вторая лампа
    delay(150);
    digitalWrite(Led2, HIGH);
    digitalWrite(Led4, HIGH);
    delay(50);
    digitalWrite(Led2, LOW);
    digitalWrite(Led4, LOW);
    delay(50);
    digitalWrite(Led2, HIGH);
    digitalWrite(Led4, HIGH);
    delay(50);
    digitalWrite(Led2, LOW);
    digitalWrite(Led4, LOW);
    delay(50);
    digitalWrite(Led2, HIGH);
    digitalWrite(Led4, HIGH);
    delay(50);
    digitalWrite(Led2, LOW);
    digitalWrite(Led4, LOW);
    delay(50);
    digitalWrite(Led2, HIGH);
    digitalWrite(Led4, HIGH);
    delay(50);
    digitalWrite(Led2, LOW);
    digitalWrite(Led4, LOW);
    delay(50);
    digitalWrite(Led2, HIGH);
    digitalWrite(Led4, HIGH);
    delay(50);
    digitalWrite(Led2, LOW);
    digitalWrite(Led4, LOW);




    //    delay(50);
    //    digitalWrite(Led1, LOW);
    //    digitalWrite(Led2, LOW);
    //    //Включаем вторую сторону
    //    digitalWrite(Led3, HIGH);
    //    digitalWrite(Led4, HIGH);
    //    delay(50);
    //    digitalWrite(Led3, LOW);
    //    digitalWrite(Led4, LOW);
  }
}
