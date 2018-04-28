#ifndef _IMU_H_
#define _IMU_H_

#include "Global.h"
//#include <MPU9250_RegisterMap.h>
#include <math.h>
#include <MPU9250.h>
#include <quaternionFilters.h>
//#include <MPU9250DMP.h>
//extern MPU9250_DMP imu;
extern MPU9250_DMP imu_sensor;

void test();

/*#include <Wire.h>
#include <EEPROM.h>
#include <NXPMotionSense.h>
#include <Adafruit_MPL3115A2.h>


struct IMU_data {
      float IMU_direction;
      float IMU_roll;
      float IMU_pitch;
      float IMU_yaw;

      float IMU_acceleration;
      float IMU_velocity;

      float direction_setpoint;
      float last_setpoint;

      float error;
      float last_error;
      float integral_error;
      float omega_Reading;
      float d_error;
      float inst_avg_error;
      float this_time;
      float last_time;
};
extern IMU_data imu;


void imuData();
void serialDisplay();*/

#endif
