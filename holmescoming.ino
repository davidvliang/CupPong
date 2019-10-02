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
  int led[3]; // mux output bits
  int demux; // pin denoting first/second demux port
  int sensor; // sensor to watch corresponding to led
  int state;
} sensor;

sensor sensorList[10] = {
  {
    {0, 0, 0},
    0,
    35,
    0
  },
  {
    {0, 0, 1},
    0,
    36,
    0
  },
  {
    {0, 1, 0},
    0,
    37,
    0
  },
  {
    {0, 1, 1},
    0,
    38,
    0
  },
  {
    {1, 0, 0},
    0,
    39,
    0
  },
  {
    {1, 0, 1},
    0,
    0,
    0
  },
  {
    {1, 1, 0},
    0,
    40,
    0
  },
  {
    {1, 1, 1},
    0,
    41,
    0
  },
  {
    {0, 0, 0},
    1,
    42,
    0
  },
  {
    {0, 0, 1},
    1,
    43,
    0
  },
};

void setup() {
  // initialize the LED pin as an output:
  pinMode(LEDPIN, OUTPUT);
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN, INPUT);
  digitalWrite(SENSORPIN, HIGH); // turn on the pullup
  
  Serial.begin(9600);
}
 
void loop() {
  for (int i = 0; i < 1; i++) {
    // Get sensor value
    sensorList[i].state = digitalRead(sensorList[i].sensor);

    // If state is low, the sensor was broken, if high the sensor was unbroken
    if (sensorList[i].state == LOW) {
      // Set LED value to on
      
      // Control demultiplexer selects
      if (sensorList[i].demux == 0) { // first demux - read all 3 bits
        digitalWrite(0, sensorList[i].led[0]);
        digitalWrite(1, sensorList[i].led[1]);
        digitalWrite(2, sensorList[i].led[2]);
      } else if (sensorList[i].demux == 1) { // second demux - only need LSB since only 2 outputs from demux needed
        digitalWrite(3, sensorList[i].led[2]);
      }

      // Output the state of the LED - LED is off 
      digitalWrite(4, 0);
    } else {
      // Set LED value to on
      
      // Control demultiplexer selects
      if (sensorList[i].demux == 0) { // first demux - read all 3 bits
        digitalWrite(0, sensorList[i].led[0]);
        digitalWrite(1, sensorList[i].led[1]);
        digitalWrite(2, sensorList[i].led[2]);
      } else if (sensorList[i].demux == 1) { // second demux - only need LSB since only 2 outputs from demux needed
        digitalWrite(3, sensorList[i].led[2]);
      }

      // Output the state of the LED - LED is off 
      digitalWrite(4, 1);
    }
  }
}
