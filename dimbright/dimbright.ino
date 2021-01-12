int redLed=6;
int bright1=0;
int bright2=125;
int bright3=255;
int del=500;
void setup() {
  // put your setup code here, to run once:
pinMode(redLed,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(redLed,bright1);
delay(del);
analogWrite(redLed,bright2);
delay(del);
analogWrite(redLed,bright3);
delay(del);
}
