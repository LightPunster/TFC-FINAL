#include "IMU.h"


void test () {
    /*imu.update(UPDATE_ACCEL|UPDATE_GYRO); t_sample = micros();
    float omega_z = imu.calcGyro(imu.gz) + omega_z_BiasCorrection;
    float theta_z += ((t_sample - t_last)/1000000.0)*(omega_z + omega_z_0)/2;
    float omega_z_0 = omega_z; t_last = t_sample;

    if(theta_z>(setpoint+180)) theta_z-=360; //Ensures that error never exceed +-180
    if(theta_z<(setpoint-180)) theta_z+=360;

    float error = setpoint - theta_z;
    float d_error = -omega_z;

    Serial.print("SP: "); Serial.print(setpoint);
    Serial.print("\tOmega: "); Serial.print(omega_z);
    Serial.print("\tAng: "); Serial.print(theta_z);*/
}

void imu_sensor_setup() {
    /*Serial.println("sensorId: " + String(sensorId));

    imu_sensor.accelUpdate();
    imu_data.aX = imu_sensor.accelX();
    imu_data.aY = imu_sensor.accelY();
    imu_data.aZ = imu_sensor.accelZ();
    imu_data.aSqrt = imu_sensor.accelSqrt();
    Serial.println("accelX: " + String(imu_data.aX));
    Serial.println("accelY: " + String(imu_data.aY));
    Serial.println("accelZ: " + String(imu_data.aZ));
    Serial.println("accelSqrt: " + String(imu_data.aSqrt));

    imu_sensor.gyroUpdate();
    imu_data.gX = imu_sensor.gyroX();
    imu_data.gY = imu_sensor.gyroY();
    imu_data.gZ = imu_sensor.gyroZ();
    Serial.println("gyroX: " + String(imu_data.gX));
    Serial.println("gyroY: " + String(imu_data.gY));
    Serial.println("gyroZ: " + String(imu_data.gZ));

    imu_sensor.magUpdate();
    imu_data.mX = imu_sensor.magX();
    imu_data.mY = imu_sensor.magY();
    imu_data.mZ = imu_sensor.magZ();
    imu_data.mDirection = imu_sensor.magHorizDirection();
    Serial.println("magX: " + String(imu_data.mX));
    Serial.println("maxY: " + String(imu_data.mY));
    Serial.println("magZ: " + String(imu_data.mZ));
    Serial.println("horizontal direction: " + String(imu_data.mDirection));

    Serial.println("at " + String(millis()) + "ms");
    Serial.println(""); // Add an empty line
    delay(500);*/
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
