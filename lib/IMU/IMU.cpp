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
    Wire.begin();
    // Read the WHO_AM_I register, this is a good test of communication
    byte c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
    Serial.print("MPU9250 "); Serial.print("I AM "); Serial.print(c, HEX);
    Serial.print(" I should be "); Serial.println(0x71, HEX);

    if (c == 0x71) // WHO_AM_I should always be 0x68
    {
      Serial.println("MPU9250 is online...");

      // Start by performing self test and reporting values
      myIMU.MPU9250SelfTest(myIMU.SelfTest);
      Serial.print("x-axis self test: acceleration trim within : ");
      Serial.print(myIMU.SelfTest[0],1); Serial.println("% of factory value");
      Serial.print("y-axis self test: acceleration trim within : ");
      Serial.print(myIMU.SelfTest[1],1); Serial.println("% of factory value");
      Serial.print("z-axis self test: acceleration trim within : ");
      Serial.print(myIMU.SelfTest[2],1); Serial.println("% of factory value");
      Serial.print("x-axis self test: gyration trim within : ");
      Serial.print(myIMU.SelfTest[3],1); Serial.println("% of factory value");
      Serial.print("y-axis self test: gyration trim within : ");
      Serial.print(myIMU.SelfTest[4],1); Serial.println("% of factory value");
      Serial.print("z-axis self test: gyration trim within : ");
      Serial.print(myIMU.SelfTest[5],1); Serial.println("% of factory value");

      // Calibrate gyro and accelerometers, load biases in bias registers
      myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);

      myIMU.initMPU9250();
      // Initialize device for active mode read of acclerometer, gyroscope, and
      // temperature
      Serial.println("MPU9250 initialized for active data mode....");

      // Read the WHO_AM_I register of the magnetometer, this is a good test of
      // communication
      byte d = myIMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
      Serial.print("AK8963 "); Serial.print("I AM "); Serial.print(d, HEX);
      Serial.print(" I should be "); Serial.println(0x48, HEX);

      // Get magnetometer calibration from AK8963 ROM
      myIMU.initAK8963(myIMU.magCalibration);
      // Initialize device for active mode read of magnetometer
      Serial.println("AK8963 initialized for active data mode....");
      if (SerialDebug)
      {
        //  Serial.println("Calibration values: ");
        Serial.print("X-Axis sensitivity adjustment value ");
        Serial.println(myIMU.magCalibration[0], 2);
        Serial.print("Y-Axis sensitivity adjustment value ");
        Serial.println(myIMU.magCalibration[1], 2);
        Serial.print("Z-Axis sensitivity adjustment value ");
        Serial.println(myIMU.magCalibration[2], 2);
      } else
        {
          Serial.print("Could not connect to MPU9250: 0x");
          Serial.println(c, HEX);
          while(1) ; // Loop forever if communication doesn't happen
        }
      }
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
