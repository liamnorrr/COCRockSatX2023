#include "arduino.h"
#include "RSXStepperMotor2023.h"

RSXStepperMotor2023::RSXStepperMotor2023(int step_pin, int dir_pin, int spin_delay)
{
    /*
    _step_pin: the pin that connects to the STEP on the stepper motor driver.
    _dir_pin: the pin that connects to the DIR on the stepper motor driver.
    _spin_delay: the delay between each step in microseconds.
    */
    _step_pin = step_pin;
    _dir_pin = dir_pin;
    _spin_delay = spin_delay;
    pinMode(step_pin, OUTPUT);
    pinMode(dir_pin, OUTPUT);
};

void RSXStepperMotor2023::run_motor(int step_num, bool spin_clockwise) // TODO: pass in limit switches to make sure motor does not run if limit is reached
{
    /*
    step_num: the number of steps to be completed by the stepper motor.
    sping_clockwise: true -> clockwise, false -> counter clockwise.
    */
    if (spin_clockwise)
    {
        digitalWrite(_dir_pin, HIGH);
    }
    else
    {
        digitalWrite(_dir_pin, LOW);
    }
    for (int i = 0; i < step_num; i++)
    {
        digitalWrite(_step_pin, HIGH);
        delayMicroseconds(_spin_delay);
        digitalWrite(_step_pin, LOW);
        delayMicroseconds(_spin_delay);
        Serial.println("bruh");
    }
}
