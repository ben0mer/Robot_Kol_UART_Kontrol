#include <Arduino.h>
#include "MACStepper.h"

#define SERVO_PIN 4

void setup() {
  Serial.begin(9600);
  Serial.println("BASLATILDI");
  pinMode(SERVO_PIN,OUTPUT);
  initSettings();
}

void loop() {

  // prepareMovement(0, 70);
  // prepareMovement(1, 60);
  // prepareMovement(2, 75);
  // prepareMovement(4, 45);
  // runAndWait();
  // prepareMovement(0, -30);
  // prepareMovement(2, -30);
  // runAndWait();
  // //prepareMovement(0, 30);
  // prepareMovement(2, 30);
  // runAndWait();
  // prepareMovement(0, -30);
  // prepareMovement(1, -60);
  // prepareMovement(2, -75);
  // prepareMovement(4, -45);
  // runAndWait();

  while (1){
  };
}