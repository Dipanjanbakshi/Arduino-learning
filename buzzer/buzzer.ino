int delay1=100;
int delay2=1000;
int buzzpin=7;
void setup() {
  // put your setup code here, to run once:
pinMode(buzzpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i=0;i<=100;i++)
{
  digitalWrite(buzzpin,HIGH);
  if(i%2==0)
  {
  delay(delay1);
  }
  else
  {
   delay(delay2);
  }
  digitalWrite(buzzpin,LOW);
    if(i%2==0)
  {
  delay(delay1);
  }
  else
  {
   delay(delay2);
  }
}
}
