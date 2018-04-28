#include <Arduino.h>
//#include <MPU9250_RegisterMap.h>
//#include <SparkFunMPU9250-DMP.h>
//#include <MPU9250DMP.h>




/************************************************************
MPU9250_DMP_Orientation
 Orientation example for MPU-9250 DMP Arduino Library
Jim Lindblom @ SparkFun Electronics
original creation date: November 23, 2016
https://github.com/sparkfun/SparkFun_MPU9250_DMP_Arduino_Library
Uses the MPU-9250's digital motion processing engine to
determine orientation of the board.
Development environment specifics:
Arduino IDE 1.6.12
SparkFun 9DoF Razor IMU M0
Supported Platforms:
- ATSAMD21 (Arduino Zero, SparkFun SAMD21 Breakouts)
*************************************************************/
#include <SparkFunMPU9250-DMP.h>

#define SerialPort SerialUSB

unsigned long stepCount = 0;
unsigned long stepTime = 0;
unsigned long lastStepCount = 0;

const signed char orientationMatrix[9] = {
  1, 0, 0,
  0, 1, 0,
  0, 0, 1
};
unsigned char lastOrient = 0;


void loop()
{
  if ( imu.fifoAvailable() )
  {
    imu.dmpUpdateFifo();
    unsigned char orient = imu.dmpGetOrientation();
    if (orient != lastOrient)
    {
      switch (orient)
      {
      case ORIENT_PORTRAIT:
        SerialPort.println("Portrait");
        break;
      case ORIENT_LANDSCAPE:
        SerialPort.println("Landscape");
        break;
      case ORIENT_REVERSE_PORTRAIT:
        SerialPort.println("Portrait (Reverse)");
        break;
      case ORIENT_REVERSE_LANDSCAPE:
        SerialPort.println("Landscape (Reverse)");
        break;
      }
      lastOrient = orient;
    }
  }
}

/////////////////////////////////////////////////////////////
/*#include <Wire.h>
#include "quaternionFilters.h"
#include "MPU9250.h"

#define AHRS true         // Set to false for basic data read
#define SerialDebug true  // Set to true to get Serial output for debugging

#include <math.h>

//MPU9250_DMP imu_sensor;
MPU9250 myIMU;


void setup() {
    ///Serial.begin(2000000); //the fastest "safest" baud rate Teensy 3.6 can handle according to documentation
    Serial.begin(9600);

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

void loop() {
    // If intPin goes high, all data registers have new data
    // On interrupt, check if data ready interrupt
    if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
    {
      myIMU.readAccelData(myIMU.accelCount);  // Read the x/y/z adc values
      myIMU.getAres();

      // Now we'll calculate the accleration value into actual g's
      // This depends on scale being set
      myIMU.ax = (float)myIMU.accelCount[0]*myIMU.aRes; // - accelBias[0];
      myIMU.ay = (float)myIMU.accelCount[1]*myIMU.aRes; // - accelBias[1];
      myIMU.az = (float)myIMU.accelCount[2]*myIMU.aRes; // - accelBias[2];

      myIMU.readGyroData(myIMU.gyroCount);  // Read the x/y/z adc values
      myIMU.getGres();

      // Calculate the gyro value into actual degrees per second
      // This depends on scale being set
      myIMU.gx = (float)myIMU.gyroCount[0]*myIMU.gRes;
      myIMU.gy = (float)myIMU.gyroCount[1]*myIMU.gRes;
      myIMU.gz = (float)myIMU.gyroCount[2]*myIMU.gRes;

      myIMU.readMagData(myIMU.magCount);  // Read the x/y/z adc values
      myIMU.getMres();
      // User environmental x-axis correction in milliGauss, should be
      // automatically calculated
      myIMU.magbias[0] = +470.;
      // User environmental x-axis correction in milliGauss TODO axis??
      myIMU.magbias[1] = +120.;
      // User environmental x-axis correction in milliGauss
      myIMU.magbias[2] = +125.;

      // Calculate the magnetometer values in milliGauss
      // Include factory calibration per data sheet and user environmental
      // corrections
      // Get actual magnetometer value, this depends on scale being set
      myIMU.mx = (float)myIMU.magCount[0]*myIMU.mRes*myIMU.magCalibration[0] -
                 myIMU.magbias[0];
      myIMU.my = (float)myIMU.magCount[1]*myIMU.mRes*myIMU.magCalibration[1] -
                 myIMU.magbias[1];
      myIMU.mz = (float)myIMU.magCount[2]*myIMU.mRes*myIMU.magCalibration[2] -
                 myIMU.magbias[2];
    } // if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)

    // Must be called before updating quaternions!
    myIMU.updateTime();

    // Sensors x (y)-axis of the accelerometer is aligned with the y (x)-axis of
    // the magnetometer; the magnetometer z-axis (+ down) is opposite to z-axis
    // (+ up) of accelerometer and gyro! We have to make some allowance for this
    // orientationmismatch in feeding the output to the quaternion filter. For the
    // MPU-9250, we have chosen a magnetic rotation that keeps the sensor forward
    // along the x-axis just like in the LSM9DS0 sensor. This rotation can be
    // modified to allow any convenient orientation convention. This is ok by
    // aircraft orientation standards! Pass gyro rate as rad/s
  //  MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  my,  mx, mz);
    MahonyQuaternionUpdate(myIMU.ax, myIMU.ay, myIMU.az, myIMU.gx*DEG_TO_RAD,
                           myIMU.gy*DEG_TO_RAD, myIMU.gz*DEG_TO_RAD, myIMU.my,
                           myIMU.mx, myIMU.mz, myIMU.deltat);

    if (!AHRS)
    {
      myIMU.delt_t = millis() - myIMU.count;
      if (myIMU.delt_t > 500)
      {
        if(SerialDebug)
        {
          // Print acceleration values in milligs!
          Serial.print("X-acceleration: "); Serial.print(1000*myIMU.ax);
          Serial.print(" mg ");
          Serial.print("Y-acceleration: "); Serial.print(1000*myIMU.ay);
          Serial.print(" mg ");
          Serial.print("Z-acceleration: "); Serial.print(1000*myIMU.az);
          Serial.println(" mg ");

          // Print gyro values in degree/sec
          Serial.print("X-gyro rate: "); Serial.print(myIMU.gx, 3);
          Serial.print(" degrees/sec ");
          Serial.print("Y-gyro rate: "); Serial.print(myIMU.gy, 3);
          Serial.print(" degrees/sec ");
          Serial.print("Z-gyro rate: "); Serial.print(myIMU.gz, 3);
          Serial.println(" degrees/sec");

          // Print mag values in degree/sec
          Serial.print("X-mag field: "); Serial.print(myIMU.mx);
          Serial.print(" mG ");
          Serial.print("Y-mag field: "); Serial.print(myIMU.my);
          Serial.print(" mG ");
          Serial.print("Z-mag field: "); Serial.print(myIMU.mz);
          Serial.println(" mG");

          myIMU.tempCount = myIMU.readTempData();  // Read the adc values
          // Temperature in degrees Centigrade
          myIMU.temperature = ((float) myIMU.tempCount) / 333.87 + 21.0;
          // Print temperature in degrees Centigrade
          Serial.print("Temperature is ");  Serial.print(myIMU.temperature, 1);
          Serial.println(" degrees C");
        }myIMU.count = millis();
      } // if (myIMU.delt_t > 500)
    } // if (!AHRS)
    else
    {
      // Serial print and/or display at 0.5 s rate independent of data rates
      myIMU.delt_t = millis() - myIMU.count;

      // update LCD once per half-second independent of read rate
      if (myIMU.delt_t > 500)
      {
        if(SerialDebug)
        {
          Serial.print("ax = "); Serial.print((int)1000*myIMU.ax);
          Serial.print(" ay = "); Serial.print((int)1000*myIMU.ay);
          Serial.print(" az = "); Serial.print((int)1000*myIMU.az);
          Serial.println(" mg");

          Serial.print("gx = "); Serial.print( myIMU.gx, 2);
          Serial.print(" gy = "); Serial.print( myIMU.gy, 2);
          Serial.print(" gz = "); Serial.print( myIMU.gz, 2);
          Serial.println(" deg/s");

          Serial.print("mx = "); Serial.print( (int)myIMU.mx );
          Serial.print(" my = "); Serial.print( (int)myIMU.my );
          Serial.print(" mz = "); Serial.print( (int)myIMU.mz );
          Serial.println(" mG");

          Serial.print("q0 = "); Serial.print(*getQ());
          Serial.print(" qx = "); Serial.print(*(getQ() + 1));
          Serial.print(" qy = "); Serial.print(*(getQ() + 2));
          Serial.print(" qz = "); Serial.println(*(getQ() + 3));
        }

  // Define output variables from updated quaternion---these are Tait-Bryan
  // angles, commonly used in aircraft orientation. In this coordinate system,
  // the positive z-axis is down toward Earth. Yaw is the angle between Sensor
  // x-axis and Earth magnetic North (or true North if corrected for local
  // declination, looking down on the sensor positive yaw is counterclockwise.
  // Pitch is angle between sensor x-axis and Earth ground plane, toward the
  // Earth is positive, up toward the sky is negative. Roll is angle between
  // sensor y-axis and Earth ground plane, y-axis up is positive roll. These
  // arise from the definition of the homogeneous rotation matrix constructed
  // from quaternions. Tait-Bryan angles as well as Euler angles are
  // non-commutative; that is, the get the correct orientation the rotations
  // must be applied in the correct order which for this configuration is yaw,
  // pitch, and then roll.
  // For more see
  // http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
  // which has additional links.
        myIMU.yaw   = atan2(2.0f * (*(getQ()+1) * *(getQ()+2) + *getQ() *
                      *(getQ()+3)), *getQ() * *getQ() + *(getQ()+1) * *(getQ()+1)
                      - *(getQ()+2) * *(getQ()+2) - *(getQ()+3) * *(getQ()+3));
        myIMU.pitch = -asin(2.0f * (*(getQ()+1) * *(getQ()+3) - *getQ() *
                      *(getQ()+2)));
        myIMU.roll  = atan2(2.0f * (*getQ() * *(getQ()+1) + *(getQ()+2) *
                      *(getQ()+3)), *getQ() * *getQ() - *(getQ()+1) * *(getQ()+1)
                      - *(getQ()+2) * *(getQ()+2) + *(getQ()+3) * *(getQ()+3));
        myIMU.pitch *= RAD_TO_DEG;
        myIMU.yaw   *= RAD_TO_DEG;
        // Declination of SparkFun Electronics (40°05'26.6"N 105°11'05.9"W) is
        // 	8° 30' E  ± 0° 21' (or 8.5°) on 2016-07-19
        // - http://www.ngdc.noaa.gov/geomag-web/#declination
        myIMU.yaw   -= 8.5;
        myIMU.roll  *= RAD_TO_DEG;

        if(SerialDebug)
        {
          Serial.print("Yaw, Pitch, Roll: ");
          Serial.print(myIMU.yaw, 2);
          Serial.print(", ");
          Serial.print(myIMU.pitch, 2);
          Serial.print(", ");
          Serial.println(myIMU.roll, 2);

          Serial.print("rate = ");
          Serial.print((float)myIMU.sumCount/myIMU.sum, 2);
          Serial.println(" Hz");
        }
      myIMU.count = millis();
      myIMU.sumCount = 0;
      myIMU.sum = 0;
    } // if (myIMU.delt_t > 500)
  } // if (AHRS)
}*/



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
