//This = from most recent reading
//Last = from the reading before the most recent one




//Global Variables
#define last_error, integral_error
#define error, omega_reading, cw_pwm_Duty, ccw_pwm_Duty, setpoint;
#define Kp_actuate, Kp_hold, Kd_actuate, Kd_hold, Ki_actuate, Ki_hold
#define pwm_Limit_actuate, pwm_Limit_hold

//Other variables (derivative error, pwm_Duty, inst_avg_error)can be local

void setup() {
	//blah blah blah, wait til 2 seconds after burn-out

	last_time = micros()/1000000; last_error = 0; integral_error = 0;
	[error,integral_error,omega_reading] = imu_read(); //global variables set here, do not need to be returns
	Actuate();
	periodStart = micros();
}

void loop() {
	[error,integral_error,omega_reading] = imu_read();

	digitalWrite(cw_valve, !(micros() - periodStart <= 1000000*0.2*cw_pwm_Duty));
	digitalWrite(ccw_valve, !(micros() - periodStart <= 1000000*0.2*ccw_pwm_Duty));

	if (micros - periodStart >= 1000000*0.2) {

		//Logic to determine whether it should actuate or hold
		//Actuate();
		//Hold();
		periodStart = micros();
	}

void imu_read() {
	this_time = micros()/1000000;
	error = setpoint – this_angle_reading;					//Calculate current error
	inst_avg_error = (error + last_error)/2;
	integral_error += inst_avg_error*(this_time - last_time);			//Calculate integral error
	last_error = error;
	last_time = this_time;
}

void Actuate() {

	if(error < 0) {												//Calculate derivative error from gyroscope reading
		derivative_error = -omega_reading;
	} else {
		derivative_error = omega_reading;
	}
	//Actuate mode, use actuate gains
	pwm_Duty = Kp_actuate*this_error + Kd_actuate*this_derivative_error + Ki_actuate*this_integral_error;
	if(abs(pwm_Duty) < pwm_Limit_actuate) pwm_Duty = 0;	//limit pwm to avoid jitter (probably 0)

	if(pwm_Duty >= 0) { 					//If > 0, write to cw valve
		if(pwm_Duty>1) pwm_Duty = 1; 			//cap pwm at 100%
		cw_pwm_Duty = pwm_Duty;
		ccw_pwm_Duty = 0;
	} else { 						//If < 0, write to ccw valve
		if(pwm_Duty<-1) pwm_Duty = -1; 			//cap pwm at -100%
		cw_pwm_Duty = 0;
		ccw_pwm_Duty = -pwm_Duty;
	}
}

void Hold() {

	if(error < 0) {												//Calculate derivative error from gyroscope reading
		derivative_error = -omega_reading;
	} else {
		derivative_error = omega_reading;
	}

	//Hold mode, use hold gains
	pwm_Duty = Kp_hold*this_error + Kd_hold*this_derivative_error + Ki_hold*this_integral_error;
	if(abs(pwm_Duty) < pwm_Limit_hold) pwm_Duty = 0; //limit pwm to avoid jitter (probably 5%-20%)

	if(pwm_Duty >= 0) { 					//If > 0, write to cw valve
		if(pwm_Duty>1) pwm_Duty = 1; 			//cap pwm at 100%
		cw_pwm_Duty = pwm_Duty;

		ccw_pwm_Duty = 0;
	} else { 						//If < 0, write to ccw valve
		if(pwm_Duty<-1) pwm_Duty = -1; 			//cap pwm at -100%
		cw_pwm_Duty = 0;
		ccw_pwm_Duty = -pwm_Duty;
	}
}




/*//This = from most recent reading
//Last = from the reading before the most recent one




//Global Variables
#define last_error, integral_error
#define error, omega_reading, cw_pwm_Duty, ccw_pwm_Duty, setpoint;
#define Kp_actuate, Kp_hold, Kd_actuate, Kd_hold, Ki_actuate, Ki_hold
#define pwm_Limit_actuate, pwm_Limit_hold

//Other variables (derivative error, pwm_Duty, inst_avg_error)can be local

void setup() {
	//blah blah blah, wait til 2 seconds after burn-out

	last_time = micros()/1000000; last_error = 0; integral_error = 0;
	[error,integral_error,omega_reading] = imu_read(); //global variables set here, do not need to be returns
	Actuate();
	periodStart = micros();
}

void loop() {
	[error,integral_error,omega_reading] = imu_read();

	digitalWrite(cw_valve, !(micros() - periodStart <= 1000000*0.2*cw_pwm_Duty));
	digitalWrite(ccw_valve, !(micros() - periodStart <= 1000000*0.2*ccw_pwm_Duty));

	if (micros - periodStart >= 1000000*0.2) {

		//Logic to determine whether it should actuate or hold
		//Actuate();
		//Hold();
		periodStart = micros();
	}

void imu_read() {
	this_time = micros()/1000000;
	error = setpoint – this_angle_reading;					//Calculate current error
	inst_avg_error = (error + last_error)/2;
	integral_error += inst_avg_error*(this_time - last_time);			//Calculate integral error
	last_error = error;
	last_time = this_time;
}

void Actuate() {

	if(error < 0) {												//Calculate derivative error from gyroscope reading
		derivative_error = -omega_reading;
	} else {
		derivative_error = omega_reading;
	}
	//Actuate mode, use actuate gains
	pwm_Duty = Kp_actuate*this_error + Kd_actuate*this_derivative_error + Ki_actuate*this_integral_error;
	if(abs(pwm_Duty) < pwm_Limit_actuate) pwm_Duty = 0;	//limit pwm to avoid jitter (probably 0)

	if(pwm_Duty >= 0) { 					//If > 0, write to cw valve
		if(pwm_Duty>1) pwm_Duty = 1; 			//cap pwm at 100%
		cw_pwm_Duty = pwm_Duty;
		ccw_pwm_Duty = 0;
	} else { 						//If < 0, write to ccw valve
		if(pwm_Duty<-1) pwm_Duty = -1; 			//cap pwm at -100%
		cw_pwm_Duty = 0;
		ccw_pwm_Duty = -pwm_Duty;
	}
}

void Hold() {

	if(error < 0) {												//Calculate derivative error from gyroscope reading
		derivative_error = -omega_reading;
	} else {
		derivative_error = omega_reading;
	}

	//Hold mode, use hold gains
	pwm_Duty = Kp_hold*this_error + Kd_hold*this_derivative_error + Ki_hold*this_integral_error;
	if(abs(pwm_Duty) < pwm_Limit_hold) pwm_Duty = 0; //limit pwm to avoid jitter (probably 5%-20%)

	if(pwm_Duty >= 0) { 					//If > 0, write to cw valve
		if(pwm_Duty>1) pwm_Duty = 1; 			//cap pwm at 100%
		cw_pwm_Duty = pwm_Duty;

		ccw_pwm_Duty = 0;
	} else { 						//If < 0, write to ccw valve
		if(pwm_Duty<-1) pwm_Duty = -1; 			//cap pwm at -100%
		cw_pwm_Duty = 0;
		ccw_pwm_Duty = -pwm_Duty;
	}
}*/
