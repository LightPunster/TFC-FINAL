#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "Global.h"
#include "IMU.h"


//declarations for control used in main loop
#define Allowed_error 0.2
//control period is two seconds
//TODO::check this value
#define Control_period 200000 //.2 seconds in microseconds


//TODO::run updated simulation and check these values
#define Kp_actuate 1*(3.14159/180)
#define Kp_hold 1*(3.14159/180)
#define Kd_actuate 0.25*(3.14159/180)
#define Kd_hold 0.25*(3.14159/180)
#define Ki_actuate 0.05
#define Ki_hold 0.05
#define pwm_Limit_actuate 1
#define pwm_Limit_hold 1
#define pwm_limit 0.05
#define pwm_period 0.2

extern float pwm_Duty;
//controls the rocket by performing algorithmic calculations and sending a signal to the solenoids
void control_hold(imu* imu_data);
void control_actuate(imu* imu_data);

#endif
