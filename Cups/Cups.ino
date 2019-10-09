/* Title: Cups
 * By: HKN
 * Date: Oct 6, 2019
 * Description: Game logic w/ cups and sensors for game.
*/

#define GAME_FLAG 12
// #define START_FLAG 12
// #define STOP_FLAG 13
#define SPECIAL_FLAG 13

int playerOne = 0;
int playerTwo = 0;

typedef struct {
  int sensor; // sensor to watch corresponding to led
  int led; // mux output bits
  int state;
} sensor;

sensor sensorList[20] = { /* SENSOR_PIN ~~ LED_PIN ~~ STATE */
  // Player One
  { 22, 23,  0 },
  { 24, 25,  0 },
  { 26, 27,  0 },
  { 28, 29,  0 },
  { 30, 31,  0 },
  { 32, 33,  0 },
  { 34, 35,  0 },
  { 36, 37,  0 },
  { 38, 39,  0 },
  { 40, 41,  0 },
  // Player Two
  { 42, 43,  0 },
  { 44, 45,  0 },
  { 46, 47,  0 },
  { 48, 49,  0 },
  { 50, 51,  0 },
  { 52, 53,  0 },
  { 10, 11,  0 },
  {  2,  3,  0 },
  {  4,  5,  0 },
  {  8,  9,  0 },
};

void setup() {

  for (int i = 0; i < 20; i++) {
    // Assign sensors/leds to pins
    pinMode(sensorList[i].sensor, INPUT);
    pinMode(sensorList[i].led, OUTPUT);

    // Init sensors/leds
    digitalWrite(sensorList[i].sensor, HIGH);
    digitalWrite(sensorList[i].led, LOW);

    // Game Flag
    pinMode(GAME_FLAG, INPUT);
    digitalWrite(GAME_FLAG, LOW);

    // Start/Stop Flags
    // pinMode(START_FLAG, INPUT);
    // pinMode(STOP_FLAG, INPUT);
    // digitalWrite(START_FLAG, LOW);
    // digitalWrite(STOP_FLAG, LOW);

    // Special Flag
    pinMode(SPECIAL_FLAG, OUTPUT);
    digitalWrite(SPECIAL_FLAG, LOW);
  }

  Serial.begin(9600);
}

void loop() {
   // while(START_FLAG == LOW || STOP_FLAG == HIGH);
   while (GAME_FLAG == LOW);

  for (int i = 0; i < 20; i++) {
    // Get sensor value
    sensorList[i].state = digitalRead(sensorList[i].sensor);

    // If state is low, the sensor was broken
    if (sensorList[i].state == LOW) {
      digitalWrite(sensorList[i].led, HIGH);

      // Increment Score
      if (i <= 9) playerOne++;
      else playerTwo++;
    }

    // if (digitalRead(STOP_FLAG) == HIGH) break;
    if (digitalRead(GAME_FLAG) == LOW) break;

  }
  // If player achieves 10 cups, end the game
 if ( playerOne == 10 ) digitalWrite(SPECIAL_FLAG, HIGH);
 if ( playerTwo == 10 ) digitalWrite(SPECIAL_FLAG, HIGH);

}
