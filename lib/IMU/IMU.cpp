#include "IMU.h"

void imu_get_data() {
    imu_sensor.accelUpdate();
    imu_data.aX = imu_sensor.accelX();
    imu_data.aY = imu_sensor.accelY();
    imu_data.aZ = imu_sensor.accelZ();
    imu_data.aSqrt = imu_sensor.accelSqrt();

    imu_sensor.gyroUpdate();
    imu_data.gX = imu_sensor.gyroX();
    imu_data.gY = imu_sensor.gyroY();
    imu_data.gZ = imu_sensor.gyroZ();

    imu_sensor.magUpdate();
    imu_data.mX = imu_sensor.magX();
    imu_data.mY = imu_sensor.magY();
    imu_data.mZ = imu_sensor.magZ();
    imu_data.mDirection = imu_sensor.magHorizDirection();


    imu_data.omega_z = imu_data.gZ + omega_z_BiasCorrection;
    imu_data.theta_z += ((imu_data.this_time - imu_data.last_time)/1000000.0) * (imu_data.omega_z + imu_data.omega_z_0)/2;
    imu_data.omega_z_0 = imu_data.omega_z;
    imu_data.last_time = imu_data.this_time;

    if(imu_data.theta_z>(commands[current_command].setpoint+180)) imu_data.theta_z-=360; //Ensures that error never exceed +-180
    if(imu_data.theta_z<(commands[current_command].setpoint-180)) imu_data.theta_z+=360;

    imu_data.error = commands[current_command].setpoint - imu_data.theta_z;
    imu_data.d_error = -imu_data.omega_z;

    /*imu_data.this_time = micros()/1000000;
    imu_data.error = commands[current_command]setpoint – this_angle_reading;					//Calculate current error
    imu_data.inst_avg_error = (imu_data.error + imu_data.last_error)/2;
    imu_data.integral_error += imu_data.inst_avg_error*(imu_data.this_time - imu_data.last_time);			//Calculate integral error
    imu_data.last_error = imu_data.error;
    imu_data.last_time = imu_data.this_time;*/
}
void test () {
    /*imu.update(UPDATE_ACCEL|UPDATE_GYRO); imu_data.this_time = micros();


    Serial.print("SP: "); Serial.print(setpoint);
    Serial.print("\tOmega: "); Serial.print(omega_z);
    Serial.print("\tAng: "); Serial.print(theta_z);*/
}

void imu_sensor_setup() {

    #ifdef _ESP32_HAL_I2C_H_ // For ESP32
      Wire.begin(SDA_PIN, SCL_PIN); // SDA, SCL
    #else
      Wire.begin();
    #endif
    imu_sensor.setWire(&Wire);
    imu_sensor.beginAccel();
    imu_sensor.beginGyro();
    imu_sensor.beginMag();
    // You can set your own offset for mag values
    // imu_sensor.magXOffset = -50;
    // imu_sensor.magYOffset = -55;
    // imu_sensor.magZOffset = -10;
    uint8_t sensorId = imu_sensor.readId();

    Serial.println("sensorId: " + String(sensorId));
    imu_sensor.accelUpdate();
    imu_data.aX = imu_sensor.accelX();
    imu_data.aY = imu_sensor.accelY();
    imu_data.aZ = imu_sensor.accelZ();
    imu_data.aSqrt = imu_sensor.accelSqrt();

    imu_sensor.gyroUpdate();
    imu_data.gX = imu_sensor.gyroX();
    imu_data.gY = imu_sensor.gyroY();
    imu_data.gZ = imu_sensor.gyroZ();

    imu_sensor.magUpdate();
    imu_data.mX = imu_sensor.magX();
    imu_data.mY = imu_sensor.magY();
    imu_data.mZ = imu_sensor.magZ();
    imu_data.mDirection = imu_sensor.magHorizDirection();
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
