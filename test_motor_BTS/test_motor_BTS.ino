/*
  Управление стробами. Управление с пульта 4 кнопки: A, B, C, D.
  Описание функций кнопок:
  A - Вкл,выкл все горит
  B - вкл,выкл моргает по бокам
  C - вкл,выкл быстрого моргания как у ментов
*/
int pwmL = 10;
int pwmR = 11;

void setup()
{
  Serial.begin(9600);
  pinMode(pwmL, OUTPUT);


}

void loop()
{
  int sensorValue = analogRead(A5);
  if (sensorValue == 1023) {

    analogWrite(pwmL, 254);
  } else {
    analogWrite(pwmL, 0);
  }
  int sensorValue2 = analogRead(A4);
  if (sensorValue2 == 1023) {

    analogWrite(pwmR, 100);
  } else {
    analogWrite(pwmR, 0);
  }
  //  digitalWrite(en_a, HIGH);
  //  digitalWrite(en_b, HIGH);
  //  analogWrite(pwmL, 254);
  //  delay(2000);
  //  analogWrite(pwmL, 0);
  //  analogWrite(pwmR, 100);
  //  delay(1500);
  //  analogWrite(pwmR, 0);
  //  while (1);
}
