#pragma once

class RSXStepperMotor2023
{
private:
	int _step_pin;
	int _dir_pin;
	int _spin_delay;

public:
	RSXStepperMotor2023(int step_pin, int dir_pin, int spin_delay = 1000);
	void run_motor(int step_num, bool spin_clockwise = true);
};
