#include <FastLED.h>
#include <stdio.h>
#define NUM_LEDS 100
#define LED_PIN A0
#define NUM_LEDS 100     
#define updateLEDS 1        
#define COLOR_SHIFT 10000  
#define DATA_PIN A0
int count=0;
uint8_t bright=255;
uint8_t whichPalette=0;  
uint8_t paletteIndex = 0;
uint8_t colorIndex[NUM_LEDS];

DEFINE_GRADIENT_PALETTE( Sunset_Real_gp1 ) {
    22.5, 52,  225,  188,
   67, 49, 254,  255,
  112, 36, 158,231,
  168,  70,  30,214,
  255,  223,  45,246};
 
DEFINE_GRADIENT_PALETTE( Sunset_Real_gp2 ) {
    22.5,246, 240,45 ,
   67, 246, 119,34,
  112, 231, 36,36,
  168, 255, 49, 143,
  255, 255, 52,  251};
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

DEFINE_GRADIENT_PALETTE( somewhere2_gp ) {
    0,   9,176,255,
   15,  15,255,111,
   25,  54,255, 37,
   40,  34,255, 59,
   61, 173,209,  8,
   79, 255, 97,  5,
   96, 255, 26, 19,
  112, 255, 29, 16,
  132, 255, 12, 49,
  150, 255,  8,105,
  173, 179, 14,216,
  188, 112, 27,255,
  204,  57, 55,255,
  229,   5,255,219,
  255,   9,176,255};

DEFINE_GRADIENT_PALETTE( cyan_magenta_yellow_white_gp ) {
    0,   0,255,255,
  127, 255,  0,255,
  191, 255,255,  0,
  255, 255,255,255};

DEFINE_GRADIENT_PALETTE( bhw1_01_gp ) {
    0, 227,101,  3,
  117, 194, 18, 19,
  255,  92,  8,192};


DEFINE_GRADIENT_PALETTE( rainbow_gp ) {
    0, 126,  1,142,
   25, 171,  1, 26,
   48, 224,  9,  1,
   71, 237,138,  1,
   94,  52,173,  1,
  117,   1,201,  1,
  140,   1,211, 54,
  163,   1,124,168,
  186,   1,  8,149,
  209,  12,  1,151,
  232,  12,  1,151,
  255, 171,  1,190};

CRGBPalette16 currentPalette=heatmap_gp;
CRGBPalette16 targetPalette=somewhere2_gp;
CRGBPalette16 myPal1 = Sunset_Real_gp1;
CRGBPalette16 myPal2 = Sunset_Real_gp2;            
unsigned long setTime = COLOR_SHIFT;
int shiftC = 0;
int mulC = 2;
struct color {
  int r;
  int g;
  int b;
};
typedef struct color Color;
CRGB leds[NUM_LEDS];
uint8_t hue1=0;
uint8_t hue2=360;
int x=10000;
int ch=1;
const int OUT_PIN = 6;
const int SAMPLE_TIME = 10;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;

int sampleBufferValue = 0;

void setup() {FastLED.addLeds<WS2811, LED_PIN, BRG  >(leds,NUM_LEDS);
FastLED.setBrightness(50);
FastLED.setCorrection(TypicalLEDStrip);
FastLED.setTemperature(OvercastSky);
pinMode(OUT_PIN,INPUT);
Serial.begin(9600);
  for (int i = 0; i < NUM_LEDS; i++) {
    colorIndex[i] = random8();
  }
}
double convBrightness(int b) {
  double c = b / 614.0000;
  if( c < 0.2 ) {
    c = 0;
  }
  else if(c > 1) {
    c = 1.00;
  }
  return c;
}
void setColor(Color *c, int r, int g, int b) {
  c->r = r;
  c->g = g;
  c->b = b;
}

void printColor(Color c) {
  Serial.print("( ");
  Serial.print(c.r);
  Serial.print(", ");
  Serial.print(c.g);
  Serial.print(", ");
  Serial.print(c.b);
  Serial.println(" )");
}


Color pitchConv(int p, int b) {
  Color c;
  double bright = convBrightness(b);

  if(p < 40) {
    setColor(&c, 255, 0, 0);
  }
  else if(p >= 40 && p <= 77) {
    int b = (p - 40) * (255/37.0000);
    setColor(&c, 255, 0, b);
  }
  else if(p > 77 && p <= 205) {
    int r = 255 - ((p - 78) * 2);
    setColor(&c, r, 0, 255);
  }
  else if(p >= 206 && p <= 238) {
    int g = (p - 206) * (255/32.0000);
    setColor(&c, 0, g, 255);
  }
  else if(p <= 239 && p <= 250) {
    int r = (p - 239) * (255/11.0000);
    setColor(&c, r, 255, 255);
  }
  else if(p >= 251 && p <= 270) {
    setColor(&c, 255, 255, 255);
  }
  else if(p >= 271 && p <= 398) {
    int rb = 255-((p-271)*2);
    setColor(&c, rb, 255, rb);
  }
  else if(p >= 398 && p <= 653) {
    setColor(&c, 0, 255-(p-398), (p-398));
  }
  else {
    setColor(&c, 255, 0, 0);
  }
  setColor(&c, c.r * bright, c.g * bright, c.b * bright);
  return c;
}

void loop() {

  millisCurrent = millis();
  int time= millis();
  millisElapsed = millisCurrent - millisLast;

  if (digitalRead(OUT_PIN) == LOW) {
    sampleBufferValue++;
  }

  if (millisElapsed > SAMPLE_TIME) {
    x=sampleBufferValue;
    Serial.println(sampleBufferValue);
    sampleBufferValue = 0;
    millisLast = millisCurrent;
switch(ch)
{
  case 1:
  {
  waveform();
  break;
}
case 2:
{
  glowdim();
   break;
}
case 3:
{
  fadeout1();
   break;
}
case 4:
{
  fadeout2();
   break;
}
case 5:
{
  gradientMovement();
   break;
}
case 6:
{
  beatSine();
   break;
}
case 7:
{
  visualizer1begin();
   break;
}
case 8:
{
  visualizer2begin();
   break;
}
case 9:
{
  visualizer1end();
   break;
}
case 10:
{
  visualizer2end();
   break;
}
}
checkTimer();
}
 
}
void checkTimer() {
  EVERY_N_SECONDS(50) {
    nextPattern();
  }
}

void nextPattern() {
  ch = random8(1,10);
}

void glowdim()
{    for(int i=0;i<NUM_LEDS;i++)
{
  leds[i]=CHSV(x,225,225);
  
}
if(x<50)
{
  FastLED.setBrightness(x);
}

   EVERY_N_SECONDS(x)
    {
      hue1++;
    }  

  FastLED.show();
}

void waveform()
{
  if( millisCurrent/ (double)setTime >= 1) {
    setTime =  millisCurrent + COLOR_SHIFT;
    //Serial.println(setTime);
    shiftC += 200;
    mulC++;
    if(shiftC >= 600) {
      shiftC = 0;
    }
    if(mulC > 3) {
      mulC = 2;
    }
  }

  for(int i = NUM_LEDS - 1; i >= updateLEDS; i--) {
    leds[i] = leds[i - updateLEDS];
  }

  int newPitch = (x*2) + shiftC;
  Color nc = pitchConv(newPitch, x);

  // Set the left most updateLEDs with the new color
  for(int i = 0; i < updateLEDS; i++) {
    leds[i] = CRGB(nc.r, nc.g, nc.b);
  }
  FastLED.show();

  //printColor(nc);
}
void fadeout1()
{  EVERY_N_MILLISECONDS(x){
    //Switch on an LED at random, choosing a random color from the palette
    leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(myPal1, x, 255, LINEARBLEND);
    leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(myPal1, x, 255, LINEARBLEND);
  }
   // Fade all LEDs down by 1 in brightness each time this is called
   fadeToBlackBy(leds, NUM_LEDS, 1/x);
   if(x>300)
   {
       fadeToBlackBy(leds, NUM_LEDS, x);
   }
   else
   {
   fadeToBlackBy(leds, NUM_LEDS, x);
   }
  
  FastLED.show();
}
void fadeout2()
{  EVERY_N_MILLISECONDS(x){
    //Switch on an LED at random, choosing a random color from the palette
    leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(myPal2, x, 255, LINEARBLEND);
    leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(myPal2, x, 255, LINEARBLEND);
  }
   // Fade all LEDs down by 1 in brightness each time this is called
   fadeToBlackBy(leds, NUM_LEDS, 1/x);
   if(x>300)
   {
       fadeToBlackBy(leds, NUM_LEDS, x);
   }
   else
   {
   fadeToBlackBy(leds, NUM_LEDS, x);
   }
  
  FastLED.show();
}
void gradientMovement()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex[i]);
  }

  nblendPaletteTowardPalette( currentPalette, targetPalette, 10 );

  switch (whichPalette) {
    case 0:
      targetPalette = somewhere2_gp;
      break;
    case 1:
      targetPalette = cyan_magenta_yellow_white_gp;
      break;
     case 2:
      targetPalette = bhw1_01_gp;
      break;
      case 3:
      targetPalette =  rainbow_gp ;
      break;
       case 4:
      targetPalette =  Sunset_Real_gp1 ;
      break;
       case 5:
      targetPalette =  Sunset_Real_gp2 ;
      break;
      case 6:
      targetPalette = heatmap_gp;
      break;
  }

  EVERY_N_SECONDS(5) {
    whichPalette++;
    if (whichPalette > 2) whichPalette = 0;
    Serial.println(currentPalette[0]);
  }
  
  EVERY_N_MILLISECONDS(2){
    for (int i = 0; i < NUM_LEDS; i++) {
      colorIndex[i]++;
    }
  }
  FastLED.setBrightness(x);
  FastLED.show();
}
void beatSine()
{
  
   uint16_t posBeat  = beatsin16(x, 0, NUM_LEDS - 1, 0, 0);
  uint16_t posBeat2 = beatsin16(x, 0, NUM_LEDS - 1, 0, 0);
  uint16_t posBeat3 = beatsin16(x, 0, NUM_LEDS - 1, 0, 32767);
  uint16_t posBeat4 = beatsin16(x, 0, NUM_LEDS - 1, 0, 32767);

  // Wave for LED color
  uint8_t colBeat  = beatsin8(x, 0, 255, 0, 0);

  leds[(posBeat + posBeat2) / 2]  = CHSV(colBeat, 255, x);
  leds[(posBeat3 + posBeat4) / 2]  = CHSV(colBeat, 255, x);

  fadeToBlackBy(leds, NUM_LEDS, 10);

  FastLED.show();
}
void visualizer1begin()
{
   uint8_t pos = map(x, 0, 614, 0, (NUM_LEDS-1)/2);
  for(int i=0;i<pos;i++)
  {
  leds[i] = CHSV( hue1, 225, bright);
  if((i+1)%5==0)
  {
    hue1=hue1+30;
  }
  bright=bright-5;
  }
  bright=255;
  hue1=0;
  for(int i=NUM_LEDS-1;i>(NUM_LEDS-1)-pos;i--)
  {
  leds[i] = CHSV( hue1, 225,bright);
  if(i%5==0)
  {
    hue1=hue1+30;
  }
  bright=bright-5;
  }
  bright=255;
  hue1=0; 
  FastLED.show();
  EVERY_N_MILLISECONDS(50)
  {
      FastLED.clear();
  }
  }

void visualizer2begin()
{
   uint8_t pos = map(x, 0, 614, 0, (NUM_LEDS-1)/2);
  for(int i=0;i<pos;i++)
  {
  leds[i] = CHSV( hue2, 225, bright);
  if((i+1)%5==0)
  {
    hue2=hue2-30;
  }
  bright=bright-5;
  }
  bright=255;
  hue2=360;
  for(int i=NUM_LEDS-1;i>(NUM_LEDS-1)-pos;i--)
  {
  leds[i] = CHSV( hue2, 225,bright);
  if(i%5==0)
  {
    hue2=hue2-30;
  }
  bright=bright-5;
  }
  bright=255;
  hue2=360; 
  FastLED.show();
  EVERY_N_MILLISECONDS(50)
  {
      FastLED.clear();
  }
  }
 void visualizer1end()
  {
     uint8_t pos = map(x, 0, 614, 0, (NUM_LEDS-1)/2);
  for(int i=50;i>=50-pos;i--)
  {
  leds[i] = CHSV( hue2, 225, bright);
  if((i+1)%5==0)
  {
    hue2=hue2-30;
  }
  bright=bright-5;
  }
  bright=255;
  hue2=360;
  for(int i=50+1;i<=50+pos;i++)
  {
  leds[i] = CHSV( hue2, 225,bright);
  if(i%5==0)
  {
    hue2=hue2-30;
  }
  bright=bright-5;
  }
  bright=255;
  hue2=360; 
  FastLED.show();
  EVERY_N_MILLISECONDS(50)
  {
      FastLED.clear();
  }
  }
 void visualizer2end()
  {
     uint8_t pos = map(x, 0, 614, 0, (NUM_LEDS-1)/2);
  for(int i=50;i>=50-pos;i--)
  {
  leds[i] = CHSV( hue1, 225, bright);
  if((i+1)%5==0)
  {
    hue1=hue1+30;
  }
  bright=bright-5;
  }
  bright=255;
  hue1=0;
  for(int i=50+1;i<=50+pos;i++)
  {
  leds[i] = CHSV( hue1, 225,bright);
  if(i%5==0)
  {
    hue1=hue1+30;
  }
  bright=bright-5;
  }
  bright=255;
  hue1=0; 
  FastLED.show();
  EVERY_N_MILLISECONDS(50)
  {
      FastLED.clear();
  }
  }
