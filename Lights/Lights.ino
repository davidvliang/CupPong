/* Title: Lights
 * By: HKN
 * Date: Oct 8, 2019
 * Description: Light show for cup pong game.
*/


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// How many NeoPixels are attached to the Arduino?
// We will be using 3 strands of 100 leds
#define LED_COUNT 45
#define LED_PIN 2

#define BUTTON 3
#define GAME_FLAG 4
// #define START_FLAG 4
// #define STOP_FLAG 5
#define SPECIAL_FLAG 6

int state = 0;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  pinMode(BUTTON, INPUT);
  pinMode(GAME_FLAG, OUTPUT);
  // pinMode(START_FLAG, OUTPUT);
  // pinMode(STOP_FLAG, OUTPUT);
  pinMode(SPECIAL_FLAG, INPUT);
  digitalWrite(BUTTON, LOW);
  // digitalWrite(START_FLAG, LOW);
  // digitalWrite(STOP_FLAG, LOW);
  digitalWrite(SPECIAL_FLAG, LOW);
  Serial.begin(9600);
}


void loop() {
   unsigned long times = 0;
   unsigned long diff = 0;
  // Standby
  if (state == 0){
    rainbow(1);             // Flowing rainbow cycle along the whole strip
  }

  // Ready-Set-Go!
  else if(state == 1) {
    colorWipe(strip.Color(255,   0,   0), 5); // Red
    colorWipe(strip.Color(255, 255,   5), 5); // Yellow
    colorWipe(strip.Color(  0, 255,   0), 5); // Green
    state = 2;
    // digitalWrite(START_FLAG, HIGH);
    digitalWrite(GAME_FLAG, HIGH);
  }

  // game code goes here to force next state change
  if (state == 2) {
    times = millis();
    diff = times + 60000;
    Serial.println(diff);

    while(state == 2) {
      Serial.println(millis());
      if (diff <= millis() || digitalRead(SPECIAL_FLAG) == HIGH) {
        state = 3;
      }
    }
      // if some one wins: change state and break
  }

  // end game
  if (state == 3){
    // digitalWrite(STOP_FLAG, HIGH);
    digitalWrite(GAME_FLAG, LOW);
    colorWipe2(strip.Color(255,  0,  0), 2500); // Solid Red
    state = 4;
  }

  // celebrate
  if (state == 4){
    theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
    theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
    state = 0;
  }
}


// --------------------- Some functions of our own for creating animated effects -----------------

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));

      if (digitalRead(BUTTON) == HIGH){
        state = 1;
        return;
      }
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
    delay(1000);
}

void colorWipe2(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
  }
    delay(wait);
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
