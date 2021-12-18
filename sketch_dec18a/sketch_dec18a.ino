#include<Servo.h>
Servo myServo;

int rawSensorValue;
float rawVolts;
float tempC;
float tempF;
int setPoint = 85;
int returnPoint = 83;
void setup() {
  pinMode(11, OUTPUT);
  myServo.attach(9, 1000, 2000);
  Serial.begin(9600);
  Serial.print("raw");
  Serial.print("\t");
  Serial.print("volts");
  Serial.print("\t");
  Serial.print("degC");
  Serial.print("\t");
  Serial.print("degF");
  Serial.println();
}

void loop() {
  rawSensorValue = analogRead(A0);
  rawVolts = volts(rawSensorValue);
  tempC = 100 * rawVolts - 50;
  tempF = 1.8 * tempC + 32;
  Serial.print(rawSensorValue);
  Serial.print("\t");
  Serial.print(volts);
  Serial.print("\t");
  Serial.print(tempC);
  Serial.print("\t");
  Serial.print(tempF);
  Serial.println();
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

}

float volts(int rawCount)
{
  float AREF = 5.0;
  float calculatedVolts;
  calculatedVolts = rawCount * AREF/1023;
  return calculatedVolts;
}
}
