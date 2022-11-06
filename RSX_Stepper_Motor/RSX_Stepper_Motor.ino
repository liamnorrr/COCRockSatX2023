#include "RSXStepperMotor.h"


const int STEP_PIN = 19;
const int DIR_PIN = 18;

void setup() {
  motor_begin(STEP_PIN, DIR_PIN);
  Serial.begin(9600);
}

void loop() {
  motor_run(STEP_PIN, DIR_PIN, 1000, 300, true);
  Serial.println("turn");
  delay(1000);
}