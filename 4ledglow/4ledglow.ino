 int a=8,j=5;
 int del=5;
void setup() {
  // put your setup code here, to run once:
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  while(a!=12)
  {
  for(int i=0;i<j;i++)
{digitalWrite(a,HIGH);
delay(del);
digitalWrite(a,LOW);
delay(del);
}a++;j=j+5;
del=del*2;
  }while(a!=12)
  {
  for(int i=0;i<j;i++)
{digitalWrite(a,HIGH);
delay(del);
digitalWrite(a,LOW);
delay(del);
}a++;j=j+5;
del=del*2;
  }
}
