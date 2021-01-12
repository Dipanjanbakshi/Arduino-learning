#include <Servo.h>
int servoPin=9;
int servoPos=30;
int lightVal;
int lightPin=A0;
int del= 100;
int count=0;
Servo myServo;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
myServo.attach(servoPin);
pinMode(lightPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
lightVal=analogRead(lightPin);
if(lightVal>=500)
{
 
  servoPos=45;
  delay(100);
  
}
else if(lightVal<500)
{
  servoPos=30 ;
}
myServo.write(servoPos);
Serial.print(servoPos);
Serial.print("      ");
Serial.println(lightVal);
}
