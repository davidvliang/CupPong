/* Title: Timer
 * By: HKN
 * Date: Oct 6, 2019
 * Description: 60-sec countdown timer

 https://create.arduino.cc/projecthub/xXarduino_11Xx/arduino-countdown-timer-fc2fd9
*/


#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define START_PIN 10
#define STOP_PIN 11

#define LED_COUNT 47
#define LED_PIN 2


CRGB leds[LED_COUNT];

byte brightness = 250;
byte saturation = 255;
byte startColor = 0;

byte segGroups[14][3] = {
  // right (seen from front) digit
  {  16,  17,  18 },    // top, a
  {  13,  14,  15 },    // top right, b
  {   9,  10,  11 },    // bottom right, c
  {   6,   7,   8 },    // bottom, d
  {   3,   4,   5 },    // bottom left, e
  {  19,  20,  21 },    // top left, f
  {   0,   1,   2 },    // center, g
  // left (seen from front) digit
  {  28,  29,  30 },    // top, a
  {  25,  26,  27 },    // top right, b
  {  41,  42,  43 },    // bottom right, c
  {  38,  39,  40 },    // bottom, d
  {  35,  36,  37 },    // bottom left, e
  {  31,  32,  33 },    // top left, f
  {  44,  45,  46 }    // center, g};
};

byte digits[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1 },  // 2
  { 1, 1, 1, 1, 0, 0, 1 },  // 3
  { 0, 1, 1, 0, 0, 1, 1 },  // 4
  { 1, 0, 1, 1, 0, 1, 1 },  // 5
  { 1, 0, 1, 1, 1, 1, 1 },  // 6
  { 1, 1, 1, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1 },  // 8
  { 1, 1, 1, 1, 0, 1, 1 },  // 9
};

void setup() {
  pinMode(START_PIN, INPUT);
  pinMode(STOP_PIN, OUTPUT);
  digitalWrite(START_PIN, LOW);
  digitalWrite(STOP_PIN, LOW);

  Serial.begin(57600);
  Serial.println("7 Segment Clock v2 - Display Test...");
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.setDither(0);
  FastLED.setBrightness(brightness);
  FastLED.clear();
  FastLED.show();
}


void loop() {
  FastLED.clear();
  FastLED.setBrightness(brightness);

  while(digitalRead(START_PIN) == LOW);

  showDigit(6, startColor+50, 0);
  showDigit(0, startColor+50, 1);
  FastLED.show();
  delay(1000);
  FastLED.clear();

  for(byte i = 5; i >= 0; i--) {
    showDigit(i, startColor+20, 0);
    for (byte j = 9; j >= 0; j--) {
      showDigit(i, startColor+100, 1);
      FastLED.show();
      delay(1000);
      FastLED.clear();
    }
  }

  // FLAG
  digitalWrite(STOP_PIN, HIGH);
  digitalWrite(START_PIN, LOW);
}

void showSegment(byte segment, byte color, byte segDisplay) {
  for (byte i = 0; i < 3; i++) {
   if (segDisplay == 0) leds[(segGroups[segment][i])].setHSV(color, saturation, brightness);  // left digit
   if (segDisplay == 1) leds[(segGroups[segment + 7][i])].setHSV(color, saturation, brightness);  // right digit
  }
}

void showDigit(byte digit, byte color, byte segDisplay) {
  for (byte i = 0; i < 7; i++) {
    if (digits[digit][i] != 0) {
      showSegment(i, color, segDisplay);
    }
  }
}
