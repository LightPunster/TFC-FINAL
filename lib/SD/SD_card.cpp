#include "SD_card.h"


void sd_setup() {
    //TODO::add print lines for status: emergency, TFC_L_connected, TFC_R_connected, TFR_connected, emergency, direction_setpoint, last_setpoint, d_error, this_time, last_time

  myFile = SD.open("log.txt", FILE_WRITE);

  if(myFile){
    myFile.print("Global Timestamp, ");
    myFile.print("Altitude, ");
    myFile.print("Maximum Altitude, ");
    myFile.print("Pressure, ");
    myFile.print("Temperature, ");
    myFile.print("Compass Direction, ");
    myFile.print("Accelerometer Roll Reading, ");
    myFile.print("Accelerometer Yaw Reading, ");
    myFile.print("Accelerometer Pitch Reading, ");
    myFile.print("Gyroscope Roll Reading, ");
    myFile.print("Gyroscope Yaw Reading, ");
    myFile.print("Gyroscope Pitch Reading, ");
    myFile.print("Magnetometer Roll Reading, ");
    myFile.print("Magnetometer Yaw Reading, ");
    myFile.print("Magnetometer Pitch Reading, ");
    //myFile.print("Compass Reading");
    myFile.print("Velocity, ");
    myFile.print("Acceleration, ");
    //myFile.print("Magnitude of Acceleration");
    myFile.print("Error, ");
    //myFile.print("Last Error, ");
    //myFile.print("Integral Error, ");
    myFile.print("Omega Reading, ");
    myFile.print("Direction Error, ");
    //myFile.print("Average Error, ");
    myFile.print("Current timestamp, ");
    myFile.print("Liftoff, ");
    myFile.print("Burnout, ");
    myFile.print("Apogee, ");
    myFile.print("E-Dump, ");
    myFile.print("Falling, ");
    myFile.print("IMU Connection, ");
    myFile.print("TFC Connection, ");
    myFile.println("Active Valves, ");

    myFile.close();
  }
}

void sd_write(elapsedMillis current_time, elapsedMillis global_time){
  myFile = SD.open("log.txt", FILE_WRITE);
  if(myFile){
    myFile.print(global_time);
    myFile.print(',');
    myFile.print(bmp.altitude);
    myFile.print(',');
    myFile.print(bmp.max_altitude);
    myFile.print(',');
    myFile.print(bmp.pressure);
    myFile.print(',');
    myFile.print(bmp.temperature);
    myFile.print(',');
    myFile.print(imu_data.mDirection);
    myFile.print(',');
    myFile.print(imu_data.aY);
    myFile.print(',');
    myFile.print(imu_data.aX);
    myFile.print(',');
    myFile.print(imu_data.aZ);
    myFile.print(',');
    myFile.print(imu_data.gY);
    myFile.print(',');
    myFile.print(imu_data.gX);
    myFile.print(',');
    myFile.print(imu_data.gZ);
    myFile.print(',');
    myFile.print(imu_data.mY);
    myFile.print(',');
    myFile.print(imu_data.mX);
    myFile.print(',');
    myFile.print(imu_data.mZ);
    myFile.print(',');
    myFile.print(imu_data.velocity);
    myFile.print(',');
    myFile.print(imu_data.aSqrt);
    myFile.print(',');
    myFile.print(imu_data.error);
    myFile.print(',');
    myFile.print(imu_data.omega_z);
    myFile.print(',');
    myFile.print(imu_data.d_error);
    myFile.print(',');
    myFile.print(current_time);
    myFile.print(',');
    myFile.print(status.liftoff);
    myFile.print(',');
    myFile.print(status.burnout);
    myFile.print(',');
    myFile.print(status.apogee);
    myFile.print(',');
    myFile.print(status.emergency);
    myFile.print(',');
    myFile.print(status.falling);
    myFile.print(',');
    myFile.print(status.IMU_connected);
    myFile.print(',');
    myFile.print(status.TFR_connected);
    myFile.print(',');
    myFile.print(status.active_valves);
    myFile.println(',');
  }
}
/*
void sd_write(elapsedMillis current_time, elapsedMillis global_time) {
    //TODO::verify good sd write functions for all data points listed, included those that need to be added from above
    //DONE//TODO::not printed to the SD, but should be. Also check for printing of all fields from above and that they are going to the correct locations/are in the correct order
    int partTime = current_time;
    myFile = SD.open("log.txt", FILE_WRITE);

    if(myFile){
    myFile.print(global_time);
    myFile.print(',');
    myFile.print(bmp.altitude);
    myFile.print(',');
    myFile.print(bmp.max_altitude);
    myFile.print(',');
    myFile.print(bmp.pressure);
    myFile.print(',');
    myFile.print(bmp.temperature);
    myFile.print(',');
    myFile.print(imu.IMU_direction);
    myFile.print(',');
    myFile.print(imu.IMU_roll);
    myFile.print(',');
    myFile.print(imu.IMU_yaw);
    myFile.print(',');
    myFile.print(imu.IMU_pitch);
    myFile.print(',');
    myFile.print(imu.IMU_velocity);
    myFile.print(',');
    myFile.print(imu.IMU_acceleration);
    myFile.print(',');
    myFile.print(imu.error);
    myFile.print(',');
    myFile.print(imu.last_error);
    myFile.print(',');
    myFile.print(imu.integral_error);
    myFile.print(',');
    myFile.print(imu.omega_Reading);
    myFile.print(',');
    myFile.print(imu.d_error);
    myFile.print(',');
    myFile.print(imu.inst_avg_error);
    myFile.print(',');
    //DONE//TODO::change these, for speed and clarity, should be
    //DONE//myFile.print(status.field);
    //DONE//myFile.print(',');
    myFile.print(current_time);
    myFile.print(',');
    myFile.print(status.liftoff);
    myFile.print(',');
    myFile.print(status.burnout);
    myFile.print(',');
    myFile.print(status.apogee);
    myFile.print(',');
    myFile.print(status.falling);
    myFile.print(',');
    myFile.print(status.emergency);
    myFile.print(',');
    myFile.print(status.IMU_connected);
    myFile.print(',');
    myFile.print(status.TFR_connected);
    myFile.print(',');
    myFile.print(status.active_valves);
    myFile.print(',');
    myFile.println('E');
    myFile.close();
    }
}*/
