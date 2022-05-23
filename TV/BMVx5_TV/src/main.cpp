/*
Управление открытием колонок и телевизора. Управление с пульта 4 кнопки: A, B, C, D.
*/
#include "GyverButton.h"
#include <Arduino.h>
// Мотор 1
#define INA1 7
#define INB1 2
#define EN1 8
#define PWM1 9

// Мотор 2
#define INA2 5
#define INB2 4
#define EN2 6
#define PWM2 3

// Пины пульта
#define ButtonA A6 //Только аналогрид
#define ButtonB A4
#define ButtonC A7 //Можно считывать только аналоговые значения
#define ButtonD A5
GButton ButtButtonA(ButtonA);
GButton ButtButtonB(ButtonB);
GButton ButtButtonC(ButtonC);
GButton ButtButtonD(ButtonD);

// Концевики
#define KonzTV 10
#define KonzKol 11
GButton ButtKonzTV(KonzTV);
GButton ButtKonzKol(KonzKol);

void setup()
{
  Serial.begin(9600);

  pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(PWM1, OUTPUT);

  pinMode(INA2, OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(PWM2, OUTPUT);

  // Описание концевиков и кнопок пульта
  ButtKonzTV.setDebounce(50);      // настройка антидребезга (по умолчанию 80 мс)
  ButtKonzTV.setTimeout(300);      // настройка таймаута на удержание (по умолчанию 500 мс)
  ButtKonzTV.setClickTimeout(600); // настройка таймаута между кликами (по умолчанию 300 мс)

  // HIGH_PULL - кнопка подключена к GND, пин подтянут к VCC (BTN_PIN --- КНОПКА --- GND)
  // LOW_PULL  - кнопка подключена к VCC, пин подтянут к GND
  // по умолчанию стоит HIGH_PULL
  ButtKonzTV.setType(HIGH_PULL);

  // NORM_OPEN - нормально-разомкнутая кнопка
  // NORM_CLOSE - нормально-замкнутая кнопка
  // по умолчанию стоит NORM_OPEN
  ButtKonzTV.setDirection(NORM_OPEN);
  // Концевик колонок
  ButtKonzKol.setDebounce(50);
  ButtKonzKol.setTimeout(300);
  ButtKonzKol.setClickTimeout(600);
  ButtKonzKol.setType(LOW_PULL);
  ButtKonzKol.setDirection(NORM_OPEN);
  // Кнопки пульта
  ButtButtonA.setDebounce(50);
  ButtButtonA.setTimeout(300);
  ButtButtonA.setClickTimeout(600);
  ButtButtonA.setType(LOW_PULL);
  ButtButtonA.setDirection(NORM_OPEN);

  ButtButtonB.setDebounce(50);
  ButtButtonB.setTimeout(300);
  ButtButtonB.setClickTimeout(600);
  ButtButtonB.setType(LOW_PULL);
  ButtButtonB.setDirection(NORM_OPEN);

  ButtButtonC.setDebounce(50);
  ButtButtonC.setTimeout(300);
  ButtButtonC.setClickTimeout(600);
  ButtButtonC.setType(LOW_PULL);
  ButtButtonC.setDirection(NORM_OPEN);

  ButtButtonD.setDebounce(50);
  ButtButtonD.setTimeout(300);
  ButtButtonD.setClickTimeout(600);
  ButtButtonD.setType(LOW_PULL);
  ButtButtonD.setDirection(NORM_OPEN);

  // Если не закрыта то закрываем
  // Сначало закрываем колонки, потом телевизор
}

void loop()
{
  // Циклы обязательные
  ButtKonzTV.tick();
  ButtKonzKol.tick();
  ButtButtonA.tick();
  ButtButtonB.tick();
  ButtButtonC.tick();
  ButtButtonD.tick();

  if (ButtButtonA.isClick())
  {
    Serial.println("Click"); // проверка на один клик
    digitalWrite(INA1, LOW);
    digitalWrite(INB1, HIGH);
    digitalWrite(EN1, HIGH);
    analogWrite(PWM1, 150);
    delay(1500);
    digitalWrite(EN1, LOW);
    analogWrite(PWM1, 0);
    digitalWrite(EN2, LOW);
    analogWrite(PWM2, 0);
  }

  if (ButtButtonC.isHold())
  {
    Serial.println("Holding"); // проверка на удержание
  }
  //Вращение всех моторов в одну сторону
  // if (ButtButtonB.isHold())
  if (ButtButtonB.isClick())
  {
    //Движение мотора усилков вниз Правый
    digitalWrite(INA1, HIGH);
    digitalWrite(INB1, LOW);
    digitalWrite(EN1, HIGH);
    analogWrite(PWM1, 200);
    // Левый
    digitalWrite(INA2, HIGH);
    digitalWrite(INB2, LOW);
    digitalWrite(EN2, HIGH);
    analogWrite(PWM2, 200);
    delay(2000);
    digitalWrite(EN2, LOW);
    analogWrite(PWM2, 0);
    delay(400);
    digitalWrite(EN1, LOW);
    analogWrite(PWM1, 0);

    Serial.println("ClickB"); // проверка на один клик
  }
  else
  {
    digitalWrite(EN1, LOW);
    analogWrite(PWM1, 0);
    digitalWrite(EN2, LOW);
    analogWrite(PWM2, 0);
  }
  //Врашение всех моторов в другую сторону
  // if (ButtButtonD.isHold())
  if (ButtButtonD.isClick())
  {
    //Движение мотора усилков вверх Правый
    digitalWrite(INA1, LOW);
    digitalWrite(INB1, HIGH);
    digitalWrite(EN1, HIGH);
    analogWrite(PWM1, 150);
    // Драйвер усилка левый
    digitalWrite(INA2, LOW);
    digitalWrite(INB2, HIGH);
    digitalWrite(EN2, HIGH);
    analogWrite(PWM2, 100);
    delay(3500);
    digitalWrite(EN1, LOW);
    analogWrite(PWM1, 0);
    digitalWrite(EN2, LOW);
    analogWrite(PWM2, 0);
    //Движение мотора
    // digitalWrite(INA2, HIGH);
    // digitalWrite(INB2, LOW);
    // digitalWrite(EN2, HIGH);
    // analogWrite(PWM2, 100);
    Serial.println("ClickD"); // проверка на один клик
  }
  else
  {
    digitalWrite(EN1, LOW);
    analogWrite(PWM1, 0);
    digitalWrite(EN2, LOW);
    analogWrite(PWM2, 0);
  }
}