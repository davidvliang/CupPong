/* 
  IR Breakbeam sensor demo!
*/

/*
 * Get sensor pins and set as inputs, set to HIGH
 * Need four bits (1, 2, 4, 8) for 10 cups 
 * 
  */

#define LEDPIN 13
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin  6: Teensy++ 2.0 has the LED on pin 6
  // Pin 13: Teensy 3.0 has the LED on pin 13
 
#define SENSORPIN 4
 
// variables will change:

typedef struct {
  int sensor; // sensor to watch corresponding to led
  int led; // mux output bits
  int state;
} sensor;

sensor sensorList[20] = {
  {
    22,
    23,
    0
  },
  {
    24,
    25,
    0
  },
  {
    26,
    27,
    0
  },
  {
    28,
    29,
    0
  },
  {
    30,
    31,
    0
  },
  {
    32,
    33,
    0
  },
  {
    34,
    35,
    0
  },
  {
    36,
    37,
    0
  },
  {
    38,
    39,
    0
  },
  {
    40,
    41,
    0
  },
  // second game
  {
    42,
    43,
    0
  },
  {
    44,
    45,
    0
  },
  {
    46,
    47,
    0
  },
  {
    48,
    49,
    0
  },
  {
    50,
    51,
    0
  },
  {
    52,
    53,
    0
  },
  {
    10,
    11,
    0
  },
  {
    2,
    3,
    0
  },
  {
    4,
    5,
    0
  },
  {
    8,
    9,
    0
  },
};

void setup() {
  for (int i = 0; i < 20; i++) {
    pinMode(sensorList[i].sensor, INPUT);
    pinMode(sensorList[i].led, OUTPUT);

    digitalWrite(sensorList[i].sensor, HIGH);
    digitalWrite(sensorList[i].led, LOW);
  }
  
  Serial.begin(9600);
}
 
// loop forever like whileloop(1)
void loop() {
   for (int i = 0; i < 20; i++) {
    // Get sensor value
    sensorList[i].state = digitalRead(sensorList[i].sensor);

    Serial.print(sensorList[i].state);
    Serial.print(" ");

    // If state is low, the sensor was broken, if high the sensor was unbroken
    if (sensorList[i].state == LOW) {
      digitalWrite(sensorList[i].led, HIGH);
    }
  }
}
