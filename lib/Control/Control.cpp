#include "Control.h"


void control_hold(imu* imu_data) {
    //float derivative_error;
    /*//Calculate derivative_error from gyroscope reading
    if(imu_data->error < 0) {
		derivative_error = -imu_data->omega_Reading;
	} else {
		derivative_error = imu_data->omega_Reading;
	}*/


	//Hold mode, use hold gains
	pwm_Duty = ((Kp_hold) * (imu_data->error)) + ((Kd_hold) * (imu_data->d_error)) + ((Ki_hold));// * (imu_data->integral_error));

	if(abs(pwm_Duty) < pwm_Limit_hold)
        pwm_Duty = 0; //limit pwm to avoid jitter (probably 5%-20%)

	if(pwm_Duty >= 0) { 					//If > 0, write to cw valve
		if(pwm_Duty>1)
            pwm_Duty = 1; 			//cap pwm at 100%
		cw_pwm_Duty = pwm_Duty;
		ccw_pwm_Duty = 0;
    } else { 						//If < 0, write to ccw valve
		if(pwm_Duty<-1)
            pwm_Duty = -1; 			//cap pwm at -100%
		cw_pwm_Duty = 0;
		ccw_pwm_Duty = -pwm_Duty;
	}
}


void control_actuate(imu* imu_data) {
    //float derivative_error;
    /*if(imu_data->error < 0) {												//Calculate derivative error from gyroscope reading
		derivative_error = -imu_data->omega_Reading;
	} else {
		derivative_error = imu_data->omega_Reading;
	}*/


	//Actuate mode, use actuate gains
	pwm_Duty = ((Kp_actuate) * (imu_data->error)) + ((Kd_actuate) * (imu_data->d_error));// + ((Ki_actuate)) * (imu_data->integral_error));

	if(abs(pwm_Duty) < pwm_Limit_actuate)
        pwm_Duty = 0;	//limit pwm to avoid jitter (probably 0)

    if(pwm_Duty >= 0) { 					//If > 0, write to cw valve
		if(pwm_Duty>1)
            pwm_Duty = 1; 			//cap pwm at 100%
        cw_pwm_Duty = pwm_Duty;
        ccw_pwm_Duty = 0;
	} else { 						//If < 0, write to ccw valve
		if(pwm_Duty<-1)
            pwm_Duty = -1; 			//cap pwm at -100%
		cw_pwm_Duty = 0;
	    ccw_pwm_Duty = -pwm_Duty;
	}
}
