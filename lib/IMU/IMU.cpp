#include "IMU.h"


void test () {
    
}























///////////////////////////////////////////////////
/*
void imuData(){
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;

  if (imu_sensor.available()) {
    // Read the motion sensors
    imu_sensor.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);

    // Update the SensorFusion filter
    filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

    // print the heading, pitch and roll
    imu.IMU_roll, imu.IMU_direction = filter.getRoll();
    imu.IMU_pitch = filter.getPitch();
    imu.IMU_yaw = filter.getYaw();
    imu.IMU_acceleration = sqrtf((ax*ax)+(ay*ay)+(az*az)); //TODO::verify that these are calculated using the Teensy's floating point unit
    imu.IMU_velocity = sqrtf((gx*gx)+(gy*gy)+(gz*gz));
    //imu.IMU_direction = filter.getRoll(); //This is dependent on the orintation of the IMU in the rocket

    imu.this_time = micros()/1000000;
	imu.error = (imu.direction_setpoint-imu.IMU_direction);					//Calculate current error

    if(imu.error > 0.0){
        imu.d_error = imu.IMU_velocity;
    }else if(imu.error < 0.0){
        imu.d_error = -1*imu.IMU_velocity;
    }else{
        imu.d_error = abs(imu.IMU_velocity);
    }
    imu.d_error +=((imu.direction_setpoint-imu.last_setpoint)/(imu.this_time-imu.last_time));
    imu.last_setpoint = imu.direction_setpoint;

	imu.inst_avg_error = (imu.error + imu.last_error)/2;
	imu.integral_error += imu.inst_avg_error*(imu.this_time - imu.last_time);			//Calculate integral error
	imu.last_error = imu.error;
	imu.last_time = imu.this_time;
    }
}*/


/*
void IMU_data::imu_read(){

	this_time = micros()/1000000;
};


void IMU_data::setNorth(){
  north = IMU_direction;
};

float IMU_data::getNorth(){
  return north;

};
*/
