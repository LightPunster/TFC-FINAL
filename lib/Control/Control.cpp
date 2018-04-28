#include "Control.h"

/*
void control_hold(IMU_data* imu) {
    float derivative_error;

    //Calculate derivative_error from gyroscope reading
    if(imu->error < 0) {
		derivative_error = -imu->omega_Reading;
	} else {
		derivative_error = imu->omega_Reading;
	}

	//Hold mode, use hold gains
	float pwm_Duty = ((Kp_hold) * (imu->error)) + ((Kd_hold) * (derivative_error)) + ((Ki_hold) * (imu->integral_error));
    Serial.print(pwm_Duty);

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


void control_actuate(IMU_data* imu) {
    float derivative_error;

    if(imu->error < 0) {												//Calculate derivative error from gyroscope reading
		derivative_error = -imu->omega_Reading;
	} else {
		derivative_error = imu->omega_Reading;
	}

	//Actuate mode, use actuate gains
	float pwm_Duty = ((Kp_actuate) * (imu->error)) + ((Kd_actuate) * (derivative_error)) + ((Ki_actuate) * (imu->integral_error));
    Serial.print(pwm_Duty);

	if(abs(pwm_Duty) < pwm_Limit_actuate)
        pwm_Duty = 0;	//limit pwm to avoid jitter (probably 0)

    if(pwm_Duty >= 0) { 					//If > 0, write to cw valve
		if(pwm_Duty>1)
            pwm_Duty = 1; 			//cap pwm at 100%
        cw_pwm_Duty = pwm_Duty;
        Serial.println(cw_pwm_Duty);
		ccw_pwm_Duty = 0;
	} else { 						//If < 0, write to ccw valve
		if(pwm_Duty<-1)
            pwm_Duty = -1; 			//cap pwm at -100%
		cw_pwm_Duty = 0;
	    ccw_pwm_Duty = -pwm_Duty;
        Serial.println(ccw_pwm_Duty);
	}
}
*/
