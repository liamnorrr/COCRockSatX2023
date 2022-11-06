/*
Contributors:
  Svarun Soda
  Andrew Nowakowski

Important Notes:
  This software has only been tested and vairfied on the following hardware:
    Stepper Motor:
      > NEMA 17HS4401 Stepper Motor
          -----------------
          |               |> 6 Connected BLACK
          |      TOP      |> 5 Not Connected
          |       \/      |> 4 Connected RED
          |       /\      |> 3 Connected GREEN
          |               |> 2 Not Connected
          |               |> 1 Connected BLUE
          -----------------
    Stepper Motor Driver Module:
      > A4988 Stepper Driver Module
         Enable(NC) 1 <-----------------> 16 VMOTor(C**)
            MS1(NC) 2 <|               |> 15 GND (C**)
            MS2(NC) 3 <|   ----        |> 14 2B(C-1) BLACK
            MS3(NC) 4 <|   |  |        |> 13 2A(C-3) GREEN
            RST(C*) 5 <|   |  |        |> 12 1A(C-4) BLUE
            SLP(C*) 6 <|      _|_      |> 11 1B(C-6) RED
            STEP(C) 7 <|       |       |> 10 VDD(C)
             DIR(C) 8 <-----------------> 9  GND(C)
        *RST and SLP are bridged together
        **connected to 8V-35V power source with a 47microF capacitor
*/

#include "arduino.h"
#include "RSXStepperMotor.h"

void motor_begin(int step_pin, int dir_pin) {
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
}

void motor_run(int step_pin, int dir_pin, long long step_num, int delay, bool clockwise) {
  if (clockwise) {
    digitalWrite(dir_pin, HIGH);
  } else {
    digitalWrite(dir_pin, LOW);
  }
  for (int i = 0; i < step_num; i++) {
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(delay);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(delay);
  }
  digitalWrite(dir_pin, LOW);
}