#ifndef _IMU_H_
#define _IMU_H_

#include "Global.h"
#include <math.h>
#include <MPU9250_asukiaaa.h>

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 26
#define SCL_PIN 25
#endif
extern MPU9250 imu_sensor;


struct imu {
    float aX;
    float aY;
    float aZ;
    float aSqrt;
    float gX;
    float gY;
    float gZ;
    float mDirection;
    float mX;
    float mY;
    float mZ;

    float omega_z;
    float omega_z_0;
    float theta_z;
    //float IMU_acceleration;
    //float IMU_velocity;

    //float direction_setpoint;
    //float last_setpoint;

    float error;
    //float last_error;
    //float integral_error;
    //float omega_Reading;
    float d_error;
    //float inst_avg_error;
    int this_time;
    int last_time;
};
extern struct imu imu_data;

void imu_sensor_setup();
void imu_get_data();

#define omega_z_BiasCorrection -3.45;



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
