int redPin=6;
int greenPin=9;
int bluePin=10;
String question="Enter the colour you want:";
String colour;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(redPin,OUTPUT);
pinMode(greenPin,OUTPUT);
pinMode(bluePin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(question);
while(Serial.available()==0){

}
colour=Serial.readString();

if(colour=="red"){
  analogWrite(redPin,255);
  analogWrite(greenPin,0);
  analogWrite(bluePin,0);
}
if(colour=="lime"){
  analogWrite(redPin,0);
  analogWrite(greenPin,255);
  analogWrite(bluePin,0);
}
if(colour=="blue"){
  analogWrite(redPin,0);
  analogWrite(greenPin,255);
  analogWrite(bluePin,0);
}
if(colour=="yellow"){
  analogWrite(redPin,50);
  analogWrite(greenPin,255);
  analogWrite(bluePin,0);
}
if(colour=="cyan"){
  analogWrite(redPin,0);
  analogWrite(greenPin,128);
  analogWrite(bluePin,255);
}
if(colour=="fuchsia"){
  analogWrite(redPin,50);
  analogWrite(greenPin,0);
  analogWrite(bluePin,255);
}
if(colour=="orange"){
  analogWrite(redPin,95);
  analogWrite(greenPin,255);
  analogWrite(bluePin,0);
}
if(colour=="green"){
  analogWrite(redPin,0);
  analogWrite(greenPin,128);
  analogWrite(bluePin,0);
}
if(colour=="purple"){
  analogWrite(redPin,128);
  analogWrite(greenPin,0);
  analogWrite(bluePin,128);
}
if(colour=="teal"){
  analogWrite(redPin,0);
  analogWrite(greenPin,128);
  analogWrite(bluePin,128);
}

}
