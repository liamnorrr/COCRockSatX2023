#ifndef RSXSTEPPERMOTOR
#define RSXSTEPPERMOTOR

void motor_begin(int step_pin, int dir_pin);
void motor_run(int step_pin, int dir_pin, long long step_num, int delay, bool clockwise);

#endif