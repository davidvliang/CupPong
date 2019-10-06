#include <FastLED.h>

#define NUM_LEDS  47
CRGB leds[NUM_LEDS];
#define DATA_PIN 2

void setup() {
  // put your setup code here, to run once:
  //int PIN = 2;
  //pinMode(PIN,OUTPUT);
   FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);


}

void loop() {
  // put your main code here, to run repeatedly:
  //LED count
    int j = 0;
  int g = 0;
  int f = 0;
  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;
  int e = 0;
   int g2 = 0;
  int f2 = 0;
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  int d2 = 0;
  int e2 = 0;

    int seven1 = 1;
    int seven2 = 0;
    int seven3;
    int seven4;
    int seven5;
    int seven6;
    int seven7;
    int seven8 = 0;
    int seven9;



    if(seven1 == 1)
    {
      f = 1;
      e = 1;  
    }

     if(seven2 == 1)
    {
      a = 1;
      f = 1;
      g = 1;
      c = 1;
      d = 1;  
    }
    


  if(g == 1)
  {
  leds[0] = CRGB::Blue;
  leds[1] = CRGB::Blue;
  leds[2] = CRGB::Blue;

    FastLED.show();
  }


  if(f == 1)
  {
  leds[3] = CRGB::Blue;
  leds[4] = CRGB::Blue;
  leds[5] = CRGB::Blue;

    FastLED.show();
  }
  
   if(a == 1)
  {
  leds[6] = CRGB::Blue;
  leds[7] = CRGB::Blue;
  leds[8] = CRGB::Blue;

    FastLED.show();
  }

   if(b == 1)
  {
  leds[9] = CRGB::Blue;
  leds[10] = CRGB::Blue;
  leds[11] = CRGB::Blue;

    FastLED.show();
  }
  
   if(c == 1)
  {
  leds[13] = CRGB::Blue;
  leds[14] = CRGB::Blue;
  leds[15] = CRGB::Blue;

    FastLED.show();
  }

   if(d == 1)
  {
  leds[16] = CRGB::Blue;
  leds[17] = CRGB::Blue;
  leds[18] = CRGB::Blue;

    FastLED.show();
  }

   if(e == 1)
  {
  leds[19] = CRGB::Blue;
  leds[20] = CRGB::Blue;
  leds[21] = CRGB::Blue;
  leds[22] = CRGB::Blue;
    FastLED.show();
  }

  if(c2 == 1)
  {
  //leds[23] = CRGB::Red;
  leds[24] = CRGB::Red;
  leds[25] = CRGB::Red;
  leds[26] = CRGB::Red;
  leds[27] = CRGB::Red;

    FastLED.show();
  }

  if(d2 == 1)
  {
  leds[28] = CRGB::Red;
  leds[29] = CRGB::Red;
  leds[30] = CRGB::Red;
  //leds[27] = CRGB::Red;
  
  FastLED.show();  
  }



   if(e2 == 1)
  {
  leds[31] = CRGB::Red;
  leds[32] = CRGB::Red;
  leds[33] = CRGB::Red;
  //leds[27] = CRGB::Red;
  
  FastLED.show();  
  }

   if(f2 == 1)
  {
  leds[35] = CRGB::Red;
  leds[36] = CRGB::Red;
  leds[37] = CRGB::Red;
  //leds[27] = CRGB::Red;
  
  FastLED.show();  
  }

  if(a2 == 1)
  {
  leds[38] = CRGB::Red;
  leds[39] = CRGB::Red;
  leds[40] = CRGB::Red;
  //leds[27] = CRGB::Red;
  
  FastLED.show();  
  }

  if(b2 == 1)
  {
  leds[41] = CRGB::Red;
  leds[42] = CRGB::Red;
  leds[43] = CRGB::Red; 

  FastLED.show();
  }

  if(g2 == 1)
  { 
  leds[44] = CRGB::Red;
  leds[45] = CRGB::Red;
  leds[46] = CRGB::Red; 

  FastLED.show(); 
    
    
  }

  delay(1000);
  
}
