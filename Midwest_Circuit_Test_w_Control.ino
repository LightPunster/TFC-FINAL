

bool tilted = false;
float omega_z, omega_z_0, theta_z;
float omega_z_BiasCorrection = -3.45;
long int t_sample, t_last;

float error, d_error;
float setpoint = 15;
float Kp = 1*(3.14159/180);
float Kd = 0.25*(3.14159/180);
long int startTime;
float pwm_period = 0.2;
float pwm_limit = 0.05;
float duty;
bool controlEnable = false;
bool END = false;
int timeToStart = 3;

void setup() {
  pinMode(cw_pin,OUTPUT);
  pinMode(ccw_pin,OUTPUT);
  pinMode(dump_pin,OUTPUT);
  pinMode(stop_pin,INPUT);

  digitalWrite(cw_pin,LOW);
  digitalWrite(ccw_pin,LOW);
  digitalWrite(dump_pin,LOW);

  Serial.begin(9600);
   
  t_last = micros(); omega_z = 0; theta_z = 0;
  startTime = micros();
  duty = 0;
}

void loop() {
  //Calculate angular displacement and control error
  imu.update(UPDATE_ACCEL|UPDATE_GYRO); t_sample = micros();
  omega_z = imu.calcGyro(imu.gz) + omega_z_BiasCorrection;
  theta_z += ((t_sample - t_last)/1000000.0)*(omega_z + omega_z_0)/2;
  omega_z_0 = omega_z; t_last = t_sample;

  if(theta_z>(setpoint+180)) theta_z-=360; //Ensures that error never exceed +-180
  if(theta_z<(setpoint-180)) theta_z+=360;

  error = setpoint - theta_z;
  d_error = -omega_z;

  Serial.print("SP: "); Serial.print(setpoint);
  Serial.print("\tOmega: "); Serial.print(omega_z);
  Serial.print("\tAng: "); Serial.print(theta_z);
  //Serial.print("\tE: "); Serial.print(error);
  //Serial.print("\tEd: "); Serial.print(d_error);

  if((!END)&&(micros() - startTime >= 1000000*timeToStart)) controlEnable = true; //Enable control after 2 seconds

  //Set duty cycle at start of each period
  if(controlEnable&&((micros()-startTime) >= 1000000*pwm_period)) {
    duty = Kp*error + Kd*d_error;
    if(duty>1) duty = 1;
    if(duty<-1) duty = -1;
    if(abs(duty)<pwm_limit) duty=0;
    startTime = micros();
  }
  Serial.print("\tEn: "); Serial.print(controlEnable);
  Serial.print("\tD: "); Serial.print(duty);
  //Serial.print("\tT: "); Serial.print((micros()-startTime)/1000000.0);

  //Write to valves
  if(duty > 0) digitalWrite(cw_pin,(micros()-startTime)<=1000000*duty*pwm_period);
  else if(duty < 0) digitalWrite(ccw_pin,(micros()-startTime)<=-1000000*duty*pwm_period);
  else {
    digitalWrite(cw_pin,LOW); digitalWrite(ccw_pin,LOW);
  }

  //Check for dump condition

  //if(!digitalRead(stop_pin)) {
    //duty = 0;
    //digitalWrite(dump_pin,HIGH);
    //controlEnable = false;
    //END = true;
  //}

  Serial.println();
}



/*#include <SparkFunMPU9250-DMP.h> //Library for gyroscope
#include <math.h>

int cw_pin = 4;
int ccw_pin = 14;
int dump_pin = 24;
int stop_pin = 12;

bool tilted = false;
float omega_z, omega_z_0, theta_z;
float omega_z_BiasCorrection = -3.45;
long int t_sample, t_last;

float error, d_error;
float setpoint = 15;
float Kp = 1*(3.14159/180);
float Kd = 0.25*(3.14159/180);
long int startTime;
float pwm_period = 0.2;
float pwm_limit = 0.05;
float duty;
bool controlEnable = false;
bool END = false;
int timeToStart = 3;

MPU9250_DMP imu;

void setup() {
  pinMode(cw_pin,OUTPUT);
  pinMode(ccw_pin,OUTPUT);
  pinMode(dump_pin,OUTPUT);
  pinMode(stop_pin,INPUT);

  digitalWrite(cw_pin,LOW);
  digitalWrite(ccw_pin,LOW);
  digitalWrite(dump_pin,LOW);

  Serial.begin(9600);

  while (imu.begin() != INV_SUCCESS) {
    Serial.println("IMU error");
    delay(100);
  }

  imu.setSensors(INV_XYZ_GYRO);
  imu.setGyroFSR(250);
  imu.setAccelFSR(16);
  imu.setLPF(5);
  imu.setSampleRate(100);
  t_last = micros(); omega_z = 0; theta_z = 0;
  startTime = micros();
  duty = 0;
}

void loop() {
  //Calculate angular displacement and control error
  imu.update(UPDATE_ACCEL|UPDATE_GYRO); t_sample = micros();
  omega_z = imu.calcGyro(imu.gz) + omega_z_BiasCorrection;
  theta_z += ((t_sample - t_last)/1000000.0)*(omega_z + omega_z_0)/2;
  omega_z_0 = omega_z; t_last = t_sample;

  if(theta_z>(setpoint+180)) theta_z-=360; //Ensures that error never exceed +-180
  if(theta_z<(setpoint-180)) theta_z+=360;

  error = setpoint - theta_z;
  d_error = -omega_z;

  Serial.print("SP: "); Serial.print(setpoint);
  Serial.print("\tOmega: "); Serial.print(omega_z);
  Serial.print("\tAng: "); Serial.print(theta_z);
  //Serial.print("\tE: "); Serial.print(error);
  //Serial.print("\tEd: "); Serial.print(d_error);

  if((!END)&&(micros() - startTime >= 1000000*timeToStart)) controlEnable = true; //Enable control after 2 seconds

  //Set duty cycle at start of each period
  if(controlEnable&&((micros()-startTime) >= 1000000*pwm_period)) {
    duty = Kp*error + Kd*d_error;
    if(duty>1) duty = 1;
    if(duty<-1) duty = -1;
    if(abs(duty)<pwm_limit) duty=0;
    startTime = micros();
  }
  Serial.print("\tEn: "); Serial.print(controlEnable);
  Serial.print("\tD: "); Serial.print(duty);
  //Serial.print("\tT: "); Serial.print((micros()-startTime)/1000000.0);

  //Write to valves
  if(duty > 0) digitalWrite(cw_pin,(micros()-startTime)<=1000000*duty*pwm_period);
  else if(duty < 0) digitalWrite(ccw_pin,(micros()-startTime)<=-1000000*duty*pwm_period);
  else {
    digitalWrite(cw_pin,LOW); digitalWrite(ccw_pin,LOW);
  }

  //Check for dump condition

  //if(!digitalRead(stop_pin)) {
    //duty = 0;
    //digitalWrite(dump_pin,HIGH);
    //controlEnable = false;
    //END = true;
  //}

  Serial.println();
}*/
