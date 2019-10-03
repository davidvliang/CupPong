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
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(35, INPUT);
  pinMode(36, INPUT);
  pinMode(37, INPUT);
  pinMode(38, INPUT);
  pinMode(39, INPUT);
  pinMode(40, INPUT);
  pinMode(41, INPUT);
  pinMode(42, INPUT);
  pinMode(43, INPUT);
  pinMode(44, INPUT);
  
  digitalWrite(2, HIGH); // turn on the pullup
  digitalWrite(3, HIGH); // turn on the pullup
  digitalWrite(4, HIGH); // turn on the pullup
  digitalWrite(5, HIGH); // turn on the pullup
  digitalWrite(6, HIGH); // turn on the pullup
  
  Serial.begin(9600);
}
 
void loop() {
  for (int i = 0; i < 10; i++) {
    // Get sensor value
    sensorList[i].state = digitalRead(sensorList[i].sensor);

    // If state is low, the sensor was broken, if high the sensor was unbroken
    if (sensorList[i].state == LOW) {
      // Set LED value to on
      
      // Control demultiplexer selects
      if (sensorList[i].demux == 0) { // first demux - read all 3 bits
        digitalWrite(2, sensorList[i].led[0]);
        digitalWrite(3, sensorList[i].led[1]);
        digitalWrite(4, sensorList[i].led[2]);
        digitalWrite(7, 0);
      } else if (sensorList[i].demux == 1) { // second demux - only need LSB since only 2 outputs from demux needed
        digitalWrite(5, sensorList[i].led[2]);
        digitalWrite(8, 0);
      }

      // Output the state of the LED - LED is off
      
    } else {
      // Set LED value to on
      
      // Control demultiplexer selects
      if (sensorList[i].demux == 0) { // first demux - read all 3 bits
        digitalWrite(2, sensorList[i].led[0]);
        digitalWrite(3, sensorList[i].led[1]);
        digitalWrite(4, sensorList[i].led[2]);
        // Enable mux 0, disable mux 1
        digitalWrite(7, 1);
        digitalWrite(8, 0);
      } else if (sensorList[i].demux == 1) { // second demux - only need LSB since only 2 outputs from demux needed
        digitalWrite(5, sensorList[i].led[2]);
        // Enable mux 1, disable mux 0
        digitalWrite(7, 0);
        digitalWrite(8, 1);
      }

      // Output the state of the LED - LED is off
      
    }
  }
}
