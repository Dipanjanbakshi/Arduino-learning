 #include <FastLED.h>
#include <stdio.h>
#define NUM_LEDS 100
#define LED_PIN A0
int audioinput=A5;
int x=0;

DEFINE_GRADIENT_PALETTE(heatmap_gp)
{
    0,   0,  0,123,
   17,   0,  0,255,
   33,   0, 11,255,
   51,   0, 55,255,
   68,   0,135,255,
   84,   0,255,255,
  102,   6,255,255,
  119,  41,255,123,
  135, 120,255, 44,
  153, 255,255,  7,
  170, 255,255,  0,
  186, 255,135,  0,
  204, 255, 55,  0,
  221, 255, 11,  0,
  237, 255,  0,  0,
  255, 120,  0,  0
};
CRGBPalette16 mypal=heatmap_gp;
CRGB leds[NUM_LEDS];
  uint8_t hue1=0;
   uint8_t hue2=360;
void setup() {
  // put your setup code here, to run once:
FastLED.addLeds<WS2811, LED_PIN, BRG  >(leds,NUM_LEDS);
FastLED.setBrightness(50);
FastLED.setCorrection(TypicalLEDStrip);
FastLED.setTemperature(OvercastSky);
  pinMode(audioinput,INPUT);
  Serial.begin(9600);
}

void loop() {
 // put your main code here, to run repeatedly
x=analogRead(audioinput);
Serial.println(x);
for(int i=0;i<NUM_LEDS;i++)
{
  leds[i]=CHSV(hue1,225,225);
  
}

   EVERY_N_SECONDS(x)
    {
      hue1++;
    }  

  FastLED.show();



}
