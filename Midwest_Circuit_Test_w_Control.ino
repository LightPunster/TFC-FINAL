#include <MPU9250_asukiaaa.h> //Library for gyroscope
#include <avr/interrupt.h>
#include <math.h>
#include <SD.h>
#include <SPI.h>

const int chipSelect = BUILTIN_SDCARD;

byte cw_pin = 4; //Reference only
long int cwOR = 0x00002000, cwAND = 0xFFFFDFFF;
byte ccw_pin = 14; //Reference only
long int ccwOR = 0x00000002, ccwAND = 0xFFFFFFFD;
int dump_pin = 24; //Reference only
long int dumpOR = 0x04000000, dumpAND = 0xFBFFFFFF;
int grn_led = 12;

float accel_magnitude; 
float omega_roll, omega_roll_0, theta_roll;
float omega_roll_BiasCorrection = -0.217;
long int t_sample, t_last;

float error, d_error;
float d_error_sum = 0;
int d_error_cnt = 0;
float setpoint = 0, setpoint_0;
float Kp = 1*(3.14159/180), Kd = 0.9*(3.14159/180);
float pwm_period = 0.2, pwm_limit = 0.05;
float duty = 0;

bool controlEnable = false, stopped = false, launched = false, begun = false;
long int periodStart, launchTime, startTime, fileStart;
float t;
int timeToStart = 5, timeToChange = 5;

String dataString = "";

MPU9250 imu;
IntervalTimer myTimer;

void setup() {
  delay(2000); //Wait for Serial monitor to open
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
  }
  Serial.println("card initialized.");

  pinMode(cw_pin,OUTPUT);
  pinMode(ccw_pin,OUTPUT);
  pinMode(dump_pin,OUTPUT);
  pinMode(grn_led,OUTPUT);
  
  //Initialize valves to OFF
  GPIOA_PDOR &= cwAND;
  GPIOD_PDOR &= ccwAND;
  GPIOE_PDOR &= dumpAND;
  digitalWrite(grn_led,LOW);
  
  Wire.begin();
  imu.setWire(&Wire);
  imu.beginGyro();
  imu.beginAccel();
  
  omega_roll = 0; theta_roll = 0;
  t_last = micros(); periodStart = micros();

  //Headings
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    //dataFile.println("-------------------------------------------------------------------------------------");
    dataFile.println("time\taccel\tset\ttheta\tctrlEN\t%dty");
  }
  dataFile.close();
  
  //Inertial Test
  /*
  digitalWrite(grn_led,HIGH);
  delay(2000);
  digitalWrite(grn_led,LOW);
  delay(2000);
  imu.gyroUpdate(); omega_roll = imu.gyroY() + omega_roll_BiasCorrection;
  Serial.println(omega_roll);
  digitalWrite(cw_pin,HIGH);
  delay(1000);
  digitalWrite(cw_pin,LOW);
  imu.gyroUpdate(); omega_roll = imu.gyroY() + omega_roll_BiasCorrection;
  Serial.println(omega_roll);
  while(1);
  */

  //Valve Test
  /*
  digitalWrite(cw_pin,HIGH);delay(30);digitalWrite(cw_pin,LOW);delay(1000);
  digitalWrite(ccw_pin,HIGH);delay(20);digitalWrite(ccw_pin,LOW);delay(1000);
  digitalWrite(dump_pin,HIGH);delay(200);digitalWrite(dump_pin,LOW);delay(1000);
  while(1);
  */

  //Omega Bias Test
  
  float accum = 0;
  while(1) {
    int sz = 100;
    float sum1 = 0;
    float sum2 = 0;
    for(int i=0; i<sz; i++) {
      imu.gyroUpdate();
      sum1 += imu.gyroY();
      sum2 += (imu.gyroY() + omega_roll_BiasCorrection);
    }
    omega_roll = sum1/sz;
    Serial.print(omega_roll); Serial.print("\t");
    omega_roll = sum2/sz;
    Serial.print(omega_roll); Serial.print("\t");
    accum += omega_roll;
    Serial.println(accum);
  }
  
}

void loop() {
  
  
  if(!launched) t=0;
  else t = (micros()-launchTime)/1000000.0;
  
  Serial.print(" t: ");Serial.print(t);
  
  imu.accelUpdate();
  accel_magnitude = pow(pow(imu.accelX(),2) + pow(imu.accelY(),2) + pow(imu.accelZ(),2),0.5);

  //Serial.print("\taccel: "); Serial.print(accel_magnitude);
  
  //Take note of launch
  if((!launched)&&(accel_magnitude>1.5)) {
    launched = true;
  }
  //Begin delay when launch is over
  if((!begun)&&(launched)&&(accel_magnitude<1.5)) {
    begun = true;
    startTime = micros();
    digitalWrite(grn_led,HIGH);
  }
  //Enable control after some delay
  if(begun&&(!controlEnable)&&(!stopped)&&(micros() - startTime >= 1000000*timeToStart)) {
    myTimer.begin(writeToValves, 1000); //Enable RTI
    controlEnable = true;
    digitalWrite(grn_led,LOW);
  }
  if(begun&&(micros() - startTime >= 1000000*(timeToStart + timeToChange))) setpoint=90; //Change to new setpoint
  
  imu.gyroUpdate(); t_sample = micros();
  omega_roll = imu.gyroY() + omega_roll_BiasCorrection;
  theta_roll += ((t_sample - t_last)/1000000.0)*(omega_roll + omega_roll_0)/2; //Numerically integrate to get angle
  
  if(theta_roll>(setpoint+180)) theta_roll-=360; //Ensures that error never exceed +-180
  if(theta_roll<(setpoint-180)) theta_roll+=360;

  error = setpoint - theta_roll;
  d_error_sum += -omega_roll + 1000000*(setpoint - setpoint_0)/((float)(t_sample-t_last));
  d_error_cnt++; d_error = d_error_sum/((float)d_error_cnt);
  setpoint_0=setpoint; omega_roll_0 = omega_roll; t_last = t_sample; //Reset to last

  Serial.print("\tset: "); Serial.print(setpoint);
  //Serial.print("\tOmega: "); Serial.print(omega_roll);
  Serial.print("\ttheta: "); Serial.print(theta_roll);
  Serial.print("\tE: "); Serial.print(error);
  //Serial.print("\tEd: "); Serial.print(d_error);

  //Set duty cycle at start of each period
  if((micros()-periodStart) >= 1000000*pwm_period) {
    d_error_sum = 0; d_error_cnt = 0;
    duty = Kp*error + Kd*d_error;
    if(duty>1) duty = 1;
    if(duty<-1) duty = -1;
    if(abs(duty)<pwm_limit) duty=0;
    periodStart = micros();
  }
  Serial.print("\tctrlEN: "); Serial.print(controlEnable);
  Serial.print("\t%dty: "); Serial.print(duty);
  Serial.println();

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    if(launched) {
      dataString += String(t);
      dataString += "\t" + String(accel_magnitude);
      dataString += "\t" + String(setpoint);
      dataString += "\t" + String(theta_roll);
      dataString += "\t" + String(controlEnable);
      dataString += "\t" + String(duty);
      dataFile.println(dataString);
      //Serial.println(dataString); //Debugging only
      dataString = "";
    } else {
      if((micros() - fileStart)/1000000.0 > 1) {
        dataFile.println("Waiting for launch...");
        fileStart = micros();
      }
    }
  }
  dataFile.close();
}

//Write to solenoid valves triggered by RTI
//(Generate left justified PWM w/ duty cycle = "duty" and period = "pwm_period")
void writeToValves() {
  if(duty > 0) { //Actuate on cw valve
    if((micros()-periodStart)<=1000000*duty*pwm_period) GPIOA_PDOR |= cwOR;
    else GPIOA_PDOR &= cwAND;
  }
  else if(duty > 0) { //Actuate on ccw valve
    if((micros()-periodStart)<=1000000*-duty*pwm_period) GPIOD_PDOR |= ccwOR;
    else GPIOD_PDOR &= ccwAND;
  }
  else {
    GPIOA_PDOR &= cwAND;
    GPIOD_PDOR &= ccwAND;
  }
}
