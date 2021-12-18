// подключение библиотеки DHT
 #include "DHT.h"
 // тип датчика DHT
 #define DHTTYPE DHT11
#include<Servo.h>
Servo myServo;

int rawSensorValue;
float rawVolts;
float tempC;
float tempF;
int setPoint = 85;
int returnPoint = 83;
// контакт подключения входа данных модуля DHT11
 int pinDHT11=9;
 // контакт подключения аналогового выхода модуля влажности почвы
 int pinSoilMoisture=A0;
 // контакт подключения аналогового выхода датчика температуры TMP36
 int pinTMP36=A1;
 // контакт подключения аналогового выхода фоторезистора
 int pinPhotoresistor=A2;

// создание экземпляра объекта DHT
 DHT dht(pinDHT11, DHTTYPE);

void setup()
 {
 pinMode(11, OUTPUT);
 myServo.attach(9, 1000, 2000);
 // запуск последовательного порта
 Serial.begin(9600);
 dht.begin();
 }

void loop()
 {
 // получение данных с DHT11
 float h = dht.readHumidity();
 if (isnan(h))
 {
 Serial.println("Failed to read from DHT");
 }
 else
 {
 Serial.print("HumidityDHT11= "); 
 Serial.print(h);
 Serial.println(" %");
 }

 
 // получение значения с аналогового вывода модуля влажности почвы
 int val0=analogRead(pinSoilMoisture);
 Serial.print("SoilMoisture= "); 
 Serial.println(val0);

 
 // получение значения с аналогового вывода датчика температуры TMP36
 int val1=analogRead(pinTMP36);
 rawVolts = volts(val1);
 int t=rawVolts * 100 - 50;
 tempF = 1.8 * tempC + 32
 Serial.print("TempC = "); 
 Serial.print(t);
 Serial.println(" C");
 if(tempF > setPoint)
  {
    myServo.write(180);
    digitalWrite(11, HIGH);
  }
  else if(tempF < returnPoint)
  {
    myServo.write(0);
    digitalWrite(11, LOW);
    delay(1);
  }
  delay(1000);

 
 // получение значения с аналогового вывода фоторезистора
 int val2=analogRead(pinPhotoresistor);
 Serial.print("Light= "); 
 Serial.println(val2);

 
 // пауза 5 секунд
 Serial.println();
 delay(5000);
 }

 
 float volts(int rawCount)
{
  float AREF = 5.0;
  float calculatedVolts;
  calculatedVolts = rawCount * AREF/1023;
  return calculatedVolts;
}
