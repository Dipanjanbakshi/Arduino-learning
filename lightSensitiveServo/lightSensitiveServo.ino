#include <Servo.h>
int lightVal;
int lightPin=A0;
int servoPin=9;
int servoPos=0;
int del= 100;
Servo myServo;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); 
pinMode(lightPin,INPUT);
myServo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
lightVal=analogRead(lightPin);
servoPos=(180./1023.)*lightVal;
myServo.write(servoPos);
Serial.print(servoPos);
Serial.print("         ");
Serial.println(lightVal);
delay(100);
}
