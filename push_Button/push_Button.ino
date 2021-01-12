int buttonPin=7;
int buttonVal;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(buttonPin,OUTPUT);
digitalWrite(buttonPin,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
buttonVal=digitalRead(buttonPin);
Serial.println(buttonVal);
}
