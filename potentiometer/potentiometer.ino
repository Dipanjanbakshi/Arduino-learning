int readPin=A3;
float v=0;
int readVal=0;
int del=500;
void setup() {
  // put your setup code here, to run once:
pinMode(readPin,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
readVal=analogRead(readPin);
v=(5./1023.)*readVal;

Serial.println(v);
delay(del);
}
