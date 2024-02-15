#include "tinysnore.h"

const byte PHOTOCELL_PIN = 3;
const byte TEST_LED_PIN = 0;
const byte MOTOR_PIN = 4;

const byte pullupPins[] = {1, 2, 5};

const int DAY_THRESHOLD = 600;
const int NIGHT_THRESHOLD = 300;
const int TEST_LED_FLASH_DURATION = 100;
const int NIGHT_SLEEP_DURATION = 1200000;
const int DAY_SLEEP_DURATION = 9000000;
const int MOTOR_ON_DURATION = 4000;
const int MAIN_SLEEP_DURATION = 36000000;

int counter = 0;

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(TEST_LED_PIN, OUTPUT);

  for (auto pin : pullupPins) {
    pinMode (pin, INPUT_PULLUP);          
  }
}

void loop() {
  int photocellValue = analogRead(PHOTOCELL_PIN);

  if (photocellValue > DAY_THRESHOLD) {
    digitalWrite(TEST_LED_PIN, HIGH);
    delay(TEST_LED_FLASH_DURATION);
    digitalWrite(TEST_LED_PIN, LOW);
    snore(DAY_SLEEP_DURATION);
  }

 else (photocellValue <= NIGHT_THRESHOLD); {
    for (int i = 0; i < 3; i++) {
      digitalWrite(TEST_LED_PIN, HIGH);
      delay(TEST_LED_FLASH_DURATION);
      digitalWrite(TEST_LED_PIN, LOW);
      delay(TEST_LED_FLASH_DURATION);
    }
    snore(NIGHT_SLEEP_DURATION);
    delay(100);
    
    counter++;
  }

  if (counter == 2 || counter == 6) {
    digitalWrite(MOTOR_PIN, HIGH);
    delay(MOTOR_ON_DURATION);
    digitalWrite(MOTOR_PIN, LOW);
  }

  if (counter >= 6) {
    counter = 0;
    snore(MAIN_SLEEP_DURATION);
    delay(TEST_LED_FLASH_DURATION);
  }
}