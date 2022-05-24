/*
   Программа управления сервами 4 мотора . Транзисторы коммутируют питание GND
   Версия 1.0

*/
#include <Servo.h>
//Создаем переменные серво
//Выезжает спидометр
Servo BoxCover1;
Servo BoxCover2;
//Крышка спидометра
Servo PanelServo1;
Servo PanelServo2;

int angle1 = 0;     // Переменная,в которой хранится положение первого сервопривода
int interval1 = 10;   // Интервал времени, через который будет производиться поворот первого сервопривода на один градус

int angle2 = 0;     // Переменная,в которой хранится положение второго сервопривода
int interval2 = 20;   // Интервал времени, через который будет производиться поворот второго сервопривода на один градус
int pin = 2;
bool flag = true;
int n = 3;

//Описание переменных концевиков
int con1 = 10;
int con2 = 11;

int ruchnik = 12;

//Управление питанием
int PowerSer1 = 2;
int PowerSer2 = 4;
int PowerSer3 = 7;
int PowerSer4 = 8; //Выезжает крышка



void setup() {
  Serial.begin(9600);
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
  //Проверяем закрыта или нет крышка спидометра


}
void loop() {
  if (digitalRead(con2) == HIGH) {
    delay(60);
    if (digitalRead(con2) == HIGH) {
      digitalWrite(PowerSer4, HIGH);
      PanelServo2.write(0);
      Serial.println("Pusk");
      do {
        Serial.println("tut");
      } while (digitalRead(con2) == HIGH);
      digitalWrite(PowerSer4, LOW);
      PanelServo2.detach();
      Serial.println("Stop");
    }
  } else {
    digitalWrite(PowerSer4, LOW);
  }
  //Крышка открывается 1
  //digitalWrite(PowerSer3, HIGH);
  //PanelServo1.write(0);
  //Выезжает крышка 2
  // digitalWrite(PowerSer4, HIGH);
  // PanelServo2.write(0);

  /*
    //Ручник поднят
    if (!digitalRead(ruchnik) ) {
    delay(70);
    if (!digitalRead(ruchnik) ) {

      if (n <= 2) {
        n = n + 1;
      } else {
        n = 1;
      }
    }
    } else {
    //Когда ручник отпуснили
    }


    switch (n) {
    case 1:
      digitalWrite(PowerSer1, HIGH);
      digitalWrite(PowerSer2, HIGH);

      BoxCover1.attach(3);
      BoxCover2.attach(5);

      BoxCover1.write(180);
      BoxCover2.write(0);
      break;
    case 2:
      digitalWrite(PowerSer1, HIGH);
      digitalWrite(PowerSer2, HIGH);

      BoxCover1.attach(3);
      BoxCover2.attach(5);

      BoxCover1.write(0);
      BoxCover2.write(180);
      break;
    case 3:
      digitalWrite(PowerSer1, LOW);
      digitalWrite(PowerSer2, LOW);

      BoxCover1.detach();
      BoxCover2.detach();

      // код для выполнения
      break;

    }

    delay(15);                           // waits for the servo to get there
  */
}
