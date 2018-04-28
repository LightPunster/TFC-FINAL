#include "Status.h"


void status_check() {

}


/*void status_liftoff(elapsedMillis T_sinceLiftoff) {
    if(((abs(imu_data.IMU_acceleration)) < liftoff_Gforce_check)) {
        T_sinceLiftoff = 0;
        //data.setNorth();
    } else {
        if(T_sinceLiftoff >= lift_check_T)
            status.liftoff = true;
    }
}*/


/*void status_burnout(elapsedMillis T_sinceBurnout) {
    if((abs(imu_data.IMU_acceleration)) >= burnout_Gforce_check){
      T_sinceBurnout = 0;
    } else {
      if(T_sinceBurnout >= burn_check_T)
        status.burnout = true;
    }
}*/


/*void status_apogee(elapsedMillis T_sinceApogee){
    if(abs(imu_data.IMU_velocity) <= apogee_velocity_check){
        T_sinceApogee = 0;
    } else {
        if(T_sinceApogee > apo_check_T){
            status.apogee = true;
            status.falling = true;
        }
    }
}*/


/*void status_falling(elapsedMillis T_sinceFalling) {
    if(bmp.altitude < (bmp.max_altitude-100)){
        T_sinceFalling = 0;
    } else {
        if (T_sinceFalling > fall_check_T){
            status.falling = true;
            status.apogee = true;
        }
    }
}*/


void flight_plan() {
    //hold at North for four seconds
    current_command = 0;
    commands[current_command].setpoint = North;
    commands[current_command].hold_time = 4000000;
    commands[current_command].roll_direction = 0;
    commands[current_command].is_done = 0;

    //hold at North for four seconds
    current_command = 1;
    commands[current_command].setpoint = North;
    commands[current_command].hold_time = 4000000;
    commands[current_command].roll_direction = 0;
    commands[current_command].is_done = 0;


    /*
    //
    current_command =
    commands[current_command].setpoint =
    commands[current_command].hold_time =
    commands[current_command].roll_direction =
    commands[current_command].is_done =
    */
}
